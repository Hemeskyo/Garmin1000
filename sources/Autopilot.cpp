#include "Autopilot.h"
#include <cstdlib>
#include <algorithm>

void Autopilot::setAP(bool value)
{
    state_ = value;
}

const bool Autopilot::getAPStatus() const
{
    return state_;
}

ControlCommand Autopilot::computeCommand(const FlightData &flightData, const AutopilotTargets &autopilotTargets, double dt_s) const
{

    ControlCommand newControlCommand;
    if (state_ == false)
    {
        return newControlCommand;
    }
    double speedStep = 100.0 * dt_s;
    double maxTurnRate = 3.0;

    double headingDiff = autopilotTargets.heading_deg - flightData.heading_deg;
    while (headingDiff > 180)
        headingDiff -= 360.0;
    while (headingDiff < -180)
        headingDiff += 360.0;

    if (std::abs(headingDiff) <= maxTurnRate)
    {
        newControlCommand.heading_rate_deg_per_sec = headingDiff / dt_s;
    }
    else
    {
        newControlCommand.heading_rate_deg_per_sec += (headingDiff > 0 ? maxTurnRate : -maxTurnRate);
    }

    double altDifference = autopilotTargets.altitude_ft - flightData.altitude_ft;
    double maxClimbRate = 2000.0; // fpm

    if (std::abs(altDifference) > 100.0)
    {
        if (altDifference > 0)
        {
            newControlCommand.vs_fpm = std::min(maxClimbRate, altDifference);
        }
        else
        {
            newControlCommand.vs_fpm = std::max(-maxClimbRate, altDifference);
        }
    }
    else
    {
        newControlCommand.vs_fpm = altDifference * dt_s;
    }
    if (flightData.ias_kt < autopilotTargets.ias_kt)
    {
        (flightData.ias_kt + speedStep) > autopilotTargets.ias_kt
            ? newControlCommand.ias_rate_kt_per_sec = (autopilotTargets.ias_kt - flightData.ias_kt) / dt_s
            : newControlCommand.ias_rate_kt_per_sec = speedStep;
    }
    else if (flightData.ias_kt > autopilotTargets.ias_kt)
    {
        (flightData.ias_kt - speedStep) < autopilotTargets.ias_kt
            ? newControlCommand.ias_rate_kt_per_sec = speedStep
            : newControlCommand.ias_rate_kt_per_sec = -speedStep;
    }

    return newControlCommand;
}

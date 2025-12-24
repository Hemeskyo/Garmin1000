#include "SimulatedSource.h"
#include <cstdlib>

FlightData SimulatedSource::next(double dt_s)
{
    time_s_ += dt_s;

    double speedStep = 2.0 * dt_s;
    double headingStep = 3.0 * dt_s;

    if (ap_engaged_)
    {

        // Basic speed management with preset step

        if (ias_kt_ < ias_target_kt_)
        {
            (ias_kt_ + speedStep) > ias_target_kt_ ? ias_kt_ = ias_target_kt_ : ias_kt_ += speedStep;
        }
        else if (ias_kt_ > ias_target_kt_)
        {
            (ias_kt_ - speedStep) < ias_target_kt_ ? ias_kt_ = ias_target_kt_ : ias_kt_ -= speedStep;
        }

        // Altitude handling with max ceiling safety

        if (altitude_ft_ < 43000)
        {
            altitude_ft_ += (vs_fpm_ / 60) * dt_s;
        }

        // Heading handling
        double headingDiff = hdg_target_deg_ - heading_deg_;
        while (headingDiff > 180)
            headingDiff -= 360.0;
        while (headingDiff < -180)
            headingDiff += 360.0;

        if (std::abs(headingDiff) <= headingStep)
        {
            heading_deg_ = hdg_target_deg_;
        }
        else
        {
            heading_deg_ += (headingDiff > 0 ? headingStep : -headingStep);
        }
        if (heading_deg_ >= 360.0)
        {
            heading_deg_ -= 360.0;
        }
        if (heading_deg_ < 0.0)
        {
            heading_deg_ += 360;
        }
    }

    FlightData d{};

    d.altitude_ft = altitude_ft_;
    d.ias_kt = ias_kt_;
    d.ap_engaged = ap_engaged_;
    d.heading_deg = heading_deg_;
    d.vs_fpm = vs_fpm_;

    return d;
}

void SimulatedSource::setIasTarget(double ias_target_kt)
{
    ias_target_kt_ = ias_target_kt;
}

void SimulatedSource::setAp(bool apState)
{
    ap_engaged_ = apState;
}

void SimulatedSource::setAltTarget(double alt_target_ft)
{
    alt_target_ft_ = alt_target_ft;
}

void SimulatedSource::setHeadingTarget(double hdg_target_deg)
{
    hdg_target_deg_ = hdg_target_deg;
}

void SimulatedSource::setVerticalSpeedTarget(double vs_target_fpm)
{
    vs_target_fpm_ = vs_target_fpm;
};
#include "SimulatedSource.h"
#include <cstdlib>
#include <random>
#include <algorithm>

FlightData SimulatedSource::getFlightdata() const
{
    FlightData d{};

    d.altitude_ft = altitude_ft_;
    d.ias_kt = ias_kt_;
    d.heading_deg = heading_deg_;
    d.vs_fpm = vs_fpm_;
    d.pitch_deg = pitch_deg_;
    d.roll_deg = roll_deg_;

    return d;
}

void SimulatedSource::randomizeApTargets(AutopilotTargets &targets)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<double> altitude_ft(0.0, 43000.0);
    std::uniform_real_distribution<double> heading_deg(0.0,360.0);
    std::uniform_real_distribution<double> ias_kt(0.0, 330.0);

    targets.altitude_ft = altitude_ft(gen);
    targets.heading_deg = heading_deg(gen);
    targets.ias_kt = ias_kt(gen);
};

void SimulatedSource::applyCommand(const ControlCommand &cmd, double dt_s)
{
    heading_deg_ += cmd.heading_rate_deg_per_sec * dt_s;
    while (heading_deg_ >= 360.0)
        heading_deg_ -= 360.0;
    while (heading_deg_ < 0.0)
        heading_deg_ += 360.0;

    ias_kt_ += cmd.ias_rate_kt_per_sec * dt_s;

    vs_fpm_ = cmd.vs_fpm;
    altitude_ft_ += vs_fpm_ * (dt_s / 60.0);

    pitch_deg_ = vs_fpm_ / 200.0;
    pitch_deg_ = std::clamp(pitch_deg_, -15.0, 15.0);

    roll_deg_ = cmd.heading_rate_deg_per_sec * 5.0;
    roll_deg_ = std::clamp(roll_deg_, -30.0, 30.0);

}
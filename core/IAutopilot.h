#pragma once
#include "FlightData.h"

struct ControlCommand
{
    double heading_rate_deg_per_sec = 0.0;
    double vs_fpm = 0.0;
    double ias_rate_kt_per_sec = 0.0;
};

struct AutopilotTargets
{
    double heading_deg = 0.0;
    double altitude_ft = 0.0;
    double ias_kt = 0.0;
};

class IAutopilot
{
public:
    virtual ~IAutopilot() = default;
    virtual ControlCommand computeCommand(
        const FlightData &current,
        const AutopilotTargets &targets,
        double dt_s) const = 0;
    virtual void setAP(bool value) = 0;
    virtual const bool getAPStatus() const = 0;

private:
    bool state_ = false;
};
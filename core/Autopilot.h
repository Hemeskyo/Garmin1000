#pragma once
#include "IAutopilot.h"

class Autopilot : public IAutopilot
{
public:
    virtual ControlCommand computeCommand(
        const FlightData &current,
        const AutopilotTargets &targets,
        double dt_s) const override;
    virtual void setAP(bool value) override;
    virtual const bool getAPStatus() const override;

private:
    bool state_ = false;
};
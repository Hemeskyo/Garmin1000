#pragma once

struct IFlightControls
{
    virtual ~IFlightControls() = default;
    virtual void setIasTarget(double ias_target_kt) = 0;
    virtual void setAltTarget(double alt_target_ft) = 0;
    virtual void setHeadingTarget(double hdg_target_deg) = 0;
    virtual void setVerticalSpeedTarget(double vs_target_fpm) = 0;
    virtual void setAp(bool apState) = 0;
};
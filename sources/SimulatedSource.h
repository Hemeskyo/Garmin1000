#pragma once
#include "IFlightDataSource.h"
#include "IFlightControls.h"

struct SimulatedSource : IFlightDataSource, IFlightControls
{
    FlightData next(double dt_s) override;
    void setIasTarget(double ias_target_kt) override;
    void setAltTarget(double alt_target_ft) override;
    void setHeadingTarget(double hdg_target_deg) override;
    void setVerticalSpeedTarget(double vs_target_fpm) override;
    void setAp(bool apState) override;

private:
    double heading_deg_ = 0.0;
    double time_s_ = 0.0;
    double altitude_ft_ = 0.0;
    double vs_fpm_ = 0.0;
    double ias_kt_ = 0.0;
    double ias_target_kt_ = 0.0;
    bool ap_engaged_ = false;
    double alt_target_ft_ = 0.0;
    double hdg_target_deg_ = 0.0;
    double vs_target_fpm_ = 0.0;
};

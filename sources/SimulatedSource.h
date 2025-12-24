#pragma once
#include "IFlightDataSource.h"
#include "IAutopilot.h"

struct SimulatedSource : IFlightDataSource
{
    FlightData getFlightdata() const override;
    void applyCommand(const ControlCommand& cmd, double dt_s);
    void randomizeApTargets(AutopilotTargets& targets);

private:
    double heading_deg_ = 0.0;
    double time_s_ = 0.0;
    double altitude_ft_ = 0.0;
    double vs_fpm_ = 0.0;
    double ias_kt_ = 0.0;
    bool ap_engaged_ = false;

};

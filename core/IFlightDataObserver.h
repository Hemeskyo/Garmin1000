#pragma once
#include "IAutopilot.h"
#include "FlightData.h"

class IFlightDataObserver {
    public:
    virtual ~IFlightDataObserver() = default;
    virtual void onFlightDataChanged(const FlightData& data) = 0;
    virtual void onAutopilotChanged(const AutopilotTargets& targets, bool engaged) = 0;
};
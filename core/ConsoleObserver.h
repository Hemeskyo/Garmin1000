#pragma once
#include "IFlightDataObserver.h"

class ConsoleObserver : public IFlightDataObserver
{
public:
    ConsoleObserver() = default;
    ~ConsoleObserver() override = default;
    virtual void onFlightDataChanged(const FlightData &data) override;
    virtual void onAutopilotChanged(const AutopilotTargets &targets, bool engaged) override;
};
#pragma once
#include "IFlightDataObserver.h"

class ConsoleFlightDataObserver : public IFlightDataObserver
{
public:
    ConsoleFlightDataObserver() = default;
    ~ConsoleFlightDataObserver() override = default;
    virtual void onFlightDataChanged(const FlightData &data) override;
    virtual void onAutopilotChanged(const AutopilotTargets &targets, bool engaged) override;
};
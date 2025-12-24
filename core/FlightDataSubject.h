#pragma once
#include "FlightData.h"
#include "IFlightDataObserver.h"
#include "IAutopilot.h"
#include <vector>
#include <algorithm>

class FlightDataSubject
{
public:
    void addObserver(IFlightDataObserver *observer)
    {
        observers_.push_back(observer);
    }
    void removeObserver(IFlightDataObserver *observer)
    {
        observers_.erase(
            std::remove(observers_.begin(), observers_.end(), observer),
            observers_.end());
    }
    void notifyFlightData(const FlightData &data)
    {
        for (auto *observer : observers_)
        {
            observer->onFlightDataChanged(data);
        }
    }
    void notifyAutopilot(const AutopilotTargets &targets, bool engaged)
    {
        for (auto *observer : observers_)
        {
            observer->onAutopilotChanged(targets, engaged);
        }
    }

private:
    std::vector<IFlightDataObserver *> observers_;
};
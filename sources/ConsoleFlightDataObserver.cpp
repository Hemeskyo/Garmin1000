#include "ConsoleFlightDataObserver.h"
#include <iostream>

void ConsoleFlightDataObserver::onFlightDataChanged(const FlightData &data)
{
    std::cout
        << "ALT " << data.altitude_ft
        << " | IAS " << data.ias_kt
        << " | HDG " << data.heading_deg
        << "\n";
}

void ConsoleFlightDataObserver::onAutopilotChanged(const AutopilotTargets &targets, bool engaged)
{
    std::cout
        << "Autopilot settings \n"
        << "Engaged " << engaged
        << " | ALT " << targets.altitude_ft
        << " | IAS " << targets.ias_kt
        << " | HDG " << targets.heading_deg
        << "\n";
}

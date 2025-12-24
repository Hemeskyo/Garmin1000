#include <iostream>
#include "SimulatedSource.h"
#include "Autopilot.h"
#include <thread>
#include <chrono>

int main()
{
    SimulatedSource sim;
    IFlightDataSource &src = sim;
    Autopilot autopilot;
    IAutopilot &ap = autopilot;

    AutopilotTargets targets;
    sim.randomizeApTargets(targets);

    while (std::abs(src.getFlightdata().altitude_ft - targets.altitude_ft) > 2 &&
           (std::abs(src.getFlightdata().heading_deg - targets.heading_deg) > 2) &&
           (std::abs(src.getFlightdata().ias_kt - targets.ias_kt) > 2))
    {

        FlightData d = src.getFlightdata();

        ap.setAP(true);

        ControlCommand cmd = ap.computeCommand(d, targets, 1.0);

        sim.applyCommand(cmd, 1.0);

        std::cout
            << "ALT " << d.altitude_ft
            << " | IAS " << d.ias_kt
            << " | HDG " << d.heading_deg
            << " | AP " << (ap.getAPStatus() ? "ON" : "OFF")
            << "\n";

        std::this_thread::sleep_for(std::chrono::seconds(1));
    };

    return 0;
};
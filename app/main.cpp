#include <iostream>
#include "SimulatedSource.h"
#include "Autopilot.h"
#include <thread>
#include <chrono>
#include "ConsoleObserver.h"
#include "FlightDataSubject.h"

int main()
{
    SimulatedSource sim;
    IFlightDataSource &src = sim;
    Autopilot autopilot;
    IAutopilot &ap = autopilot;
    AutopilotTargets targets;

    ConsoleObserver consoleLog;
    FlightDataSubject flightDataSubject;

    flightDataSubject.addObserver(&consoleLog);

    sim.randomizeApTargets(targets);
    ap.setAP(true);

    flightDataSubject.notifyAutopilot(targets, ap.getAPStatus());

    while (std::abs(src.getFlightdata().altitude_ft - targets.altitude_ft) > 2 ||
           (std::abs(src.getFlightdata().heading_deg - targets.heading_deg) > 2) ||
           (std::abs(src.getFlightdata().ias_kt - targets.ias_kt) > 2))
    {

        FlightData d = src.getFlightdata();
        ControlCommand cmd = ap.computeCommand(d, targets, 1.0);
        sim.applyCommand(cmd, 1.0);

        flightDataSubject.notifyFlightData(d);
        // std::this_thread::sleep_for(std::chrono::seconds(1));
    };

    return 0;
};
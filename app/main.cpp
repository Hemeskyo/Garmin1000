#include <iostream>
#include "SimulatedSource.h"
#include "Autopilot.h"
#include <thread>
#include <chrono>
#include "ConsoleFlightDataObserver.h"
#include "QtFlightDataObserver.h"
#include "FlightDataSubject.h"
#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SimulatedSource sim;
    IFlightDataSource &src = sim;
    Autopilot autopilot;
    IAutopilot &ap = autopilot;
    AutopilotTargets targets;

    ConsoleFlightDataObserver consoleObserver;
    QtFlightDataObserver *qtObserver = new QtFlightDataObserver();
    qtObserver->show();

    FlightDataSubject flightDataSubject;

    flightDataSubject.addObserver(&consoleObserver);
    flightDataSubject.addObserver(qtObserver);

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

    return app.exec();
};
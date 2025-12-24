#include <iostream>
#include "SimulatedSource.h"
#include <thread>
#include <chrono>
int main()
{
    SimulatedSource sim;
    IFlightDataSource &src = sim;

    sim.setHeadingTarget(100);
    sim.setAp(true);

    for (int i = 0; i < 12; i++)
    {

        FlightData d = src.next(5.0);

        std::cout
            << "ALT " << d.altitude_ft
            << " | IAS " << d.ias_kt
            << " | HDG " << d.heading_deg
            << " | AP " << (d.ap_engaged ? "ON" : "OFF")
            << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    };

    return 0;
};
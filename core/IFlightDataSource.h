#pragma once
#include "FlightData.h"

struct IFlightDataSource{
    virtual ~IFlightDataSource() = default;
    virtual FlightData getFlightdata() const = 0;
};
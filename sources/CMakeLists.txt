set(CMAKE_AUTOMOC ON)

add_library(sources
SimulatedSource.cpp
Autopilot.cpp
ConsoleFlightDataObserver.cpp
QtFlightDataObserver.cpp
PrimaryFlightDisplay.cpp
../core/QtFlightDataObserver.h
../core/PrimaryFlightDisplay.h
)

target_link_libraries(sources 
PUBLIC core)

target_include_directories(sources 
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
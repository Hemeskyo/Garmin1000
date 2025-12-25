set(CMAKE_AUTOMOC ON)

add_library(sources
SimulatedSource.cpp
Autopilot.cpp
ConsoleFlightDataObserver.cpp
QtFlightDataObserver.cpp
../core/QtFlightDataObserver.h
)

target_link_libraries(sources 
PUBLIC core)

target_include_directories(sources 
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
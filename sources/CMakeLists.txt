add_library(sources
SimulatedSource.cpp
Autopilot.cpp)

target_link_libraries(sources 
PUBLIC core)

target_include_directories(sources 
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_AUTOMOC ON)
cmake_minimum_required(VERSION 3.16)
project(Garmin1000 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_subdirectory(core)
add_subdirectory(app)
add_subdirectory(sources)
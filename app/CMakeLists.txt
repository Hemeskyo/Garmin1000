add_executable(app
main.cpp)

target_link_libraries(app
PRIVATE sources
Qt6::Widgets)
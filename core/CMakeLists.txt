add_library(core INTERFACE)
target_link_libraries(
    core INTERFACE
    Qt6::Widgets
    Qt6::Core
)
target_include_directories(core
INTERFACE
${CMAKE_CURRENT_SOURCE_DIR})
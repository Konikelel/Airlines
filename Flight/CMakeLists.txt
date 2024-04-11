add_library(
    Flight
    Flight.cpp
    Flight.hpp
)

target_include_directories(Flight PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Flight PUBLIC CrewMember Passenger Plane Utils Company)
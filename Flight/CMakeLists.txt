add_library(
    Flight
    Flight.cpp
    Flight.h
    FlightStatus.h
)

target_include_directories(Flight PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Flight PUBLIC CrewMember Passenger Plane Utils)
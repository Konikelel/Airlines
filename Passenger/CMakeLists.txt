add_library(
    Passenger
    Passenger.cpp
    Passenger.hpp
)

target_include_directories(Passenger PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Passenger PUBLIC Flight Plane Utils)
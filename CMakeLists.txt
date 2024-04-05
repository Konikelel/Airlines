cmake_minimum_required(VERSION 3.13)
project(Airlines)

add_subdirectory(CrewMember)
add_subdirectory(Flight)
add_subdirectory(Passenger)
add_subdirectory(Person)
add_subdirectory(Plane)
add_subdirectory(Utils)

add_subdirectory(Tests)


target_link_libraries(Airlines PUBLIC CrewMember Flight Passenger Person Utils Tests)

target_compile_options(${PROJECT_NAME} PRIVATE -Wextra -Wall -pedantic)
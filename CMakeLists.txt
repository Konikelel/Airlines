cmake_minimum_required(VERSION 3.13)
cmake_policy(SET CMP0135 NEW)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Airlines)

enable_testing()

add_subdirectory(CrewMember)
add_subdirectory(Flight)
add_subdirectory(Passenger)
add_subdirectory(Person)
add_subdirectory(Plane)
add_subdirectory(Utils)

add_subdirectory(Tests)

add_executable(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_link_libraries(Airlines PUBLIC CrewMember Flight Passenger Person Plane Utils)

target_compile_options(${PROJECT_NAME} PRIVATE -Wextra -Wall -pedantic)
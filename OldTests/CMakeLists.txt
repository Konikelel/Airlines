add_library(
    Tests
    Global.test.cpp
    Passenger.test.cpp
    Person.test.cpp
    Plane.test.cpp
    Tests.h
)

target_include_directories(Tests PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Tests PUBLIC Passenger Person Plane Utils)

add_executable(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/Global.test.cpp")
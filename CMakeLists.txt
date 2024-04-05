cmake_minimum_required(VERSION 3.13)
cmake_policy(SET CMP0135 NEW)

project(Airlines)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )
  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  
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

cmake_minimum_required(VERSION 3.5)
include(FetchContent)
include(CTest)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
  Tests
  "${CMAKE_CURRENT_SOURCE_DIR}/Person.tests.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Plane.tests.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Passenger.tests.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/CrewMember.tests.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Flight.tests.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Global.tests.cpp"
)
target_link_libraries(Tests PRIVATE gtest_main Person Plane Passenger CrewMember Flight Company)


include(GoogleTest)
gtest_discover_tests(Tests)
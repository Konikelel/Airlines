include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
  Tests
  "${CMAKE_CURRENT_SOURCE_DIR}/UnitTest.cpp"
)

target_link_libraries(Tests PRIVATE gtest_main Airlines)

add_test(
  NAME UnitTests
  COMMAND Tests
)

# include(GoogleTest)
# gtest_discover_tests(Tests)
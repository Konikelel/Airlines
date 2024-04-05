add_executable(
  Tests
  "${CMAKE_CURRENT_SOURCE_DIR}/ExampleTest.cpp"
)

target_link_libraries(Tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(Tests)
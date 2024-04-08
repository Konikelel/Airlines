add_library(
    Person
    Person.cpp
    Person.hpp
    Gender.hpp
)

target_include_directories(Person PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Person PUBLIC Utils)
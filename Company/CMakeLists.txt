add_library(
    Company
    Company.hpp
)

target_include_directories(Company PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Company PUBLIC Plane CrewMember Flight)
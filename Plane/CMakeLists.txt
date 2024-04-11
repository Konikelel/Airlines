add_library(
    Plane
    Plane.cpp
    Plane.hpp
)

target_include_directories(Plane PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Plane PUBLIC Flight Utils Company)
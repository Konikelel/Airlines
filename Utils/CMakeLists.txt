add_library(
    Utils
    CustomErrors.cpp
    CustomErrors.hpp
    StringHandler.cpp
    StringHandler.hpp
    VectorHandler.hpp
    ListHandler.hpp
    Comparisons.cpp
)

target_include_directories(Utils INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Utils PUBLIC Flight Person Plane)
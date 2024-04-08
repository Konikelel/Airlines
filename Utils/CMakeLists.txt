add_library(
    Utils
    CustomErrors.cpp
    CustomErrors.hpp
    StringHandler.cpp
    StringHandler.hpp
    VectorHandler.hpp
)

target_include_directories(Utils INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
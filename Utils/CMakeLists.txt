add_library(
    Utils
    CustomErrors.cpp
    CustomErrors.h
    StringHandler.cpp
    StringHandler.h
    VectorHandler.h
)

target_include_directories(Utils INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
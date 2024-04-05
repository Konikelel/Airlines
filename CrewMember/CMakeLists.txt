add_library(
    CrewMember
    CrewMember.cpp
    CrewMember.h
    CrewRole.h
    CrewStatus.h
)

target_include_directories(CrewMember PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(CrewMember PUBLIC Flight Person)
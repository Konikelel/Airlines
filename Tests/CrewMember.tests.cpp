#include "CrewMember.hpp"

#include <gtest/gtest.h>

#include "CustomErrors.hpp"

TEST(CrewMemberClass, constructor) {
    CrewMember crewMember{PILOT, 1, "Victor", "Alb", 1, MALE};
}
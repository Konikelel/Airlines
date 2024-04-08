#include "Plane.hpp"

#include <gtest/gtest.h>

#include "CustomErrors.hpp"

TEST(PlaneClass, constructor) {
    Plane plane{100, "B737", 100, 3, 2};

    EXPECT_EQ(plane.getId(), 100);
    EXPECT_EQ(plane.getName(), "B737");
    EXPECT_EQ(plane.getCapacityPassengers(), 100);
    EXPECT_EQ(plane.getRequiredStewardess(), 3);
    EXPECT_EQ(plane.getRequiredPilots(), 2);
}

TEST(PlaneClass, destructor) {
    Plane plane{101, "B737", 100, 3, 2};

    EXPECT_NO_THROW(plane.changeId(100));
}

TEST(PlaneClass, setters) {
    Plane plane1{101, "B737", 100, 3, 2};
    Plane plane2{102, "B737", 150, 4, 3};

    EXPECT_THROW(plane2.changeId(101), NonUniqueIDException);

    EXPECT_THROW(plane2.setName(""), InvalidName);

    plane2.setRequiredStewardess(5);
    EXPECT_EQ(plane2.getRequiredStewardess(), 5);
    EXPECT_EQ(plane2.getCapacityStewardess(), 5 * 2);

    plane2.setRequiredPilots(4);
    EXPECT_EQ(plane2.getRequiredPilots(), 4);
    EXPECT_EQ(plane2.getCapacityPilots(), 4 * 2);
}

TEST(PlaneClass, boolFunctions) {
    Plane plane{101, "B737", 100, 3, 2};

    EXPECT_FALSE(plane.inRangePassengers(101));
    EXPECT_TRUE(plane.inRangePassengers(100));
    EXPECT_TRUE(plane.inRangePassengers(99));

    EXPECT_FALSE(plane.inRangeStewardesses(2));
    EXPECT_TRUE(plane.inRangeStewardesses(3));
    EXPECT_TRUE(plane.inRangeStewardesses(4));
    EXPECT_TRUE(plane.inRangeStewardesses(6));
    EXPECT_FALSE(plane.inRangeStewardesses(7));

    EXPECT_FALSE(plane.inRangePilots(1));
    EXPECT_TRUE(plane.inRangePilots(2));
    EXPECT_TRUE(plane.inRangePilots(3));
    EXPECT_TRUE(plane.inRangePilots(4));
    EXPECT_FALSE(plane.inRangePilots(5));
}
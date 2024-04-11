#include "Plane.hpp"

#include <gtest/gtest.h>

#include "Company.hpp"
#include "CustomErrors.hpp"

TEST(PlaneClass, constructor) {
    Company* company = new (Company){"Test1"};

    Plane plane{company, 100, "B737", 100, 3, 2};

    EXPECT_EQ(plane.getId(), 100);
    EXPECT_EQ(plane.getName(), "B737");
    EXPECT_EQ(plane.getCapacityPassengers(), 100);
    EXPECT_EQ(plane.getRequiredStewardesses(), 3);
    EXPECT_EQ(plane.getRequiredPilots(), 2);
}

TEST(PlaneClass, destructor) {
    Company* company = new (Company){"Test1"};

    Plane plane{company, 101, "B737", 100, 3, 2};

    EXPECT_NO_THROW(plane.changeId(100));
}

TEST(PlaneClass, setters) {
    Company* company = new (Company){"Test1"};

    Plane plane1{company, 101, "B737", 100, 3, 2};
    Plane plane2{company, 102, "B737", 150, 4, 3};

    EXPECT_THROW(plane1.setCompany(nullptr), InvalidPointer);

    EXPECT_THROW(plane2.changeId(101), NonUniqueIDException);

    EXPECT_THROW(plane2.setName(""), InvalidName);

    plane2.setRequiredStewardesses(5);
    EXPECT_EQ(plane2.getRequiredStewardesses(), 5);
    EXPECT_EQ(plane2.getCapacityStewardesses(), 5 * 2);

    plane2.setRequiredPilots(4);
    EXPECT_EQ(plane2.getRequiredPilots(), 4);
    EXPECT_EQ(plane2.getCapacityPilots(), 4 * 2);
}

TEST(PlaneClass, boolFunctions) {
    Company* company = new (Company){"Test1"};

    Plane plane{company, 101, "B737", 100, 3, 2};

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
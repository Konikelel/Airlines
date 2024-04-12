#include "Plane.hpp"

#include <gtest/gtest.h>

#include "Company.hpp"
#include "CustomErrors.hpp"

TEST(PlaneClass, constructor) {
    Company* company = new (Company){"Test"};

    Plane plane1{100, "B737", 100, 3, 2};
    Plane plane2{company, 101, "B737", 100, 3, 2};
    // getId
    EXPECT_EQ(plane2.getId(), 101);
    // getName
    EXPECT_EQ(plane2.getName(), "B737");
    // getCompany
    EXPECT_EQ(plane1.getCompany(), nullptr);
    EXPECT_EQ(plane2.getCompany(), company);
    // getCapacityPassengers
    EXPECT_EQ(plane2.getCapacityPassengers(), 100);
    // getRequiredStewardesses
    EXPECT_EQ(plane2.getRequiredStewardesses(), 3);
    // getCapacityStewardesses
    EXPECT_EQ(plane2.getCapacityStewardesses(), 3 * 2);
    // getRequiredPilots
    EXPECT_EQ(plane2.getRequiredPilots(), 2);
    // getCapacityPilots
    EXPECT_EQ(plane2.getCapacityPilots(), 2 * 2);
}

TEST(PlaneClass, destructor) {
    Plane plane{101, "B737", 100, 3, 2};

    EXPECT_NO_THROW(plane.changeId(100));
}

TEST(PlaneClass, setters) {
    Company* company = new (Company){"Test"};

    Plane plane1{101, "B737", 100, 3, 2};
    Plane plane2{102, "B737", 150, 4, 3};
    // setCompany
    plane1.setCompany(company);
    EXPECT_EQ(plane1.getCompany(), company);
    EXPECT_THROW(plane1.setCompany(nullptr), InvalidPointer);
    // ADD FLIGHT
    // EXPECT_THROW(plane1.setCompany(company), CannotPerform);
    // changeId
    plane2.changeId(100);
    EXPECT_EQ(plane2.getId(), 100);
    EXPECT_THROW(plane2.changeId(101), NonUniqueIDException);
    // setName
    plane2.setName("aBc");
    EXPECT_EQ(plane2.getName(), "aBc");
    EXPECT_THROW(plane2.setName(""), InvalidName);
    // setCapacityPassengers, setRequiredStewardesses, setRequiredPilots
    plane2.setCapacityPassengers(200);
    EXPECT_EQ(plane2.getCapacityPassengers(), 200);
    plane2.setRequiredStewardesses(5);
    EXPECT_EQ(plane2.getRequiredStewardesses(), 5);
    EXPECT_EQ(plane2.getCapacityStewardesses(), 5 * 2);
    plane2.setRequiredPilots(4);
    EXPECT_EQ(plane2.getRequiredPilots(), 4);
    EXPECT_EQ(plane2.getCapacityPilots(), 4 * 2);
    // ADD FLIGHT
    // EXPECT_THROW(plane2.setCapacityPassengers(5), CannotPerform);
    // EXPECT_THROW(plane2.setRequiredStewardesses(5), CannotPerform);
    // EXPECT_THROW(plane2.setRequiredPilots(5), CannotPerform);
}

TEST(PlaneClass, boolFunctions) {
    Company* company = new (Company){"Test1"};

    Plane plane{company, 101, "B737", 100, 3, 2};
    // inRangePassengers
    EXPECT_FALSE(plane.inRangePassengers(101));
    EXPECT_TRUE(plane.inRangePassengers(100));
    EXPECT_TRUE(plane.inRangePassengers(99));
    // inRangeStewardesses
    EXPECT_FALSE(plane.inRangeStewardesses(2));
    EXPECT_TRUE(plane.inRangeStewardesses(3));
    EXPECT_TRUE(plane.inRangeStewardesses(4));
    EXPECT_TRUE(plane.inRangeStewardesses(6));
    EXPECT_FALSE(plane.inRangeStewardesses(7));
    // inRangePilots
    EXPECT_FALSE(plane.inRangePilots(1));
    EXPECT_TRUE(plane.inRangePilots(2));
    EXPECT_TRUE(plane.inRangePilots(3));
    EXPECT_TRUE(plane.inRangePilots(4));
    EXPECT_FALSE(plane.inRangePilots(5));
}
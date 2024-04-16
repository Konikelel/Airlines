#include "Plane.hpp"

#include <gtest/gtest.h>

#include "Company.hpp"
#include "CrewMember.hpp"
#include "CustomErrors.hpp"
#include "VectorHandler.hpp"

TEST(plane, constructor) {
    Company* pCompany = new (Company){"Test"};

    Plane plane1{100, "B737", 100, 3, 2};
    Plane plane2{pCompany, 101, "B737", 100, 3, 2};
    // getId
    EXPECT_EQ(plane2.getId(), 101);
    // getName
    EXPECT_EQ(plane2.getName(), "B737");
    // getCompany
    EXPECT_EQ(plane1.getCompany(), nullptr);
    EXPECT_EQ(plane2.getCompany(), pCompany);
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

    delete pCompany;
}

TEST(plane, destructor) {
    Company* pCompany = new (Company){"Test1"};

    Flight& flight1 = pCompany->createFlight("RYR123", 1, 2, "Warsaw", "Berlin");
    Flight& flight2 = pCompany->createFlight("RYR123", 3, 4, "Warsaw", "Berlin");

    {
        Plane plane{pCompany, 101, "B737", 100, 3, 2};
        flight1.setPlane(plane);
        flight2.setPlane(plane);

        EXPECT_EQ(*flight1.getPlane(), plane);
        EXPECT_EQ(*flight2.getPlane(), plane);
        EXPECT_EQ(pCompany->getPlanes().size(), 1);
        EXPECT_EQ(plane.getFlights().size(), 2);

        EXPECT_TRUE(existVector(pCompany->getPlanes(), plane));
        EXPECT_TRUE(existVector(plane.getFlights(), flight1));
        EXPECT_TRUE(existVector(plane.getFlights(), flight2));
    }

    EXPECT_EQ(flight1.getPlane(), nullptr);
    EXPECT_EQ(flight2.getPlane(), nullptr);
    EXPECT_EQ(pCompany->getPlanes().size(), 0);

    delete pCompany;
}

TEST(plane, setters) {
    Company* pCompany = new (Company){"Test"};

    Plane plane1{101, "B737", 100, 3, 2};
    Plane plane2{102, "B737", 150, 4, 3};
    // setCompany
    plane1.setCompany(pCompany);
    EXPECT_EQ(plane1.getCompany(), pCompany);
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
    EXPECT_THROW(plane2.setCapacityPassengers(0), InvalidNumber);
    plane2.setRequiredStewardesses(5);
    EXPECT_EQ(plane2.getRequiredStewardesses(), 5);
    EXPECT_EQ(plane2.getCapacityStewardesses(), 5 * 2);
    EXPECT_THROW(plane2.setRequiredStewardesses(0), InvalidNumber);
    plane2.setRequiredPilots(4);
    EXPECT_EQ(plane2.getRequiredPilots(), 4);
    EXPECT_EQ(plane2.getCapacityPilots(), 4 * 2);
    EXPECT_THROW(plane2.setRequiredPilots(0), InvalidNumber);
    // ADD FLIGHT
    // EXPECT_THROW(plane2.setCapacityPassengers(5), CannotPerform);
    // EXPECT_THROW(plane2.setRequiredStewardesses(5), CannotPerform);
    // EXPECT_THROW(plane2.setRequiredPilots(5), CannotPerform);

    delete pCompany;
}

TEST(plane, boolFunctions) {
    Company* pCompany = new (Company){"Test1"};

    Plane plane{pCompany, 101, "B737", 100, 3, 2};
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

    delete pCompany;
}

TEST(plane, flight) {
    // Company* pCompany = new (Company){"Test1"};

    // Flight* pFlight1 = new (Flight){pCompany, "RYR123", 1, 2, "Warsaw", "Berlin"};
    // Flight* pFlight2 = new (Flight){pCompany, "RYR123", 3, 4, "Warsaw", "Berlin"};

    // Plane* pPlane = new (Plane){pCompany, 101, "B737", 100, 1, 1};
    // // Test only if works
    // //  addFlight
    // pPlane->addFlight(pFlight1);
    // EXPECT_TRUE(existVector(pPlane->getFlights(), pFlight1));
    // EXPECT_EQ(pFlight1->getPlane(), pPlane);
    // EXPECT_EQ(pPlane->getFlights().size(), 1);
    // // removeFlight
    // pPlane->removeFlight(pFlight1);
    // EXPECT_FALSE(existVector(pPlane->getFlights(), pFlight1));
    // EXPECT_EQ(pFlight1->getPlane(), nullptr);
    // EXPECT_EQ(pPlane->getFlights().size(), 0);
    // // removeFlights
    // pPlane->addFlight(pFlight1);
    // pPlane->addFlight(pFlight2);
    // pPlane->removeFlights();
    // EXPECT_EQ(pFlight1->getPlane(), nullptr);
    // EXPECT_EQ(pPlane->getFlights().size(), 0);

    // delete pCompany, pFlight1, pFlight2, pPlane;
}
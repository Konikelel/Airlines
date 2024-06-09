#include "Plane.hpp"

#include <gtest/gtest.h>
#include <memory.h>

#include "Company.hpp"
#include "CustomErrors.hpp"
#include "SetHandler.hpp"
#include "VectorHandler.hpp"

TEST(plane, constructor) {
    Company* pCompany = new (Company){"Test"};

    Plane plane1{"B737", 100, 3, 2};
    Plane plane2{pCompany, "B737", 100, 3, 2};
    // getName
    EXPECT_EQ(plane2.getName(), "B737");
    // getCompany
    EXPECT_EQ(plane1.getCompany(), nullptr);
    EXPECT_EQ(plane2.getCompany(), pCompany);
    // getFlights
    EXPECT_EQ(plane2.getFlights().size(), 0);
    //  getCapacityPassengers
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
        Plane plane{pCompany, "B737", 100, 3, 2};
        flight1.setPlane(plane);
        flight2.setPlane(plane);

        EXPECT_EQ(flight1.getPlane(), &plane);
        EXPECT_EQ(flight2.getPlane(), &plane);
        EXPECT_EQ(pCompany->getPlanes().size(), 1);
        EXPECT_EQ(plane.getFlights().size(), 2);

        EXPECT_TRUE(existSet(pCompany->getPlanes(), plane));
        EXPECT_TRUE(existSet(plane.getFlights(), flight1));
        EXPECT_TRUE(existSet(plane.getFlights(), flight2));
    }

    EXPECT_EQ(flight1.getPlane(), nullptr);
    EXPECT_EQ(flight2.getPlane(), nullptr);
    EXPECT_EQ(pCompany->getPlanes().size(), 0);

    delete pCompany;
}

TEST(plane, setters) {
    Company* pCompany = new (Company){"Test"};
    Flight& flight = pCompany->createFlight("RYR123", 1, 2, "Warsaw", "Berlin");

    Plane plane1{pCompany, "B737", 100, 3, 2};
    Plane plane2{"B737", 150, 4, 3};
    plane1.addFlight(flight);
    // setName
    plane2.setName("aBc");
    EXPECT_EQ(plane2.getName(), "aBc");
    EXPECT_THROW(plane2.setName(""), InvalidName);
    // setCapacityPassengers
    plane2.setCapacityPassengers(200);
    EXPECT_EQ(plane2.getCapacityPassengers(), 200);
    EXPECT_THROW(plane2.setCapacityPassengers(0), InvalidNumber);
    EXPECT_THROW(plane1.setCapacityPassengers(200), CannotPerform);
    // setRequiredStewardesses
    plane2.setRequiredStewardesses(5);
    EXPECT_EQ(plane2.getRequiredStewardesses(), 5);
    EXPECT_EQ(plane2.getCapacityStewardesses(), 5 * 2);
    EXPECT_THROW(plane2.setRequiredStewardesses(0), InvalidNumber);
    EXPECT_THROW(plane1.setRequiredStewardesses(5), CannotPerform);
    // setRequiredPilots
    plane2.setRequiredPilots(4);
    EXPECT_EQ(plane2.getRequiredPilots(), 4);
    EXPECT_EQ(plane2.getCapacityPilots(), 4 * 2);
    EXPECT_THROW(plane2.setRequiredPilots(0), InvalidNumber);
    EXPECT_THROW(plane1.setRequiredPilots(4), CannotPerform);

    delete pCompany;
}

TEST(plane, boolFunctions) {
    Company* pCompany = new (Company){"Test1"};

    Plane plane{pCompany, "B737", 100, 3, 2};
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
    // maximumStewardesses
    EXPECT_FALSE(plane.maximumStewardesses(3 * 2 - 1));
    EXPECT_FALSE(plane.maximumStewardesses(3 * 2));
    EXPECT_TRUE(plane.maximumStewardesses(3 * 2 + 1));
    // inRangePilots
    EXPECT_FALSE(plane.inRangePilots(1));
    EXPECT_TRUE(plane.inRangePilots(2));
    EXPECT_TRUE(plane.inRangePilots(3));
    EXPECT_TRUE(plane.inRangePilots(4));
    EXPECT_FALSE(plane.inRangePilots(5));
    // maximumPilots
    EXPECT_FALSE(plane.maximumPilots(2 * 2 - 1));
    EXPECT_FALSE(plane.maximumPilots(2 * 2));
    EXPECT_TRUE(plane.maximumPilots(2 * 2 + 1));

    delete pCompany;
}

TEST(plane, company) {
    Company* pCompany1 = new (Company){"Test1"};
    Company* pCompany2 = new (Company){"Test2"};
    Flight& flight = pCompany1->createFlight("RYR123", 1, 2, "Warsaw", "Berlin");

    Plane plane{"B737", 100, 3, 2};
    // setCompany
    // SETTING NULLPTR, PREVIOUS NULLPTR
    EXPECT_NO_THROW(plane.setCompany(nullptr));
    EXPECT_EQ(plane.getCompany(), nullptr);
    // SETTING COMPANY, PREVIOUS NULLPTR
    plane.setCompany(pCompany1);
    plane.addFlight(flight);

    EXPECT_EQ(plane.getCompany(), pCompany1);
    EXPECT_EQ(pCompany1->getPlanes().size(), 1);
    EXPECT_EQ(plane.getFlights().size(), 1);
    EXPECT_TRUE(existSet(pCompany1->getPlanes(), plane));
    // SETTING COMPANY, PREVIOUS COMPANY
    plane.setCompany(pCompany2);

    EXPECT_EQ(pCompany1->getPlanes().size(), 0);
    EXPECT_EQ(plane.getFlights().size(), 0);

    EXPECT_EQ(plane.getCompany(), pCompany2);
    EXPECT_EQ(pCompany2->getPlanes().size(), 1);
    EXPECT_TRUE(existSet(pCompany2->getPlanes(), plane));
    // SETTING NULLPTR, PREVIOUS COMPANY
    plane.setCompany(nullptr);

    EXPECT_EQ(pCompany2->getPlanes().size(), 0);
    EXPECT_EQ(plane.getCompany(), nullptr);

    delete pCompany1;
    delete pCompany2;
}

TEST(plane, flight) {
    Company* pCompany = new (Company){"Test1"};
    Flight& flight1 = pCompany->createFlight("RYR123", 1, 2, "Warsaw", "Berlin");
    Flight& flight2 = pCompany->createFlight("RYR123", 3, 4, "Warsaw", "Berlin");

    Plane plane{pCompany, "B737", 100, 3, 2};
    // addFlight
    plane.addFlight(flight1);

    EXPECT_EQ(plane.getFlights().size(), 1);
    EXPECT_TRUE(existSet(plane.getFlights(), flight1));

    EXPECT_EQ(flight1.getPlane(), &plane);
    // removeFlight
    plane.addFlight(flight2);
    EXPECT_TRUE(plane.removeFlight(flight1));

    EXPECT_EQ(plane.getFlights().size(), 1);
    EXPECT_FALSE(existSet(plane.getFlights(), flight1));
    EXPECT_TRUE(existSet(plane.getFlights(), flight2));

    EXPECT_EQ(flight1.getPlane(), nullptr);
    EXPECT_EQ(flight2.getPlane(), &plane);

    // removeFlights
    plane.addFlight(flight1);
    EXPECT_TRUE(plane.removeFlights());

    EXPECT_EQ(plane.getFlights().size(), 0);
    EXPECT_FALSE(existSet(plane.getFlights(), flight1));
    EXPECT_FALSE(existSet(plane.getFlights(), flight2));

    EXPECT_EQ(flight1.getPlane(), nullptr);
    EXPECT_EQ(flight2.getPlane(), nullptr);

    delete pCompany;
}
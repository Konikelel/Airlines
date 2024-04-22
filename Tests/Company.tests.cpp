#include "Company.hpp"

#include <gtest/gtest.h>

#include "CustomErrors.hpp"
#include "Flight.hpp"
#include "Passenger.hpp"
#include "Plane.hpp"
#include "VectorHandler.hpp"

TEST(company, constructor) {
    Company* pCompany = new (Company){"Test1"};

    // setName
    EXPECT_EQ(pCompany->getName(), "Test1");
    EXPECT_EQ(pCompany->getFlights().size(), 0);
    EXPECT_EQ(pCompany->getPlanes().size(), 0);
    EXPECT_EQ(pCompany->getStewardesses().size(), 0);
    EXPECT_EQ(pCompany->getPilots().size(), 0);

    delete pCompany;
}

TEST(company, destructor) {
    Company* pCompany = new (Company){"Test1"};

    Plane plane{pCompany, 1, "B737", 1, 1, 1};
    CrewMember crewMember1{pCompany, PILOT, 1, "Victor", "Alb", 1, MALE};
    CrewMember crewMember2{pCompany, STEWARDESS, 2, "Anna", "Vic", 2, FEMALE};

    Flight& flight1 = pCompany->createFlight("RYR123", plane, 1, 2, "Warsaw", "Berlin");
    flight1.addCrewMember(crewMember1);
    flight1.addCrewMember(crewMember2);

    delete pCompany;

    EXPECT_EQ(plane.getCompany(), nullptr);
    EXPECT_EQ(crewMember1.getCompany(), nullptr);
    EXPECT_EQ(crewMember2.getCompany(), nullptr);

    EXPECT_EQ(plane.getFlights().size(), 0);
    EXPECT_EQ(crewMember1.getFlights().size(), 0);
    EXPECT_EQ(crewMember2.getFlights().size(), 0);
}

TEST(company, setters) {
    Company* pCompany = new (Company){"Test1"};

    EXPECT_EQ(pCompany->getName(), "Test1");

    pCompany->setName("Test2");
    EXPECT_EQ(pCompany->getName(), "Test2");

    EXPECT_THROW(pCompany->setName(""), InvalidName);

    delete pCompany;
}

TEST(company, plane) {}

TEST(company, crewMember) {}

TEST(company, flight) {}
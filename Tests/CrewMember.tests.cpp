#include "CrewMember.hpp"

#include <gtest/gtest.h>

#include "Company.hpp"
#include "CustomErrors.hpp"
#include "SetHandler.hpp"
#include "VectorHandler.hpp"

TEST(crewMember, constructor) {
    Company* pCompany = new (Company){"Test1"};

    CrewMember crewMember1{STEWARDESS, "Victor", "Alb", 1, MALE};
    CrewMember crewMember2{pCompany, PILOT, "Victor", "Alb", 1, MALE};
    // getCompany
    EXPECT_EQ(crewMember1.getCompany(), nullptr);
    EXPECT_EQ(crewMember2.getCompany(), pCompany);
    // getFlights
    EXPECT_EQ(crewMember1.getFlights().size(), 0);
    EXPECT_EQ(crewMember2.getFlights().size(), 0);
    // getRole
    EXPECT_EQ(crewMember1.getRole(), STEWARDESS);
    EXPECT_EQ(crewMember2.getRole(), PILOT);

    delete pCompany;
}

TEST(crewMember, destructor) {
    Company* pCompany = new (Company){"Test1"};

    Flight& flight1 = pCompany->createFlight("RYR123", 1, 2, "Warsaw", "Berlin");
    Flight& flight2 = pCompany->createFlight("RYR123", 3, 4, "Warsaw", "Berlin");

    {
        CrewMember crewMember{pCompany, PILOT, "Victor", "Alb", 1, MALE};
        crewMember.addFlight(flight1);
        crewMember.addFlight(flight2);

        EXPECT_EQ(flight1.getPilots().size(), 1);
        EXPECT_EQ(flight2.getPilots().size(), 1);
        EXPECT_EQ(pCompany->getPilots().size(), 1);
        EXPECT_EQ(crewMember.getFlights().size(), 2);

        EXPECT_TRUE(existSet(flight1.getPilots(), crewMember));
        EXPECT_TRUE(existSet(flight2.getPilots(), crewMember));
        EXPECT_TRUE(existSet(pCompany->getPilots(), crewMember));
        EXPECT_TRUE(existSet(crewMember.getFlights(), flight1));
        EXPECT_TRUE(existSet(crewMember.getFlights(), flight2));
    }

    EXPECT_EQ(flight1.getPilots().size(), 0);
    EXPECT_EQ(flight2.getPilots().size(), 0);
    EXPECT_EQ(pCompany->getPilots().size(), 0);

    delete pCompany;
}

TEST(crewMember, company) {
    Company* pCompany1 = new (Company){"Test1"};
    Company* pCompany2 = new (Company){"Test2"};
    Flight& flight = pCompany1->createFlight("RYR123", 1, 2, "Warsaw", "Berlin");

    CrewMember crewMember{pCompany1, PILOT, "Victor", "Alb", 1, MALE};
    // setCompany
    // SETTING NULLPTR, PREVIOUS NULLPTR
    EXPECT_NO_THROW(crewMember.setCompany(nullptr));
    EXPECT_EQ(crewMember.getCompany(), nullptr);
    // SETTING COMPANY, PREVIOUS NULLPTR
    crewMember.setCompany(pCompany1);
    crewMember.addFlight(flight);

    EXPECT_EQ(crewMember.getCompany(), pCompany1);
    EXPECT_EQ(pCompany1->getPilots().size(), 1);
    EXPECT_EQ(crewMember.getFlights().size(), 1);
    EXPECT_TRUE(existSet(pCompany1->getPilots(), crewMember));
    // SETTING COMPANY, PREVIOUS COMPANY
    crewMember.setCompany(pCompany2);

    EXPECT_EQ(pCompany1->getPilots().size(), 0);
    EXPECT_EQ(crewMember.getFlights().size(), 0);

    EXPECT_EQ(crewMember.getCompany(), pCompany2);
    EXPECT_EQ(pCompany2->getPilots().size(), 1);
    EXPECT_TRUE(existSet(pCompany2->getPilots(), crewMember));
    // SETTING NULLPTR, PREVIOUS COMPANY
    crewMember.setCompany(nullptr);

    EXPECT_EQ(pCompany2->getPilots().size(), 0);
    EXPECT_EQ(crewMember.getCompany(), nullptr);

    delete pCompany1;
    delete pCompany2;
}

TEST(crewMember, flight) {
    Company* pCompany = new (Company){"Test1"};
    Flight& flight1 = pCompany->createFlight("RYR123", 1, 2, "Warsaw", "Berlin");
    Flight& flight2 = pCompany->createFlight("RYR123", 3, 4, "Warsaw", "Berlin");

    CrewMember crewMember{pCompany, PILOT, "Victor", "Alb", 1, MALE};
    // addFlight
    crewMember.addFlight(flight1);

    EXPECT_EQ(crewMember.getFlights().size(), 1);
    EXPECT_EQ(flight1.getPilots().size(), 1);

    EXPECT_TRUE(existSet(crewMember.getFlights(), flight1));
    EXPECT_TRUE(existSet(flight1.getPilots(), crewMember));
    // removeFlight
    crewMember.addFlight(flight2);
    EXPECT_TRUE(crewMember.removeFlight(flight1));

    EXPECT_EQ(crewMember.getFlights().size(), 1);
    EXPECT_EQ(flight1.getPilots().size(), 0);
    EXPECT_EQ(flight2.getPilots().size(), 1);

    EXPECT_FALSE(existSet(flight1.getPilots(), crewMember));
    EXPECT_FALSE(existSet(crewMember.getFlights(), flight1));
    EXPECT_TRUE(existSet(crewMember.getFlights(), flight2));
    // removeFlights
    crewMember.addFlight(flight1);
    EXPECT_TRUE(crewMember.removeFlights());

    EXPECT_EQ(crewMember.getFlights().size(), 0);
    EXPECT_EQ(flight1.getPilots().size(), 0);

    EXPECT_FALSE(existSet(crewMember.getFlights(), flight1));
    EXPECT_FALSE(existSet(flight1.getPilots(), crewMember));

    EXPECT_FALSE(existSet(crewMember.getFlights(), flight2));
    EXPECT_FALSE(existSet(flight2.getPilots(), crewMember));

    delete pCompany;
}
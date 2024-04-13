#include "CrewMember.hpp"

#include <gtest/gtest.h>

#include "Company.hpp"
#include "CustomErrors.hpp"
#include "VectorHandler.hpp"

TEST(CrewMemberClass, constructor) {
    Company* company = new (Company){"Test1"};

    CrewMember crewMember1{PILOT, 3, "Victor", "Alb", 1, MALE};
    CrewMember crewMember2{company, PILOT, 2, "Victor", "Alb", 1, MALE};
    // getCompany
    EXPECT_EQ(crewMember2.getCompany(), company);
    // getFlights
    EXPECT_EQ(crewMember1.getFlights().size(), 0);
    // getRole
    EXPECT_EQ(crewMember1.getRole(), PILOT);

    delete company;
}

TEST(CrewMemberClass, destructor) {
    Company* pCompany = new (Company){"Test1"};
    Flight flight1{pCompany, "RYR123", 1, 2, "Warsaw", "Berlin"};
    Flight flight2{pCompany, "RYR123", 3, 4, "Warsaw", "Berlin"};
    // terminate
    CrewMember crewMember{pCompany, PILOT, 1, "Victor", "Alb", 1, MALE};
    crewMember.addFlight(flight1);
    crewMember.addFlight(flight2);

    crewMember.terminate();
    EXPECT_EQ(crewMember.getFlights().size(), 0);
    EXPECT_EQ(crewMember.getCompany(), nullptr);
    // CHECK IF CREW MEMBER ALSO DELETED FROM COMPANY

    delete pCompany;
}

TEST(CrewMemberClass, setters) {
    Company* pCompany1 = new (Company){"Test1"};
    Company* pCompany2 = new (Company){"Test1"};
    Flight flight1{pCompany1, "RYR123", 1, 2, "Warsaw", "Berlin"};
    Flight flight2{pCompany1, "RYR123", 3, 4, "Warsaw", "Berlin"};

    CrewMember crewMember{PILOT, 1, "Victor", "Alb", 1, MALE};
    // setCompany
    crewMember.setCompany(pCompany1);
    EXPECT_EQ(crewMember.getCompany(), pCompany1);
    EXPECT_THROW(crewMember.setCompany(nullptr), InvalidPointer);
    crewMember.addFlight(flight1);
    crewMember.addFlight(flight2);
    crewMember.setCompany(pCompany1);
    EXPECT_EQ(crewMember.getFlights().size(), 2);
    crewMember.setCompany(pCompany2);
    EXPECT_EQ(crewMember.getFlights().size(), 0);
    EXPECT_EQ(crewMember.getCompany(), pCompany2);

    delete pCompany1, pCompany2;
}

TEST(CrewMemberClass, flightClassWorkCheck) {
    // Company* pCompany = new (Company){"Test1"};
    // Flight flight1{pCompany, "RYR123", 1, 2, "Warsaw", "Berlin"};
    // Flight flight2{pCompany, "RYR123", 3, 4, "Warsaw", "Berlin"};

    // CrewMember crewMember{pCompany, PILOT, 1, "Victor", "Alb", 2, MALE};
    // // Test only if works
    // //  addFlight
    // crewMember.addFlight(flight1);
    // EXPECT_TRUE(existVector(crewMember.getFlights(), flight1));
    // EXPECT_TRUE(existVector(flight1.getPilots(), crewMember));
    // EXPECT_EQ(flight1.getPilots().size(), 1);
    // EXPECT_EQ(crewMember.getFlights().size(), 1);
    // // removeFlight
    // crewMember.removeFlight(flight1);
    // EXPECT_FALSE(existVector(crewMember.getFlights(), flight1));
    // EXPECT_FALSE(existVector(flight1.getPilots(), crewMember));
    // EXPECT_EQ(flight1.getPilots().size(), 0);
    // EXPECT_EQ(crewMember.getFlights().size(), 0);
    // // removeFlights
    // crewMember.addFlight(flight1);
    // crewMember.addFlight(flight2);
    // crewMember.removeFlights();
    // EXPECT_EQ(flight1.getPilots().size(), 0);
    // EXPECT_EQ(crewMember.getFlights().size(), 0);

    // delete pCompany;
}
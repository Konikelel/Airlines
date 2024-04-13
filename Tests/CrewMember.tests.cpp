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
    Company* pCompany1 = new (Company){"Test1"};
    Flight* pFlight1 = new (Flight){pCompany1, "RYR123", 1, 2, "Warsaw", "Berlin"};
    Flight* pFlight2 = new (Flight){pCompany1, "RYR123", 3, 4, "Warsaw", "Berlin"};
    // terminate
    CrewMember crewMember{pCompany1, PILOT, 1, "Victor", "Alb", 1, MALE};
    crewMember.addFlight(pFlight1);
    crewMember.addFlight(pFlight2);

    crewMember.terminate();
    EXPECT_EQ(crewMember.getFlights().size(), 0);
    EXPECT_EQ(crewMember.getCompany(), nullptr);
    // CHECK IF CREW MEMBER ALSO DELETED FROM COMPANY
}

TEST(CrewMemberClass, setters) {
    Company* pCompany1 = new (Company){"Test1"};
    Company* pCompany2 = new (Company){"Test1"};
    Flight* pFlight1 = new (Flight){pCompany1, "RYR123", 1, 2, "Warsaw", "Berlin"};
    Flight* pFlight2 = new (Flight){pCompany1, "RYR123", 3, 4, "Warsaw", "Berlin"};

    CrewMember crewMember{PILOT, 1, "Victor", "Alb", 1, MALE};
    // setCompany
    crewMember.setCompany(pCompany1);
    EXPECT_EQ(crewMember.getCompany(), pCompany1);
    EXPECT_THROW(crewMember.setCompany(nullptr), InvalidPointer);
    crewMember.addFlight(pFlight1);
    crewMember.addFlight(pFlight2);
    crewMember.setCompany(pCompany1);
    EXPECT_EQ(crewMember.getFlights().size(), 2);
    crewMember.setCompany(pCompany2);
    EXPECT_EQ(crewMember.getFlights().size(), 0);
    EXPECT_EQ(crewMember.getCompany(), pCompany2);

    delete pCompany1, pCompany2, pFlight1, pFlight2;
}

TEST(CrewMemberClass, flightClassWorkCheck) {
    Company* pCompany = new (Company){"Test1"};
    Flight* pFlight1 = new (Flight){pCompany, "RYR123", 1, 2, "Warsaw", "Berlin"};
    Flight* pFlight2 = new (Flight){pCompany, "RYR123", 3, 4, "Warsaw", "Berlin"};

    CrewMember* pCrewMember = new (CrewMember){pCompany, PILOT, 1, "Victor", "Alb", 2, MALE};
    // Test only if works
    //  addFlight
    pCrewMember->addFlight(pFlight1);
    EXPECT_TRUE(existVector(pCrewMember->getFlights(), pFlight1));
    EXPECT_TRUE(existVector(pFlight1->getPilots(), pCrewMember));
    EXPECT_EQ(pFlight1->getPilots().size(), 1);
    EXPECT_EQ(pCrewMember->getFlights().size(), 1);
    // removeFlight
    pCrewMember->removeFlight(pFlight1);
    EXPECT_FALSE(existVector(pCrewMember->getFlights(), pFlight1));
    EXPECT_FALSE(existVector(pFlight1->getPilots(), pCrewMember));
    EXPECT_EQ(pFlight1->getPilots().size(), 0);
    EXPECT_EQ(pCrewMember->getFlights().size(), 0);
    // removeFlights
    pCrewMember->addFlight(pFlight1);
    pCrewMember->addFlight(pFlight2);
    pCrewMember->removeFlights();
    EXPECT_EQ(pFlight1->getPilots().size(), 0);
    EXPECT_EQ(pCrewMember->getFlights().size(), 0);

    delete pCompany, pFlight1, pFlight2, pCrewMember;
}
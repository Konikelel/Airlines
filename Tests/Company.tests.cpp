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

TEST(company, plane) {
    Company* pCompany1 = new (Company){"Test1"};
    Company* pCompany2 = new (Company){"Test2"};

    Flight& flight1 = pCompany1->createFlight("RYR123", 1, 2, "Warsaw", "Berlin");

    Plane plane1{101, "B737", 100, 3, 2};
    Plane plane2{102, "B737", 100, 3, 2};
    // addPlane
    //  SET COMPANY, PREVIOUS NULLPTR
    EXPECT_EQ(plane1.getCompany(), nullptr);
    EXPECT_EQ(plane1.getFlights().size(), 0);
    EXPECT_EQ(pCompany1->getPlanes().size(), 0);
    EXPECT_EQ(pCompany2->getPlanes().size(), 0);

    pCompany1->addPlane(plane1);

    EXPECT_EQ(plane1.getCompany(), pCompany1);
    EXPECT_EQ(plane1.getFlights().size(), 0);
    EXPECT_TRUE(existVector(pCompany1->getPlanes(), plane1));
    // SET COMPANY, PREVIOUS COMPANY SAME
    plane1.addFlight(flight1);
    EXPECT_EQ(plane1.getCompany(), pCompany1);
    EXPECT_EQ(plane1.getFlights().size(), 1);

    pCompany1->addPlane(plane1);

    EXPECT_EQ(plane1.getCompany(), pCompany1);
    EXPECT_EQ(plane1.getFlights().size(), 1);
    EXPECT_EQ(pCompany1->getPlanes().size(), 1);
    EXPECT_TRUE(existVector(pCompany1->getPlanes(), plane1));
    // SET COMPANY, PREVIOUS COMPANY DIFFERENT
    pCompany2->addPlane(plane1);

    EXPECT_EQ(plane1.getCompany(), pCompany2);
    EXPECT_EQ(plane1.getFlights().size(), 0);
    EXPECT_FALSE(existVector(pCompany1->getPlanes(), plane1));
    EXPECT_TRUE(existVector(pCompany2->getPlanes(), plane1));
    // removePlane
    EXPECT_FALSE(pCompany1->removePlane(plane1));

    pCompany1->addPlane(plane1);
    plane1.addFlight(flight1);

    EXPECT_EQ(plane1.getCompany(), pCompany1);
    EXPECT_EQ(plane1.getFlights().size(), 1);

    EXPECT_TRUE(pCompany1->removePlane(plane1));

    EXPECT_EQ(plane1.getCompany(), nullptr);
    EXPECT_EQ(plane1.getFlights().size(), 0);
    EXPECT_FALSE(existVector(pCompany1->getPlanes(), plane1));
    // removePlanes
    pCompany1->addPlane(plane1);
    pCompany1->addPlane(plane2);

    pCompany1->removePlanes();

    EXPECT_EQ(plane1.getCompany(), nullptr);
    EXPECT_EQ(plane2.getCompany(), nullptr);
    EXPECT_EQ(pCompany1->getPlanes().size(), 0);

    delete pCompany1, pCompany2;
}

TEST(company, crewMember) {
    Company* pCompany1 = new (Company){"Test1"};
    Company* pCompany2 = new (Company){"Test2"};

    CrewMember crewMember1{STEWARDESS, 3, "Victor", "Alb", 1, MALE};
    CrewMember crewMember2{PILOT, 2, "Victor", "Alb", 1, MALE};

    Flight& flight = pCompany1->createFlight("RYR123", 1, 2, "Warsaw", "Berlin");

    // addCrewMember
    //  SET COMPANY, PREVIOUS NULLPTR
    EXPECT_EQ(crewMember1.getCompany(), nullptr);
    EXPECT_EQ(crewMember1.getFlights().size(), 0);
    EXPECT_EQ(crewMember2.getCompany(), nullptr);
    EXPECT_EQ(crewMember2.getFlights().size(), 0);
    EXPECT_EQ(pCompany1->getStewardesses().size(), 0);
    EXPECT_EQ(pCompany1->getPilots().size(), 0);
    EXPECT_EQ(pCompany2->getStewardesses().size(), 0);
    EXPECT_EQ(pCompany2->getPilots().size(), 0);

    pCompany1->addCrewMember(crewMember1);

    EXPECT_EQ(crewMember1.getCompany(), pCompany1);
    EXPECT_EQ(pCompany1->getStewardesses().size(), 1);
    EXPECT_EQ(pCompany1->getPilots().size(), 0);
    EXPECT_TRUE(existVector(pCompany1->getStewardesses(), crewMember1));
    // SET COMPANY, PREVIOUS COMPANY SAME
    crewMember1.addFlight(flight);
    EXPECT_EQ(crewMember1.getCompany(), pCompany1);
    EXPECT_EQ(crewMember1.getFlights().size(), 1);

    pCompany1->addCrewMember(crewMember1);

    EXPECT_EQ(crewMember1.getCompany(), pCompany1);
    EXPECT_EQ(crewMember1.getFlights().size(), 1);
    EXPECT_EQ(pCompany1->getStewardesses().size(), 1);
    EXPECT_TRUE(existVector(pCompany1->getStewardesses(), crewMember1));
    // SET COMPANY, PREVIOUS COMPANY DIFFERENT
    pCompany2->addCrewMember(crewMember1);

    EXPECT_EQ(crewMember1.getCompany(), pCompany2);
    EXPECT_EQ(crewMember1.getFlights().size(), 0);
    EXPECT_FALSE(existVector(pCompany1->getStewardesses(), crewMember1));
    EXPECT_TRUE(existVector(pCompany2->getStewardesses(), crewMember1));
    // removeCrewMember
    EXPECT_FALSE(pCompany1->removeCrewMember(crewMember1));

    pCompany1->addCrewMember(crewMember1);
    crewMember1.addFlight(flight);

    EXPECT_EQ(crewMember1.getCompany(), pCompany1);
    EXPECT_EQ(crewMember1.getFlights().size(), 1);

    EXPECT_TRUE(pCompany1->removeCrewMember(crewMember1));

    EXPECT_EQ(crewMember1.getCompany(), nullptr);
    EXPECT_EQ(crewMember1.getFlights().size(), 0);
    EXPECT_FALSE(existVector(pCompany1->getStewardesses(), crewMember1));
    // removeCrewMembers
    pCompany1->addCrewMember(crewMember1);
    pCompany1->addCrewMember(crewMember2);

    EXPECT_EQ(pCompany1->getStewardesses().size(), 1);
    EXPECT_EQ(pCompany1->getPilots().size(), 1);

    pCompany1->removeCrewMembers();

    EXPECT_EQ(crewMember1.getCompany(), nullptr);
    EXPECT_EQ(crewMember2.getCompany(), nullptr);
    EXPECT_EQ(pCompany1->getStewardesses().size(), 0);
    EXPECT_EQ(pCompany1->getPilots().size(), 0);

    delete pCompany1, pCompany2;
}

TEST(company, flight) {
    Company* pCompany = new (Company){"Test1"};

    Plane plane{pCompany, 1, "B737", 1, 1, 1};

    CrewMember pilot{pCompany, PILOT, 1, "Vic", "Ay", 1, MALE};

    CrewMember stewardess{pCompany, STEWARDESS, 4, "Ki", "Be", 1, FEMALE};

    Passenger passenger{7, "Ew", "Ao", 1, MALE};
    // createFlights
    Flight& flight1 = pCompany->createFlight("RYR120", plane, 2, 5, "Warsaw", "Berlin");
    Flight& flight2 = pCompany->createFlight("RYR120", 2, 5, "Warsaw", "Berlin");

    EXPECT_EQ(pCompany->getFlights().size(), 2);

    flight1.addCrewMember(stewardess);
    flight1.addCrewMember(pilot);
    flight1.addPassenger(passenger);

    EXPECT_EQ(pCompany->getFlights().size(), 2);
    EXPECT_EQ(flight1.getStewardesses().size(), 1);
    EXPECT_EQ(flight1.getPilots().size(), 1);
    EXPECT_EQ(flight1.getPassengers().size(), 1);
    EXPECT_EQ(flight1.getPlane(), &plane);

    EXPECT_EQ(stewardess.getFlights().size(), 1);
    EXPECT_EQ(pilot.getFlights().size(), 1);
    EXPECT_EQ(passenger.getFlights().size(), 1);
    EXPECT_EQ(plane.getFlights().size(), 1);
    // removeFlight
    pCompany->removeFlight(flight1);

    EXPECT_EQ(stewardess.getFlights().size(), 0);
    EXPECT_EQ(pilot.getFlights().size(), 0);
    EXPECT_EQ(passenger.getFlights().size(), 0);
    EXPECT_EQ(plane.getFlights().size(), 0);
    EXPECT_EQ(pCompany->getFlights().size(), 1);

    flight1 = pCompany->createFlight("RYR120", 2, 5, "Warsaw", "Berlin");

    EXPECT_EQ(pCompany->getFlights().size(), 2);

    flight1.addCrewMember(stewardess);
    flight2.addCrewMember(pilot);
    // removeFlights
    pCompany->removeFlights();

    EXPECT_EQ(pCompany->getFlights().size(), 0);
    EXPECT_EQ(stewardess.getFlights().size(), 0);
    EXPECT_EQ(pilot.getFlights().size(), 0);

    delete pCompany;
}
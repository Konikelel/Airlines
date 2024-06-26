#include "Flight.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "Company.hpp"
#include "CustomErrors.hpp"
#include "ListHandler.hpp"
#include "Passenger.hpp"
#include "Plane.hpp"
#include "SetHandler.hpp"
#include "VectorHandler.hpp"

TEST(flight, constructor) {
    Company* pCompany = new (Company){"Test1"};

    Flight& flight1 = pCompany->createFlight("RYR120", 1, 2, "Warsaw", "Berlin");

    Plane plane{pCompany, "B737", 100, 4, 2};
    Flight& flight2 = pCompany->createFlight("RYR102", plane, 1, 2, "Poznan", "Krakow");
    // getCompany
    EXPECT_EQ(flight1.getCompany(), pCompany);
    // getFlightNr
    EXPECT_EQ(flight1.getFlightNr(), "RYR120");
    // getStatus
    EXPECT_EQ(flight1.getStatus(), INCOMPLETE);
    // getPlane
    EXPECT_EQ(flight1.getPlane(), nullptr);
    EXPECT_EQ(flight2.getPlane(), &plane);
    // getTimeDeparture
    EXPECT_EQ(flight1.getTimeDeparture(), 1);
    // getTimeArrival
    EXPECT_EQ(flight1.getTimeArrival(), 2);
    // getCityDepartures
    EXPECT_EQ(flight1.getCityDeparture(), "Warsaw");
    // getCityArrival
    EXPECT_EQ(flight1.getCityArrival(), "Berlin");

    // getPassengers
    EXPECT_EQ(flight1.getPassengers().size(), 0);
    // getStewardesses
    EXPECT_EQ(flight1.getStewardesses().size(), 0);
    // getPilots
    EXPECT_EQ(flight1.getPilots().size(), 0);

    delete pCompany;
}

TEST(flight, settersTime) {
    Company* pCompany = new (Company){"Test1"};

    Flight& flight = pCompany->createFlight("RYR120", 1, 2, "Warsaw", "Berlin");
    // setFlightNr
    EXPECT_THROW(flight.setFlightNr("ryr"), InvalidFlightNr);
    flight.setFlightNr("ryr1");
    EXPECT_EQ(flight.getFlightNr(), "RYR1");
    flight.setFlightNr("rYr1201");
    EXPECT_EQ(flight.getFlightNr(), "RYR1201");
    EXPECT_THROW(flight.setFlightNr("rYr12012"), InvalidFlightNr);
    EXPECT_THROW(flight.setFlightNr("RY120"), InvalidFlightNr);
    EXPECT_THROW(flight.setFlightNr("R120"), InvalidFlightNr);
    // changeDataDeparture
    flight.changeDataDeparture(1);
    flight.changeDataDeparture(0, "aBc");
    EXPECT_EQ(flight.getTimeDeparture(), 0);
    EXPECT_EQ(flight.getCityDeparture(), "aBc");

    EXPECT_THROW(flight.changeDataDeparture(2), InvalidTime);
    EXPECT_THROW(flight.changeDataDeparture(3), InvalidTime);
    EXPECT_THROW(flight.changeDataDeparture(0, ""), InvalidName);
    // changeDataArrival
    flight.changeDataDeparture(1);
    flight.changeDataArrival(2);
    flight.changeDataArrival(3, "aBc");
    EXPECT_EQ(flight.getTimeArrival(), 3);
    EXPECT_EQ(flight.getCityArrival(), "aBc");

    EXPECT_THROW(flight.changeDataArrival(1), InvalidTime);
    EXPECT_THROW(flight.changeDataArrival(0), InvalidTime);
    EXPECT_THROW(flight.changeDataArrival(3, ""), InvalidName);
    // setDataTime
    Passenger passenger{"Victor", "Alb", 1, MALE};
    flight.addPassenger(passenger);

    EXPECT_THROW(flight.changeDataDeparture(1), CannotPerform);
    EXPECT_THROW(flight.changeDataDeparture(1, "Warsaw"), CannotPerform);

    delete pCompany;
}

TEST(flight, overlap) {
    Company* pCompany = new (Company){"Test1"};

    Flight& flight = pCompany->createFlight("RYR120", 2, 5, "Warsaw", "Berlin");
    // timeOverlap
    EXPECT_TRUE(flight.timeOverlap(2, 5));
    EXPECT_TRUE(flight.timeOverlap(1, 5));
    EXPECT_TRUE(flight.timeOverlap(2, 6));
    EXPECT_TRUE(flight.timeOverlap(2, 4));
    EXPECT_FALSE(flight.timeOverlap(0, 1));
    EXPECT_FALSE(flight.timeOverlap(6, 7));

    Flight& flight1 = pCompany->createFlight("RYR120", 0, 1, "Warsaw", "Berlin");
    Flight& flight2 = pCompany->createFlight("RYR120", 0, 2, "Warsaw", "Berlin");
    Flight& flight3 = pCompany->createFlight("RYR120", 3, 4, "Warsaw", "Berlin");
    Flight& flight4 = pCompany->createFlight("RYR120", 6, 7, "Warsaw", "Berlin");
    Flight& flight5 = pCompany->createFlight("RYR120", 5, 6, "Warsaw", "Berlin");

    EXPECT_FALSE(flight.timeOverlap(flight1));
    EXPECT_TRUE(flight.timeOverlap(flight2));

    EXPECT_TRUE(flight.timeOverlap(flight3));

    EXPECT_FALSE(flight.timeOverlap(flight4));
    EXPECT_TRUE(flight.timeOverlap(flight5));

    delete pCompany;
}

TEST(flight, company) {
    Company* pCompany = new (Company){"Test1"};

    Flight& flight = pCompany->createFlight("RYR120", 2, 5, "Warsaw", "Berlin");

    EXPECT_EQ(pCompany->getFlights().size(), 1);
    EXPECT_TRUE(existList(pCompany->getFlights(), flight));
    EXPECT_EQ(flight.getCompany(), pCompany);

    pCompany->removeFlight(flight);

    EXPECT_EQ(pCompany->getFlights().size(), 0);
    EXPECT_FALSE(existList(pCompany->getFlights(), flight));

    delete pCompany;
}

TEST(flight, plane) {
    Company* pCompany1 = new (Company){"Test1"};
    Company* pCompany2 = new (Company){"Test1"};

    Plane plane1{pCompany1, "B737", 1, 1, 1};
    Plane plane2{pCompany1, "B738", 1, 1, 1};
    Plane plane3{pCompany2, "B738", 1, 1, 1};

    CrewMember pilot1{pCompany1, PILOT, "Vic", "Ay", 1, MALE};
    CrewMember pilot2{pCompany1, PILOT, "Val", "Ro", 1, MALE};
    CrewMember pilot3{pCompany1, PILOT, "Val", "Ro", 1, MALE};

    CrewMember stewardess1{pCompany1, STEWARDESS, "Ki", "Be", 1, FEMALE};
    CrewMember stewardess2{pCompany1, STEWARDESS, "Jo", "Qa", 1, FEMALE};
    CrewMember stewardess3{pCompany1, STEWARDESS, "Jo", "Qa", 1, FEMALE};

    Passenger passenger1{"Ew", "Ao", 1, MALE};
    Passenger passenger2{"Ow", "Co", 2, FEMALE};

    Flight& flight1 = pCompany1->createFlight("RYR120", 2, 5, "Warsaw", "Berlin");
    Flight& flight2 = pCompany1->createFlight("RYR120", 2, 5, "Warsaw", "Berlin");
    // setPlane
    plane1.addFlight(flight1);

    EXPECT_EQ(flight1.getPlane(), &plane1);
    EXPECT_EQ(plane1.getFlights().size(), 1);
    EXPECT_TRUE(existSet(plane1.getFlights(), flight1));
    EXPECT_THROW(plane1.addFlight(flight2), TimeOverlap);
    // removePlane
    flight1.removePlane();

    EXPECT_EQ(flight1.getPlane(), nullptr);
    EXPECT_EQ(plane1.getFlights().size(), 0);
    EXPECT_FALSE(existSet(plane1.getFlights(), flight1));
    // setPlane
    flight1.addPassenger(passenger1);
    flight1.addCrewMember(stewardess1);
    flight1.addCrewMember(pilot1);
    flight1.addCrewMember(stewardess3);
    flight1.addCrewMember(pilot3);

    flight1.setPlane(plane1);

    EXPECT_EQ(flight1.getPlane(), &plane1);
    EXPECT_EQ(plane1.getFlights().size(), 1);
    EXPECT_TRUE(existSet(plane1.getFlights(), flight1));
    // removePlane
    flight1.setPlane(plane2);

    EXPECT_EQ(flight1.getPlane(), &plane2);
    EXPECT_EQ(plane2.getFlights().size(), 1);
    EXPECT_EQ(plane1.getFlights().size(), 0);
    EXPECT_TRUE(existSet(plane2.getFlights(), flight1));

    flight1.removePlane();
    // CHECK FOR CAPACITY LIMITS
    flight1.addCrewMember(pilot2);

    EXPECT_THROW(flight1.setPlane(plane1), InvalidPlane);
    flight1.removePlane();

    flight1.addCrewMember(stewardess2);

    EXPECT_THROW(flight1.setPlane(plane1), InvalidPlane);
    flight1.removePlane();

    flight1.addPassenger(passenger2);

    EXPECT_THROW(flight1.setPlane(plane1), InvalidPlane);
    flight1.removePlane();

    EXPECT_THROW(flight1.setPlane(plane3), InvalidPlane);

    delete pCompany1;
    delete pCompany2;

    flight1;
}

TEST(flight, passenger) {
    Company* pCompany = new (Company){"Test1"};

    Plane plane{pCompany, "B737", 1, 1, 1};

    Passenger passenger1{"Ew", "Ao", 1, MALE};
    Passenger passenger2{"Ow", "Co", 2, FEMALE};

    Flight& flight1 = pCompany->createFlight("RYR120", plane, 2, 5, "Warsaw", "Berlin");
    Flight& flight2 = pCompany->createFlight("RYR120", 2, 5, "Warsaw", "Berlin");
    // addPassenger
    flight1.addPassenger(passenger1);

    EXPECT_EQ(flight1.getPassengers().size(), 1);
    EXPECT_TRUE(existSet(flight1.getPassengers(), passenger1));

    EXPECT_EQ(passenger1.getFlights().size(), 1);
    EXPECT_TRUE(existSet(passenger1.getFlights(), flight1));

    // TIME OVERLAP
    EXPECT_THROW(flight2.addPassenger(passenger1), TimeOverlap);
    // DUPLICATION
    flight2.addPassenger(passenger2);
    EXPECT_THROW(flight2.addPassenger(passenger2), DuplicationError);
    // CAPACITY
    EXPECT_THROW(flight1.addPassenger(passenger2), MaximumCapacity);

    // removePassenger
    EXPECT_TRUE(flight1.removePassenger(passenger1));

    EXPECT_EQ(flight1.getPassengers().size(), 0);
    EXPECT_EQ(passenger1.getFlights().size(), 0);

    // removePassengers
    flight2.addPassenger(passenger1);

    EXPECT_EQ(flight2.getPassengers().size(), 2);
    EXPECT_EQ(passenger1.getFlights().size(), 1);
    EXPECT_EQ(passenger2.getFlights().size(), 1);

    EXPECT_TRUE(existSet(flight2.getPassengers(), passenger1));
    EXPECT_TRUE(existSet(flight2.getPassengers(), passenger2));
    EXPECT_TRUE(existSet(passenger1.getFlights(), flight2));
    EXPECT_TRUE(existSet(passenger2.getFlights(), flight2));

    EXPECT_TRUE(flight2.removePassengers());

    EXPECT_EQ(flight2.getPassengers().size(), 0);
    EXPECT_EQ(passenger1.getFlights().size(), 0);
    EXPECT_EQ(passenger2.getFlights().size(), 0);

    delete pCompany;
}

TEST(flight, crewMember) {
    Company* pCompany1 = new (Company){"Test1"};
    Company* pCompany2 = new (Company){"Test1"};

    Plane plane{pCompany1, "B737", 1, 1, 1};

    CrewMember pilot1{pCompany1, PILOT, "Vic", "Ay", 1, MALE};
    CrewMember pilot2{pCompany1, PILOT, "Val", "Ro", 1, MALE};
    CrewMember pilot3{pCompany1, PILOT, "Val", "Ro", 1, MALE};
    CrewMember pilot4{pCompany2, PILOT, "Val", "Ro", 1, MALE};

    CrewMember stewardess1{pCompany1, STEWARDESS, "Ki", "Be", 1, FEMALE};
    CrewMember stewardess2{pCompany1, STEWARDESS, "Jo", "Qa", 1, FEMALE};
    CrewMember stewardess3{pCompany1, STEWARDESS, "Jo", "Qa", 1, FEMALE};
    CrewMember stewardess4{pCompany2, STEWARDESS, "Jo", "Qa", 1, FEMALE};

    Flight& flight1 = pCompany1->createFlight("RYR120", plane, 2, 5, "Warsaw", "Berlin");
    Flight& flight2 = pCompany1->createFlight("RYR120", 2, 5, "Warsaw", "Berlin");
    // addCrewMember
    flight1.addCrewMember(pilot1);

    EXPECT_EQ(flight1.getPilots().size(), 1);
    EXPECT_EQ(flight1.getStewardesses().size(), 0);

    flight1.addCrewMember(stewardess1);

    EXPECT_EQ(flight1.getPilots().size(), 1);
    EXPECT_EQ(flight1.getStewardesses().size(), 1);

    EXPECT_TRUE(existSet(flight1.getPilots(), pilot1));
    EXPECT_TRUE(existSet(flight1.getStewardesses(), stewardess1));
    EXPECT_TRUE(existSet(pilot1.getFlights(), flight1));
    EXPECT_TRUE(existSet(stewardess1.getFlights(), flight1));

    // TIME OVERLAP
    EXPECT_THROW(flight2.addCrewMember(pilot1), TimeOverlap);
    EXPECT_THROW(flight2.addCrewMember(stewardess1), TimeOverlap);
    // DUPLICATION
    flight2.addCrewMember(pilot2);
    flight2.addCrewMember(stewardess2);

    EXPECT_THROW(flight2.addCrewMember(pilot2), DuplicationError);
    EXPECT_THROW(flight2.addCrewMember(stewardess2), DuplicationError);

    flight2.removeCrewMembers();
    // CAPACITY
    flight1.addCrewMember(pilot2);
    flight1.addCrewMember(stewardess2);

    EXPECT_THROW(flight1.addCrewMember(pilot3), MaximumCapacity);
    EXPECT_THROW(flight1.addCrewMember(stewardess3), MaximumCapacity);

    // COMPANY MISMATCH
    EXPECT_THROW(flight2.addCrewMember(pilot4), InvalidCrew);
    EXPECT_THROW(flight2.addCrewMember(stewardess4), InvalidCrew);

    // removeCrewMember
    EXPECT_TRUE(flight1.removeCrewMember(pilot1));

    EXPECT_EQ(flight1.getPilots().size(), 1);
    EXPECT_FALSE(existSet(flight1.getPilots(), pilot1));
    EXPECT_EQ(pilot1.getFlights().size(), 0);
    EXPECT_EQ(flight1.getStewardesses().size(), 2);

    EXPECT_TRUE(flight1.removeCrewMember(stewardess1));

    EXPECT_EQ(flight1.getStewardesses().size(), 1);
    EXPECT_EQ(flight1.getPilots().size(), 1);
    EXPECT_FALSE(existSet(flight1.getStewardesses(), stewardess1));
    EXPECT_EQ(stewardess1.getFlights().size(), 0);

    flight1.removeCrewMember(pilot2);
    flight1.removeCrewMember(stewardess2);
    // removeCrewMembers
    flight2.addCrewMember(pilot1);
    flight2.addCrewMember(stewardess1);
    flight2.addCrewMember(pilot2);
    flight2.addCrewMember(stewardess2);

    EXPECT_EQ(flight2.getPilots().size(), 2);
    EXPECT_EQ(flight2.getStewardesses().size(), 2);
    EXPECT_EQ(pilot1.getFlights().size(), 1);
    EXPECT_EQ(pilot2.getFlights().size(), 1);
    EXPECT_EQ(stewardess1.getFlights().size(), 1);
    EXPECT_EQ(stewardess2.getFlights().size(), 1);

    EXPECT_TRUE(flight2.removeCrewMembers());

    EXPECT_EQ(flight2.getPilots().size(), 0);
    EXPECT_EQ(flight2.getStewardesses().size(), 0);
    EXPECT_EQ(pilot1.getFlights().size(), 0);
    EXPECT_EQ(pilot2.getFlights().size(), 0);
    EXPECT_EQ(stewardess1.getFlights().size(), 0);
    EXPECT_EQ(stewardess2.getFlights().size(), 0);

    delete pCompany1;
    delete pCompany2;
}

TEST(flight, status) {
    Company* pCompany = new (Company){"Test1"};

    Plane plane{pCompany, "B737", 1, 1, 1};

    CrewMember pilot1{pCompany, PILOT, "Vic", "Ay", 1, MALE};
    CrewMember pilot2{pCompany, PILOT, "Val", "Ro", 1, MALE};

    CrewMember stewardess1{pCompany, STEWARDESS, "Ki", "Be", 1, FEMALE};
    CrewMember stewardess2{pCompany, STEWARDESS, "Jo", "Qa", 1, FEMALE};

    Flight& flight = pCompany->createFlight("RYR120", 2, 5, "Warsaw", "Berlin");

    flight.setPlane(plane);
    EXPECT_EQ(flight.getStatus(), INCOMPLETE);

    flight.addCrewMember(pilot1);
    EXPECT_EQ(flight.getStatus(), INCOMPLETE);
    flight.addCrewMember(stewardess1);
    EXPECT_EQ(flight.getStatus(), AS_PLANNED);

    flight.addCrewMember(pilot2);
    EXPECT_EQ(flight.getStatus(), AS_PLANNED);
    flight.addCrewMember(stewardess2);
    EXPECT_EQ(flight.getStatus(), AS_PLANNED);

    flight.removePlane();
    EXPECT_EQ(flight.getStatus(), INCOMPLETE);
    flight.removeCrewMember(pilot2);
    flight.removeCrewMember(stewardess2);

    flight.setPlane(plane);
    EXPECT_EQ(flight.getStatus(), AS_PLANNED);

    flight.removeCrewMember(pilot1);
    EXPECT_EQ(flight.getStatus(), INCOMPLETE);

    delete pCompany;
}
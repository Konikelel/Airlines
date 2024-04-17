#include "Flight.hpp"

#include <gtest/gtest.h>

#include <memory>

#include "Company.hpp"
#include "CustomErrors.hpp"
#include "Plane.hpp"

TEST(flight, constructor) {
    Company* pCompany = new (Company){"Test1"};

    Flight flight1 = pCompany->createFlight("RYR120", 1, 2, "Warsaw", "Berlin");

    Plane plane{pCompany, 101, "B737", 100, 4, 2};
    Flight flight2 = pCompany->createFlight("RYR102", plane, 1, 2, "Poznan", "Krakow");
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

TEST(flight, setters) {
    Company* pCompany = new (Company){"Test1"};

    Flight flight = pCompany->createFlight("RYR120", 1, 2, "Warsaw", "Berlin");
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
    EXPECT_THROW(flight.changeDataDeparture(2), InvalidTime);
    EXPECT_THROW(flight.changeDataDeparture(3), InvalidTime);
    flight.changeDataDeparture(1);
    flight.changeDataDeparture(0, "aBc");
    EXPECT_EQ(flight.getTimeDeparture(), 0);
    EXPECT_EQ(flight.getCityDeparture(), "aBc");

    flight.changeDataDeparture(1);
    EXPECT_THROW(flight.changeDataArrival(1), InvalidTime);
    EXPECT_THROW(flight.changeDataArrival(0), InvalidTime);
    flight.changeDataArrival(2);
    flight.changeDataArrival(3, "aBc");
    EXPECT_EQ(flight.getTimeArrival(), 3);
    EXPECT_EQ(flight.getCityArrival(), "aBc");

    EXPECT_THROW(flight.changeDataDeparture(0, ""), InvalidName);
    EXPECT_THROW(flight.changeDataArrival(3, ""), InvalidName);

    flight.changeDataDeparture(2);
    flight.changeDataArrival(5);
    EXPECT_TRUE(flight.timeOverlap(2, 5));
    EXPECT_TRUE(flight.timeOverlap(1, 5));
    EXPECT_TRUE(flight.timeOverlap(2, 6));
    EXPECT_TRUE(flight.timeOverlap(2, 4));
    EXPECT_FALSE(flight.timeOverlap(0, 1));
    EXPECT_FALSE(flight.timeOverlap(6, 7));

    delete pCompany;
}
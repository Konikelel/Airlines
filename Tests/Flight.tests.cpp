#include "Flight.hpp"

#include <gtest/gtest.h>

#include <memory>

#include "Company.hpp"
#include "CustomErrors.hpp"
#include "Plane.hpp"

TEST(FlightClass, constructor) {
    Company* company = new (Company){"Test1"};

    Flight flight1{company, "RYR120", 1, 2, "Warsaw", "Berlin"};

    auto pPlane = new (Plane){company, 101, "B737", 100, 4, 2};
    Flight flight2{company, "RYR102", pPlane, 1, 2, "Poznan", "Krakow"};

    EXPECT_EQ(flight1.getFlightNr(), "RYR120");
    EXPECT_EQ(flight1.getTimeDeparture(), 1);
    EXPECT_EQ(flight1.getTimeArrival(), 2);
    EXPECT_EQ(flight1.getCityDeparture(), "Warsaw");
    EXPECT_EQ(flight1.getCityArrival(), "Berlin");

    EXPECT_EQ(flight2.getPlane(), pPlane);
    delete pPlane, company;
}

TEST(FlightClass, setters) {  // ADD TESTING FOR CREW MEMBERS AND PASSENGERS
    Company* company = new (Company){"Test1"};

    Flight flight{company, "RYR120", 1, 2, "Warsaw", "Berlin"};

    EXPECT_THROW(flight.setCompany(nullptr), InvalidPointer);

    EXPECT_THROW(flight.setFlightNr("ryr"), InvalidFlightNr);
    flight.setFlightNr("ryr1");
    EXPECT_EQ(flight.getFlightNr(), "RYR1");
    flight.setFlightNr("rYr1201");
    EXPECT_EQ(flight.getFlightNr(), "RYR1201");
    EXPECT_THROW(flight.setFlightNr("rYr12012"), InvalidFlightNr);
    EXPECT_THROW(flight.setFlightNr("RY120"), InvalidFlightNr);
    EXPECT_THROW(flight.setFlightNr("R120"), InvalidFlightNr);

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
}
#include "Passenger.hpp"

#include <gtest/gtest.h>

#include "Company.hpp"
#include "CustomErrors.hpp"
#include "SetHandler.hpp"
#include "VectorHandler.hpp"

TEST(passenger, constructor) {
    Passenger passenger{"Victor", "Alb", 1, MALE};
    // getFlights
    EXPECT_EQ(passenger.getFlights().size(), 0);
}

TEST(passenger, destructor) {
    Company* pCompany = new (Company){"Test1"};

    Flight& flight1 = pCompany->createFlight("RYR123", 1, 2, "Warsaw", "Berlin");
    Flight& flight2 = pCompany->createFlight("RYR123", 3, 4, "Warsaw", "Berlin");

    {
        Passenger passenger{"Victor", "Alb", 1, MALE};
        passenger.addFlight(flight1);
        passenger.addFlight(flight2);

        EXPECT_EQ(flight1.getPassengers().size(), 1);
        EXPECT_EQ(flight2.getPassengers().size(), 1);
        EXPECT_EQ(passenger.getFlights().size(), 2);

        EXPECT_TRUE(existSet(flight1.getPassengers(), passenger));
        EXPECT_TRUE(existSet(flight2.getPassengers(), passenger));
        EXPECT_TRUE(existSet(passenger.getFlights(), flight1));
        EXPECT_TRUE(existSet(passenger.getFlights(), flight2));
    }

    EXPECT_EQ(flight1.getPassengers().size(), 0);
    EXPECT_EQ(flight2.getPassengers().size(), 0);

    delete pCompany;
}

TEST(passenger, flight) {
    Company* pCompany = new (Company){"Test1"};
    Flight& flight1 = pCompany->createFlight("RYR123", 1, 2, "Warsaw", "Berlin");
    Flight& flight2 = pCompany->createFlight("RYR123", 3, 4, "Warsaw", "Berlin");

    Passenger passenger{"Victor", "Alb", 1, MALE};
    // addFlight
    passenger.addFlight(flight1);

    EXPECT_EQ(passenger.getFlights().size(), 1);
    EXPECT_EQ(flight1.getPassengers().size(), 1);

    EXPECT_TRUE(existSet(passenger.getFlights(), flight1));
    EXPECT_TRUE(existSet(flight1.getPassengers(), passenger));
    // removeFlight
    passenger.addFlight(flight2);
    EXPECT_TRUE(passenger.removeFlight(flight1));

    EXPECT_EQ(passenger.getFlights().size(), 1);
    EXPECT_EQ(flight1.getPassengers().size(), 0);
    EXPECT_EQ(flight2.getPassengers().size(), 1);

    EXPECT_FALSE(existSet(flight1.getPassengers(), passenger));
    EXPECT_FALSE(existSet(passenger.getFlights(), flight1));
    EXPECT_TRUE(existSet(passenger.getFlights(), flight2));
    // removeFlights
    passenger.addFlight(flight1);
    EXPECT_TRUE(passenger.removeFlights());

    EXPECT_EQ(passenger.getFlights().size(), 0);
    EXPECT_EQ(flight1.getPassengers().size(), 0);

    EXPECT_FALSE(existSet(passenger.getFlights(), flight1));
    EXPECT_FALSE(existSet(flight1.getPassengers(), passenger));

    EXPECT_FALSE(existSet(passenger.getFlights(), flight2));
    EXPECT_FALSE(existSet(flight2.getPassengers(), passenger));

    delete pCompany;
}
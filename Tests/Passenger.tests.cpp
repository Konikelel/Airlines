#include "Passenger.hpp"

#include <gtest/gtest.h>

#include "Company.hpp"
#include "CustomErrors.hpp"
#include "VectorHandler.hpp"

TEST(passenger, constructor) {
    Passenger passenger{1, "Victor", "Alb", 1, MALE};
}

TEST(passenger, flight) {
    Company* pCompany = new (Company){"Test1"};
    Flight& flight1 = pCompany->createFlight("RYR123", 1, 2, "Warsaw", "Berlin");
    Flight& flight2 = pCompany->createFlight("RYR123", 3, 4, "Warsaw", "Berlin");

    Passenger passenger{1, "Victor", "Alb", 1, MALE};
    // addFlight
    passenger.addFlight(flight1);

    EXPECT_EQ(passenger.getFlights().size(), 1);
    EXPECT_EQ(flight1.getPassengers().size(), 1);

    EXPECT_TRUE(existVector(passenger.getFlights(), flight1));
    EXPECT_TRUE(existVector(flight1.getPassengers(), passenger));
    // removeFlight
    passenger.addFlight(flight2);
    EXPECT_TRUE(passenger.removeFlight(flight1));

    EXPECT_EQ(passenger.getFlights().size(), 1);
    EXPECT_FALSE(existVector(passenger.getFlights(), flight1));

    EXPECT_EQ(flight1.getPassengers().size(), 0);
    EXPECT_FALSE(existVector(flight1.getPassengers(), passenger));

    EXPECT_EQ(flight2.getPassengers().size(), 1);
    EXPECT_TRUE(existVector(flight2.getPassengers(), passenger));
    // removeFlights
    passenger.addFlight(flight1);
    EXPECT_TRUE(passenger.removeFlights());

    EXPECT_EQ(passenger.getFlights().size(), 0);
    EXPECT_EQ(flight1.getPassengers().size(), 0);

    EXPECT_FALSE(existVector(passenger.getFlights(), flight1));
    EXPECT_FALSE(existVector(flight1.getPassengers(), passenger));

    EXPECT_FALSE(existVector(passenger.getFlights(), flight2));
    EXPECT_FALSE(existVector(flight2.getPassengers(), passenger));

    delete pCompany;
}
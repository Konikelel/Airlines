#include "Passenger.hpp"

#include <gtest/gtest.h>

#include "Company.hpp"
#include "CustomErrors.hpp"
#include "VectorHandler.hpp"

TEST(PassengerClass, constructor) {
    Passenger passenger{1, "Victor", "Alb", 1, MALE};
}

TEST(PassengerClass, flightClassWorkCheck) {
    // Company* pCompany = new (Company){"Test1"};
    // Flight flight1{pCompany, "RYR123", 1, 2, "Warsaw", "Berlin"};
    // Flight flight2{pCompany, "RYR123", 3, 4, "Warsaw", "Berlin"};

    // Passenger passenger{1, "Victor", "Alb", 1, MALE};
    // // Test only if works
    // //  addFlight
    // passenger.addFlight(flight1);
    // EXPECT_TRUE(existVector(passenger.getFlights(), flight1));
    // EXPECT_TRUE(existVector(flight1.getPassengers(), passenger));
    // EXPECT_EQ(flight1.getPassengers().size(), 1);
    // EXPECT_EQ(passenger.getFlights().size(), 1);
    // // removeFlight
    // passenger.removeFlight(flight1);
    // EXPECT_FALSE(existVector(passenger.getFlights(), flight1));
    // EXPECT_FALSE(existVector(flight1.getPassengers(), passenger));
    // EXPECT_EQ(flight1.getPassengers().size(), 0);
    // EXPECT_EQ(passenger.getFlights().size(), 0);
    // // removeFlights
    // passenger.addFlight(flight1);
    // passenger.addFlight(flight2);
    // passenger.removeFlights();
    // EXPECT_EQ(flight1.getPassengers().size(), 0);
    // EXPECT_EQ(passenger.getFlights().size(), 0);

    // delete pCompany, flight1, flight2, passenger;
}
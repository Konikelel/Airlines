#include "Passenger.hpp"

#include <gtest/gtest.h>

#include "Company.hpp"
#include "CustomErrors.hpp"
#include "VectorHandler.hpp"

TEST(PassengerClass, constructor) {
    Passenger passenger{1, "Victor", "Alb", 1, MALE};
}

TEST(PassengerClass, flightClassWorkCheck) {
    Company* pCompany = new (Company){"Test1"};
    Flight* pFlight1 = new (Flight){pCompany, "RYR123", 1, 2, "Warsaw", "Berlin"};
    Flight* pFlight2 = new (Flight){pCompany, "RYR123", 3, 4, "Warsaw", "Berlin"};

    Passenger* pPassenger = new (Passenger){1, "Victor", "Alb", 1, MALE};
    // Test only if works
    //  addFlight
    pPassenger->addFlight(pFlight1);
    EXPECT_TRUE(existVector(pPassenger->getFlights(), pFlight1));
    EXPECT_TRUE(existVector(pFlight1->getPassengers(), pPassenger));
    EXPECT_EQ(pFlight1->getPassengers().size(), 1);
    EXPECT_EQ(pPassenger->getFlights().size(), 1);
    // removeFlight
    pPassenger->removeFlight(pFlight1);
    EXPECT_FALSE(existVector(pPassenger->getFlights(), pFlight1));
    EXPECT_FALSE(existVector(pFlight1->getPassengers(), pPassenger));
    EXPECT_EQ(pFlight1->getPassengers().size(), 0);
    EXPECT_EQ(pPassenger->getFlights().size(), 0);
    // removeFlights
    pPassenger->addFlight(pFlight1);
    pPassenger->addFlight(pFlight2);
    pPassenger->removeFlights();
    EXPECT_EQ(pFlight1->getPassengers().size(), 0);
    EXPECT_EQ(pPassenger->getFlights().size(), 0);

    delete pCompany, pFlight1, pFlight2, pPassenger;
}
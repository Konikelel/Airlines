#include <gtest/gtest.h>

#include "Company.hpp"
#include "CustomErrors.hpp"
#include "Flight.hpp"
#include "Passenger.hpp"
#include "Plane.hpp"
#include "VectorHandler.hpp"

TEST(Global, passengerFlight) {
    Company* pCompany = new (Company){"Test"};
    Flight* pFlight = new (Flight){pCompany, "RYR120", 1, 2, "Warsaw", "Berlin"};
    Passenger* pPassenger = new (Passenger){1, "Victor", "Alb", 2, MALE};

    pPassenger->addFlight(pFlight);
    EXPECT_TRUE(existVector(pPassenger->getFlights(), pFlight));
    EXPECT_TRUE(existVector(pFlight->getPassengers(), pPassenger));
}
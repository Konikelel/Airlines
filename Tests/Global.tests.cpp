#include <gtest/gtest.h>

#include "CustomErrors.hpp"
#include "Flight.hpp"
#include "Passenger.hpp"
#include "Plane.hpp"

TEST(Global, passengerFlight) {
    auto pPlane = std::make_shared<Plane>(Plane{101, "B737", 100, 4, 2});

    auto pPassenger = std::make_shared<Passenger>(Passenger{1, "Victor", "Alb", 1, MALE});
    auto pFlight = std::make_shared<Flight>(Flight{"RYR102", 1, 2, "Poznan", "Krakow"});

    pPassenger.get()->addFlight(pFlight.get());

    EXPECT_TRUE(pPassenger.get()->existFlight(pFlight.get()));
    EXPECT_TRUE(pFlight.get()->existPassenger(pPassenger.get()));
}
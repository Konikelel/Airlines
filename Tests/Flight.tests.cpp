#include "Flight.hpp"

#include <gtest/gtest.h>

#include <memory>

#include "CustomErrors.hpp"
#include "Plane.hpp"

TEST(FlightClass, constructor) {
    Flight flight1{"RYR120", 1, 2, "Warsaw", "Berlin"};

    // auto pPlane = std::make_shared<Plane>(Plane{101, "B737", 100, 4, 2});
    // Flight flight2{"RYR102", pPlane, 1, 2, "Poznan", "Krakow"};
}
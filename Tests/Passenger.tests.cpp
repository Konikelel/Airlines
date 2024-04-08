#include "Passenger.hpp"

#include <gtest/gtest.h>

#include "CustomErrors.hpp"

TEST(PassengerClass, constructor) {
    Passenger passenger{1, "Victor", "Alb", 1, MALE};
}
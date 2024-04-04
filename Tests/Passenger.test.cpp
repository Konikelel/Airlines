#include "Passenger/Passenger.h"

#include <iostream>

#include "Person/Person.h"
#include "Tests.h"

int testPassenger() {
    std::cout << "Testing Passenger class:" << std::endl;
    bool passed;

    std::cout << "Testing constructor... ";
    {
        Passenger passenger{100, "Victor", "Alb", 0, MALE};
    }
    std::cout << "Passed";

    return 0;
}
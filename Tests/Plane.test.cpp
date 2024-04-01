#include "Plane/Plane.h"

#include <exception>
#include <iostream>

#include "Utils/CustomErrors.h"

int testPlane() {  // ADD IN DESTRUCTOR TO REMOVE ID FROM LIST
    std::cout << "Testing Plane class:" << std::endl;
    bool passed = false;

    Plane plane{100, "B737", 100, 3, 2};

    std::cout << "Testing constructor and setters... ";
    {
        plane.setId(101);
        plane.setName("B777");
        plane.setCapacityPassengers(100);
        plane.setRequiredStewardess(3);
        plane.setRequiredPilots(2);
    }
    std::cout << "Passed" << std::endl;

    std::cout << "Testing uniqueId... ";
    {
        Plane plane2{102, "B737", 100, 3, 2};

        try {
            plane2.setId(101);
        } catch (const NonUniqueIDException& e) {
            passed = true;
        }
    }
    std::cout << (passed ? "Passed" : throw std::runtime_error("Failed")) << std::endl;

    std::cout << "Testing passenger inRange functions... ";  // IMPLEMENT CHECKING WITH VECTORS
    {
        passed = (plane.inRangePassengers(100) && plane.inRangePassengers(99) && !plane.inRangePassengers(101));
    }
    std::cout << (passed ? "Passed" : throw std::runtime_error("Failed")) << std::endl;

    std::cout << "Testing stewardess inRange functions... ";  // IMPLEMENT CHECKING WITH VECTORS
    {
        passed = (plane.inRangeStewardesses(3) && !plane.inRangeStewardesses(2) &&
                  plane.inRangeStewardesses(3 * 2) && !plane.inRangeStewardesses(3 * 2 + 1));
    }
    std::cout << (passed ? "Passed" : throw std::runtime_error("Failed")) << std::endl;

    std::cout << "Testing pilots inRange functions... ";  // IMPLEMENT CHECKING WITH VECTORS
    {
        passed = (plane.inRangePilots(2) && !plane.inRangePilots(1) &&
                  plane.inRangePilots(2 * 2) && !plane.inRangePilots(2 * 2 + 1));
    }
    std::cout << (passed ? "Passed" : throw std::runtime_error("Failed")) << std::endl;

    // IMPLEMENT REST FUNCTIONS

    return 0;
}
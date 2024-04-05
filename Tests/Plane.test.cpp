#include "Plane.h"

#include <exception>
#include <iostream>

#include "CustomErrors.h"
#include "Tests.h"

int testPlane() {  // ADD IN DESTRUCTOR TO REMOVE ID FROM LIST
    std::cout << "Testing Plane class:" << std::endl;
    bool passed;

    Plane plane{100, "B737", 100, 3, 2};

    std::cout << "Testing constructor, getters, setters... ";
    passed = false;
    {
        Plane plane1{101, "B737", 50, 1, 1};

        try {
            plane1.setName("");
        } catch (const InvalidName& e) {
            passed = true;
        }

        plane1.changeId(99);
        plane1.setName("B777");
        plane1.setCapacityPassengers(100);
        plane1.setRequiredStewardess(3);
        plane1.setRequiredPilots(2);

        passed = (plane1.getId() == 99 && plane1.getName() == "B777" && plane1.getCapacityPassengers() == 100 &&
                  plane1.getRequiredStewardess() == 3 && plane1.getRequiredPilots() == 2) &&
                 passed;
    }
    std::cout << (passed ? "Passed" : throw std::runtime_error("Failed")) << std::endl;

    std::cout << "Testing uniqueId... ";
    passed = false;
    {
        Plane plane2{102, "B737", 100, 3, 2};

        try {
            plane2.changeId(100);
        } catch (const NonUniqueIDException& e) {
            passed = true;
        }
    }
    std::cout << (passed ? "Passed" : throw std::runtime_error("Failed")) << std::endl;

    std::cout << "Testing destructor... ";
    passed = true;
    {
        try {
            plane.changeId(99);
        } catch (const NonUniqueIDException& e) {
            passed = false;
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
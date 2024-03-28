#include <memory>
#include <string>
#include <vector>

#ifndef PLANE_H
#define PLANE_H

#include "../Flight/Flight.h"

class Plane {
   private:
    unsigned int id;
    std::string name;

    unsigned int capacityPassengers;
    unsigned int requiredStewardess;
    unsigned int requiredPilots;

    std::vector<std::shared_ptr<Flight>> pFlights;
};

#endif
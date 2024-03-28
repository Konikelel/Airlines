#include <memory>
#include <string>
#include <vector>

#ifndef PLANE_H
#define PLANE_H

#include "../Flight/Flight.h"

class Plane {
   private:
    std::string name;

    unsigned int capacityPassengers;
    unsigned int capacityCrewMembers;  // divide to pilots and stewardess ???

    std::vector<std::shared_ptr<Flight>> pFlights;
};

#endif
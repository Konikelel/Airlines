#include <string>
#include <vector>

#ifndef PLANE_H
#define PLANE_H

#include "../Flight/Flight.h"

class Plane {
   public:
    static std::vector<unsigned int> usedIds;

    Plane(
        unsigned int id,
        std::string name,
        unsigned int capacityPassengers,
        unsigned int requiredStewardess,
        unsigned int requiredPilots);

    void addFlight(const Flight*& pFlight);
    void removeFlight(const Flight*& pFlight);

   private:
    void setId(const unsigned int id);

    unsigned int id;
    std::string name;

    unsigned int capacityPassengers;
    unsigned int requiredStewardess;  // VALIDATE IF TOO MANY
    unsigned int requiredPilots;      // VALIDATE IF TOO MANY

    std::vector<Flight*> flights;
};

#endif
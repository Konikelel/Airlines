#include <string>
#include <vector>

#ifndef PLANE_H
#define PLANE_H

#include "Flight/Flight.h"
#include "PlaneStatus.h"

class Plane {
   public:
    static std::vector<unsigned int> usedIds;

    Plane(
        unsigned int& id,
        std::string& name,
        unsigned int& capacityPassengers,
        unsigned int& requiredStewardess,
        unsigned int& requiredPilots);

    void setName(const std::string& name);
    void setStatus(const PlaneStatus& status);

    void setCapacityPassengers(const unsigned int& number);
    void setRequiredStewardess(const unsigned int& number);
    void setRequiredPilots(const unsigned int& number);

    const unsigned int& getCapacityPassengers();
    const unsigned int& getRequiredStewardess();
    const unsigned int& getRequiredPilots();

    void addFlight(Flight*& pFlight);
    void removeFlight(Flight*& pFlight);

    void removeFlights();
    void terminate();

   private:
    void setId(const unsigned int& id);

    unsigned int id;
    std::string name;
    PlaneStatus status;

    unsigned int capacityPassengers;
    unsigned int requiredStewardess;  // VALIDATE IF TOO MANY
    unsigned int requiredPilots;      // VALIDATE IF TOO MANY

    std::vector<Flight*> flights;
};

#endif
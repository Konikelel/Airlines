#include <string>
#include <vector>

#ifndef PLANE_H
#define PLANE_H

#include "Flight/Flight.h"

class Plane {
   public:
    static std::vector<unsigned int> usedIds;

    Plane(
        unsigned int& id,
        std::string& name,
        unsigned int& capacityPassengers,
        unsigned int& requiredStewardess,
        unsigned int& requiredPilots);

    const unsigned int& getCapacityPassengers();
    const unsigned int& getRequiredStewardess();
    const unsigned int& getRequiredPilots();

    void setName(const std::string& name);

    void setCapacityPassengers(const unsigned int& number);
    void setRequiredStewardess(const unsigned int& number);
    void setRequiredPilots(const unsigned int& number);

    bool inRangePassengers(unsigned int number);
    bool inRangePassengers(std::vector<Passenger*> passengers);

    bool inRangeStewardesses(unsigned int number);
    bool inRangeStewardesses(std::vector<CrewMember*> stewardesses);

    bool inRangePilots(unsigned int number);
    bool inRangePilots(std::vector<CrewMember*> pilots);

    bool inRangeCrew(std::vector<CrewMember*> stewardesses, std::vector<CrewMember*> pilots);

    void addFlight(Flight*& pFlight);
    void removeFlight(Flight*& pFlight);

    void removeFlights();
    void terminate();

   private:
    void setId(const unsigned int& id);

    unsigned int id;
    std::string name;

    unsigned int capacityPassengers;
    unsigned int requiredStewardess;
    unsigned int requiredPilots;

    unsigned int capacityStewardess;
    unsigned int capacityPilots;

    std::vector<Flight*> flights;
};

#endif
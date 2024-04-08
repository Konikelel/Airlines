#include <string>
#include <vector>

#ifndef PLANE_H
#define PLANE_H

#include "Flight.hpp"

class Plane {
   public:
    static std::vector<unsigned int> usedIds;

    Plane(
        unsigned int id,
        std::string name,
        unsigned int capacityPassengers,
        unsigned int requiredStewardess,
        unsigned int requiredPilots);

    ~Plane();

    unsigned int getId();
    std::string getName();
    unsigned int getCapacityPassengers();
    unsigned int getRequiredStewardess();
    unsigned int getCapacityStewardess();
    unsigned int getRequiredPilots();
    unsigned int getCapacityPilots();

    void changeId(const unsigned int id);
    void setName(const std::string name);

    void setCapacityPassengers(const unsigned int number);
    void setRequiredStewardess(const unsigned int number);
    void setRequiredPilots(const unsigned int number);

    bool inRangePassengers(const unsigned int number) const;
    bool inRangePassengers(const std::vector<Passenger*>& passengers) const;

    bool inRangeStewardesses(const unsigned int number) const;
    bool inRangeStewardesses(const std::vector<CrewMember*>& stewardesses) const;

    bool inRangePilots(const unsigned int number) const;
    bool inRangePilots(const std::vector<CrewMember*>& pilots) const;

    bool inRangeCrew(const std::vector<CrewMember*>& stewardesses, const std::vector<CrewMember*>& pilots) const;

    void addFlight(Flight* pFlight);
    void removeFlight(const Flight* pFlight);

    void removeFlights();
    void terminate();

   private:
    void setId(const unsigned int id);

    unsigned int id;
    std::string name;

    std::vector<Flight*> flights;

    unsigned int capacityPassengers;
    unsigned int requiredStewardess;
    unsigned int requiredPilots;

    unsigned int capacityStewardess;
    unsigned int capacityPilots;
};

#endif
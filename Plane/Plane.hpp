#include <string>
#include <vector>

#ifndef PLANE_H
#define PLANE_H

#include "Flight.hpp"

class Plane {
   public:
    Plane(
        Company* pCompany,
        unsigned int id,
        std::string name,
        unsigned int capacityPassengers,
        unsigned int requiredStewardesses,
        unsigned int requiredPilots);

    Plane(
        unsigned int id,
        std::string name,
        unsigned int capacityPassengers,
        unsigned int requiredStewardesses,
        unsigned int requiredPilots);

    ~Plane();

    unsigned int getId() const;
    std::string getName() const;
    Company* getCompany() const;
    unsigned int getCapacityPassengers() const;
    unsigned int getRequiredStewardesses() const;
    unsigned int getCapacityStewardesses() const;
    unsigned int getRequiredPilots() const;
    unsigned int getCapacityPilots() const;

    void setCompany(Company* pCompany);

    // SET ID AND REMOVE OLD ONE FROM VECTOR usedIds
    void changeId(const unsigned int id);
    void setName(const std::string name);

    void setCapacityPassengers(const unsigned int number);
    void setRequiredStewardesses(const unsigned int number);
    void setRequiredPilots(const unsigned int number);

    // CHECK IF NUMBER OF PASSENGERS IS WITHIN CAPACITY RANGE
    bool inRangePassengers(const unsigned int number) const;
    bool inRangePassengers(const std::vector<Passenger*>& passengers) const;

    // CHECK IF NUMBER OF STEWARDESSES IS BETWEEN REQUIRED AND CAPACITY NUMBER
    bool inRangeStewardesses(const unsigned int number) const;
    bool inRangeStewardesses(const std::vector<CrewMember*>& stewardesses) const;

    // CHECK IF NUMBER OF PILOTS IS BETWEEN REQUIRED AND CAPACITY NUMBER
    bool inRangePilots(const unsigned int number) const;
    bool inRangePilots(const std::vector<CrewMember*>& pilots) const;

    // CHECK IN RANGE STEWARDESSES AND PILOTS
    bool inRangeCrew(const std::vector<CrewMember*>& stewardesses, const std::vector<CrewMember*>& pilots) const;

    // ADD FLIGHT POINTER TO PLANE, IF PLANE IS NOT ADDED IN FLIGHT, ADD PLANE POINTER TO FLIGHT
    void addFlight(Flight* pFlight);
    // REMOVE FLIGHT POINTER FROM PLANE, IF PLANE IS ADDED IN FLIGHT, REMOVE PLANE POINTER FROM FLIGHT
    void removeFlight(Flight* pFlight);
    // REMOVE ALL FLIGHTS FROM PLANE AND PLANE FROM FLIGHTS
    void removeFlights();

   private:
    static std::vector<unsigned int> usedIds;
    // SET ID, CALLED IN CONSTRUCTOR
    void setId(const unsigned int id);

    unsigned int id;
    std::string name;

    Company* pCompany;
    std::vector<Flight*> flights;

    unsigned int capacityPassengers;
    unsigned int requiredStewardesses;
    unsigned int requiredPilots;

    unsigned int capacityStewardesses;
    unsigned int capacityPilots;
};

#endif
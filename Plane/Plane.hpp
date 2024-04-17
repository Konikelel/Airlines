#include <functional>
#include <string>
#include <vector>

#ifndef PLANE_H
#define PLANE_H

#include "Company.hpp"
#include "Flight.hpp"

class Plane {
   public:
    static std::vector<unsigned int> usedIds;

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
    Company*& getCompany();
    std::vector<std::reference_wrapper<Flight>>& getFlights();
    unsigned int getCapacityPassengers() const;
    unsigned int getRequiredStewardesses() const;
    unsigned int getCapacityStewardesses() const;
    unsigned int getRequiredPilots() const;
    unsigned int getCapacityPilots() const;

    void setCompany(Company* pCompany);

    void changeId(const unsigned int id);
    void setName(const std::string name);

    void setCapacityPassengers(const unsigned int number);
    void setRequiredStewardesses(const unsigned int number);
    void setRequiredPilots(const unsigned int number);

    bool inRangePassengers(const unsigned int number) const;

    bool inRangeStewardesses(const unsigned int number) const;
    bool maximumStewardesses(const unsigned int number) const;

    bool inRangePilots(const unsigned int number) const;
    bool maximumPilots(const unsigned int number) const;

    bool inRangeCrew(const unsigned int stewardess, const unsigned int pilots) const;

    // INVOKE FUNCTION FROM FLIGHT TO ADD PLANE
    void addFlight(Flight& flight);
    // INVOKE FUNCTION FROM FLIGHT TO REMOVE PLANE
    bool removeFlight(Flight& flight);
    // INVOKE FOR ALL FLIGHTS FUNCTION removeFlight
    bool removeFlights();

   private:
    void setId(const unsigned int id);

    unsigned int id;
    std::string name;

    Company* pCompany;
    std::vector<std::reference_wrapper<Flight>> flights;

    unsigned int capacityPassengers;
    unsigned int requiredStewardesses;
    unsigned int requiredPilots;

    unsigned int capacityStewardesses;
    unsigned int capacityPilots;

    friend Company;
};

#endif
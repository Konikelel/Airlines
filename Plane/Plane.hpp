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
        std::string name,
        unsigned int capacityPassengers,
        unsigned int requiredStewardesses,
        unsigned int requiredPilots);

    Plane(
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
    std::set<std::reference_wrapper<Flight>>& getFlights();

    bool setCompany(Company* pCompany);
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

    friend bool operator==(const std::reference_wrapper<Plane>& one, const Plane& other);
    friend bool operator<(const std::reference_wrapper<Plane>& one, const std::reference_wrapper<Plane>& other);
    friend std::ostream& operator<<(std::ostream& os, Plane& plane);

   private:
    void setId();

    unsigned int id;
    std::string name;

    Company* pCompany;
    std::set<std::reference_wrapper<Flight>> flights;

    unsigned int capacityPassengers;
    unsigned int requiredStewardesses;
    unsigned int requiredPilots;

    unsigned int capacityStewardesses;
    unsigned int capacityPilots;
};

#endif
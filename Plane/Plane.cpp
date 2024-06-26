#include "Plane.hpp"

#include <iostream>

#include "CustomErrors.hpp"
#include "IdGenerator.hpp"
#include "SetHandler.hpp"
#include "VectorHandler.hpp"

std::vector<unsigned int> Plane::usedIds;

Plane::Plane(Company* pCompany,
             std::string name,
             unsigned int capacityPassengers,
             unsigned int requiredStewardess,
             unsigned int requiredPilots) : Plane(name, capacityPassengers, requiredStewardess, requiredPilots) {
    setCompany(pCompany);
}

Plane::Plane(std::string name,
             unsigned int capacityPassengers,
             unsigned int requiredStewardess,
             unsigned int requiredPilots) : pCompany{nullptr} {
    setId();
    setName(name);
    setCapacityPassengers(capacityPassengers);
    setRequiredStewardesses(requiredStewardess);
    setRequiredPilots(requiredPilots);

    this->capacityStewardesses = requiredStewardess * 2;
    this->capacityPilots = requiredPilots * 2;
}

Plane::~Plane() {
    deleteVector(usedIds, id);

    if (pCompany)
        pCompany->removePlane(*this);
}

unsigned int Plane::getId() const {
    return id;
}

std::string Plane::getName() const {
    return name;
}

Company* Plane::getCompany() const {
    return pCompany;
}

std::set<std::reference_wrapper<Flight>>& Plane::getFlights() {
    return flights;
}

unsigned int Plane::getCapacityPassengers() const {
    return capacityPassengers;
}

unsigned int Plane::getRequiredStewardesses() const {
    return requiredStewardesses;
}

unsigned int Plane::getCapacityStewardesses() const {
    return capacityStewardesses;
}

unsigned int Plane::getRequiredPilots() const {
    return requiredPilots;
}

unsigned int Plane::getCapacityPilots() const {
    return capacityPilots;
}

bool Plane::setCompany(Company* pCompany) {
    if (pCompany == this->pCompany)
        return false;

    if (this->pCompany) {
        removeFlights();
        deleteSet(this->pCompany->getPlanes(), *this);
    }

    if (pCompany)
        addSet(pCompany->getPlanes(), *this);

    this->pCompany = pCompany;
    return true;
}

void Plane::setId() {
    id = generateUniqueId(usedIds);
    addVector(usedIds, id);
}

void Plane::setName(std::string name) {
    if (!name.size())
        throw InvalidName("Name must contain any character");

    this->name = name;
}

void Plane::setCapacityPassengers(const unsigned int number) {
    if (!flights.empty())
        throw CannotPerform("Cannot modify. Plane is in use");
    if (!number)
        throw InvalidNumber("Number of passengers cannot be 0");

    this->capacityPassengers = number;
}

void Plane::setRequiredStewardesses(const unsigned int number) {
    if (!flights.empty())
        throw CannotPerform("Cannot modify. Plane is in use");
    if (!number)
        throw InvalidNumber("Number of stewardess cannot be 0");

    this->capacityStewardesses = number * 2;
    this->requiredStewardesses = number;
}

void Plane::setRequiredPilots(const unsigned int number) {
    if (!flights.empty())
        throw CannotPerform("Cannot modify. Plane is in use");
    if (!number)
        throw InvalidNumber("Number of pilots cannot be 0");

    this->capacityPilots = number * 2;
    this->requiredPilots = number;
}

bool Plane::inRangePassengers(unsigned int number) const {
    return capacityPassengers >= number;
}

bool Plane::inRangeStewardesses(unsigned int number) const {
    return requiredStewardesses <= number && number <= capacityStewardesses;
}

bool Plane::maximumStewardesses(const unsigned int number) const {
    return number > capacityStewardesses;
}

bool Plane::inRangePilots(unsigned int number) const {
    return requiredPilots <= number && number <= capacityPilots;
}

bool Plane::maximumPilots(const unsigned int number) const {
    return number > capacityPilots;
}

bool Plane::inRangeCrew(const unsigned int stewardess, const unsigned int pilots) const {
    return inRangeStewardesses(stewardess) && inRangePilots(pilots);
}

void Plane::addFlight(Flight& flight) {
    flight.setPlane(*this);
}

bool Plane::removeFlight(Flight& flight) {
    return flight.removePlane();
}

bool Plane::removeFlights() {
    bool success = true;

    for (auto it = flights.begin(); it != flights.end();)
        success = removeFlight(*(it++)) && success;

    return true;
}

bool operator==(const std::reference_wrapper<Plane>& one, const Plane& other) {
    return one.get().id == other.id;
}

bool operator<(const std::reference_wrapper<Plane>& one, const std::reference_wrapper<Plane>& other) {
    return one.get().id < other.get().id;
};

std::ostream& operator<<(std::ostream& os, Plane& plane) {
    os << "Id: " << plane.getId() << " "
       << "Company: " << plane.getCompany()->getName() << " "
       << "Flights: " << plane.getFlights().size() << std::endl;

    return os;
}

#include "Plane.hpp"

#include <iostream>

#include "CustomErrors.hpp"
#include "IdGenerator.hpp"
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

Plane::~Plane() {  // TESTED
    deleteVector(usedIds, id);

    if (pCompany)
        pCompany->removePlane(*this);
}

unsigned int Plane::getId() const {  // TESTED
    return id;
}

std::string Plane::getName() const {  // TESTED
    return name;
}

Company* Plane::getCompany() const {  // TESTED
    return pCompany;
}

std::set<std::reference_wrapper<Flight>>& Plane::getFlights() {  // TESTED
    return flights;
}

unsigned int Plane::getCapacityPassengers() const {  // TESTED
    return capacityPassengers;
}

unsigned int Plane::getRequiredStewardesses() const {  // TESTED
    return requiredStewardesses;
}

unsigned int Plane::getCapacityStewardesses() const {  // TESTED
    return capacityStewardesses;
}

unsigned int Plane::getRequiredPilots() const {  // TESTED
    return requiredPilots;
}

unsigned int Plane::getCapacityPilots() const {  // TESTED
    return capacityPilots;
}

void Plane::setCompany(Company* pCompany) {
    if (pCompany)
        pCompany->addPlane(*this);
    else if (this->pCompany)
        this->pCompany->removePlane(*this);
}

void Plane::setId() {  // TESTED
    id = generateId();
    addVector(usedIds, id);
}

void Plane::setName(std::string name) {  // TESTED
    if (!name.size())
        throw InvalidName("Name must contain any character");

    this->name = name;
}

void Plane::setCapacityPassengers(const unsigned int number) {  // TESTED
    if (!flights.empty())
        throw CannotPerform("Cannot modify. Plane is in use");
    if (!number)
        throw InvalidNumber("Number of passengers cannot be 0");

    this->capacityPassengers = number;
}

void Plane::setRequiredStewardesses(const unsigned int number) {  // TESTED
    if (!flights.empty())
        throw CannotPerform("Cannot modify. Plane is in use");
    if (!number)
        throw InvalidNumber("Number of stewardess cannot be 0");

    this->capacityStewardesses = number * 2;
    this->requiredStewardesses = number;
}

void Plane::setRequiredPilots(const unsigned int number) {  // TESTED
    if (!flights.empty())
        throw CannotPerform("Cannot modify. Plane is in use");
    if (!number)
        throw InvalidNumber("Number of pilots cannot be 0");

    this->capacityPilots = number * 2;
    this->requiredPilots = number;
}

bool Plane::inRangePassengers(unsigned int number) const {  // TESTED
    return capacityPassengers >= number;
}

bool Plane::inRangeStewardesses(unsigned int number) const {  // TESTED
    return requiredStewardesses <= number && number <= capacityStewardesses;
}

bool Plane::maximumStewardesses(const unsigned int number) const {  // TESTED
    return number > capacityStewardesses;
}

bool Plane::inRangePilots(unsigned int number) const {  // TESTED
    return requiredPilots <= number && number <= capacityPilots;
}

bool Plane::maximumPilots(const unsigned int number) const {  // TESTED
    return number > capacityPilots;
}

bool Plane::inRangeCrew(const unsigned int stewardess, const unsigned int pilots) const {  // TESTED
    return inRangeStewardesses(stewardess) && inRangePilots(pilots);
}

void Plane::addFlight(Flight& flight) {  // TESTED
    flight.setPlane(*this);
}

bool Plane::removeFlight(Flight& flight) {  // TESTED
    return flight.removePlane();
}

bool Plane::removeFlights() {  // TESTED
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
       << "Company: " << plane.getCompany() << " "
       << "Flights: " << plane.getFlights().size() << std::endl;

    return os;
}

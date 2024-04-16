#include "Plane.hpp"

#include <iostream>

#include "CustomErrors.hpp"
#include "VectorHandler.hpp"

std::vector<unsigned int> Plane::usedIds;

Plane::Plane(Company* pCompany,
             unsigned int id,
             std::string name,
             unsigned int capacityPassengers,
             unsigned int requiredStewardess,
             unsigned int requiredPilots) : Plane(id, name, capacityPassengers, requiredStewardess, requiredPilots) {
    setCompany(pCompany);
}

Plane::Plane(unsigned int id,
             std::string name,
             unsigned int capacityPassengers,
             unsigned int requiredStewardess,
             unsigned int requiredPilots) : pCompany{nullptr} {
    setId(id);
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

Company*& Plane::getCompany() {
    return pCompany;
}

std::vector<std::reference_wrapper<Flight>>& Plane::getFlights() {
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

void Plane::setCompany(Company* pCompany) {
    if (!pCompany)
        throw InvalidPointer("Invalid company object");
    if (flights.size())
        throw CannotPerform("Cannot modify. Plane is in use");
    if (this->pCompany == pCompany)
        return;

    this->pCompany = pCompany;
}

void Plane::changeId(const unsigned int id) {
    unsigned int oldId = this->id;
    setId(id);
    deleteVector(usedIds, oldId);
}

void Plane::setId(const unsigned int id) {
    if (existVector(usedIds, id))
        throw NonUniqueIDException();

    addVector(usedIds, id);
    this->id = id;
}

void Plane::setName(std::string name) {
    if (!name.size())
        throw InvalidName("Name must contain any character");

    this->name = name;
}

void Plane::setCapacityPassengers(const unsigned int number) {
    if (flights.size())
        throw CannotPerform("Cannot modify. Plane is in use");
    if (!number)
        throw InvalidNumber("Number of passengers cannot be 0");

    this->capacityPassengers = number;
}

void Plane::setRequiredStewardesses(const unsigned int number) {
    if (flights.size())
        throw CannotPerform("Cannot modify. Plane is in use");
    if (!number)
        throw InvalidNumber("Number of stewardess cannot be 0");

    this->capacityStewardesses = number * 2;
    this->requiredStewardesses = number;
}

void Plane::setRequiredPilots(const unsigned int number) {
    if (flights.size())
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
    return number > capacityStewardesses;
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
    for (Flight& flight : flights)
        success = removeFlight(flight) && success;

    return success;
}

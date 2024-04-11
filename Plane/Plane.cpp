#include "Plane.hpp"

#include <iostream>

#include "CustomErrors.hpp"
#include "VectorHandler.hpp"

std::vector<unsigned int> Plane::usedIds = {};

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
    if (flights.size())
        throw CannotPerform("Cannot modify. Plane is in use");
    if (!pCompany)
        throw InvalidPointer("Invalid company object");

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

    usedIds.push_back(id);
    this->id = id;
}

void Plane::setName(std::string name) {
    if (name.size() == 0)
        throw InvalidName("Name must contain any character");

    this->name = name;
}

void Plane::setCapacityPassengers(const unsigned int number) {
    if (flights.size())
        throw CannotPerform("Cannot modify. Plane is in use");
    this->capacityPassengers = number;
}

void Plane::setRequiredStewardesses(const unsigned int number) {
    if (flights.size())
        throw CannotPerform("Cannot modify. Plane is in use");

    this->capacityStewardesses = number * 2;
    this->requiredStewardesses = number;
}

void Plane::setRequiredPilots(const unsigned int number) {
    if (flights.size())
        throw CannotPerform("Cannot modify. Plane is in use");

    this->capacityPilots = number * 2;
    this->requiredPilots = number;
}

bool Plane::inRangePassengers(unsigned int number) const {
    return capacityPassengers >= number;
}

bool Plane::inRangePassengers(const std::vector<Passenger*>& passengers) const {
    return inRangePassengers(passengers.size());
}

bool Plane::inRangeStewardesses(unsigned int number) const {
    return requiredStewardesses <= number && number <= capacityStewardesses;
}

bool Plane::inRangeStewardesses(const std::vector<CrewMember*>& stewardesses) const {
    return inRangeStewardesses(stewardesses.size());
}

bool Plane::inRangePilots(unsigned int number) const {
    return requiredPilots <= number && number <= capacityPilots;
}

bool Plane::inRangePilots(const std::vector<CrewMember*>& pilots) const {
    return inRangePilots(pilots.size());
}

bool Plane::inRangeCrew(const std::vector<CrewMember*>& stewardesses, const std::vector<CrewMember*>& pilots) const {
    return inRangeStewardesses(stewardesses) && inRangePilots(pilots);
}

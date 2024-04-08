#include "Plane.h"

#include <iostream>

#include "CustomErrors.h"
#include "VectorHandler.h"

std::vector<unsigned int> Plane::usedIds = {};

Plane::Plane(unsigned int id,
             std::string name,
             unsigned int capacityPassengers,
             unsigned int requiredStewardess,
             unsigned int requiredPilots) : flights{{}} {
    setId(id);
    setName(name);

    setCapacityPassengers(capacityPassengers);
    setRequiredStewardess(requiredStewardess);
    setRequiredPilots(requiredPilots);

    this->capacityStewardess = requiredStewardess * 2;
    this->capacityPilots = requiredPilots * 2;
}

Plane::~Plane() {
    deleteVector(usedIds, id);
}

unsigned int Plane::getId() {
    return id;
}

std::string Plane::getName() {
    return name;
}

unsigned int Plane::getCapacityPassengers() {
    return capacityPassengers;
}

unsigned int Plane::getRequiredStewardess() {
    return requiredStewardess;
}

unsigned int Plane::getCapacityStewardess() {
    return capacityStewardess;
}

unsigned int Plane::getRequiredPilots() {
    return requiredPilots;
}

unsigned int Plane::getCapacityPilots() {
    return capacityPilots;
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
    this->capacityPassengers = number;
}

void Plane::setRequiredStewardess(const unsigned int number) {
    this->capacityStewardess = number * 2;
    this->requiredStewardess = number;
}

void Plane::setRequiredPilots(const unsigned int number) {
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
    return requiredStewardess <= number && number <= capacityStewardess;
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

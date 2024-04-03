#include "Plane.h"

#include <iostream>

#include "Utils/CustomErrors.h"
#include "Utils/VectorHandler.h"

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
    popFromVector(usedIds, id);
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

unsigned int Plane::getRequiredPilots() {
    return requiredPilots;
}

void Plane::setId(const unsigned int id) {
    if (existInVector(usedIds, id))
        throw NonUniqueIDException();

    usedIds.push_back(id);
    this->id = id;
}

void Plane::setName(const std::string name) {
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

bool Plane::inRangePassengers(unsigned int number) {
    return capacityPassengers >= number;
}

bool Plane::inRangePassengers(const std::vector<Passenger*>& passengers) {
    return inRangePassengers(passengers.size());
}

bool Plane::inRangeStewardesses(unsigned int number) {
    return requiredStewardess <= number && number <= capacityStewardess;
}

bool Plane::inRangeStewardesses(const std::vector<CrewMember*>& stewardesses) {
    return inRangeStewardesses(stewardesses.size());
}

bool Plane::inRangePilots(unsigned int number) {
    return requiredPilots <= number && number <= capacityPilots;
}

bool Plane::inRangePilots(const std::vector<CrewMember*>& pilots) {
    return inRangePilots(pilots.size());
}

bool Plane::inRangeCrew(const std::vector<CrewMember*>& stewardesses, const std::vector<CrewMember*>& pilots) {
    return inRangeStewardesses(stewardesses) && inRangePilots(pilots);
}

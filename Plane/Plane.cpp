#include "Plane.h"

#include <iostream>

#include "Utils/CustomErrors.h"
#include "Utils/VectorHandler.h"

std::vector<unsigned int> Plane::usedIds = {};

Plane::Plane(unsigned int& id,
             std::string& name,
             unsigned int& capacityPassengers,
             unsigned int& requiredStewardess,
             unsigned int& requiredPilots) : flights{{}},
                                             capacityStewardess{requiredStewardess * 2},
                                             capacityPilots{requiredPilots * 2} {
    setId(id);
    setName(name);
    setCapacityPassengers(capacityPassengers);
    setRequiredStewardess(requiredStewardess);
    setRequiredPilots(requiredPilots);
    setStatus(OPERATING);
}

void Plane::setName(const std::string& name) {
    this->name = name;
}

// void Plane::setStatus(const PlaneStatus& status) {
//     this->status = status;

//     if (!flights.size())
//         return;

//     switch (status) {
//         case OPERATING:
//             // CHANGE ALL PLANE FLIGHTS THAT HAVE ALL CREW TO AS_PLANNED
//             break;
//         case MAINTENANCE:
//             // CHANGE ALL PLANE FLIGHTS TO ON_HOLD
//             break;
//     }
// }

void Plane::setCapacityPassengers(const unsigned int& number) {
    this->capacityPassengers = number;
}

void Plane::setRequiredStewardess(const unsigned int& number) {
    this->requiredStewardess = number;
}

void Plane::setRequiredPilots(const unsigned int& number) {
    this->requiredPilots = number;
}

const unsigned int& Plane::getCapacityPassengers() {
    return capacityPassengers;
}

const unsigned int& Plane::getRequiredStewardess() {
    return requiredStewardess;
}

const unsigned int& Plane::getRequiredPilots() {
    return requiredPilots;
}

bool Plane::inRangePassengers(unsigned int number) {
    return capacityPassengers >= number;
}

bool Plane::inRangePassengers(std::vector<Passenger*> passengers) {
    return inRangePassengers(passengers.size());
}

bool Plane::inRangeStewardesses(unsigned int number) {
    return requiredStewardess <= number <= capacityStewardess;
}

bool Plane::inRangeStewardesses(std::vector<CrewMember*> stewardesses) {
    return inRangeStewardesses(stewardesses.size());
}

bool Plane::inRangePilots(unsigned int number) {
    return requiredPilots <= number <= capacityPilots;
}

bool Plane::inRangePilots(std::vector<CrewMember*> pilots) {
    return inRangePilots(pilots.size());
}

bool Plane::inRangeCrew(std::vector<CrewMember*> stewardesses, std::vector<CrewMember*> pilots) {
    return inRangeStewardesses(stewardesses) && inRangePilots(pilots);
}

// void Plane::addFlight(Flight*& pFlight) {
//     // CHANGE PLANE IN FLIGHT
//     if (status == OPERATING)
//         flights.push_back(pFlight);
//     else
//         std::cout << "Cannot add flight. Plane status is set to: " << status;
// }

void Plane::setId(const unsigned int& id) {
    if (FindInVector(usedIds, id) != usedIds.end())
        throw NonUniqueIDException();

    usedIds.push_back(id);
    this->id = id;
}

#include "Company.hpp"

#include <iostream>

#include "CustomErrors.hpp"
#include "ListHandler.hpp"
#include "VectorHandler.hpp"

Company::Company(std::string name) {
    setName(name);
}

Company::~Company() {
    removeFlights();
    removePlanes();
    removeCrewMembers();
}

void Company::setName(std::string name) {
    if (!name.size())
        throw InvalidName("First name must contain any character");

    this->name = name;
}

std::list<Flight>& Company::getFlights() {
    return flights;
}

std::vector<std::reference_wrapper<Plane>>& Company::getPlanes() {
    return planes;
}

std::vector<std::reference_wrapper<CrewMember>>& Company::getStewardesses() {
    return stewardesses;
}

std::vector<std::reference_wrapper<CrewMember>>& Company::getPilots() {
    return pilots;
}

void Company::addPlane(Plane& plane) {
    Company*& pCompany = plane.getCompany();

    if (pCompany == this)
        return;
    if (pCompany)
        pCompany->removePlane(plane);

    pCompany = this;
    planes.push_back(plane);
}

bool Company::removePlane(Plane& plane) {
    Company*& pCompany = plane.getCompany();

    if (pCompany != this)
        return false;

    plane.removeFlights();
    pCompany = nullptr;

    return deleteVector(planes, plane);
}

bool Company::removePlanes() {
    bool success = true;

    for (auto plane : planes)
        success = removePlane(plane) && success;

    return success;
}

void Company::addCrewMember(CrewMember& crewMember) {
    Company*& pCompany = crewMember.getCompany();

    if (pCompany == this)
        return;
    if (pCompany)
        pCompany->removeCrewMember(crewMember);

    pCompany = this;
    if (crewMember.getRole())
        stewardesses.push_back(crewMember);
    else
        pilots.push_back(crewMember);
}

bool Company::removeCrewMember(CrewMember& crewMember) {
    Company*& pCompany = crewMember.getCompany();

    if (pCompany != this)
        return false;

    crewMember.removeFlights();
    pCompany = nullptr;

    return deleteVector(crewMember.getRole() ? stewardesses : pilots, crewMember);
}

bool Company::removeCrewMembers() {
    bool success = true;

    for (auto stewardess : stewardesses)
        success = removeCrewMember(stewardess) && success;
    for (auto pilot : pilots)
        success = removeCrewMember(pilot) && success;

    return success;
}

Flight& Company::createFlight(std::string flightNr,
                              Plane& plane,
                              unsigned int timeDeparture,
                              unsigned int timeArrival,
                              std::string cityDeparture,
                              std::string cityArrival) {
    flights.push_back((Flight){this, flightNr, plane, timeDeparture, timeArrival, cityDeparture, cityArrival});
    return flights.back();
}

Flight& Company::createFlight(std::string flightNr,
                              unsigned int timeDeparture,
                              unsigned int timeArrival,
                              std::string cityDeparture,
                              std::string cityArrival) {
    flights.push_back((Flight){this, flightNr, timeDeparture, timeArrival, cityDeparture, cityArrival});
    return flights.back();
}

bool Company::removeFlight(Flight& flight) {
    Company*& pCompany = flight.getCompany();

    if (pCompany != this)
        return false;

    return deleteList(flights, flight);
}

bool Company::removeFlights() {
    bool success = true;

    for (auto flight : flights)
        success = removeFlight(flight) && success;

    return success;
}
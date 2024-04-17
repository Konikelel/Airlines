#include "Company.hpp"

#include <iostream>

#include "CustomErrors.hpp"
#include "ListHandler.hpp"
#include "VectorHandler.hpp"

Company::Company(std::string name) {
    setName(name);
}

Company::~Company() {
    removePlanes();
    removeCrewMembers();
    removeFlights();
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

    plane.pCompany = this;
    addVector(planes, plane);
}

bool Company::removePlane(Plane& plane) {
    if (plane.pCompany != this)
        return false;

    plane.removeFlights();

    plane.pCompany = nullptr;
    return deleteVector(planes, plane);
}

bool Company::removePlanes() {
    bool success = true;

    for (Plane& plane : planes)
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
    addVector(crewMember.getRole() ? stewardesses : pilots, crewMember);
}

bool Company::removeCrewMember(CrewMember& crewMember) {
    if (crewMember.pCompany != this)
        return false;

    crewMember.removeFlights();

    crewMember.pCompany = nullptr;
    return deleteVector(crewMember.getRole() ? stewardesses : pilots, crewMember);
}

bool Company::removeCrewMembers() {
    bool success = true;

    for (CrewMember& stewardess : stewardesses)
        success = removeCrewMember(stewardess) && success;
    for (CrewMember& pilot : pilots)
        success = removeCrewMember(pilot) && success;

    return success;
}

Flight& Company::createFlight(std::string flightNr,
                              Plane& plane,
                              unsigned int timeDeparture,
                              unsigned int timeArrival,
                              std::string cityDeparture,
                              std::string cityArrival) {
    Flight& newElement = addList(flights, (Flight){this, flightNr, timeDeparture, timeArrival, cityDeparture, cityArrival});
    newElement.setPlane(plane);
    return newElement;
}

Flight& Company::createFlight(std::string flightNr,
                              unsigned int timeDeparture,
                              unsigned int timeArrival,
                              std::string cityDeparture,
                              std::string cityArrival) {
    return addList(flights, (Flight){this, flightNr, timeDeparture, timeArrival, cityDeparture, cityArrival});
}

bool Company::removeFlight(Flight& flight) {
    if (flight.pCompany != this)
        return false;

    flight.removePlane();
    flight.removePassengers();
    flight.removeCrewMembers();

    flight.pCompany = nullptr;
    return deleteList(flights, flight);
}

bool Company::removeFlights() {
    flights.clear();
    return true;
}
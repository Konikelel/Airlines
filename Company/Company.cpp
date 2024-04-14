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
}

void Company::setName(std::string name) {
    if (!name.size())
        throw InvalidName("First name must contain any character");

    this->name = name;
}

std::vector<std::reference_wrapper<Plane>>& Company::getPlanes() {
    return planes;
}

std::list<Flight>& Company::getFlights() {
    return flights;
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

    deleteList(flights, flight);
    flight.removeCrewMembers();
    flight.removePassengers();
    return true;
}

bool Company::removeFlights() {
    bool success = true;

    for (auto flight : flights)
        success = removeFlight(flight) && success;

    return success;
}

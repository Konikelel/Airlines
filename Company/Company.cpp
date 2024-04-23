#include "Company.hpp"

#include <iostream>

#include "CustomErrors.hpp"
#include "ListHandler.hpp"
#include "VectorHandler.hpp"

Company::Company(std::string name) {  // TESTED
    setName(name);
}

Company::~Company() {  // TESTED
    removePlanes();
    removeCrewMembers();
    removeFlights();
}

std::string Company::getName() {  // TESTED
    return name;
}

void Company::setName(std::string name) {  // TESTED
    if (!name.size())
        throw InvalidName("First name must contain any character");

    this->name = name;
}

std::list<Flight>& Company::getFlights() {  // TESTED
    return flights;
}

std::vector<std::reference_wrapper<Plane>>& Company::getPlanes() {  // TESTED
    return planes;
}

std::vector<std::reference_wrapper<CrewMember>>& Company::getStewardesses() {  // TESTED
    return stewardesses;
}

std::vector<std::reference_wrapper<CrewMember>>& Company::getPilots() {  // TESTED
    return pilots;
}

void Company::addPlane(Plane& plane) {  // TESTED
    Company*& pCompany = plane.getCompany();

    if (pCompany == this)
        return;
    if (pCompany)
        pCompany->removePlane(plane);

    plane.pCompany = this;
    addVector(planes, plane);
}

bool Company::removePlane(Plane& plane) {  // TESTED
    if (plane.pCompany != this)
        return false;

    plane.removeFlights();

    plane.pCompany = nullptr;
    return deleteVector(planes, plane);
}

bool Company::removePlanes() {  // TESTED
    bool success = true;

    for (Plane& plane : planes) {
        success = plane.removeFlights() && success;
        plane.pCompany = nullptr;
    }

    planes.clear();
    return success;
}

void Company::addCrewMember(CrewMember& crewMember) {  // TESTED
    Company*& pCompany = crewMember.getCompany();

    if (pCompany == this)
        return;
    if (pCompany)
        pCompany->removeCrewMember(crewMember);

    pCompany = this;
    addVector(crewMember.getRole() ? stewardesses : pilots, crewMember);
}

bool Company::removeCrewMember(CrewMember& crewMember) {  // TESTED
    if (crewMember.pCompany != this)
        return false;

    crewMember.removeFlights();

    crewMember.pCompany = nullptr;
    return deleteVector(crewMember.getRole() ? stewardesses : pilots, crewMember);
}

bool Company::removeCrewMembers() {  // TESTED
    bool success = true;

    for (CrewMember& stewardess : stewardesses) {
        success = stewardess.removeFlights() && success;
        stewardess.pCompany = nullptr;
    }
    for (CrewMember& pilot : pilots) {
        success = pilot.removeFlights() && success;
        pilot.pCompany = nullptr;
    }

    stewardesses.clear();
    pilots.clear();
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
}  // TESTED

Flight& Company::createFlight(std::string flightNr,
                              unsigned int timeDeparture,
                              unsigned int timeArrival,
                              std::string cityDeparture,
                              std::string cityArrival) {
    return addList(flights, (Flight){this, flightNr, timeDeparture, timeArrival, cityDeparture, cityArrival});
}  // TESTED

bool Company::removeFlight(Flight& flight) {
    if (flight.pCompany != this)
        return false;

    flight.removePlane();
    flight.removePassengers();
    flight.removeCrewMembers();

    flight.pCompany = nullptr;
    return deleteList(flights, flight);
}  // TESTED

bool Company::removeFlights() {
    for (Flight& flight : flights) {
        flight.removePlane();
        flight.removePassengers();
        flight.removeCrewMembers();
    }

    flights.clear();
    return true;
}  // TESTED
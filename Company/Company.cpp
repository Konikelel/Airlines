#include "Company.hpp"

#include <iostream>

#include "CustomErrors.hpp"
#include "ListHandler.hpp"
#include "SetHandler.hpp"

Company::Company(std::string name) {  // TESTED
    setName(name);
}

Company::~Company() {  // TESTED
    removePlanes();
    removeCrewMembers();
    removeFlights();
}

std::string Company::getName() const {  // TESTED
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

std::set<std::reference_wrapper<Plane>>& Company::getPlanes() {  // TESTED
    return planes;
}

std::set<std::reference_wrapper<CrewMember>>& Company::getStewardesses() {  // TESTED
    return stewardesses;
}

std::set<std::reference_wrapper<CrewMember>>& Company::getPilots() {  // TESTED
    return pilots;
}

void Company::addPlane(Plane& plane) {  // TESTED
    Company*& pCompany = plane.getCompany();

    if (pCompany == this)
        return;
    if (pCompany)
        pCompany->removePlane(plane);

    plane.pCompany = this;
    addSet(planes, plane);
}

bool Company::removePlane(Plane& plane) {  // TESTED
    if (plane.pCompany != this)
        return false;

    plane.removeFlights();

    plane.pCompany = nullptr;
    return deleteSet(planes, plane);
}

bool Company::removePlanes() {  // TESTED
    bool success = true;

    for (auto it = planes.begin(); it != planes.end();)
        success = removePlane(*(it++)) && success;

    return success;
}

void Company::addCrewMember(CrewMember& crewMember) {  // TESTED
    Company*& pCompany = crewMember.getCompany();

    if (pCompany == this)
        return;
    if (pCompany)
        pCompany->removeCrewMember(crewMember);

    crewMember.pCompany = this;
    addSet(crewMember.getRole() ? stewardesses : pilots, crewMember);
}

bool Company::removeCrewMember(CrewMember& crewMember) {  // TESTED
    if (crewMember.pCompany != this)
        return false;

    crewMember.removeFlights();

    crewMember.pCompany = nullptr;
    return deleteSet(crewMember.getRole() ? stewardesses : pilots, crewMember);
}

bool Company::removeCrewMembers() {  // TESTED
    bool success = true;

    for (auto it = stewardesses.begin(); it != stewardesses.end();)
        success = removeCrewMember(*(it++)) && success;

    for (auto it = pilots.begin(); it != pilots.end();)
        success = removeCrewMember(*(it++)) && success;

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

bool Company::removeFlight(Flight& flight) {  // TESTED
    if (flight.pCompany != this)
        return false;

    flight.removePlane();
    flight.removePassengers();
    flight.removeCrewMembers();

    flight.pCompany = nullptr;
    return deleteList(flights, flight);
}

bool Company::removeFlights() {  // TESTED
    bool success = true;

    for (auto it = flights.begin(); it != flights.end();)
        success = removeFlight(*(it++)) && success;

    return success;
}

std::ostream& operator<<(std::ostream& os, Company& company) {
    os << "Name: " << company.getName() << std::endl;

    std::list<Flight> flights = company.getFlights();
    if (flights.size())
        os << "Flights: " << std::endl;
    for (Flight& flight : flights)
        os << "\t* " << flight << std::endl;

    std::set<std::reference_wrapper<Plane>> planes = company.getPlanes();
    if (!planes.empty())
        os << "Planes: " << std::endl;
    for (Plane& plane : planes)
        os << "\t* " << plane << std::endl;

    std::set<std::reference_wrapper<CrewMember>> stewardesses = company.getStewardesses();
    if (!stewardesses.empty())
        os << "Stewardesses: " << std::endl;
    for (CrewMember& stewardess : stewardesses)
        os << "\t* " << stewardess << std::endl;

    std::set<std::reference_wrapper<CrewMember>> pilots = company.getPilots();
    if (!pilots.empty())
        os << "Pilots: " << std::endl;
    for (CrewMember& pilot : pilots)
        os << "\t* " << pilot << std::endl;

    return os;
}

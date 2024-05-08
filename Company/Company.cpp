#include "Company.hpp"

#include <iostream>

#include "CustomErrors.hpp"
#include "ListHandler.hpp"
#include "SetHandler.hpp"

Company::Company(std::string name) {
    setName(name);
}

Company::~Company() {
    removePlanes();
    removeCrewMembers();
    removeFlights();
}

std::string Company::getName() const {
    return name;
}

void Company::setName(const std::string name) {
    if (!name.size())
        throw InvalidName("First name must contain any character");

    this->name = name;
}

std::list<Flight>& Company::getFlights() {
    return flights;
}

std::set<std::reference_wrapper<Plane>>& Company::getPlanes() {
    return planes;
}

std::set<std::reference_wrapper<CrewMember>>& Company::getStewardesses() {
    return stewardesses;
}

std::set<std::reference_wrapper<CrewMember>>& Company::getPilots() {
    return pilots;
}

void Company::addPlane(Plane& plane) {
    plane.setCompany(this);
}

bool Company::removePlane(Plane& plane) {
    if (plane.getCompany() != this)
        return false;

    return plane.setCompany(nullptr);
}

bool Company::removePlanes() {
    bool success = true;

    for (auto it = planes.begin(); it != planes.end();)
        success = removePlane(*(it++)) && success;

    return success;
}

void Company::addCrewMember(CrewMember& crewMember) {
    crewMember.setCompany(this);
}

bool Company::removeCrewMember(CrewMember& crewMember) {
    if (crewMember.getCompany() != this)
        return false;

    return crewMember.setCompany(nullptr);
}

bool Company::removeCrewMembers() {
    bool success = true;

    for (auto it = stewardesses.begin(); it != stewardesses.end();)
        success = removeCrewMember(*(it++)) && success;

    for (auto it = pilots.begin(); it != pilots.end();)
        success = removeCrewMember(*(it++)) && success;

    return success;
}

Flight& Company::createFlight(std::string flightNr,
                              Plane& plane,
                              unsigned long long timeDeparture,
                              unsigned long long timeArrival,
                              std::string cityDeparture,
                              std::string cityArrival) {
    Flight& newElement = addList(flights, (Flight){this, flightNr, timeDeparture, timeArrival, cityDeparture, cityArrival});
    newElement.setPlane(plane);
    return newElement;
}

Flight& Company::createFlight(std::string flightNr,
                              unsigned long long timeDeparture,
                              unsigned long long timeArrival,
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
    bool success = true;

    for (auto it = flights.begin(); it != flights.end();)
        success = removeFlight(*(it++)) && success;

    return success;
}

std::set<std::reference_wrapper<CrewMember>> Company::availableCrewMembers(unsigned long long timeStart, unsigned long long timeEnd, CrewRole role) {
    std::set<std::reference_wrapper<CrewMember>> crewMembers;
    bool hasTimeOverlap;

    for (CrewMember& crewMember : (role ? stewardesses : pilots)) {
        hasTimeOverlap = false;

        for (Flight flight : crewMember.getFlights())
            if (flight.timeOverlap(timeStart, timeEnd)) {
                hasTimeOverlap = true;
                break;
            }

        if (!hasTimeOverlap)
            addSet(crewMembers, crewMember);
    }
    return crewMembers;
}

std::ostream& operator<<(std::ostream& os, Company& company) {
    os << "Name: " << company.getName() << std::endl;

    std::list<Flight> flights = company.getFlights();
    if (flights.size())
        os << "Flights: " << std::endl;
    for (Flight& flight : flights)
        os << "\t* " << flight;

    std::set<std::reference_wrapper<Plane>> planes = company.getPlanes();
    if (!planes.empty())
        os << "Planes: " << std::endl;
    for (Plane& plane : planes)
        os << "\t* " << plane;

    std::set<std::reference_wrapper<CrewMember>> stewardesses = company.getStewardesses();
    if (!stewardesses.empty())
        os << "Stewardesses: " << std::endl;
    for (CrewMember& stewardess : stewardesses)
        os << "\t* " << stewardess;

    std::set<std::reference_wrapper<CrewMember>> pilots = company.getPilots();
    if (!pilots.empty())
        os << "Pilots: " << std::endl;
    for (CrewMember& pilot : pilots)
        os << "\t* " << pilot;

    return os;
}

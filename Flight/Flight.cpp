#include "Flight.hpp"

#include <cctype>
#include <iostream>

#include "Company.hpp"
#include "CrewMember.hpp"
#include "CustomErrors.hpp"
#include "ListHandler.hpp"
#include "Passenger.hpp"
#include "Plane.hpp"
#include "StringHandler.hpp"
#include "VectorHandler.hpp"

Flight::Flight(Company* pCompany,
               std::string flightNr,
               unsigned int timeDeparture,
               unsigned int timeArrival,
               std::string cityDeparture,
               std::string cityArrival) : pPlane{nullptr},
                                          status{INCOMPLETE} {
    setupCompany(pCompany);
    setFlightNr(flightNr);
    setDataTime(timeDeparture, cityDeparture, timeArrival, cityArrival);
}

Company* Flight::getCompany() {
    return pCompany;
}

std::string Flight::getFlightNr() const {
    return flightNr;
}

FlightStatus Flight::getStatus() const {
    return status;
}

Plane* Flight::getPlane() const {
    return pPlane;
}

unsigned int Flight::getTimeDeparture() const {
    return timeDeparture;
}

unsigned int Flight::getTimeArrival() const {
    return timeArrival;
}

std::string Flight::getCityDeparture() const {
    return cityDeparture;
}

std::string Flight::getCityArrival() const {
    return cityArrival;
}

std::vector<std::reference_wrapper<Passenger>>& Flight::getPassengers() {
    return passengers;
}

std::vector<std::reference_wrapper<CrewMember>>& Flight::getStewardesses() {
    return stewardesses;
}

std::vector<std::reference_wrapper<CrewMember>>& Flight::getPilots() {
    return pilots;
}

void Flight::setFlightNr(std::string flightNr) {
    if (flightNr.size() < 4)
        throw InvalidFlightNr("Flight number must be longer than 3 symbols");
    if (flightNr.size() > 7)
        throw InvalidFlightNr("Flight number must be shorter than 8 symbols");

    for (char& symbol : flightNr.substr(0, 3))
        if (!std::isalpha(symbol))
            throw InvalidFlightNr("First three symbols in flight number must be letters");

    this->flightNr = toUpper(flightNr);
}

void Flight::setPlane(Plane& plane) {
    if (!plane.inRangePassengers(passengers.size()))
        throw InvalidPlane("Plane cannot accommodate all passengers");

    if (plane.maximumStewardesses(stewardesses.size()))
        throw InvalidPlane("Plane cannot accommodate all stewardesses");

    if (plane.maximumPilots(pilots.size()))
        throw InvalidPlane("Plane cannot accommodate all pilots");

    for (Flight& flight : plane.getFlights())
        if (timeOverlap(flight))
            throw TimeOverlap("Passenger is on other flight. Cannot add flight");

    removePlane();
    setupPlane(plane);
}

bool Flight::removePlane() {
    bool success = false;

    if (pPlane)
        success = deleteVector(pPlane->getFlights(), *this);

    pPlane = nullptr;
    return success;
}

void Flight::changeDataDeparture(const unsigned int time) {
    setDataTime(time, timeArrival);
}

void Flight::changeDataArrival(const unsigned int time) {
    setDataTime(timeDeparture, time);
}

void Flight::changeDataDeparture(const unsigned int time, const std::string city) {
    if (!city.size())
        throw InvalidName("City departure must contain any character");

    changeDataDeparture(time);
    this->cityDeparture = city;
}

void Flight::changeDataArrival(const unsigned int time, const std::string city) {
    if (!city.size())
        throw InvalidName("City arrival must contain any character");

    changeDataArrival(time);
    this->cityArrival = city;
}

void Flight::addPassenger(Passenger& passenger) {
    if (pPlane && !pPlane->inRangePassengers(passengers.size() + 1))
        throw MaximumCapacity("Maximum capacity for passengers reached");
    if (existVector(passengers, passenger))
        throw DuplicationError("Passenger is already on the flight");

    for (Flight& flight : passenger.getFlights())
        if (timeOverlap(flight))
            throw TimeOverlap("Passenger is on other flight. Cannot add flight");

    addVector(passengers, passenger);
    addVector(passenger.getFlights(), *this);
}

bool Flight::removePassenger(Passenger& passenger) {
    return deleteVector(passengers, passenger) && deleteVector(passenger.getFlights(), *this);
}

bool Flight::removePassengers() {
    bool success = true;
    for (Passenger& passenger : passengers)
        success = removePassenger(passenger) && success;
    return success;
}

void Flight::addCrewMember(CrewMember& crewMember) {
    CrewRole role = crewMember.getRole();

    if (crewMember.getCompany() != pCompany)
        throw InvalidCrew("CrewMember must be in the same company as flight");

    if (pPlane && (role ? pPlane->maximumStewardesses(stewardesses.size()) : pPlane->maximumPilots(pilots.size())))
        throw MaximumCapacity("Maximum capacity for crewMember reached");

    if (existVector(role ? stewardesses : pilots, crewMember))
        throw DuplicationError("CrewMember is already on the flight");

    for (Flight& flight : crewMember.getFlights())
        if (timeOverlap(flight))
            throw TimeOverlap("CrewMember is on other flight. Cannot add flight");

    addVector(role ? stewardesses : pilots, crewMember);
    addVector(crewMember.getFlights(), *this);
    setStatus();
}

bool Flight::removeCrewMember(CrewMember& crewMember) {
    CrewRole role = crewMember.getRole();

    setStatus();
    return deleteVector(role ? stewardesses : pilots, crewMember) && deleteVector(crewMember.getFlights(), *this);
}

bool Flight::removeCrewMembers() {
    bool success = true;

    for (CrewMember& crewMember : stewardesses)
        success = removeCrewMember(crewMember) && success;

    for (CrewMember& crewMember : pilots)
        success = removeCrewMember(crewMember) && success;
    return success;
}

bool Flight::timeOverlap(const Flight& flight) const {
    return timeOverlap(flight.getTimeDeparture(), flight.getTimeArrival());
}

bool Flight::timeOverlap(const unsigned int timeStart, const unsigned int timeEnd) const {
    return !(timeDeparture > timeEnd || timeArrival < timeStart);
}

void Flight::setStatus() {
    status = (pPlane && pPlane->inRangeCrew(stewardesses.size(), pilots.size())) ? AS_PLANNED : INCOMPLETE;
}

// PRIVATE
void Flight::setupCompany(Company* pCompany) {
    if (pPlane && pPlane->getCompany() != pCompany)
        throw InvalidPlane("Plane must be from the same company");

    this->pCompany = pCompany;
}

void Flight::setupPlane(Plane& plane) {
    if (plane.getCompany() != pCompany)
        throw InvalidPlane("Plane must be from the same company");

    this->pPlane = &plane;
    addVector(plane.getFlights(), *this);
    setStatus();
}

void Flight::setDataTime(const unsigned int timeDeparture, const unsigned int timeArrival) {
    if (passengers.size() || stewardesses.size() || pilots.size())
        throw CannotPerform("Flight is already booked");
    if (timeArrival <= timeDeparture)
        throw InvalidTime("Arrival and Departure time is invalid");

    this->timeDeparture = timeDeparture;
    this->timeArrival = timeArrival;
}

void Flight::setDataTime(const unsigned int timeDeparture, const std::string cityDeparture, const unsigned int timeArrival, const std::string cityArrival) {
    if (!cityDeparture.size())
        throw InvalidName("City departure must contain any character");
    if (!cityArrival.size())
        throw InvalidName("City arrival must contain any character");
    setDataTime(timeDeparture, timeArrival);

    this->cityDeparture = cityDeparture;
    this->cityArrival = cityArrival;
}
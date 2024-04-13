#include "Flight.hpp"

#include <cctype>
#include <iostream>

#include "Company.hpp"
#include "CrewMember.hpp"
#include "CustomErrors.hpp"
#include "Passenger.hpp"
#include "Plane.hpp"
#include "StringHandler.hpp"
#include "VectorHandler.hpp"

Flight::Flight(Company* pCompany,
               std::string flightNr,
               Plane* pPlane,
               unsigned int timeDeparture,
               unsigned int timeArrival,
               std::string cityDeparture,
               std::string cityArrival) : Flight(pCompany, flightNr, timeDeparture, timeArrival, cityDeparture, cityArrival) {
    setupPlane(pPlane);
}

Flight::Flight(Company* pCompany,
               std::string flightNr,
               unsigned int timeDeparture,
               unsigned int timeArrival,
               std::string cityDeparture,
               std::string cityArrival) : pPlane{nullptr} {
    setupCompany(pCompany);
    setFlightNr(flightNr);
    setDataTime(timeDeparture, cityDeparture, timeArrival, cityArrival);
}

std::string Flight::getFlightNr() const {
    return flightNr;
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

std::vector<Passenger*>& Flight::getPassengers() {
    return passengers;
}

std::vector<CrewMember*>& Flight::getStewardesses() {
    return stewardesses;
}

std::vector<CrewMember*>& Flight::getPilots() {
    return pilots;
}

void Flight::setFlightNr(std::string flightNr) {
    if (flightNr.size() < 4)
        throw InvalidFlightNr("Flight number must be longer than 3 symbols");
    if (flightNr.size() > 7)
        throw InvalidFlightNr("Flight number must be shorter than 8 symbols");

    for (auto& symbol : flightNr.substr(0, 3))
        if (!std::isalpha(symbol))
            throw InvalidFlightNr("First three symbols in flight number must be letters");

    this->flightNr = toUpper(flightNr);
}

void Flight::setPlane(Plane* pPlane) {
    if (!pPlane)
        throw InvalidPointer("Invalid plane object");

    if (!pPlane->inRangePassengers(passengers.size()))
        throw InvalidPlane("Plane cannot accommodate all passengers");

    if (!pPlane->inRangeStewardesses(stewardesses.size()))
        throw InvalidPlane("Plane cannot operate with the current number of stewardess");

    if (!pPlane->inRangePilots(pilots.size()))
        throw InvalidPlane("Plane cannot operate with the current number of pilots");

    for (auto pFlight : pPlane->getFlights())
        if (timeOverlap(pFlight))
            throw TimeOverlap("Passenger is on other flight. Cannot add flight");

    removePlane();
    setupPlane(pPlane);
}

bool Flight::removePlane() {
    bool success = deleteVector(pPlane->getFlights(), this);
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

void Flight::addPassenger(Passenger* pPassenger) {
    if (pPlane && !pPlane->inRangePassengers(passengers.size() + 1))
        throw MaximumCapacity("Maximum capacity for passengers reached");
    if (existVector(passengers, pPassenger))
        throw DuplicationError("Passenger is already on the flight");

    for (auto pFlight : pPassenger->getFlights())
        if (timeOverlap(pFlight))
            throw TimeOverlap("Passenger is on other flight. Cannot add flight");

    passengers.push_back(pPassenger);
    pPassenger->getFlights().push_back(this);
}

bool Flight::removePassenger(Passenger* pPassenger) {
    return deleteVector(passengers, pPassenger) && deleteVector(pPassenger->getFlights(), this);
}

void Flight::addCrewMember(CrewMember* pCrewMember) {
    CrewRole role = pCrewMember->getRole();
    if (pCrewMember->getCompany() != pCompany)
        throw InvalidCrew("CrewMember must be in the same company as flight");
    if (pPlane && !(role ? pPlane->inRangeStewardesses(stewardesses.size() + 1) : pPlane->inRangePilots(pilots.size() + 1)))
        throw MaximumCapacity("Maximum capacity for crewMember reached");
    if (existVector(role ? stewardesses : pilots, pCrewMember))
        throw DuplicationError("CrewMember is already on the flight");

    for (auto pFlight : pCrewMember->getFlights())
        if (timeOverlap(pFlight))
            throw TimeOverlap("CrewMember is on other flight. Cannot add flight");

    role ? stewardesses.push_back(pCrewMember) : pilots.push_back(pCrewMember);
    pCrewMember->getFlights().push_back(this);
}

bool Flight::removeCrewMember(CrewMember* pCrewMember) {
    CrewRole role = pCrewMember->getRole();

    if (pPlane && !(role ? pPlane->inRangeStewardesses(stewardesses.size() - 1) : pPlane->inRangePilots(pilots.size() - 1)))
        throw MinimumCapacity("Cannot remove crewMember. Required number to operate flight reached");

    return deleteVector(role ? stewardesses : pilots, pCrewMember) && deleteVector(pCrewMember->getFlights(), this);
}

bool Flight::timeOverlap(const Flight* pFlight) {
    return timeOverlap(pFlight->getTimeDeparture(), pFlight->getTimeArrival());
}

bool Flight::timeOverlap(const unsigned int timeStart, const unsigned int timeEnd) {
    return !(timeDeparture > timeEnd || timeArrival < timeStart);
}

// PRIVATE
void Flight::setupCompany(Company* pCompany) {
    if (!pCompany)
        throw InvalidPointer("Invalid company object");
    if (pPlane && pPlane->getCompany() != pCompany)
        throw InvalidPlane("Plane must be from the same company");

    this->pCompany = pCompany;
    // pPlane->getFlights().push_back(this);
}

void Flight::setupPlane(Plane* pPlane) {
    if (!pPlane)
        throw InvalidPointer("Invalid plane object");
    if (pPlane->getCompany() != pCompany)
        throw InvalidPlane("Plane must be from the same company");

    this->pPlane = pPlane;
    pPlane->getFlights().push_back(this);
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
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
               std::string cityArrival) : pCompany{pCompany},
                                          pPlane{nullptr},
                                          status{INCOMPLETE} {
    setFlightNr(flightNr);
    setDataTime(timeDeparture, cityDeparture, timeArrival, cityArrival);
}

Company* Flight::getCompany() {  // TESTED
    return pCompany;
}

std::string Flight::getFlightNr() const {  // TESTED
    return flightNr;
}

FlightStatus Flight::getStatus() const {  // TESTED
    return status;
}

Plane* Flight::getPlane() const {  // TESTED
    return pPlane;
}

unsigned int Flight::getTimeDeparture() const {  // TESTED
    return timeDeparture;
}

unsigned int Flight::getTimeArrival() const {  // TESTED
    return timeArrival;
}

std::string Flight::getCityDeparture() const {  // TESTED
    return cityDeparture;
}

std::string Flight::getCityArrival() const {  // TESTED
    return cityArrival;
}

std::vector<std::reference_wrapper<Passenger>>& Flight::getPassengers() {  // TESTED
    return passengers;
}

std::vector<std::reference_wrapper<CrewMember>>& Flight::getStewardesses() {  // TESTED
    return stewardesses;
}

std::vector<std::reference_wrapper<CrewMember>>& Flight::getPilots() {  // TESTED
    return pilots;
}

void Flight::setFlightNr(std::string flightNr) {  // TESTED
    if (flightNr.size() < 4)
        throw InvalidFlightNr("Flight number must be longer than 3 symbols");
    if (flightNr.size() > 7)
        throw InvalidFlightNr("Flight number must be shorter than 8 symbols");

    for (char& symbol : flightNr.substr(0, 3))
        if (!std::isalpha(symbol))
            throw InvalidFlightNr("First three symbols in flight number must be letters");

    this->flightNr = toUpper(flightNr);
}

void Flight::setPlane(Plane& plane) {  // TESTED
    if (!plane.inRangePassengers(passengers.size()))
        throw InvalidPlane("Plane cannot accommodate all passengers");

    if (plane.maximumStewardesses(stewardesses.size()))
        throw InvalidPlane("Plane cannot accommodate all stewardesses");

    if (plane.maximumPilots(pilots.size()))
        throw InvalidPlane("Plane cannot accommodate all pilots");

    for (Flight& flight : plane.getFlights())
        if (timeOverlap(flight))
            throw TimeOverlap("Plane is on other flight. Cannot add flight");

    removePlane();
    setupPlane(plane);
}

bool Flight::removePlane() {  // TESTED
    bool success = false;

    if (pPlane)
        success = deleteVector(pPlane->getFlights(), *this);

    pPlane = nullptr;
    return success;
}

void Flight::changeDataDeparture(const unsigned int time) {  // TESTED
    setDataTime(time, timeArrival);
}

void Flight::changeDataArrival(const unsigned int time) {  // TESTED
    setDataTime(timeDeparture, time);
}

void Flight::changeDataDeparture(const unsigned int time, const std::string city) {  // TESTED
    if (!city.size())
        throw InvalidName("City departure must contain any character");

    changeDataDeparture(time);
    this->cityDeparture = city;
}

void Flight::changeDataArrival(const unsigned int time, const std::string city) {  // TESTED
    if (!city.size())
        throw InvalidName("City arrival must contain any character");

    changeDataArrival(time);
    this->cityArrival = city;
}

void Flight::addPassenger(Passenger& passenger) {  // TESTED
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

bool Flight::removePassenger(Passenger& passenger) {  // TESTED
    return deleteVector(passengers, passenger) && deleteVector(passenger.getFlights(), *this);
}

bool Flight::removePassengers() {  // TESTED
    bool success = true;

    for (Passenger& passenger : passengers)
        success = deleteVector(passenger.getFlights(), *this) && success;
    passengers.clear();

    return success;
}

void Flight::addCrewMember(CrewMember& crewMember) {  // TESTED
    CrewRole role = crewMember.getRole();

    if (crewMember.getCompany() != pCompany)
        throw InvalidCrew("CrewMember must be in the same company as flight");

    if (pPlane && (role ? pPlane->maximumStewardesses(stewardesses.size() + 1) : pPlane->maximumPilots(pilots.size() + 1)))
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

bool Flight::removeCrewMember(CrewMember& crewMember) {  // TESTED
    CrewRole role = crewMember.getRole();

    setStatus();
    return deleteVector(role ? stewardesses : pilots, crewMember) && deleteVector(crewMember.getFlights(), *this);
}

bool Flight::removeCrewMembers() {  // TESTED
    bool success = true;
    status = INCOMPLETE;

    for (CrewMember& crewMember : stewardesses)
        success = deleteVector(crewMember.getFlights(), *this) && success;
    for (CrewMember& crewMember : pilots)
        success = deleteVector(crewMember.getFlights(), *this) && success;

    stewardesses.clear();
    pilots.clear();
    return success;
}

bool Flight::timeOverlap(const Flight& flight) const {  // TESTED
    return timeOverlap(flight.getTimeDeparture(), flight.getTimeArrival());
}

bool Flight::timeOverlap(const unsigned int timeStart, const unsigned int timeEnd) const {  // TESTED
    return !(timeDeparture > timeEnd || timeArrival < timeStart);
}

void Flight::setStatus() {  // TESTED
    status = (pPlane && pPlane->inRangeCrew(stewardesses.size(), pilots.size())) ? AS_PLANNED : INCOMPLETE;
}
// PRIVATE

void Flight::setupPlane(Plane& plane) {  // TESTED
    if (plane.getCompany() != pCompany)
        throw InvalidPlane("Plane must be from the same company");

    this->pPlane = &plane;
    addVector(plane.getFlights(), *this);
    setStatus();
}

void Flight::setDataTime(const unsigned int timeDeparture, const unsigned int timeArrival) {  // TESTED
    if (passengers.size() || stewardesses.size() || pilots.size())
        throw CannotPerform("Flight is already booked");
    if (timeArrival <= timeDeparture)
        throw InvalidTime("Arrival and Departure time is invalid");

    this->timeDeparture = timeDeparture;
    this->timeArrival = timeArrival;
}

void Flight::setDataTime(const unsigned int timeDeparture, const std::string cityDeparture, const unsigned int timeArrival, const std::string cityArrival) {  // TESTED
    if (!cityDeparture.size())
        throw InvalidName("City departure must contain any character");
    if (!cityArrival.size())
        throw InvalidName("City arrival must contain any character");
    setDataTime(timeDeparture, timeArrival);

    this->cityDeparture = cityDeparture;
    this->cityArrival = cityArrival;
}
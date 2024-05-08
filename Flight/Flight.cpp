#include "Flight.hpp"

#include <cctype>
#include <iostream>

#include "Company.hpp"
#include "CrewMember.hpp"
#include "CustomErrors.hpp"
#include "IdGenerator.hpp"
#include "ListHandler.hpp"
#include "Passenger.hpp"
#include "Plane.hpp"
#include "SetHandler.hpp"
#include "StringHandler.hpp"
#include "VectorHandler.hpp"

std::vector<unsigned int> Flight::usedIds;

Flight::Flight(Company* pCompany,
               std::string flightNr,
               unsigned long long timeDeparture,
               unsigned long long timeArrival,
               std::string cityDeparture,
               std::string cityArrival) : pCompany{pCompany},
                                          pPlane{nullptr},
                                          status{INCOMPLETE} {
    setId();
    setFlightNr(flightNr);
    setDataTime(timeDeparture, cityDeparture, timeArrival, cityArrival);
}

void Flight::setId() {
    id = generateUniqueId(usedIds);
    addVector(usedIds, id);
}

Flight::~Flight() {
    deleteVector(usedIds, id);
}

Company* Flight::getCompany() const {  // TESTED
    return pCompany;
}

unsigned int Flight::getId() const {
    return id;
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

unsigned long long Flight::getTimeDeparture() const {  // TESTED
    return timeDeparture;
}

unsigned long long Flight::getTimeArrival() const {  // TESTED
    return timeArrival;
}

std::string Flight::getCityDeparture() const {  // TESTED
    return cityDeparture;
}

std::string Flight::getCityArrival() const {  // TESTED
    return cityArrival;
}

std::set<std::reference_wrapper<Passenger>>& Flight::getPassengers() {  // TESTED
    return passengers;
}

std::set<std::reference_wrapper<CrewMember>>& Flight::getStewardesses() {  // TESTED
    return stewardesses;
}

std::set<std::reference_wrapper<CrewMember>>& Flight::getPilots() {  // TESTED
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
        success = deleteSet(pPlane->getFlights(), *this);

    status = INCOMPLETE;
    pPlane = nullptr;
    return success;
}

void Flight::changeDataDeparture(const unsigned long long time) {  // TESTED
    setDataTime(time, timeArrival);
}

void Flight::changeDataArrival(const unsigned long long time) {  // TESTED
    setDataTime(timeDeparture, time);
}

void Flight::changeDataDeparture(const unsigned long long time, const std::string city) {  // TESTED
    if (!city.size())
        throw InvalidName("City departure must contain any character");

    changeDataDeparture(time);
    this->cityDeparture = city;
}

void Flight::changeDataArrival(const unsigned long long time, const std::string city) {  // TESTED
    if (!city.size())
        throw InvalidName("City arrival must contain any character");

    changeDataArrival(time);
    this->cityArrival = city;
}

void Flight::addPassenger(Passenger& passenger) {  // TESTED
    if (pPlane && !pPlane->inRangePassengers(passengers.size() + 1))
        throw MaximumCapacity("Maximum capacity for passengers reached");
    if (existSet(passengers, passenger))
        throw DuplicationError("Passenger is already on the flight");

    for (Flight& flight : passenger.getFlights())
        if (timeOverlap(flight))
            throw TimeOverlap("Passenger is on other flight. Cannot add flight");

    addSet(passengers, passenger);
    addSet(passenger.getFlights(), *this);
}

bool Flight::removePassenger(Passenger& passenger) {  // TESTED
    return deleteSet(passengers, passenger) && deleteSet(passenger.getFlights(), *this);
}

bool Flight::removePassengers() {  // TESTED
    bool success = true;

    for (auto it = passengers.begin(); it != passengers.end();)
        success = removePassenger(*(it++)) && success;

    return success;
}

void Flight::addCrewMember(CrewMember& crewMember) {  // TESTED
    CrewRole role = crewMember.getRole();

    if (crewMember.getCompany() != pCompany)
        throw InvalidCrew("CrewMember must be in the same company as flight");

    if (pPlane && (role ? pPlane->maximumStewardesses(stewardesses.size() + 1) : pPlane->maximumPilots(pilots.size() + 1)))
        throw MaximumCapacity("Maximum capacity for crewMember reached");

    if (existSet(role ? stewardesses : pilots, crewMember))
        throw DuplicationError("CrewMember is already on the flight");

    for (Flight& flight : crewMember.getFlights())
        if (timeOverlap(flight))
            throw TimeOverlap("CrewMember is on other flight. Cannot add flight");

    addSet(role ? stewardesses : pilots, crewMember);
    addSet(crewMember.getFlights(), *this);
    setStatus();
}

bool Flight::removeCrewMember(CrewMember& crewMember) {  // TESTED
    CrewRole role = crewMember.getRole();

    bool success = deleteSet(role ? stewardesses : pilots, crewMember) && deleteSet(crewMember.getFlights(), *this);
    setStatus();
    return success;
}

bool Flight::removeCrewMembers() {  // TESTED
    bool success = true;
    status = INCOMPLETE;

    for (CrewMember& crewMember : stewardesses)
        success = deleteSet(crewMember.getFlights(), *this) && success;
    for (CrewMember& crewMember : pilots)
        success = deleteSet(crewMember.getFlights(), *this) && success;

    stewardesses.clear();
    pilots.clear();
    return success;
}

bool Flight::timeOverlap(const Flight& flight) const {  // TESTED
    return timeOverlap(flight.getTimeDeparture(), flight.getTimeArrival());
}

bool Flight::timeOverlap(const unsigned long long timeStart, const unsigned long long timeEnd) const {  // TESTED
    return !(timeDeparture > timeEnd || timeArrival < timeStart);
}

bool Flight::operator==(const Flight& other) const {
    return this->flightNr == other.flightNr && this->timeDeparture == other.timeDeparture && this->timeArrival == other.timeArrival;
}

void Flight::setStatus() {  // TESTED
    status = (pPlane && pPlane->inRangeCrew(stewardesses.size(), pilots.size())) ? AS_PLANNED : INCOMPLETE;
}
// PRIVATE

void Flight::setupPlane(Plane& plane) {  // TESTED
    if (plane.getCompany() != pCompany)
        throw InvalidPlane("Plane must be from the same company");

    this->pPlane = &plane;
    addSet(plane.getFlights(), *this);
    setStatus();
}

void Flight::setDataTime(const unsigned long long timeDeparture, const unsigned long long timeArrival) {  // TESTED
    if (passengers.size() || stewardesses.size() || pilots.size())
        throw CannotPerform("Flight is already booked");
    if (timeArrival <= timeDeparture)
        throw InvalidTime("Arrival and Departure time is invalid");

    this->timeDeparture = timeDeparture;
    this->timeArrival = timeArrival;
}

void Flight::setDataTime(const unsigned long long timeDeparture, const std::string cityDeparture, const unsigned long long timeArrival, const std::string cityArrival) {  // TESTED
    if (!cityDeparture.size())
        throw InvalidName("City departure must contain any character");
    if (!cityArrival.size())
        throw InvalidName("City arrival must contain any character");
    setDataTime(timeDeparture, timeArrival);

    this->cityDeparture = cityDeparture;
    this->cityArrival = cityArrival;
}

bool operator==(const std::reference_wrapper<Flight>& one, const Flight& other) {
    return one.get().id == other.id;
}

bool operator<(const std::reference_wrapper<Flight>& one, const std::reference_wrapper<Flight>& other) {
    return one.get().id < other.get().id;
}

std::ostream& operator<<(std::ostream& os, Flight& flight) {
    os << "Id: " << flight.getId() << " "
       << "FlightNr: " << flight.getFlightNr() << " "
       << "Status: " << (flight.getStatus() ? "AS_PLANNED" : "INCOMPLETE") << " "
       << "Departure: " << flight.getCityDeparture() << " "
       << "Arrival: " << flight.getCityArrival() << std::endl;

    return os;
}
#include "Flight.h"

#include <cctype>
#include <iostream>

#include "CrewMember/CrewMember.h"
#include "Passenger/Passenger.h"
#include "Plane/Plane.h"
#include "Utils/CustomErrors.h"
#include "Utils/StringHandler.h"
#include "Utils/VectorHandler.h"

Flight::Flight(std::string& flightNr,
               FlightStatus& status,
               Plane*& pPlane,
               unsigned int& timeDeparture,
               unsigned int& timeArrival,
               std::string& cityDeparture,
               std::string& cityArrival,
               std::vector<CrewMember*>& stewardesses,
               std::vector<CrewMember*>& pilots) : Flight(flightNr, status, pPlane, timeDeparture, timeArrival, cityDeparture, cityArrival) {
    setStewardess(stewardesses);
    setPilots(pilots);
}

Flight::Flight(std::string& flightNr,
               FlightStatus& status,
               Plane*& pPlane,
               unsigned int& timeDeparture,
               unsigned int& timeArrival,
               std::string& cityDeparture,
               std::string& cityArrival) : Flight(flightNr, status, timeDeparture, timeArrival, cityDeparture, cityArrival) {
    setPlane(pPlane);
}

Flight::Flight(std::string& flightNr,
               FlightStatus& status,
               unsigned int& timeDeparture,
               unsigned int& timeArrival,
               std::string& cityDeparture,
               std::string& cityArrival) : pPlane{nullptr},
                                           pilots{{}},
                                           stewardesses{{}},
                                           passengers{{}} {
    setFlightNr(flightNr);
    setStatus(status);
    setDataDeparture(timeDeparture, cityDeparture);
    setDataArrival(timeArrival, cityArrival);
}

void Flight::setFlightNr(std::string& flightNr) {
    if (flightNr.size() < 4)
        throw InvalidFlightNr("Flight number must be longer than 3 symbols");
    if (flightNr.size() > 7)
        throw InvalidFlightNr("Flight number must be shorter than 8 symbols");

    for (auto& symbol : flightNr.substr(0, 3))
        if (!std::isalpha(symbol))
            throw InvalidFlightNr("First three symbols in flight number must be letters");

    this->flightNr = toUpper(flightNr);
}

void Flight::setPlane(Plane*& pPlane) {
    if (!pPlane->inRangePassengers(passengers))
        throw InvalidPlane("Plane cannot accommodate all passengers");

    if (!pPlane->inRangeStewardesses(stewardesses))
        throw InvalidPlane("Plane cannot operate with the current stewardess");

    if (!pPlane->inRangePilots(pilots))
        throw InvalidPlane("Plane cannot operate with the current pilots");

    this->pPlane = pPlane;
}

void Flight::setDataDeparture(const unsigned int& time) {
    if (timeArrival <= time)
        throw InvalidTime("Arrival time is invalid compared to departure time");

    this->timeDeparture = time;
}

void Flight::setDataArrival(const unsigned int& time) {
    if (timeDeparture <= time)
        throw InvalidTime("Departure time is invalid compared to arrival time");

    this->timeArrival = time;
}

void Flight::setDataDeparture(const unsigned int& time, std::string& city) {
    setDataDeparture(time);
    this->cityDeparture = toTitle(city);
}

void Flight::setDataArrival(const unsigned int& time, std::string& city) {
    setDataArrival(time);
    this->cityArrival = toTitle(city);
}

void Flight::setStewardess(std::vector<CrewMember*>& stewardesses) {
    if (pPlane && pPlane->inRangeStewardesses(getNrValidCrewMembers(stewardesses)))
        throw InvalidCrew("Available stewardesses cannot operate the plane");

    this->stewardesses = stewardesses;
}

void Flight::setPilots(std::vector<CrewMember*>& pilots) {
    if (pPlane && getNrValidCrewMembers(pilots) != pPlane->getRequiredPilots())
        throw InvalidCrew("Available pilots cannot operate the plane");

    this->pilots = pilots;
}

unsigned int& Flight::getTimeDeparture() {
    return timeDeparture;
}

unsigned int& Flight::getTimeArrival() {
    return timeArrival;
}

void Flight::addPassenger(Passenger*& pPassenger) {
    if (pPlane && pPlane->inRangePassengers(passengers.size() + 1))
        throw MaximumCapacity("Maximum capacity for passengers reached");

    this->passengers.push_back(pPassenger);
}

bool Flight::removePassenger(Passenger*& pPassenger) {
    auto iPassenger = PopFromVector(passengers, pPassenger);
    return iPassenger != passengers.end();
}

void Flight::addStewardess(CrewMember*& pStewardess) {
    if (pPlane && pPlane->inRangeStewardesses(stewardesses.size() + 1))
        throw MaximumCapacity("Maximum capacity for stewardesses reached");

    this->stewardesses.push_back(pStewardess);
}

bool Flight::removeStewardess(CrewMember*& pStewardess) {
    auto iStewardess = PopFromVector(stewardesses, pStewardess);
    return iStewardess != stewardesses.end();
}

void Flight::addPilots(CrewMember*& pPilot) {
    if (pPlane && pPlane->inRangePilots(pilots.size() + 1))
        throw MaximumCapacity("Maximum capacity for pilots reached");

    this->pilots.push_back(pPilot);
}

bool Flight::removePilots(CrewMember*& pPilot) {
    auto iPilot = PopFromVector(pilots, pPilot);
    return iPilot != pilots.end();
}

int& Flight::getNrValidCrewMembers(std::vector<CrewMember*>& crew) {
    int validNr = crew.size();
    for (auto& member : crew)
        if (member->isBusy(timeDeparture, timeArrival))
            validNr--;

    return validNr;
}

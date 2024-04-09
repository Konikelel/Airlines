#include "Flight.hpp"

#include <cctype>
#include <iostream>

#include "CrewMember.hpp"
#include "CustomErrors.hpp"
#include "Passenger.hpp"
#include "Plane.hpp"
#include "StringHandler.hpp"
#include "VectorHandler.hpp"

Flight::Flight(std::string flightNr,
               std::shared_ptr<Plane> pPlane,
               unsigned int timeDeparture,
               unsigned int timeArrival,
               std::string cityDeparture,
               std::string cityArrival) : Flight(flightNr, timeDeparture, timeArrival, cityDeparture, cityArrival) {
    setPlane(pPlane);
}

Flight::Flight(std::string flightNr,
               unsigned int timeDeparture,
               unsigned int timeArrival,
               std::string cityDeparture,
               std::string cityArrival) : pPlane{nullptr},
                                          passengers{{}},
                                          stewardesses{{}},
                                          pilots{{}} {
    setFlightNr(flightNr);
    setDataTime(timeDeparture, cityDeparture, timeArrival, cityArrival);
}

std::string Flight::getFlightNr() const {
    return flightNr;
}

Plane* Flight::getPlane() const {
    return pPlane.get();
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

void Flight::changePlane(std::shared_ptr<Plane> pPlane) {
    if (!pPlane->inRangePassengers(passengers))
        throw InvalidPlane("Plane cannot accommodate all passengers");

    if (!pPlane->inRangeStewardesses(stewardesses))
        throw InvalidPlane("Plane cannot operate with the current number of stewardess");

    if (!pPlane->inRangePilots(pilots))
        throw InvalidPlane("Plane cannot operate with the current number of pilots");

    setPlane(pPlane);
}

void Flight::setPlane(std::shared_ptr<Plane> pPlane) {
    this->pPlane = pPlane;
}

void Flight::setDataTime(const unsigned int timeDeparture, const unsigned int timeArrival) {
    if (timeArrival <= timeDeparture)
        throw InvalidTime("Arrival and Departure time is invalid compared to arrival time");

    this->timeDeparture = timeDeparture;
    this->timeArrival = timeArrival;
}

void Flight::setDataTime(const unsigned int timeDeparture, const std::string cityDeparture, const unsigned int timeArrival, const std::string cityArrival) {
    setDataTime(timeDeparture, timeArrival);

    this->cityDeparture = cityDeparture;
    this->cityArrival = cityArrival;
}

void Flight::changeDataDeparture(const unsigned int time) {
    if (timeArrival <= time)
        throw InvalidTime("Arrival time is invalid compared to departure time");

    this->timeDeparture = time;
}

void Flight::changeDataArrival(const unsigned int time) {
    if (time <= timeDeparture)
        throw InvalidTime("Departure time is invalid compared to arrival time");

    this->timeArrival = time;
}

void Flight::changeDataDeparture(const unsigned int time, const std::string city) {
    changeDataDeparture(time);
    this->cityDeparture = toTitle(city);
}

void Flight::changeDataArrival(const unsigned int time, const std::string city) {
    changeDataArrival(time);
    this->cityArrival = toTitle(city);
}

void Flight::addPassenger(Passenger* const pPassenger) {
    if (existPassenger(pPassenger))
        throw DuplicationError("Passenger is already on the flight");

    passengers.push_back(pPassenger);

    Flight* pFlight = this;
    if (!pPassenger->existFlight(pFlight))
        pPassenger->addFlight(pFlight);
}

bool Flight::removePassenger(Passenger* pPassenger) {
    bool success = deleteVector(passengers, pPassenger);

    Flight* pFlight = this;
    pPassenger->removeFlight(pFlight);

    return success;
}

bool Flight::existPassenger(Passenger* pPassenger) {
    return existVector(passengers, pPassenger);
}

bool Flight::timeOverlap(const unsigned int timeStart, const unsigned int timeEnd) {
    return !(timeDeparture > timeEnd || timeArrival < timeStart);
}

// PRIVATE

int Flight::nrValidCrewMembers(const std::vector<CrewMember*>& crew) {
    int validNr = crew.size();
    for (auto& member : crew) {
        if (member->isBusy(timeDeparture, timeArrival))
            validNr--;
    }

    return validNr;
}

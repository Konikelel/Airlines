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
               Plane*& pPlane,
               unsigned int& timeDeparture,
               unsigned int& timeArrival,
               std::string& cityDeparture,
               std::string& cityArrival) : Flight(flightNr, timeDeparture, timeArrival, cityDeparture, cityArrival) {
    setPlane(pPlane);
}

Flight::Flight(std::string& flightNr,
               unsigned int& timeDeparture,
               unsigned int& timeArrival,
               std::string& cityDeparture,
               std::string& cityArrival) : pPlane{nullptr},
                                           pilots{{}},
                                           stewardesses{{}},
                                           passengers{{}} {
    setFlightNr(flightNr);
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
        throw InvalidPlane("Plane cannot operate with the current number of stewardess");

    if (!pPlane->inRangePilots(pilots))
        throw InvalidPlane("Plane cannot operate with the current number of pilots");

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

void Flight::addPassenger(Passenger*& pPassenger) {
    if (existPassenger(pPassenger))
        throw DuplicationError("Passenger is already on the flight");

    passengers.push_back(pPassenger);

    Flight* pFlight = this;
    if (!pPassenger->existFlight(pFlight))
        pPassenger->addFlight(pFlight);
}

bool Flight::existPassenger(Passenger*& pPassenger) {
    return FindInVector(passengers, pPassenger) != passengers.end();
}

bool Flight::timeOverlap(unsigned int& timeStart, unsigned int& timeEnd) {
    return !(timeDeparture > timeEnd || timeArrival < timeStart);
}

// PRIVATE

int Flight::nrValidCrewMembers(std::vector<CrewMember*>& crew) {
    int validNr = crew.size();
    for (auto& member : crew) {
        if (member->isBusy(timeDeparture, timeArrival))
            validNr--;
    }

    return validNr;
}

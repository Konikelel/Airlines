#include "Flight.h"

#include <cctype>
#include <iostream>

#include "CrewMember/CrewMember.h"
#include "Passenger/Passenger.h"
#include "Plane/Plane.h"
#include "Utils/CustomErrors.h"
#include "Utils/StringHandler.h"

Flight::Flight(std::string& flightNr,
               FlightStatus& status,
               Plane*& pPlane,
               unsigned int& timeDeparture,
               unsigned int& timeArrival,
               std::string& cityDeparture,
               std::string& cityArrival,
               std::vector<CrewMember*>& stewardesses,
               std::vector<CrewMember*>& pilots) {
    setPlane(pPlane);
    setStewardess(stewardesses);
    setPilots(pilots);
}

Flight::Flight(std::string& flightNr,
               FlightStatus& status, Plane*& pPlane,
               unsigned int& timeDeparture,
               unsigned int& timeArrival,
               std::string& cityDeparture,
               std::string& cityArrival) {
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
        throw InvalidFlightNr("Name must be longer than 3 symbols");
    if (flightNr.size() > 7)
        throw InvalidFlightNr("Name must be shorter than 8 symbols");

    for (auto& symbol : flightNr.substr(0, 3))
        if (!std::isalpha(symbol))
            throw InvalidFlightNr("First three symbols must be letters");

    this->flightNr = toUpper(flightNr);
}

void Flight::setStatus(const FlightStatus& status) {  // ADD CANCELED
    if (!pPlane || !pPlane->operationalCrew(stewardesses, pilots)) {
        std::cout << "Plane unavailable or invalid number of crew. Set Flight status to ON_HOLD";
        this->status = ON_HOLD;
    } else
        this->status = status;
}

void Flight::setPlane(Plane*& pPlane) {
    if (pPlane->passengersMax(passengers))
        throw InvalidPlane("Passengers exceed the capacity");

    if (!pPlane->operationalCrew(stewardesses, pilots))
        throw InvalidPlane("Insufficient crew or crew exced the limit of the plane");

    this->pPlane = pPlane;
}

void Flight::setDataDeparture(const unsigned int& time) {
    if (timeArrival <= time)
        throw InvalidTime("Time arrival is earlier or the same as time departure");

    this->timeDeparture = time;
}

void Flight::setDataArrival(const unsigned int& time) {
    if (timeDeparture <= time)
        throw InvalidTime("Time departure is later or the same as time arrival");

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
    if (pPlane && getNrValidCrewMembers(stewardesses) != pPlane->getRequiredStewardess())
        throw InvalidCrew("Available stewardesses are not sufficient for plane");

    this->stewardesses = stewardesses;
}

void Flight::setPilots(std::vector<CrewMember*>& pilots) {
    if (pPlane && getNrValidCrewMembers(pilots) != pPlane->getRequiredPilots())
        throw InvalidCrew("Available pilots are not sufficient for plane");

    this->pilots = pilots;
}

int& Flight::getNrValidCrewMembers(std::vector<CrewMember*>& crew) {
    int validNr = crew.size();
    for (auto& member : crew)
        if (member->isBusy(timeDeparture, timeArrival))
            validNr--;

    return validNr;
}

unsigned int& Flight::getTimeDeparture() {
    return timeDeparture;
}

unsigned int& Flight::getTimeArrival() {
    return timeArrival;
}

#include "Passenger.hpp"

#include "CustomErrors.hpp"
#include "VectorHandler.hpp"

Passenger::Passenger(unsigned int id,
                     std::string nameFirst,
                     std::string nameSecond,
                     unsigned int timeBirthday,
                     Gender gender) : Person(id, nameFirst, nameSecond, timeBirthday, gender) {
}

Passenger::~Passenger() {
    removeFlights();
}

std::vector<Flight*>& Passenger::getFlights() {
    return flights;
}

void Passenger::addFlight(Flight* pFlight) {
    if (!pFlight)
        throw InvalidPointer("Invalid flight object");

    pFlight->addPassenger(this);
}

bool Passenger::removeFlight(Flight* pFlight) {
    if (!pFlight)
        throw InvalidPointer("Invalid flight object");

    return pFlight->removePassenger(this);
}

bool Passenger::removeFlights() {
    bool success = false;

    for (auto pFlight : flights)
        success = removeFlight(pFlight) && success;

    return success;
}

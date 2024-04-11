#include "Passenger.hpp"

#include "CustomErrors.hpp"
#include "VectorHandler.hpp"

Passenger::Passenger(unsigned int id,
                     std::string nameFirst,
                     std::string nameSecond,
                     unsigned int timeBirthday,
                     Gender gender) : Person(id, nameFirst, nameSecond, timeBirthday, gender),
                                      flights{{}} {
}

void Passenger::addFlight(Flight* pFlight) {
    if (!pFlight->existPassenger(this))  // Maybe unnecessary
        pFlight->addPassenger(this);

    if (existFlight(pFlight))
        throw DuplicationError("Passenger is already on the flight");

    flights.push_back(pFlight);
}

bool Passenger::removeFlight(Flight* pFlight) {
    bool success = deleteVector(flights, pFlight);

    pFlight->removePassenger(this);

    return success;
}

bool Passenger::existFlight(Flight* pFlight) {
    return existVector(flights, pFlight);
}

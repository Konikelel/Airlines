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
    Passenger* pPassenger = this;
    if (!pFlight->existPassenger(pPassenger))  // Maybe unnecessary
        pFlight->addPassenger(pPassenger);
    if (existFlight(pFlight))
        throw DuplicationError("Passenger is already on the flight");

    flights.push_back(pFlight);
}

bool Passenger::removeFlight(Flight* pFlight) {
    bool success = deleteVector(flights, pFlight);

    Passenger* pPassenger = this;
    pFlight->removePassenger(pPassenger);

    return success;
}

bool Passenger::existFlight(Flight* pFlight) {
    return existVector(flights, pFlight);
}

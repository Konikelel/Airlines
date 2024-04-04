#include "Passenger.h"

#include "Utils/CustomErrors.h"
#include "Utils/VectorHandler.h"

Passenger::Passenger(unsigned int id,
                     std::string nameFirst,
                     std::string nameSecond,
                     unsigned int timeBirthday,
                     Gender gender) : Person(id, nameFirst, nameSecond, timeBirthday, gender),
                                      flights{{}} {
}

void Passenger::addFlight(Flight* pFlight) {
    if (existFlight(pFlight))
        throw DuplicationError("Passenger is already on the flight");

    flights.push_back(pFlight);

    Passenger* pPassenger = this;
    if (!pFlight->existPassenger(pPassenger))  // Maybe unnecessary
        pFlight->addPassenger(pPassenger);
}

bool Passenger::removeFlight(Flight* pFlight) {
    bool success = deleteVector(flights, pFlight);

    Passenger* pPassenger = this;
    if (pFlight->existPassenger(pPassenger))
        pFlight->removePassenger(pPassenger);

    return success;
}

bool Passenger::existFlight(Flight* pFlight) {
    return existVector(flights, pFlight);
}

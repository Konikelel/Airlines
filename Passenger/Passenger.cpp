#include "Passenger.h"

Passenger::Passenger(unsigned int id,
                     std::string nameFirst,
                     std::string nameSecond,
                     unsigned int timeBirthday,
                     Gender gender) : Person(id, nameFirst, nameSecond, timeBirthday, gender) {
    this->flights = {};
}

void Passenger::addFlight(Flight*& pFlight) {
    this->flights.push_back(pFlight);
}

void Passenger::removeFlight(Flight*& pFlight) {
    // TO IMPLEMENT
}

void Passenger::removeFlights() {
    // TO IMPLEMENT
}

void Passenger::terminate() {
    // TO IMPLEMENT
}

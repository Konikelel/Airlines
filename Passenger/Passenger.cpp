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

std::vector<std::reference_wrapper<Flight>>& Passenger::getFlights() {
    return flights;
}

void Passenger::addFlight(Flight& flight) {
    flight.addPassenger(*this);
}

bool Passenger::removeFlight(Flight& flight) {
    return flight.removePassenger(*this);
}

bool Passenger::removeFlights() {
    bool success = true;

    for (auto flight : flights)
        success = removeFlight(flight) && success;

    return success;
}
#include "Passenger.hpp"

#include <iostream>

Passenger::Passenger(std::string nameFirst,
                     std::string nameSecond,
                     unsigned int timeBirthday,
                     Gender gender) : Person(nameFirst, nameSecond, timeBirthday, gender) {
}

Passenger::~Passenger() {  // TESTED
    removeFlights();
}

std::set<std::reference_wrapper<Flight>>& Passenger::getFlights() {  // TESTED
    return flights;
}

void Passenger::addFlight(Flight& flight) {  // TESTED
    flight.addPassenger(*this);
}

bool Passenger::removeFlight(Flight& flight) {  // TESTED
    return flight.removePassenger(*this);
}

bool Passenger::removeFlights() {  // TESTED
    bool success = true;

    for (auto it = flights.begin(); it != flights.end();)
        success = removeFlight(*(it++)) && success;

    return success;
}

bool operator==(const std::reference_wrapper<Passenger>& one, const Passenger& other) {
    return one.get().getId() == other.getId();
}

bool operator<(const std::reference_wrapper<Passenger>& one, const std::reference_wrapper<Passenger>& other) {
    return one.get().getId() < other.get().getId();
}

std::ostream& operator<<(std::ostream& os, Passenger& passenger) {
    os << "Id: " << passenger.getId() << " "
       << "Flights: " << passenger.getFlights().size() << std::endl;

    return os;
}

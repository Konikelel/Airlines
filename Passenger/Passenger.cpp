#include "Passenger.hpp"

#include <iostream>

#include "CustomErrors.hpp"
#include "VectorHandler.hpp"

Passenger::Passenger(unsigned int id,
                     std::string nameFirst,
                     std::string nameSecond,
                     unsigned int timeBirthday,
                     Gender gender) : Person(id, nameFirst, nameSecond, timeBirthday, gender) {
}

Passenger::~Passenger() {  // TESTED
    removeFlights();
}

std::vector<std::reference_wrapper<Flight>>& Passenger::getFlights() {  // TESTED
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

    for (Flight& flight : flights)
        success = deleteVector(flight.getPassengers(), *this) && success;

    flights.clear();
    return success;
}

std::ostream& operator<<(std::ostream& os, Passenger& passenger) {
    os << "Id: " << passenger.getId() << " "
       << "Flights: " << passenger.getFlights().size() << std::endl;

    return os;
}

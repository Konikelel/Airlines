#include <functional>
#include <set>
#include <string>

#ifndef PASSENGER_H
#define PASSENGER_H

#include "Flight.hpp"
#include "Person.hpp"

class Passenger : public Person {
   public:
    Passenger(
        std::string nameFirst,
        std::string nameSecond,
        unsigned int timeBirthday,
        Gender gender);

    ~Passenger();

    std::set<std::reference_wrapper<Flight>>& getFlights();

    // INVOKE FUNCTION FROM FLIGHT TO ADD PASSENGER
    void addFlight(Flight& flight);
    // INVOKE FUNCTION FROM FLIGHT TO REMOVE PASSENGER
    bool removeFlight(Flight& flight);

    // INVOKE FOR ALL FLIGHTS FUNCTION removeFlight
    bool removeFlights();

    friend bool operator==(const std::reference_wrapper<Passenger>& one, const Passenger& other);
    friend bool operator<(const std::reference_wrapper<Passenger>& one, const std::reference_wrapper<Passenger>& other);

   private:
    std::set<std::reference_wrapper<Flight>> flights;

    friend std::ostream& operator<<(std::ostream& os, Passenger& passenger);
};

#endif
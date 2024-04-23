#include <functional>
#include <string>
#include <vector>

#ifndef PASSENGER_H
#define PASSENGER_H

#include "Flight.hpp"
#include "Person.hpp"

class Passenger : public Person {
   public:
    Passenger(
        unsigned int id,
        std::string nameFirst,
        std::string nameSecond,
        unsigned int timeBirthday,
        Gender gender);

    ~Passenger();

    std::vector<std::reference_wrapper<Flight>>& getFlights();

    // INVOKE FUNCTION FROM FLIGHT TO ADD PASSENGER
    void addFlight(Flight& flight);
    // INVOKE FUNCTION FROM FLIGHT TO REMOVE PASSENGER
    bool removeFlight(Flight& flight);

    // INVOKE FOR ALL FLIGHTS FUNCTION removeFlight
    bool removeFlights();

   private:
    std::vector<std::reference_wrapper<Flight>> flights;

    friend std::ostream& operator<<(std::ostream& os, Passenger& passenger);
};

#endif
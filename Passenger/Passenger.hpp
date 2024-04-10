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

    // ADD FLIGHT POINTER TO PASSENGER, IF PASSENGER IS NOT ON THE FLIGHT, INVOKE FUNCTION IN FLIGHT TO ADD PASSENGER POINTER
    void addFlight(Flight* pFlight);
    // REMOVE FLIGHT POINTER FROM PASSENGER, IF PASSENGER IS ON THE FLIGHT, INVOKE FUNCTION IN FLIGHT TO REMOVE PASSENGER POINTER
    bool removeFlight(Flight* pFlight);

    // REMOVE ALL FLIGHTS FROM PASSENGER AND PASSENGER POINTERS FROM FLIGHTS
    bool removeFlights();

    // CHECK IF PASSENGER IS ON THE FLIGHT
    bool existFlight(Flight* pFlight);

   private:
    std::vector<Flight*> flights;
};

#endif
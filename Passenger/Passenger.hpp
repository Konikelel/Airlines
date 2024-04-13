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

    std::vector<Flight*>& getFlights();  // TEST

    // ADD FLIGHT POINTER TO PASSENGER, IF PASSENGER IS NOT ON THE FLIGHT, INVOKE FUNCTION IN FLIGHT TO ADD PASSENGER POINTER
    void addFlight(Flight* pFlight);  // TEST
    // REMOVE FLIGHT POINTER FROM PASSENGER, IF PASSENGER IS ON THE FLIGHT, INVOKE FUNCTION IN FLIGHT TO REMOVE PASSENGER POINTER
    bool removeFlight(Flight* pFlight);  // TEST

    // REMOVE ALL FLIGHTS FROM PASSENGER AND PASSENGER POINTERS FROM FLIGHTS
    bool removeFlights();  // TEST

   private:
    std::vector<Flight*> flights;
};

#endif
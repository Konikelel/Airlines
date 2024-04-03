#include <string>
#include <vector>

#ifndef PASSENGER_H
#define PASSENGER_H

#include "Flight/Flight.h"
#include "Person/Person.h"

class Passenger : public Person {
   public:
    Passenger(
        unsigned int id,
        std::string nameFirst,
        std::string nameSecond,
        unsigned int timeBirthday,
        Gender gender);

    void addFlight(Flight* pFlight);
    bool removeFlight(Flight* pFlight);  // BEST (const Flight* pFlight) const {} BUT ERRORS

    bool removeFlights();
    void terminate();

    bool existFlight(Flight* pFlight);

   private:
    std::vector<Flight*> flights;
};

#endif
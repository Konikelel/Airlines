#include <string>
#include <vector>

#ifndef PASSENGER_H
#define PASSENGER_H

#include "../Flight/Flight.h"
#include "../Person/Person.h"

class Passenger : public Person {
   public:
    Passenger(
        unsigned int& id,
        std::string& nameFirst,
        std::string& nameSecond,
        unsigned int& timeBirthday,
        Gender& gender);

    void addFlight(Flight*& pFlight);
    void removeFlight(Flight*& pFlight);

    void removeFlights();
    void terminate();

   private:
    std::vector<Flight*> flights;
};

#endif
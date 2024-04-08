#include <vector>

#ifndef CREW_MEMBER_H
#define CREW_MEMBER_H

#include "CrewRole.hpp"
#include "Flight.hpp"
#include "Person.hpp"

class CrewMember : public Person {
   public:
    CrewMember(
        CrewRole& role,
        unsigned int& id,
        std::string& nameFirst,
        std::string& nameSecond,
        unsigned int& timeBirthday,
        Gender& gender);

    void addFlight(Flight*& pFlight);
    void removeFlight(Flight*& pFlight);

    void removeFlights();
    void terminate();

    bool isBusy(unsigned int& timeStart, unsigned int& timeEnd);

   private:
    std::vector<Flight*> flights;

    CrewRole role;
};

#endif
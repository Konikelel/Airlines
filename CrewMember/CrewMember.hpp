#include <vector>

#ifndef CREW_MEMBER_H
#define CREW_MEMBER_H

#include "CrewRole.hpp"
#include "Flight.hpp"
#include "Person.hpp"

class CrewMember : public Person {
   public:
    CrewMember(
        CrewRole role,
        unsigned int id,
        std::string nameFirst,
        std::string nameSecond,
        unsigned int timeBirthday,
        Gender gender);

    // ADD FLIGHT POINTER TO CREW MEMBER, IF CREW MEMBER IS NOT ON THE FLIGHT AND DEPENDING ON WORKING STATUS, INVOKE FUNCTION IN FLIGHT TO ADD CREW MEMBER POINTER TO PASSENGERS OR (STEWARDESSES / PILOTS)
    void addFlight(Flight* pFlight, bool working);
    // REMOVE FLIGHT POINTER FROM CREW MEMBER, IF CREW MEMBER IS ON THE FLIGHT, INVOKE FUNCTION IN FLIGHT TO REMOVE CREW MEMBER POINTER
    void removeFlight(Flight* pFlight);

    // REMOVE ALL FLIGHTS FROM CREW MEMBER AND CREW MEMBER POINTERS FROM FLIGHTS
    bool removeFlights();

    bool isBusy(unsigned int timeStart, unsigned int timeEnd);

   private:
    std::vector<Flight*> flights;

    CrewRole role;
};

#endif
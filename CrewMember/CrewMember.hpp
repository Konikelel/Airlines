#include <vector>

#ifndef CREW_MEMBER_H
#define CREW_MEMBER_H

#include "Company.hpp"
#include "CrewRole.hpp"
#include "Flight.hpp"
#include "Person.hpp"

class CrewMember : public Person {
   public:
    CrewMember(
        Company* pCompany,
        CrewRole role,
        unsigned int id,
        std::string nameFirst,
        std::string nameSecond,
        unsigned int timeBirthday,
        Gender gender);

    CrewMember(
        CrewRole role,
        unsigned int id,
        std::string nameFirst,
        std::string nameSecond,
        unsigned int timeBirthday,
        Gender gender);

    Company* getCompany();
    CrewRole getRole();

    void setCompany(Company* pCompany);

    // ADD FLIGHT POINTER TO CREW MEMBER, IF CREW MEMBER IS NOT ON THE FLIGHT, INVOKE FUNCTION IN FLIGHT TO ADD CREW MEMBER POINTER TO FLIGHT
    void addFlight(Flight* pFlight);
    // REMOVE FLIGHT POINTER FROM CREW MEMBER, IF CREW MEMBER IS ON THE FLIGHT, INVOKE FUNCTION IN FLIGHT TO REMOVE CREW MEMBER POINTER
    void removeFlight(Flight* pFlight);

    // REMOVE ALL FLIGHTS FROM CREW MEMBER AND CREW MEMBER POINTERS FROM FLIGHTS
    bool removeFlights();

    // CALLED IN DESTRUCTOR REMOVE ALL FLIGHTS AND CREW MEMBER FROM COMPANY
    void terminate();

   private:
    Company* pCompany;
    std::vector<Flight*> flights;

    CrewRole role;
};

#endif
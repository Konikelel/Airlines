#include <functional>
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

    ~CrewMember();

    Company*& getCompany();
    std::vector<std::reference_wrapper<Flight>>& getFlights();
    CrewRole getRole() const;

    // INVOKE FUNCTION FROM COMPANY TO ADD CREW MEMBER
    void setCompany(Company* pCompany);

    // INVOKE FUNCTION FROM FLIGHT TO ADD CREW MEMBER
    void addFlight(Flight& flight);
    // INVOKE FUNCTION FROM FLIGHT TO REMOVE CREW MEMBER
    bool removeFlight(Flight& flight);

    // INVOKE FOR ALL FLIGHTS FUNCTION removeFlight
    bool removeFlights();

   private:
    Company* pCompany;
    std::vector<std::reference_wrapper<Flight>> flights;

    CrewRole role;
};

#endif
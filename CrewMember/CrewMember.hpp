#include <functional>
#include <set>

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
        std::string nameFirst,
        std::string nameSecond,
        unsigned int timeBirthday,
        Gender gender);

    CrewMember(
        CrewRole role,
        std::string nameFirst,
        std::string nameSecond,
        unsigned int timeBirthday,
        Gender gender);

    ~CrewMember();

    CrewRole getRole() const;
    Company* getCompany() const;
    std::set<std::reference_wrapper<Flight>>& getFlights();

    // INVOKE FUNCTION FROM COMPANY TO ADD CREW MEMBER
    void setCompany(Company* pCompany);

    // INVOKE FUNCTION FROM FLIGHT TO ADD CREW MEMBER
    void addFlight(Flight& flight);
    // INVOKE FUNCTION FROM FLIGHT TO REMOVE CREW MEMBER
    bool removeFlight(Flight& flight);

    // INVOKE FOR ALL FLIGHTS FUNCTION removeFlight
    bool removeFlights();

    friend bool operator==(const std::reference_wrapper<CrewMember>& one, const CrewMember& other);
    friend bool operator<(const std::reference_wrapper<CrewMember>& one, const std::reference_wrapper<CrewMember>& other);

   private:
    Company* pCompany;
    std::set<std::reference_wrapper<Flight>> flights;

    CrewRole role;

    friend Company;
    friend std::ostream& operator<<(std::ostream& os, CrewMember& crewMember);
};

#endif
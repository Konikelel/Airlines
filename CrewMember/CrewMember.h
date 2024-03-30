#include <vector>

#ifndef CREW_MEMBER_H
#define CREW_MEMBER_H

#include "CrewRole.h"
#include "CrewStatus.h"
#include "Flight/Flight.h"
#include "Person/Person.h"

class CrewMember : public Person {
   public:
    CrewMember(
        CrewRole& role,
        unsigned int& id,
        std::string& nameFirst,
        std::string& nameSecond,
        unsigned int& timeBirthday,
        Gender& gender);

    void setStatus(const CrewStatus& status);

    void addFlight(Flight*& pFlight);
    void removeFlight(Flight*& pFlight);

    void removeFlights();
    void terminate();

    bool isBusy(unsigned int& timeStart, unsigned int& timeEnd);

   private:
    CrewRole role;
    CrewStatus status;

    std::vector<Flight*> flights;
};

#endif
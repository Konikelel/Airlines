#include <string>
#include <vector>

#ifndef COMPANY_H
#define COMPANY_H

#include "CrewMember.hpp"
#include "Flight.hpp"
#include "Plane.hpp"

class Company {
   public:
    Company(std::string name);

    void setName(std::string name);

    void addPlane(Plane* pPlane);
    bool removePlane(Plane* pPlane);

    void addFlight(Flight* pFlight);
    bool removeFlight(Flight* pFlight);

    void addStewardess(CrewMember* pStewardess);
    bool removeStewardess(CrewMember* pStewardess);

    void addPilot(CrewMember* pPilot);
    bool removePilot(CrewMember* pPilot);

    // DELETE ALL FLIGHTS, COMPANY'S PLANES AND MAKE CREW MEMBERS UNEMPLOYED
    void terminate();

   private:
    std::string name;
    std::vector<Plane*> planes;
    std::vector<Plane*> flights;
    std::vector<CrewMember*> stewardesses;
    std::vector<CrewMember*> pilots;
};

#endif
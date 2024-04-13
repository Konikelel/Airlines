#include <functional>
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

    std::vector<std::reference_wrapper<Plane>>& getPlanes();
    std::vector<std::reference_wrapper<Flight>>& getFlights();
    std::vector<std::reference_wrapper<CrewMember>>& getStewardesses();
    std::vector<std::reference_wrapper<CrewMember>>& getPilots();
    // ADD PLANE TO COMPANY AND SET PLANE'S COMPANY
    void addPlane(Plane& plane);
    // REMOVE PLANE FROM COMPANY AND REMOVES PLANE'S COMPANY

    bool removePlane(Plane& plane);
    // ADD CREW MEMBER TO COMPANY AND SET CREW MEMBER'S COMPANY
    void addCrewMember(CrewMember& crewMember);
    // REMOVE CREW MEMBER FROM COMPANY AND REMOVES CREW MEMBER'S COMPANY
    bool removeCrewMember(CrewMember& crewMember);

   private:
    std::string name;
    std::vector<std::reference_wrapper<Plane>> planes;
    std::vector<std::reference_wrapper<Flight>> flights;
    std::vector<std::reference_wrapper<CrewMember>> stewardesses;
    std::vector<std::reference_wrapper<CrewMember>> pilots;
};

#endif
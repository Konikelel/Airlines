#include <functional>
#include <list>
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

    ~Company();

    std::string getName();
    std::list<Flight>& getFlights();
    std::vector<std::reference_wrapper<Plane>>& getPlanes();
    std::vector<std::reference_wrapper<CrewMember>>& getStewardesses();
    std::vector<std::reference_wrapper<CrewMember>>& getPilots();

    void setName(std::string name);
    // ADD PLANE TO COMPANY AND SET PLANE'S COMPANY
    void addPlane(Plane& plane);
    // REMOVE PLANE FROM COMPANY AND REMOVES PLANE'S COMPANY
    bool removePlane(Plane& plane);
    bool removePlanes();

    // ADD CREW MEMBER TO COMPANY AND SET CREW MEMBER'S COMPANY
    void addCrewMember(CrewMember& crewMember);
    // REMOVE CREW MEMBER FROM COMPANY AND REMOVES CREW MEMBER'S COMPANY
    bool removeCrewMember(CrewMember& crewMember);
    bool removeCrewMembers();

    // CRETE FLIGHT IN COMPANY
    Flight& createFlight(std::string flightNr,
                         Plane& plane,
                         unsigned int timeDeparture,
                         unsigned int timeArrival,
                         std::string cityDeparture,
                         std::string cityArrival);

    Flight& createFlight(std::string flightNr,
                         unsigned int timeDeparture,
                         unsigned int timeArrival,
                         std::string cityDeparture,
                         std::string cityArrival);
    // REMOVE FLIGHT, DELETE FROM ALL CLASSES
    bool removeFlight(Flight& flight);
    bool removeFlights();

   private:
    std::string name;
    std::list<Flight> flights;
    std::vector<std::reference_wrapper<Plane>> planes;
    std::vector<std::reference_wrapper<CrewMember>> stewardesses;
    std::vector<std::reference_wrapper<CrewMember>> pilots;
};

#endif
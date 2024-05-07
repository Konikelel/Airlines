#include <functional>
#include <list>
#include <set>
#include <string>

#ifndef COMPANY_H
#define COMPANY_H

#include "CrewMember.hpp"
#include "CrewRole.hpp"
#include "Flight.hpp"
#include "Plane.hpp"

class Company {
   public:
    Company(std::string name);

    ~Company();

    std::string getName() const;
    std::list<Flight>& getFlights();
    std::set<std::reference_wrapper<Plane>>& getPlanes();
    std::set<std::reference_wrapper<CrewMember>>& getStewardesses();
    std::set<std::reference_wrapper<CrewMember>>& getPilots();

    void setName(const std::string name);
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
                         unsigned long long timeDeparture,
                         unsigned long long timeArrival,
                         std::string cityDeparture,
                         std::string cityArrival);

    Flight& createFlight(std::string flightNr,
                         unsigned long long timeDeparture,
                         unsigned long long timeArrival,
                         std::string cityDeparture,
                         std::string cityArrival);
    // REMOVE FLIGHT, DELETE FROM ALL CLASSES
    bool removeFlight(Flight& flight);
    bool removeFlights();

    std::set<std::reference_wrapper<CrewMember>> availableCrewMembers(unsigned long long timeStart, unsigned long long timeEnd, CrewRole role);

    friend std::ostream& operator<<(std::ostream& os, Company& company);

   private:
    std::string name;
    std::list<Flight> flights;
    std::set<std::reference_wrapper<Plane>> planes;
    std::set<std::reference_wrapper<CrewMember>> stewardesses;
    std::set<std::reference_wrapper<CrewMember>> pilots;
};

#endif
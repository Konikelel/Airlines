#include <string>
#include <vector>

#ifndef FLIGHT_H
#define FLIGHT_H

class CrewMember;
class Passenger;
class Plane;

class Flight {
   public:
    Flight(
        std::string& flightNr,
        Plane*& pPlane,
        unsigned int& timeDeparture,
        unsigned int& timeArrival,
        std::string& cityDeparture,
        std::string& cityArrival);

    Flight(
        std::string& flightNr,
        unsigned int& timeDeparture,
        unsigned int& timeArrival,
        std::string& cityDeparture,
        std::string& cityArrival);

    void setFlightNr(std::string& flightNr);
    void setPlane(Plane*& pPlane);

    void setDataDeparture(const unsigned int& time);
    void setDataArrival(const unsigned int& time);
    void setDataDeparture(const unsigned int& time, std::string& city);
    void setDataArrival(const unsigned int& time, std::string& city);

    void addPassenger(Passenger*& pPassenger);
    bool removePassenger(Passenger*& pPassenger);

    void addStewardess(CrewMember*& pStewardess);
    bool removeStewardess(CrewMember*& pStewardess);

    void addPilots(CrewMember*& pPilot);
    bool removePilots(CrewMember*& pPilot);

    void terminate();

    bool existPassenger(Passenger*& pPassenger);
    bool existStewardess(Passenger*& pStewardess);
    bool existPilot(Passenger*& pPilot);

    bool operator==(const Flight*& pFlight);
    bool timeOverlap(unsigned int& timeStart, unsigned int& timeEnd);

   private:
    int nrValidCrewMembers(std::vector<CrewMember*>& crew);

    std::string flightNr;
    Plane* pPlane;

    unsigned int timeDeparture;  // time in miliseconds
    unsigned int timeArrival;    // time in miliseconds
    std::string cityDeparture;
    std::string cityArrival;

    std::vector<Passenger*> passengers;
    std::vector<CrewMember*> stewardesses;
    std::vector<CrewMember*> pilots;
};

#endif
#include <string>
#include <vector>

#ifndef FLIGHT_H
#define FLIGHT_H

#include "FlightStatus.h"

class CrewMember;
class Passenger;
class Plane;

class Flight {
   public:
    Flight(
        std::string& flightNr,
        FlightStatus& status,
        Plane*& pPlane,
        unsigned int& timeDeparture,
        unsigned int& timeArrival,
        std::string& cityDeparture,
        std::string& cityArrival,
        std::vector<CrewMember*>& stewardesses,
        std::vector<CrewMember*>& pilots);

    Flight(
        std::string& flightNr,
        FlightStatus& status,
        Plane*& pPlane,
        unsigned int& timeDeparture,
        unsigned int& timeArrival,
        std::string& cityDeparture,
        std::string& cityArrival);

    Flight(
        std::string& flightNr,
        FlightStatus& status,
        unsigned int& timeDeparture,
        unsigned int& timeArrival,
        std::string& cityDeparture,
        std::string& cityArrival);

    void setFlightNr(std::string& flightNr);
    void setStatus(const FlightStatus& status);
    void setPlane(Plane*& pPlane);

    void setDataDeparture(const unsigned int& time);
    void setDataArrival(const unsigned int& time);
    void setDataDeparture(const unsigned int& time, std::string& city);
    void setDataArrival(const unsigned int& time, std::string& city);

    unsigned int& getTimeDeparture();
    unsigned int& getTimeArrival();

    void addPassenger(Passenger*& pPassenger);
    void addStewardess(CrewMember*& pStewardess);
    void removePassenger(Passenger*& pPassenger);
    void addPilots(CrewMember*& pPilot);

    void removeStewardess(CrewMember*& pStewardess);
    void removePilots(CrewMember*& pPilot);

    bool operator==(const Flight*& pFlight);

   private:
    void setStewardess(std::vector<CrewMember*>& stewardesses);
    void setPilots(std::vector<CrewMember*>& pilots);

    int& getNrValidCrewMembers(std::vector<CrewMember*>& crew);

    std::string flightNr;
    FlightStatus status;
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
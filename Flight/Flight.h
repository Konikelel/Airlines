#include <string>
#include <vector>

#ifndef FLIGHT_H
#define FLIGHT_H

#include "FlightStatus.h"

class CrewMember;
class Passenger;
class Plane;

class Flight {
   private:
    std::string flightNr;
    FlightStatus status;
    Plane* pPlane;

    unsigned int timeDeparture;  // time in miliseconds
    unsigned int timeArrival;    // time in miliseconds
    std::string cityDeparture;
    std::string cityArrival;

    std::vector<Passenger*> passenger;
    std::vector<CrewMember*> stewardess;
    std::vector<CrewMember*> pilots;
};

#endif
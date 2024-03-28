#include <memory>
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
    std::shared_ptr<Plane> pPlane;

    unsigned int timeDeparture;  // time in miliseconds
    unsigned int timeArrival;    // time in miliseconds
    std::string cityDeparture;
    std::string cityArrival;

    std::vector<std::shared_ptr<Passenger>> passenger;
    std::vector<std::shared_ptr<CrewMember>> crewMember;
};

#endif
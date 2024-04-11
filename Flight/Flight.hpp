#include <memory>
#include <string>
#include <vector>

#ifndef FLIGHT_H
#define FLIGHT_H

class Company;
class CrewMember;
class Passenger;
class Plane;

class Flight {
   public:
    Flight(
        Company* pCompany,
        std::string flightNr,
        Plane* pPlane,
        unsigned int timeDeparture,
        unsigned int timeArrival,
        std::string cityDeparture,
        std::string cityArrival);

    Flight(
        Company* pCompany,
        std::string flightNr,
        unsigned int timeDeparture,
        unsigned int timeArrival,
        std::string cityDeparture,
        std::string cityArrival);

    std::string getFlightNr() const;
    Plane* getPlane() const;
    unsigned int getTimeDeparture() const;
    unsigned int getTimeArrival() const;
    std::string getCityDeparture() const;
    std::string getCityArrival() const;

    void setFlightNr(const std::string flightNr);
    // CHANGE PLANE FOR ANOTHER AND CHECK IF PASSENGERS, STEWARDESS, PILOTS ARE WITHIN RANGE
    void changePlane(Plane* pPlane);

    // CHANGE DATA TIME CALLED IN CONSTRUCTOR VALIDATING ARGUMENTS WITH THIS DATA PARAMETERS
    void changeDataDeparture(const unsigned int time);
    void changeDataArrival(const unsigned int time);
    void changeDataDeparture(const unsigned int time, const std::string city);
    void changeDataArrival(const unsigned int time, const std::string city);

    // ADD PASSENGER POINTER TO FLIGHT, IF PASSENGER IS NOT ON THE FLIGHT ADD FLIGHT POINTER TO PASSENGER
    void addPassenger(Passenger* pPassenger);
    // REMOVE PASSENGER POINTER FROM FLIGHT, IF PASSENGER IS ON THE FLIGHT REMOVE FLIGHT POINTER FROM PASSENGER
    bool removePassenger(Passenger* pPassenger);

    // ADD STEWARDESS POINTER TO FLIGHT, IF STEWARDESS IS NOT ON THE FLIGHT ADD FLIGHT POINTER TO STEWARDESS
    void addStewardess(CrewMember* pStewardess);
    // REMOVE STEWARDESS POINTER FROM FLIGHT, IF STEWARDESS IS ON THE FLIGHT REMOVE FLIGHT POINTER FROM STEWARDESS
    bool removeStewardess(CrewMember* pStewardess);

    // ADD PILOT POINTER TO FLIGHT, IF PILOT IS NOT ON THE FLIGHT ADD FLIGHT POINTER TO PILOT
    void addPilots(CrewMember* pPilot);
    // REMOVE PILOT POINTER FROM FLIGHT, IF PILOT IS ON THE FLIGHT REMOVE FLIGHT POINTER FROM PILOT
    bool removePilots(CrewMember* pPilot);

    // REMOVE PLANE, ALL PASSENGERS, STEWARDESS, PILOTS FROM FLIGHT AND FLIGHT FROM THEM
    void terminate();

    // CHECK IF PASSENGER, STEWARDESS, PILOT IS ON THE FLIGHT
    bool existPassenger(Passenger* pPassenger);
    bool existStewardess(CrewMember* pStewardess);
    bool existPilot(CrewMember* pPilot);

    // CHECK FOR FLIGHT TIME OVERLAP WITH TIME PERIOD
    bool timeOverlap(const unsigned int timeStart, const unsigned int timeEnd);

   private:
    void setCompany(Company* pCompany);
    // SET PLANE CALLED IN CONSTRUCTOR WITHOUT ANY CHECK ON CAPACITY LIMITS
    void setPlane(Plane* pPlane);
    // SET DATA TIME CALLED IN CONSTRUCTOR VALIDATING ARGUMENTS
    void setDataTime(const unsigned int timeDeparture, const unsigned int timeArrival);
    void setDataTime(const unsigned int timeDeparture, const std::string cityDeparture, const unsigned int timeArrival, const std::string cityArrival);

    Company* pCompany;
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
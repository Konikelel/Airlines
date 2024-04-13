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

    std::vector<Passenger*>& getPassengers();
    std::vector<CrewMember*>& getStewardesses();
    std::vector<CrewMember*>& getPilots();

    void setFlightNr(const std::string flightNr);
    // CHANGE PLANE FOR ANOTHER AND CHECK IF PASSENGERS, STEWARDESS, PILOTS ARE WITHIN RANGE
    void setPlane(Plane* pPlane);
    bool removePlane();

    // CHANGE DATA TIME CALLED IN CONSTRUCTOR VALIDATING ARGUMENTS WITH THIS DATA PARAMETERS
    void changeDataDeparture(const unsigned int time);
    void changeDataArrival(const unsigned int time);
    void changeDataDeparture(const unsigned int time, const std::string city);
    void changeDataArrival(const unsigned int time, const std::string city);

    // ADD PASSENGER POINTER TO FLIGHT, IF PASSENGER IS NOT ON THE FLIGHT ADD FLIGHT POINTER TO PASSENGER
    void addPassenger(Passenger* pPassenger);  // TEST
    // REMOVE PASSENGER POINTER FROM FLIGHT, IF PASSENGER IS ON THE FLIGHT REMOVE FLIGHT POINTER FROM PASSENGER
    bool removePassenger(Passenger* pPassenger);  // TEST

    // ADD STEWARDESS POINTER TO FLIGHT, IF STEWARDESS IS NOT ON THE FLIGHT ADD FLIGHT POINTER TO STEWARDESS
    void addCrewMember(CrewMember* pCrewMember);  // TEST
    // REMOVE STEWARDESS POINTER FROM FLIGHT, IF STEWARDESS IS ON THE FLIGHT REMOVE FLIGHT POINTER FROM STEWARDESS
    bool removeCrewMember(CrewMember* pCrewMember);  // TEST

    // REMOVE PLANE, ALL PASSENGERS, STEWARDESS, PILOTS FROM FLIGHT AND FLIGHT FROM THEM
    void terminate();  // TEST

    // CHECK FOR FLIGHT TIME OVERLAP WITH TIME PERIOD
    bool timeOverlap(const Flight* pFlight);                                     // TEST
    bool timeOverlap(const unsigned int timeStart, const unsigned int timeEnd);  // TEST

   private:
    void setupCompany(Company* pCompany);
    // SET PLANE CALLED IN CONSTRUCTOR WITHOUT ANY CHECK ON CAPACITY LIMITS
    void setupPlane(Plane* pPlane);
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
#include <functional>
#include <set>
#include <string>
#include <vector>

#ifndef FLIGHT_H
#define FLIGHT_H

#include "FlightStatus.hpp"

class Company;
class CrewMember;
class Passenger;
class Plane;

class Flight {
   public:
    ~Flight();

    static std::vector<unsigned int> usedIds;

    Company* getCompany() const;
    unsigned int getId() const;
    std::string getFlightNr() const;
    FlightStatus getStatus() const;
    Plane* getPlane() const;
    unsigned long long getTimeDeparture() const;
    unsigned long long getTimeArrival() const;
    std::string getCityDeparture() const;
    std::string getCityArrival() const;

    std::set<std::reference_wrapper<Passenger>>& getPassengers();
    std::set<std::reference_wrapper<CrewMember>>& getStewardesses();
    std::set<std::reference_wrapper<CrewMember>>& getPilots();

    void setStatus();
    void setFlightNr(const std::string flightNr);
    // CHANGE PLANE FOR ANOTHER AND CHECK IF PASSENGERS, STEWARDESS, PILOTS ARE WITHIN RANGE
    void setPlane(Plane& plane);
    bool removePlane();

    // CHANGE DATA TIME CALLED IN CONSTRUCTOR VALIDATING ARGUMENTS WITH THIS DATA PARAMETERS
    void changeDataDeparture(const unsigned long long time);
    void changeDataArrival(const unsigned long long time);
    void changeDataDeparture(const unsigned long long time, const std::string city);
    void changeDataArrival(const unsigned long long time, const std::string city);

    // ADD PASSENGER TO FLIGHT,ADD FLIGHT TO PASSENGER
    void addPassenger(Passenger& passenger);
    // REMOVE PASSENGER FROM FLIGHT, REMOVE FLIGHT FROM PASSENGER
    bool removePassenger(Passenger& passenger);
    bool removePassengers();

    // ADD CREW MEMBER TO FLIGHT, ADD FLIGHT TO CREW MEMBER
    void addCrewMember(CrewMember& crewMember);
    // REMOVE CREW MEMBER FROM FLIGHT, REMOVE FLIGHT FROM CREW MEMBER
    bool removeCrewMember(CrewMember& crewMember);
    bool removeCrewMembers();

    // CHECK FOR FLIGHT TIME OVERLAP WITH TIME PERIOD
    bool timeOverlap(const Flight& flight) const;
    bool timeOverlap(const unsigned long long timeStart, const unsigned long long timeEnd) const;

    bool operator==(const Flight& other) const;

    friend bool operator==(const std::reference_wrapper<Flight>& one, const Flight& other);
    friend bool operator<(const std::reference_wrapper<Flight>& one, const std::reference_wrapper<Flight>& other);
    friend std::ostream& operator<<(std::ostream& os, Flight& flight);

   private:
    Flight(
        Company* pCompany,
        std::string flightNr,
        unsigned long long timeDeparture,
        unsigned long long timeArrival,
        std::string cityDeparture,
        std::string cityArrival);

    void setId();

    // SET PLANE CALLED IN CONSTRUCTOR WITHOUT ANY CHECK ON CAPACITY LIMITS
    void setupPlane(Plane& plane);
    // SET DATA TIME CALLED IN CONSTRUCTOR VALIDATING ARGUMENTS
    void setDataTime(const unsigned long long timeDeparture, const unsigned long long timeArrival);
    void setDataTime(const unsigned long long timeDeparture, const std::string cityDeparture, const unsigned long long timeArrival, const std::string cityArrival);

    unsigned int id;
    Company* pCompany;
    std::string flightNr;
    FlightStatus status;
    Plane* pPlane;

    unsigned long long timeDeparture;  // time in miliseconds
    unsigned long long timeArrival;    // time in miliseconds
    std::string cityDeparture;
    std::string cityArrival;

    std::set<std::reference_wrapper<Passenger>> passengers;
    std::set<std::reference_wrapper<CrewMember>> stewardesses;
    std::set<std::reference_wrapper<CrewMember>> pilots;

    friend Company;
};

#endif
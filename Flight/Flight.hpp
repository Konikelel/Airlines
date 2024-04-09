#include <memory>
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
        std::string flightNr,
        std::shared_ptr<Plane> pPlane,
        unsigned int timeDeparture,
        unsigned int timeArrival,
        std::string cityDeparture,
        std::string cityArrival);

    Flight(
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
    void changePlane(std::shared_ptr<Plane> pPlane);

    void changeDataDeparture(const unsigned int time);
    void changeDataArrival(const unsigned int time);
    void changeDataDeparture(const unsigned int time, const std::string city);
    void changeDataArrival(const unsigned int time, const std::string city);

    void addPassenger(Passenger* pPassenger);
    bool removePassenger(Passenger* pPassenger);

    void addStewardess(CrewMember* pStewardess);
    bool removeStewardess(CrewMember* pStewardess);

    void addPilots(CrewMember* pPilot);
    bool removePilots(CrewMember* pPilot);

    void terminate();

    bool existPassenger(Passenger* pPassenger);  // BEST (const Passenger* pPassenger) BUT ERRORS
    bool existStewardess(CrewMember* pStewardess);
    bool existPilot(CrewMember* pPilot);

    bool timeOverlap(const unsigned int timeStart, const unsigned int timeEnd);

   private:
    void setPlane(std::shared_ptr<Plane> pPlane);
    void setDataTime(const unsigned int timeDeparture, const unsigned int timeArrival);
    void setDataTime(const unsigned int timeDeparture, const std::string cityDeparture, const unsigned int timeArrival, const std::string cityArrival);

    int nrValidCrewMembers(const std::vector<CrewMember*>& crew);

    std::string flightNr;
    std::shared_ptr<Plane> pPlane;

    unsigned int timeDeparture;  // time in miliseconds
    unsigned int timeArrival;    // time in miliseconds
    std::string cityDeparture;
    std::string cityArrival;

    std::vector<Passenger*> passengers;
    std::vector<CrewMember*> stewardesses;
    std::vector<CrewMember*> pilots;
};

#endif
#include <string>
#include <vector>

class Company {
    Company(std::string name);

    void addPlane(Plane* pPlane);
    bool removePlane(Plane* pPlane);

    void addFlight(Flight* pFlight);
    bool removeFlight(Flight* pFlight);

    void addStewardess(CrewMember* pStewardess);
    bool removeStewardess(CrewMember* pStewardess);

    void addPilot(CrewMember* pPilot);
    bool removePilot(CrewMember* pPilot);

   private:
    std::string name;
    std::vector<Plane*> planes;
    std::vector<Plane*> flights;
    std::vector<CrewMember*> stewardesses;
    std::vector<CrewMember*> pilots;
};
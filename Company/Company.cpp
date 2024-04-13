#include "Company.hpp"

#include "CustomErrors.hpp"
#include "VectorHandler.hpp"

Company::Company(std::string name) {
    setName(name);
}

void Company::setName(std::string name) {
    if (!name.size())
        throw InvalidName("First name must contain any character");

    this->name = name;
}

std::vector<std::reference_wrapper<Plane>>& Company::getPlanes() {
    return planes;
}

std::vector<std::reference_wrapper<Flight>>& Company::getFlights() {
    return flights;
}

std::vector<std::reference_wrapper<CrewMember>>& Company::getStewardesses() {
    return stewardesses;
}

std::vector<std::reference_wrapper<CrewMember>>& Company::getPilots() {
    return pilots;
}

void Company::addPlane(Plane& plane) {
    Company*& pCompany = plane.getCompany();

    if (pCompany == this)
        return;
    if (pCompany)
        pCompany->removePlane(plane);

    pCompany = this;
    planes.push_back(plane);
}

bool Company::removePlane(Plane& plane) {
    Company*& pCompany = plane.getCompany();

    if (pCompany != this)
        return false;

    plane.removeFlights();
    pCompany = nullptr;

    return deleteVector(planes, plane);
}

void Company::addCrewMember(CrewMember& crewMember) {
    Company*& pCompany = crewMember.getCompany();

    if (pCompany == this)
        return;
    if (pCompany)
        pCompany->removeCrewMember(crewMember);

    pCompany = this;
    if (crewMember.getRole())
        stewardesses.push_back(crewMember);
    else
        pilots.push_back(crewMember);
}

bool Company::removeCrewMember(CrewMember& crewMember) {
    Company*& pCompany = crewMember.getCompany();

    if (pCompany != this)
        return false;

    crewMember.removeFlights();
    pCompany = nullptr;

    return deleteVector(crewMember.getRole() ? stewardesses : pilots, crewMember);
}

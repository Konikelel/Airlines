#include "CrewMember.hpp"

#include "CustomErrors.hpp"

CrewMember::CrewMember(Company* pCompany,
                       CrewRole role,
                       unsigned int id,
                       std::string nameFirst,
                       std::string nameSecond,
                       unsigned int timeBirthday,
                       Gender gender) : CrewMember(role, id, nameFirst, nameSecond, timeBirthday, gender) {
    setCompany(pCompany);
}

CrewMember::CrewMember(CrewRole role,
                       unsigned int id,
                       std::string nameFirst,
                       std::string nameSecond,
                       unsigned int timeBirthday,
                       Gender gender) : Person(id, nameFirst, nameSecond, timeBirthday, gender),
                                        pCompany{nullptr},
                                        role{role} {
}

CrewMember::~CrewMember() {
    // INVOKE FUNCTION FROM COMPANY TO REMOVE CREW MEMBER IF CREW MEMBER IS EMPLOYED
}

Company* CrewMember::getCompany() {
    return pCompany;
}

std::vector<Flight*>& CrewMember::getFlights() {
    return flights;
}

CrewRole CrewMember::getRole() {
    return role;
}

void CrewMember::setCompany(Company*& pCompany) {
    if (this->pCompany == pCompany)
        return;

    // INVOKE FUNCTION FROM COMPANY TO ADD CREW MEMBER
}

void CrewMember::addFlight(Flight*& pFlight) {
    pFlight->addCrewMember(this);
}

bool CrewMember::removeFlight(Flight*& pFlight) {
    return pFlight->removeCrewMember(this);
}

bool CrewMember::removeFlights() {
    bool success = false;
    for (auto pFlight : flights)
        success = removeFlight(pFlight) && success;

    return success;
}

void CrewMember::terminate() {
    // INVOKE FUNCTION FROM COMPANY TO REMOVE CREW MEMBER
}

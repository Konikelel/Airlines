#include "CrewMember.hpp"

#include <iostream>

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
    if (pCompany)  // TESTED
        pCompany->removeCrewMember(*this);
}

Company*& CrewMember::getCompany() {  // TESTED
    return pCompany;
}

std::vector<std::reference_wrapper<Flight>>& CrewMember::getFlights() {  // TESTED
    return flights;
}

CrewRole CrewMember::getRole() const {  // TESTED
    return role;
}

void CrewMember::setCompany(Company* pCompany) {  // TESTED
    if (pCompany)
        pCompany->addCrewMember(*this);
    else if (this->pCompany)
        this->pCompany->removeCrewMember(*this);
}

void CrewMember::addFlight(Flight& flight) {  // TESTED
    flight.addCrewMember(*this);
}

bool CrewMember::removeFlight(Flight& flight) {  // TESTED
    return flight.removeCrewMember(*this);
}

bool CrewMember::removeFlights() {  // TESTED
    bool success = true;

    for (Flight& flight : flights)
        success = removeFlight(flight) && success;

    return success;
}
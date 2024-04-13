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
    if (pCompany)
        pCompany->removeCrewMember(*this);
}

Company*& CrewMember::getCompany() {
    return pCompany;
}

std::vector<std::reference_wrapper<Flight>>& CrewMember::getFlights() {
    return flights;
}

CrewRole CrewMember::getRole() const {
    return role;
}

void CrewMember::setCompany(Company* pCompany) {
    if (!pCompany)
        throw InvalidPointer("Invalid company object");

    pCompany->addCrewMember(*this);
}

void CrewMember::addFlight(Flight& flight) {
    flight.addCrewMember(*this);
}

bool CrewMember::removeFlight(Flight& flight) {
    return flight.removeCrewMember(*this);
}

bool CrewMember::removeFlights() {
    bool success = true;
    for (auto flight : flights)
        success = removeFlight(flight) && success;

    return success;
}

void CrewMember::terminate() {
    setCompany(nullptr);
}

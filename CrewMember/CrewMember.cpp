#include "CrewMember.hpp"

#include <iostream>

#include "CustomErrors.hpp"
#include "VectorHandler.hpp"

CrewMember::CrewMember(Company* pCompany,
                       CrewRole role,
                       std::string nameFirst,
                       std::string nameSecond,
                       unsigned int timeBirthday,
                       Gender gender) : CrewMember(role, nameFirst, nameSecond, timeBirthday, gender) {
    setCompany(pCompany);
}

CrewMember::CrewMember(CrewRole role,
                       std::string nameFirst,
                       std::string nameSecond,
                       unsigned int timeBirthday,
                       Gender gender) : Person(nameFirst, nameSecond, timeBirthday, gender),
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

std::set<std::reference_wrapper<Flight>>& CrewMember::getFlights() {  // TESTED
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

    for (auto it = flights.begin(); it != flights.end();)
        success = removeFlight(*(it++)) && success;

    return success;
}

bool operator==(const std::reference_wrapper<CrewMember>& one, const CrewMember& other) {
    return one.get().getId() == other.getId();
}

bool operator<(const std::reference_wrapper<CrewMember>& one, const std::reference_wrapper<CrewMember>& other) {
    return one.get().getId() < other.get().getId();
}

std::ostream& operator<<(std::ostream& os, CrewMember& crewMember) {
    os << "Id: " << crewMember.getId() << " "
       << "Company: " << crewMember.getCompany() << " "
       << "Flights: " << crewMember.getFlights().size() << std::endl;

    return os;
}

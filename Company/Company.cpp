#include "Company.hpp"

#include "CustomErrors.hpp"

Company::Company(std::string name) {
    setName(name);
}

void Company::setName(std::string name) {
    if (!name.size())
        throw InvalidName("First name must contain any character");

    this->name = name;
}

void Company::addCrewMember(CrewMember*& pCrewMember) {
    if (pCrewMember->getCompany())
        pCrewMember->removeFlights();

    pCrewMember->setCompany(this);
}

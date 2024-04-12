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

Company* CrewMember::getCompany() {
    return pCompany;
}

CrewRole CrewMember::getRole() {
    return role;
}

void CrewMember::setCompany(Company* pCompany) {
    if (!pCompany)
        throw InvalidPointer("Invalid company object");
    // REMOVE ALL FLIGHTS WHERE CREW MEMBER
    this->pCompany = pCompany;
}

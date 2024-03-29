#include "CrewMember.h"

CrewMember::CrewMember(CrewRole role,
                       unsigned int id,
                       std::string nameFirst,
                       std::string nameSecond,
                       unsigned int timeBirthday,
                       Gender gender) : role{role},
                                        Person(id, nameFirst, nameSecond, timeBirthday, gender) {
    this->flights = {};
    setStatus(WORKING);
}
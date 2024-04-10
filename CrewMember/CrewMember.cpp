#include "CrewMember.hpp"

CrewMember::CrewMember(CrewRole role,
                       unsigned int id,
                       std::string nameFirst,
                       std::string nameSecond,
                       unsigned int timeBirthday,
                       Gender gender) : Person(id, nameFirst, nameSecond, timeBirthday, gender),
                                        flights{{}},
                                        role{role} {
}
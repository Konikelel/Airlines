#include "CrewMember.h"

CrewMember::CrewMember(CrewRole& role,
                       unsigned int& id,
                       std::string& nameFirst,
                       std::string& nameSecond,
                       unsigned int& timeBirthday,
                       Gender& gender) : flights{{}},
                                         role{role},
                                         Person(id, nameFirst, nameSecond, timeBirthday, gender) {
}

bool CrewMember::isBusy(unsigned int& timeStart, unsigned int& timeEnd) {
    for (auto& flight : flights)
        if (flight->timeOverlap(timeStart, timeEnd))
            return true;
    return false;
}

#include "CrewMember.h"

CrewMember::CrewMember(CrewRole& role,
                       unsigned int& id,
                       std::string& nameFirst,
                       std::string& nameSecond,
                       unsigned int& timeBirthday,
                       Gender& gender) : flights{{}},
                                         role{role},
                                         Person(id, nameFirst, nameSecond, timeBirthday, gender) {
    setStatus(WORKING);
}

bool CrewMember::isBusy(unsigned int& timeStart, unsigned int& timeEnd) {
    if (status == VACATION)
        return true;

    for (auto& flight : flights)
        if (!(flight->getTimeDeparture() > timeEnd || flight->getTimeArrival() < timeStart))
            return true;
    return false;
}

#include "Person.h"

#include <memory>

#include "../Utils/CustomErrors.h"

std::vector<unsigned int> Person::usedIds = {};

Person::Person(unsigned int id,
               std::string nameFirst,
               std::string nameSecond,
               unsigned int timeBirthday,
               Gender gender) : nameFirst{nameFirst}, nameSecond{nameSecond}, gender{gender} {
    setTimeBirthday(timeBirthday);
    setId(id);
}

void Person::setId(unsigned int id) {
    if (!uniqueId(id))
        throw NonUniqueIDException();

    this->id = id;
}

void Person::setTimeBirthday(unsigned int time) {
    // CHECK IF IN FUTURE, RAISE ERROR
    this->timeBirthday = time;
}

bool Person::uniqueId(unsigned int id) const {
    for (auto& usedId : usedIds)
        if (id == usedId)
            return false;
    return true;
}

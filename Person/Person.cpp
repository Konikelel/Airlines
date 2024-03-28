#include "Person.h"

#include <memory>

#include "../Utils/CustomErrors.h"
#include "../Utils/VectorHandler.h"

std::vector<unsigned int> Person::usedIds = {};

Person::Person(unsigned int id,
               std::string nameFirst,
               std::string nameSecond,
               unsigned int timeBirthday,
               Gender gender) : nameFirst{nameFirst}, nameSecond{nameSecond}, gender{gender} {
    setTimeBirthday(timeBirthday);
    setId(id);
}

void Person::setNameFirst(const std::string name) {
    this->nameFirst = name;
}

void Person::setNameSecond(const std::string name) {
    this->nameSecond = name;
}

void Person::setId(const unsigned int id) {
    if (FindInVector(usedIds, id) != usedIds.end())
        throw NonUniqueIDException();

    this->id = id;
}

void Person::setTimeBirthday(const unsigned int time) {
    // CHECK IF IN FUTURE, RAISE ERROR
    this->timeBirthday = time;
}
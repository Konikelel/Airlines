#include "Person.h"

#include "Utils/CustomErrors.h"
#include "Utils/StringHandler.h"
#include "Utils/VectorHandler.h"

std::vector<unsigned int> Person::usedIds = {};

Person::Person(unsigned int id,
               std::string nameFirst,
               std::string nameSecond,
               unsigned int timeBirthday,
               Gender gender) : gender{gender} {
    setId(id);
    setNameFirst(nameFirst);
    setNameSecond(nameSecond);
    setTimeBirthday(timeBirthday);
}

unsigned int Person::getId() {
    return id;
}

std::string Person::getNameFirst() {
    return nameFirst;
}

std::string Person::getNameSecond() {
    return nameSecond;
}

unsigned int Person::getTimeBirthday() {
    return timeBirthday;
}

Gender Person::getGender() {
    return gender;
}

void Person::changeId(const unsigned int id) {
    unsigned int oldId = this->id;
    setId(id);
    popFromVector(usedIds, oldId);
}

void Person::setId(const unsigned int id) {
    if (existInVector(usedIds, id))
        throw NonUniqueIDException();

    usedIds.push_back(id);
    this->id = id;
}

void Person::setNameFirst(std::string name) {
    this->nameFirst = toTitle(name);
}

void Person::setNameSecond(std::string name) {
    this->nameSecond = toTitle(name);
}

void Person::setTimeBirthday(const unsigned int time) {
    // CHECK IF IN FUTURE, RAISE ERROR
    this->timeBirthday = time;
}
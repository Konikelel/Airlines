#include "Person.hpp"

#include "CustomErrors.hpp"
#include "StringHandler.hpp"
#include "VectorHandler.hpp"

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

Person::~Person() {
    deleteVector(usedIds, id);
}

unsigned int Person::getId() const {
    return id;
}

std::string Person::getNameFirst() const {
    return nameFirst;
}

std::string Person::getNameSecond() const {
    return nameSecond;
}

unsigned int Person::getTimeBirthday() const {
    return timeBirthday;
}

Gender Person::getGender() const {
    return gender;
}

void Person::changeId(const unsigned int id) {
    unsigned int oldId = this->id;
    setId(id);
    deleteVector(usedIds, oldId);
}

void Person::setId(const unsigned int id) {
    if (existVector(usedIds, id))
        throw NonUniqueIDException();

    usedIds.push_back(id);
    this->id = id;
}

void Person::setNameFirst(std::string name) {
    if (!name.size())
        throw InvalidName("First name must contain any character");

    this->nameFirst = toTitle(name);
}

void Person::setNameSecond(std::string name) {
    if (!name.size())
        throw InvalidName("Second name must contain any character");

    this->nameSecond = toTitle(name);
}

void Person::setTimeBirthday(const unsigned int time) {
    // CHECK IF IN FUTURE, RAISE ERROR
    this->timeBirthday = time;
}
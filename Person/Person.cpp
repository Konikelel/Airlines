#include "Person.hpp"

#include "CustomErrors.hpp"
#include "StringHandler.hpp"
#include "VectorHandler.hpp"

std::vector<unsigned int> Person::usedIds;

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

Person::~Person() {  // TESTED
    deleteVector(usedIds, id);
}

unsigned int Person::getId() const {  // TESTED
    return id;
}

std::string Person::getNameFirst() const {  // TESTED
    return nameFirst;
}

std::string Person::getNameSecond() const {  // TESTED
    return nameSecond;
}

unsigned int Person::getTimeBirthday() const {  // TESTED
    return timeBirthday;
}

Gender Person::getGender() const {  // TESTED
    return gender;
}

void Person::changeId(const unsigned int id) {  // TESTED
    unsigned int oldId = this->id;
    setId(id);
    deleteVector(usedIds, oldId);
}

void Person::setId(const unsigned int id) {  // TESTED
    if (existVector(usedIds, id))
        throw NonUniqueIDException();

    usedIds.push_back(id);
    this->id = id;
}

void Person::setNameFirst(std::string name) {  // TESTED
    if (!name.size())
        throw InvalidName("First name must contain any character");

    this->nameFirst = toTitle(name);
}

void Person::setNameSecond(std::string name) {  // TESTED
    if (!name.size())
        throw InvalidName("Second name must contain any character");

    this->nameSecond = toTitle(name);
}

void Person::setTimeBirthday(const unsigned int time) {  // TESTED
    // CHECK IF IN FUTURE, RAISE ERROR
    this->timeBirthday = time;
}
#include <memory>
#include <string>
#include <vector>

#ifndef PERSON_H
#define PERSON_H

#include "Gender.h"

class Person {
   public:
    static std::vector<unsigned int> usedIds;

    Person(
        unsigned int id,
        std::string nameFirst,
        std::string nameSecond,
        unsigned int timeBirthday,
        Gender gender);

    void setNameFirst(const std::string name);
    void setNameSecond(const std::string name);

   private:
    void setId(const unsigned int id);
    void setTimeBirthday(const unsigned int time);

    bool uniqueId(const unsigned int id) const;

    unsigned int id;
    std::string nameFirst;
    std::string nameSecond;

    unsigned int timeBirthday;  // time in miliseconds
    Gender gender;
};

#endif
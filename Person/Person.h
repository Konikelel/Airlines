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

    void setNameFirst(std::string name);
    void setNameSecond(std::string name);

   private:
    void setId(unsigned int id);
    void setTimeBirthday(unsigned int time);

    bool uniqueId(unsigned int id) const;

    unsigned int id;
    std::string nameFirst;
    std::string nameSecond;

    unsigned int timeBirthday;  // time in miliseconds
    Gender gender;
};

#endif
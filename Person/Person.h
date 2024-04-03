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

    unsigned int getId();
    std::string getNameFirst();
    std::string getNameSecond();
    unsigned int getTimeBirthday();
    Gender getGender();

    void changeId(const unsigned int id);
    void setNameFirst(const std::string name);
    void setNameSecond(const std::string name);

    void setTimeBirthday(const unsigned int time);

   private:
    void setId(const unsigned int id);

    unsigned int id;
    std::string nameFirst;
    std::string nameSecond;

    unsigned int timeBirthday;  // time in miliseconds
    Gender gender;
};

#endif
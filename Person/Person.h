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

    void setNameFirst(std::string& name);
    void setNameSecond(std::string& name);

   private:
    void setId(const unsigned int& id);
    void setTimeBirthday(const unsigned int& time);

    unsigned int id;
    std::string nameFirst;
    std::string nameSecond;

    unsigned int timeBirthday;  // time in miliseconds
    Gender gender;
};

#endif
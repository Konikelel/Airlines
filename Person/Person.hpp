#include <string>
#include <vector>

#ifndef PERSON_H
#define PERSON_H

#include "Gender.hpp"

class Person {
   public:
    static std::vector<unsigned int> usedIds;

    Person(
        unsigned int id,
        std::string nameFirst,
        std::string nameSecond,
        unsigned int timeBirthday,
        Gender gender);
    ~Person();

    unsigned int getId() const;
    std::string getNameFirst() const;
    std::string getNameSecond() const;
    unsigned int getTimeBirthday() const;
    Gender getGender() const;

    // SET ID AND REMOVE OLD ONE FROM VECTOR usedIds
    void changeId(const unsigned int id);
    void setNameFirst(const std::string name);
    void setNameSecond(const std::string name);

    void setTimeBirthday(const unsigned int time);

   private:
    // SET ID, CALLED IN CONSTRUCTOR
    void setId(const unsigned int id);

    unsigned int id;
    std::string nameFirst;
    std::string nameSecond;

    unsigned int timeBirthday;  // time in miliseconds UTC
    Gender gender;
};

#endif
#include "Passenger.h"

Passenger::Passenger(unsigned int& id,
                     std::string& nameFirst,
                     std::string& nameSecond,
                     unsigned int& timeBirthday,
                     Gender& gender) : Person(id, nameFirst, nameSecond, timeBirthday, gender) {
    this->flights = {};
}

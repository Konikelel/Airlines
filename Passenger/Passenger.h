#include <memory>
#include <string>
#include <vector>

#ifndef PASSENGER_H
#define PASSENGER_H

#include "../Flight/Flight.h"
#include "../Person/Person.h"

class Passenger : public Person {
    std::vector<std::shared_ptr<Flight>> pFlights;
};

#endif
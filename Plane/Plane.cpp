#include "Plane.h"

#include "../Utils/CustomErrors.h"
#include "../Utils/VectorHandler.h"

std::vector<unsigned int> Plane::usedIds = {};

Plane::Plane(unsigned int id,
             std::string name,
             unsigned int capacityPassengers,
             unsigned int requiredStewardess,
             unsigned int requiredPilots) : name{name},
                                            capacityPassengers{capacityPassengers},
                                            requiredStewardess{requiredStewardess},
                                            requiredPilots{requiredPilots} {
    setId(id);
}

void Plane::setId(const unsigned int id) {
    if (FindInVector(usedIds, id) != usedIds.end())
        throw NonUniqueIDException();

    this->id = id;
}

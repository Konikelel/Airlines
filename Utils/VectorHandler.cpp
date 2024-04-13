#include "VectorHandler.hpp"

bool operator==(const Person& one, const Person& other) {
    return one.getId() == other.getId();
}

bool operator==(const Flight& one, const Flight& other) {
    return one.getFlightNr() == other.getFlightNr();  // ADD ID TO FLIGHT
}

bool operator==(const Plane& one, const Plane& other) {
    return one.getId() == other.getId();
}
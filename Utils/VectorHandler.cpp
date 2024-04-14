#include "VectorHandler.hpp"

bool operator==(const Person& one, const Person& other) {
    return one.getId() == other.getId();
}

bool operator==(const Flight& one, const Flight& other) {  // IMPLEMENT ID
    return one.getFlightNr() == other.getFlightNr() && one.getTimeDeparture() == other.getTimeDeparture() && one.getTimeArrival() == other.getTimeArrival();
}

bool operator==(const Plane& one, const Plane& other) {
    return one.getId() == other.getId();
}
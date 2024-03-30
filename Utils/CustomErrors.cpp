#include "CustomErrors.h"

const char* NonUniqueIDException::what() const noexcept {
    return "ID provided is not unique.";
}

const char* CannotAllocateMemory::what() const noexcept {
    return "Cannot allocate memory.";
}

InvalidFlightNr::InvalidFlightNr(const std::string& msg) : message{msg} {
}

const char* InvalidFlightNr::what() const noexcept {
    return ("Invalid Flight Number: " + message).c_str();
}

InvalidPlane::InvalidPlane(const std::string& msg) : message{msg} {
}

const char* InvalidPlane::what() const noexcept {
    return ("Invalid Plane: " + message).c_str();
}

InvalidTime::InvalidTime(const std::string& msg) : message{msg} {
}

const char* InvalidTime::what() const noexcept {
    return ("Invalid Time: " + message).c_str();
}

InvalidCrew::InvalidCrew(const std::string& msg) : message{msg} {
}

const char* InvalidCrew::what() const noexcept {
    return ("Invalid Crew: " + message).c_str();
}

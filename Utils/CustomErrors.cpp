#include "CustomErrors.h"

const char* NonUniqueIDException::what() const noexcept {
    return "ID provided is not unique.";
}

const char* CannotAllocateMemory::what() const noexcept {
    return "Cannot allocate memory.";
}

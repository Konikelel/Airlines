#include "CustomErrors.h"

const char* NonUniqueIDException::what() const noexcept {
    return "ID provided is not unique.";
}
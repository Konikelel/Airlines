#include "CustomErrors.hpp"

const char* NonUniqueIDException::what() const noexcept {
    return "ID provided is not unique.";
}
#include "CustomErrors.h"

const char* NonUniqueIDException::what() const noexcept {
    return "ID provided is not unique.";
}

template <typename T>
const char* CustomException<T>::what() const noexcept {
    return message.c_str();
}

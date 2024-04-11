#include <exception>
#include <string>

#ifndef CUSTOM_ERRORS_H
#define CUSTOM_ERRORS_H

class NonUniqueIDException : public std::exception {
   public:
    const char* what() const noexcept override;
};

template <typename T>
class CustomException : public std::exception {
   public:
    CustomException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    };

   private:
    std::string message;
};

using InvalidPointer = CustomException<std::exception>;
using InvalidFlightNr = CustomException<std::exception>;
using InvalidPlane = CustomException<std::exception>;
using InvalidTime = CustomException<std::exception>;
using InvalidCrew = CustomException<std::exception>;
using InvalidName = CustomException<std::exception>;
using MaximumCapacity = CustomException<std::exception>;
using DuplicationError = CustomException<std::exception>;

#endif
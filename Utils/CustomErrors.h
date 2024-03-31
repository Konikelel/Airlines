#include <exception>
#include <string>

#ifndef CUSTOM_ERRORS_H
#define CUSTOM_ERRORS_H

template <typename T>
class CustomException : public std::exception {
   public:
    CustomException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override;

   private:
    std::string message;
};

class NonUniqueIDException : public std::exception {
   public:
    const char* what() const noexcept override;
};

using InvalidFlightNr = CustomException<InvalidFlightNr>;
using InvalidPlane = CustomException<InvalidPlane>;
using InvalidTime = CustomException<InvalidTime>;
using InvalidCrew = CustomException<InvalidCrew>;

#endif
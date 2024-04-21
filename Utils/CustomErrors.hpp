#include <exception>
#include <string>

#ifndef CUSTOM_ERRORS_H
#define CUSTOM_ERRORS_H

class NonUniqueIDException : public std::exception {
   public:
    const char* what() const noexcept override;
};

class CustomException : public std::exception {
   public:
    CustomException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    };

   private:
    std::string message;
};

class InvalidPointer : public CustomException {
    using CustomException::CustomException;
};
class InvalidFlightNr : public CustomException {
    using CustomException::CustomException;
};
class InvalidPlane : public CustomException {
    using CustomException::CustomException;
};
class InvalidTime : public CustomException {
    using CustomException::CustomException;
};
class InvalidCrew : public CustomException {
    using CustomException::CustomException;
};
class InvalidName : public CustomException {
    using CustomException::CustomException;
};
class InvalidNumber : public CustomException {
    using CustomException::CustomException;
};
class MaximumCapacity : public CustomException {
    using CustomException::CustomException;
};
class DuplicationError : public CustomException {
    using CustomException::CustomException;
};
class CannotPerform : public CustomException {
    using CustomException::CustomException;
};
class TimeOverlap : public CustomException {
    using CustomException::CustomException;
};

#endif
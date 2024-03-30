#include <exception>
#include <string>

#ifndef CUSTOM_ERRORS_H
#define CUSTOM_ERRORS_H

class NonUniqueIDException : public std::exception {
   public:
    const char* what() const noexcept override;
};

class CannotAllocateMemory : public std::exception {
   public:
    const char* what() const noexcept override;
};

class InvalidFlightNr : public std::exception {
   public:
    InvalidFlightNr(const std::string& msg);

    const char* what() const noexcept override;

   private:
    std::string message;
};

class InvalidPlane : public std::exception {
   public:
    InvalidPlane(const std::string& msg);

    const char* what() const noexcept override;

   private:
    std::string message;
};

class InvalidTime : public std::exception {
   public:
    InvalidTime(const std::string& msg);

    const char* what() const noexcept override;

   private:
    std::string message;
};

class InvalidCrew : public std::exception {
   public:
    InvalidCrew(const std::string& msg);

    const char* what() const noexcept override;

   private:
    std::string message;
};

#endif
#include <exception>

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

#endif
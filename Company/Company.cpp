#include "Company.hpp"

#include "CustomErrors.hpp"

Company::Company(std::string name) : planes{{}},
                                     flights{{}},
                                     stewardesses{{}},
                                     pilots{{}} {
    setName(name);
}

void Company::setName(std::string name) {
    if (!name.size())
        throw InvalidName("First name must contain any character");

    this->name = name;
}
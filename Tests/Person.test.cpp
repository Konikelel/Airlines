#include "Person/Person.h"

#include <iostream>

#include "Tests.h"

int testPerson() {
    std::cout << "Testing Person class:" << std::endl;
    bool passed = false;
    Person person{100, "Victor", "Alb", 0, MALE};

    std::cout << "Testing constructor and setters... ";
    {
        Person person1{0, "Anna", "B", 1, FEMALE};
        person1.setId(1);
        person1.setNameFirst("Joe");
        person1.setNameSecond("sth");
        person1.setTimeBirthday(2);

        passed = (person1.getId() == 1 && person1.getNameFirst() == "Joe" &&
                  person1.getNameSecond() == "Sth" && person1.getTimeBirthday() == 2);
    }
    std::cout << (passed ? "Passed" : throw std::runtime_error("Failed")) << std::endl;

    return 0;
}
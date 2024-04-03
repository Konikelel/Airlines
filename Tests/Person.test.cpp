#include "Person/Person.h"

#include <iostream>

#include "Tests.h"
#include "Utils/CustomErrors.h"

int testPerson() {
    std::cout << "Testing Person class:" << std::endl;
    bool passed = false;
    Person person{100, "Victor", "Alb", 0, MALE};

    std::cout << "Testing constructor and setters... ";
    {
        Person person1{0, "Anna", "B", 1, FEMALE};
        person1.changeId(1);
        person1.setNameFirst("joe");
        person1.setNameSecond("sth");
        person1.setTimeBirthday(2);

        passed = (person1.getId() == 1 && person1.getNameFirst() == "Joe" &&
                  person1.getNameSecond() == "Sth" && person1.getTimeBirthday() == 2);
    }
    std::cout << (passed ? "Passed" : throw std::runtime_error("Failed")) << std::endl;

    std::cout << "Testing uniqueId... ";
    passed = false;
    {
        Person person2{2, "Joe", "Bib", 2, MALE};
        try {
            person.changeId(100);
        } catch (const NonUniqueIDException& e) {
            passed = true;
        }
    }
    std::cout << (passed ? "Passed" : throw std::runtime_error("Failed")) << std::endl;

    std::cout << "Testing destructor... ";
    passed = true;
    {
        try {
            person.changeId(1);
        } catch (const NonUniqueIDException& e) {
            passed = false;
        }
    }
    std::cout << (passed ? "Passed" : throw std::runtime_error("Failed")) << std::endl;

    return 0;
}
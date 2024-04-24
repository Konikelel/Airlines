#include "Person.hpp"

#include <gtest/gtest.h>

#include "CustomErrors.hpp"
#include "VectorHandler.hpp"

TEST(person, constructor) {
    Person person{"Victor", "Alb", 2, MALE};
    // getNameFirst
    EXPECT_EQ(person.getNameFirst(), "Victor");
    // getNameSecond
    EXPECT_EQ(person.getNameSecond(), "Alb");
    // getTimeBirthday
    EXPECT_EQ(person.getTimeBirthday(), 2);
    // getGender
    EXPECT_EQ(person.getGender(), MALE);
}

TEST(person, destructor) {
    Person person{"Victor", "Alb", 1, MALE};
}

TEST(person, setters) {
    Person person1{"Victor", "Alb", 1, MALE};
    Person person2{"Jacob", "Web", 2, MALE};
    // setNameFirst
    person1.setNameFirst("jacob");
    EXPECT_EQ(person1.getNameFirst(), "Jacob");

    EXPECT_THROW(person2.setNameFirst(""), InvalidName);
    // setNameSecond
    person1.setNameSecond("web");
    EXPECT_EQ(person1.getNameSecond(), "Web");

    EXPECT_THROW(person1.setNameSecond(""), InvalidName);
    // setTimeBirthday
    person2.setTimeBirthday(3);
    EXPECT_EQ(person2.getTimeBirthday(), 3);
}
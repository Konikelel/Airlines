#include "Person.hpp"

#include <gtest/gtest.h>

#include "CustomErrors.hpp"

TEST(PersonClass, constructor) {
    Person person{1, "Victor", "Alb", 2, MALE};
    // getId
    EXPECT_EQ(person.getId(), 1);
    // getNameFirst
    EXPECT_EQ(person.getNameFirst(), "Victor");
    // getNameSecond
    EXPECT_EQ(person.getNameSecond(), "Alb");
    // getTimeBirthday
    EXPECT_EQ(person.getTimeBirthday(), 2);
    // getGender
    EXPECT_EQ(person.getGender(), MALE);
}

TEST(PersonClass, destructor) {
    Person person{2, "Victor", "Alb", 1, MALE};

    EXPECT_NO_THROW(person.changeId(1));
}

TEST(PersonClass, setters) {
    Person person1{1, "Victor", "Alb", 1, MALE};
    Person person2{2, "Jacob", "Web", 2, MALE};
    // changeId
    EXPECT_THROW(person2.changeId(1), NonUniqueIDException);
    // setNameFirst
    EXPECT_THROW(person2.setNameFirst(""), InvalidName);
    person1.setNameFirst("jacob");
    EXPECT_EQ(person1.getNameFirst(), "Jacob");
    // setNameSecond
    EXPECT_THROW(person1.setNameSecond(""), InvalidName);
    person1.setNameSecond("web");
    EXPECT_EQ(person1.getNameSecond(), "Web");
    // setTimeBirthday
    person2.setTimeBirthday(3);
    EXPECT_EQ(person2.getTimeBirthday(), 3);
}
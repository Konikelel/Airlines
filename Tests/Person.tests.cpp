#include "Person.hpp"

#include <gtest/gtest.h>

#include "CustomErrors.hpp"
#include "VectorHandler.hpp"

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
    person2.changeId(3);
    EXPECT_EQ(person2.getId(), 3);
    EXPECT_EQ(person2.usedIds.size(), 2);

    EXPECT_THROW(person2.changeId(1), NonUniqueIDException);
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
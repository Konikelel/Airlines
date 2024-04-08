#include "Person.h"

#include <gtest/gtest.h>

#include "CustomErrors.h"

TEST(PersonClass, constructor) {
    Person person{1, "Victor", "Alb", 1, MALE};

    EXPECT_EQ(person.getId(), 1);
    EXPECT_EQ(person.getNameFirst(), "Victor");
    EXPECT_EQ(person.getNameSecond(), "Alb");
    EXPECT_EQ(person.getTimeBirthday(), 1);
    EXPECT_EQ(person.getGender(), MALE);
}

TEST(PersonClass, destructor) {
    Person person{2, "Victor", "Alb", 1, MALE};

    EXPECT_NO_THROW(person.changeId(1));
}

TEST(PersonClass, setters) {
    Person person1{1, "Victor", "Alb", 1, MALE};
    Person person2{2, "Jacob", "Web", 2, MALE};

    EXPECT_THROW(person2.changeId(1), NonUniqueIDException);

    EXPECT_THROW(person2.setNameFirst(""), InvalidName);
    EXPECT_THROW(person2.setNameSecond(""), InvalidName);

    person2.setNameFirst("jacob");
    EXPECT_EQ(person2.getNameFirst(), "Jacob");
    person2.setNameFirst("web");
    EXPECT_EQ(person2.getNameSecond(), "Web");
}
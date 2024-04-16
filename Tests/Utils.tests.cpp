#include <gtest/gtest.h>

#include "CustomErrors.hpp"
#include "ListHandler.hpp"
#include "StringHandler.hpp"
#include "VectorHandler.hpp"

TEST(utils, stringHandler) {
    // TO LOWER
    EXPECT_EQ(toLower("ABC"), "abc");
    EXPECT_EQ(toLower("aBC"), "abc");
    EXPECT_EQ(toLower("AbC"), "abc");
    EXPECT_EQ(toLower("ABc"), "abc");
    EXPECT_EQ(toLower("abc"), "abc");
    // TO UPPER
    EXPECT_EQ(toUpper("abc"), "ABC");
    EXPECT_EQ(toUpper("Abc"), "ABC");
    EXPECT_EQ(toUpper("aBc"), "ABC");
    EXPECT_EQ(toUpper("abC"), "ABC");
    EXPECT_EQ(toUpper("ABC"), "ABC");
    // TO TITLE
    EXPECT_EQ(toTitle("abc"), "Abc");
    EXPECT_EQ(toTitle("Abc"), "Abc");
    EXPECT_EQ(toTitle("aBc"), "Abc");
    EXPECT_EQ(toTitle("abC"), "Abc");
    EXPECT_EQ(toTitle("ABC"), "Abc");
}

TEST(utils, vectorHandler) {
    std::vector<int> example = {1, 2, 3, 4, 5, 6, 7, 8};
    // NOT CHANGED VECTOR
    EXPECT_EQ(*findVector(example, 1), 1);
    EXPECT_EQ(*findVector(example, 4), 4);
    EXPECT_EQ(*findVector(example, 8), 8);

    EXPECT_EQ(findVector(example, 0), example.end());
    EXPECT_EQ(findVector(example, 9), example.end());

    EXPECT_TRUE(existVector(example, 1));
    EXPECT_TRUE(existVector(example, 4));
    EXPECT_TRUE(existVector(example, 8));

    EXPECT_FALSE(existVector(example, 0));
    EXPECT_FALSE(existVector(example, 9));
    // ADDING ELEMENTS TO VECTOR
    int number1 = 0;
    int number2 = 9;
    addVector(example, number1);
    addVector(example, number2);

    EXPECT_EQ(*findVector(example, 0), 0);
    EXPECT_EQ(*findVector(example, 9), 9);

    EXPECT_TRUE(existVector(example, 0));
    EXPECT_TRUE(existVector(example, 9));
    // REMOVING ELEMENTS FROM VECTOR
    deleteVector(example, 0);
    deleteVector(example, 9);

    EXPECT_EQ(findVector(example, 0), example.end());
    EXPECT_EQ(findVector(example, 9), example.end());

    EXPECT_FALSE(existVector(example, 0));
    EXPECT_FALSE(existVector(example, 9));
}

TEST(utils, listHandler) {
    std::list<int> example = {1, 2, 3, 4, 5, 6, 7, 8};
    // NOT CHANGED VECTOR
    EXPECT_EQ(*findList(example, 1), 1);
    EXPECT_EQ(*findList(example, 4), 4);
    EXPECT_EQ(*findList(example, 8), 8);

    EXPECT_EQ(findList(example, 0), example.end());
    EXPECT_EQ(findList(example, 9), example.end());

    EXPECT_TRUE(existList(example, 1));
    EXPECT_TRUE(existList(example, 4));
    EXPECT_TRUE(existList(example, 8));

    EXPECT_FALSE(existList(example, 0));
    EXPECT_FALSE(existList(example, 9));
    // ADDING ELEMENTS TO VECTOR
    int number1 = 0;
    int number2 = 9;
    addList(example, number1);
    addList(example, number2);

    EXPECT_EQ(*findList(example, 0), 0);
    EXPECT_EQ(*findList(example, 9), 9);

    EXPECT_TRUE(existList(example, 0));
    EXPECT_TRUE(existList(example, 9));
    // REMOVING ELEMENTS FROM VECTOR
    deleteList(example, 0);
    deleteList(example, 9);

    EXPECT_EQ(findList(example, 0), example.end());
    EXPECT_EQ(findList(example, 9), example.end());

    EXPECT_FALSE(existList(example, 0));
    EXPECT_FALSE(existList(example, 9));
}
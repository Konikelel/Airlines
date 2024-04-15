#include <gtest/gtest.h>

#include "CustomErrors.hpp"
#include "StringHandler.hpp"
#include "VectorHandler.hpp"

TEST(utils, stringHandler) {
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
}
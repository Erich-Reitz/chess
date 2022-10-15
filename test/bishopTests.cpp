#include "../src/pieces/Bishop.cpp"

#include "gtest/gtest.h"

namespace {
    TEST(test_bishop, TestCannotMoveToSamePosition) {
        Bishop *bishop = new Bishop(); 
        EXPECT_EQ(bishop->canMove(0, 0, 0, 0), false); 
    }

    TEST(test_bishop, TestCannotMoveHorizontally) {
        Bishop *bishop = new Bishop(); 
        EXPECT_EQ(bishop->canMove(0, 0, 7, 0), false); 
        EXPECT_EQ(bishop->canMove(7, 0, 0, 0), false); 
    }

    TEST(test_bishop, TestCannotMoveVertically) {
        Bishop *bishop = new Bishop(); 
        EXPECT_EQ(bishop->canMove(0, 7, 0, 0), false); 
        EXPECT_EQ(bishop->canMove(7, 0, 7, 7), false); 
    }

    TEST(test_bishop, TestCanMoveDiagonallyUpRight) {
        Bishop *bishop = new Bishop(); 
        EXPECT_EQ(bishop->canMove(0, 0, 1, 1), true); 
    }

    TEST(test_bishop, TestCanMoveDiagonallyDownLeft) {
        Bishop *bishop = new Bishop(); 
        EXPECT_EQ(bishop->canMove(1, 1, 0, 0), true); 
    }
}
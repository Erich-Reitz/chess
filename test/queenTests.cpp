#include "../src/pieces/Queen.cpp"

#include "gtest/gtest.h"

namespace {
    TEST(test_queen, TestCannotMoveToSamePosition) {
        Queen *queen = new Queen(); 
        EXPECT_EQ(queen->canMove(0, 0, 0, 0), false); 
    }

    TEST(test_queen, TestCanMoveHorizontally) {
        Queen *queen = new Queen(); 
        EXPECT_EQ(queen->canMove(0, 0, 7, 0), true); 
        EXPECT_EQ(queen->canMove(7, 0, 0, 0), true); 
    }

    TEST(test_queen, TestCanMoveVertically) {
        Queen *queen = new Queen(); 
        EXPECT_EQ(queen->canMove(0, 7, 0, 0), true); 
        EXPECT_EQ(queen->canMove(7, 0, 7, 7), true); 
    }

    TEST(test_queen, TestCanMoveDiagonallyUpRight) {
        Queen *queen = new Queen(); 
        EXPECT_EQ(queen->canMove(0, 0, 1, 1), true); 
    }

    TEST(test_queen, TestCanMoveDiagonallyDownLeft) {
        Queen *queen = new Queen(); 
        EXPECT_EQ(queen->canMove(1, 1, 0, 0), true); 
    }

    TEST(test_queen, TestQueenCannotMoveInvalidMove) {
        Queen *queen = new Queen(); 
        EXPECT_EQ(queen->canMove(0, 0, 2, 3), false); 
    }
}
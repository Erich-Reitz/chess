#include "../src/pieces/King.cpp"

#include "gtest/gtest.h"

namespace {
    TEST(test_king, TestCannotMoveToSamePosition) {
        King *king = new King(); 
        EXPECT_EQ(king->canMove(0, 0, 0, 0), false); 
    }

    TEST(test_king, TestCanMoveHorizontally) {
        King *king = new King(); 
        EXPECT_EQ(king->canMove(0, 0, 7, 0), true); 
        EXPECT_EQ(king->canMove(7, 0, 0, 0), true); 
    }

    TEST(test_king, TestCanMoveVertically) {
        King *king = new King(); 
        EXPECT_EQ(king->canMove(0, 7, 0, 0), true); 
        EXPECT_EQ(king->canMove(7, 0, 7, 7), true); 
    }

    TEST(test_king, TestCanMoveDiagonallyUpRight) {
        King *king = new King(); 
        EXPECT_EQ(king->canMove(0, 0, 1, 1), true); 
    }

    TEST(test_king, TestCanMoveDiagonallyDownLeft) {
        King *king = new King(); 
        EXPECT_EQ(king->canMove(1, 1, 0, 0), true); 
    }

    TEST(test_king, TestKingCannotMoveInvalidMove) {
        King *king = new King(); 
        EXPECT_EQ(king->canMove(0, 0, 2, 3), false); 
    }
}
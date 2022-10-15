#include "../src/pieces/King.cpp"

#include "gtest/gtest.h"

namespace {
    TEST(test_king, TestCannotMoveToSamePosition) {
        King *king = new King(); 
        EXPECT_EQ(king->canMove(0, 0, 0, 0), false); 
    }

    TEST(test_king, TestCanMoveOneToTheRight) {
        King *king = new King(); 
        EXPECT_EQ(king->canMove(0, 0, 1, 0), true);
    }

    TEST(test_king, TestCanMoveOneUp) {
        King *king = new King(); 
        EXPECT_EQ(king->canMove(0, 0, 0, 1), true);
    }

    TEST(test_king, TestCanMoveOneDown) {
        King *king = new King(); 
        EXPECT_EQ(king->canMove(0, 1, 0, 0), true);
    }

    TEST(test_king, TestCanMoveOneLeft) {
        King *king = new King(); 
        EXPECT_EQ(king->canMove(1, 0, 0, 0), true);
    }

    TEST(test_king, TestCanMoveOneUpRight) {
        King *king = new King(); 
        EXPECT_EQ(king->canMove(0, 0, 1, 1), true);
    }

    TEST(test_king, TestCanMoveOneUpLeft) {
        King *king = new King(); 
        EXPECT_EQ(king->canMove(1, 0, 0, 1), true);
    }

    TEST(test_king, TestCanMoveOneDownRight) {
        King *king = new King(); 
        EXPECT_EQ(king->canMove(0, 1, 1, 0), true);
    }

    TEST(test_king, TestCanMoveOneDownLeft) {
        King *king = new King(); 
        EXPECT_EQ(king->canMove(1, 1, 0, 0), true);
    }

    TEST(test_king, TestKingCannotMoveTwoDiagonally) {
        King *king = new King(); 
        EXPECT_EQ(king->canMove(0, 0, 2, 2), false);
    }
}
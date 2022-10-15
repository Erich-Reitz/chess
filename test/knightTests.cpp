#include "../src/pieces/Knight.cpp"

#include "gtest/gtest.h"

namespace {
    int originalRow = 4; 
    int originalCol = 4; 

    TEST(test_knight, TestCannotMoveToSamePosition) {
        Knight *knight = new Knight(); 
        EXPECT_EQ(knight->canMove(originalCol, originalRow, originalCol, originalRow), false); 
    }

    TEST(test_knight, TestCanMoveTwoUpAndLeftOne) {
        Knight *knight = new Knight(); 
        EXPECT_EQ(knight->canMove(originalCol, originalRow, originalCol - 1, originalRow + 2), true); 
    }

    TEST(test_knight, TestCanMoveOneUpAndLeftTwo) {
        Knight *knight = new Knight(); 
        EXPECT_EQ(knight->canMove(originalCol, originalRow, originalCol - 2, originalRow + 1), true); 
    }

    TEST(test_knight, TestCanMoveTwoUpAndRightOne) {
        Knight *knight = new Knight(); 
        EXPECT_EQ(knight->canMove(originalCol, originalRow, originalCol + 1, originalRow + 2), true); 
    }

    TEST(test_knight, TestCanMoveOneUpAndRightTwo) {
        Knight *knight = new Knight(); 
        EXPECT_EQ(knight->canMove(originalCol, originalRow, originalCol + 2, originalRow + 1), true); 
    }

    // --- //

    TEST(test_knight, TestCanMoveTwoDownAndLeftOne) {
        Knight *knight = new Knight(); 
        EXPECT_EQ(knight->canMove(originalCol, originalRow, originalCol - 1, originalRow - 2), true); 
    }

    TEST(test_knight, TestCanMoveOneDownAndLeftTwo) {
        Knight *knight = new Knight(); 
        EXPECT_EQ(knight->canMove(originalCol, originalRow, originalCol - 2, originalRow - 1), true); 
    }

    TEST(test_knight, TestCanMoveTwoDownAndRightOne) {
        Knight *knight = new Knight(); 
        EXPECT_EQ(knight->canMove(originalCol, originalRow, originalCol + 1, originalRow - 2), true); 
    }

    TEST(test_knight, TestCanMoveOneDownAndRightTwo) {
        Knight *knight = new Knight(); 
        EXPECT_EQ(knight->canMove(originalCol, originalRow, originalCol + 2, originalRow - 1), true); 
        delete knight; 
    }
    

    TEST(test_knight, TestCannotMoveOneToTheRight) {
        Knight *knight = new Knight(); 
        EXPECT_EQ(knight->canMove(originalCol, originalRow, originalCol + 1, originalRow), false); 
    }
}
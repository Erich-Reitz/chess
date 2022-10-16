#include "../src/pieces/Pawn.cpp"

#include "gtest/gtest.h"

namespace {
    TEST(test_pawn, TestCannotMoveToSamePosition) {
        Pawn *pawn = new Pawn(); 
        EXPECT_EQ(pawn->canMove(0, 0, 0, 0), false); 
    }

    TEST(test_pawn, TestWhitePawnCanMoveOneFirstMove) {
        Pawn *pawn = new Pawn(true); 
        EXPECT_EQ(pawn->canMove(0, 6, 0, 5), true); 
    }

    TEST(test_pawn, TestWhitePawnCanMoveTwoFirstMove) {
        Pawn *pawn = new Pawn(true); 
        EXPECT_EQ(pawn->canMove(0, 6, 0, 4), true); 
    }
    TEST(test_pawn, TestWhitePawnCannotMoveThreeFirstMove) {
        Pawn *pawn = new Pawn(true); 
        EXPECT_EQ(pawn->canMove(0, 6, 0, 3), false); 
    }

    TEST(test_pawn, TestBlackPawnCanMoveOneFirstMove) {
        Pawn *pawn = new Pawn(false); 
        EXPECT_EQ(pawn->canMove(0, 1, 0, 2), true); 
    }

    TEST(test_pawn, TestBlackPawnCanMoveTwoFirstMove) {
        Pawn *pawn = new Pawn(false); 
        EXPECT_EQ(pawn->canMove(0, 1, 0, 3), true); 
    }
    TEST(test_pawn, TestBlackPawnCannotMoveThreeFirstMove) {
        Pawn *pawn = new Pawn(false); 
        EXPECT_EQ(pawn->canMove(0, 1, 0, 4), false); 
    }

    TEST(test_pawn, TestPawnCannotMoveTwoIfHasAlreadyMoved) {
        Pawn *pawn = new Pawn(false); 
        pawn->setMoved(true); 
        EXPECT_EQ(pawn->canMove(0, 2, 0, 4), false); 
    }

}
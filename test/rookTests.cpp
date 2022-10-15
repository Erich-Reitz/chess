#include "../src/pieces/Rook.cpp"

#include "gtest/gtest.h"

namespace {
    TEST(test_rook, TestCannotMoveToSamePosition) {
        Rook *rook = new Rook(); 
        EXPECT_EQ(rook->canMove(0, 0, 0, 0), false); 
    }


    TEST(test_rook, TestCanMoveHorizontally) {
        Rook *rook = new Rook(); 
        EXPECT_EQ(rook->canMove(0, 0, 7, 0), true); 
        EXPECT_EQ(rook->canMove(7, 0, 0, 0), true); 
    }

    TEST(test_rook, TestCanMoveVertically) {
        Rook *rook = new Rook(); 
        EXPECT_EQ(rook->canMove(0, 7, 0, 0), true); 
        EXPECT_EQ(rook->canMove(7, 0, 7, 7), true); 
    }

    TEST(test_rook, TestCannotMoveDiagonallyUpRight) {
        Rook *rook = new Rook(); 
        EXPECT_EQ(rook->canMove(0, 0, 1, 1), false); 
    }

    TEST(test_rook, TestCannotMoveDiagonallyDownLeft) {
        Rook *rook = new Rook(); 
        EXPECT_EQ(rook->canMove(1, 1, 0, 0), false); 
    }
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
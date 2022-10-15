#include <limits.h>
#include <string>
#include <random>


#include "gtest/gtest.h"

#include "bishopTests.cpp"
#include "rookTests.cpp"


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
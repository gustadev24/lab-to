// Create tests for substractOperation
#include <gtest/gtest.h>
#include "operations/substract.h"

TEST(SubstractOperationTest, BasicSubstract) {
    SubstractOperation sub(5, 3);
    EXPECT_DOUBLE_EQ(sub.getResult(), 2);
}

TEST(SubstractOperationTest, NegativeSubstract) {
    SubstractOperation sub(-5, -3);
    EXPECT_DOUBLE_EQ(sub.getResult(), -2);
}

TEST(SubstractOperationTest, MixedSubstract) {
    SubstractOperation sub(5, -3);
    EXPECT_DOUBLE_EQ(sub.getResult(), 8);
}

TEST(SubstractOperationTest, ZeroSubstract) {
    SubstractOperation sub(0, 0);
    EXPECT_DOUBLE_EQ(sub.getResult(), 0);
}

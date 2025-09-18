#include <gtest/gtest.h>
#include "operations/sum.h"

TEST(SumOperationTest, BasicSum) {
    SumOperation sum(3, 5);
    EXPECT_DOUBLE_EQ(sum.getResult(), 8);
}

TEST(SumOperationTest, NegativeSum) {
    SumOperation sum(-3, -5);
    EXPECT_DOUBLE_EQ(sum.getResult(), -8);
}

TEST(SumOperationTest, MixedSum) {
    SumOperation sum(-3, 5);
    EXPECT_DOUBLE_EQ(sum.getResult(), 2);
}

TEST(SumOperationTest, ZeroSum) {
    SumOperation sum(0, 0);
    EXPECT_DOUBLE_EQ(sum.getResult(), 0);
}

#include <gtest/gtest.h>
#include "operations/sum.h"

TEST(SumOperationTest, BasicSum) {
    SumOperation* sum = new SumOperation(3, 5);
    EXPECT_DOUBLE_EQ(sum->getResult(), 8);
    delete sum;
}

TEST(SumOperationTest, NegativeSum) {
    SumOperation* sum = new SumOperation(-3, -5);
    EXPECT_DOUBLE_EQ(sum->getResult(), -8);
    delete sum;
}

TEST(SumOperationTest, MixedSum) {
    SumOperation* sum = new SumOperation(-3, 5);
    EXPECT_DOUBLE_EQ(sum->getResult(), 2);
    delete sum;
}

TEST(SumOperationTest, ZeroSum) {
    SumOperation* sum = new SumOperation(0, 0);
    EXPECT_DOUBLE_EQ(sum->getResult(), 0);
    delete sum;
}

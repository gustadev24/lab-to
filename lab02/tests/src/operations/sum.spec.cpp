#include <gtest/gtest.h>
#include "operations/sum.h"
#include <memory>

TEST(SumOperationTest, BasicSum) {
    std::unique_ptr<SumOperation> sum = std::make_unique<SumOperation>(3, 5);
    EXPECT_DOUBLE_EQ(sum->getResult(), 8);
}

TEST(SumOperationTest, NegativeSum) {
    std::unique_ptr<SumOperation> sum = std::make_unique<SumOperation>(-3, -5);
    EXPECT_DOUBLE_EQ(sum->getResult(), -8);
}

TEST(SumOperationTest, MixedSum) {
    std::unique_ptr<SumOperation> sum = std::make_unique<SumOperation>(-3, 5);
    EXPECT_DOUBLE_EQ(sum->getResult(), 2);
}

TEST(SumOperationTest, ZeroSum) {
    std::unique_ptr<SumOperation> sum = std::make_unique<SumOperation>(0, 0);
    EXPECT_DOUBLE_EQ(sum->getResult(), 0);
}

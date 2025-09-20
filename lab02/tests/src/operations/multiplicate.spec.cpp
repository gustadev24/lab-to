#include <gtest/gtest.h>
#include "operations/multiplicate.h"
#include <memory>

TEST(MultiplicateOperationTest, BasicMultiplication) {
    std::unique_ptr<MultiplicateOperation> mul = std::make_unique<MultiplicateOperation>(3, 5);
    EXPECT_DOUBLE_EQ(mul->getResult(), 15);
}

TEST(MultiplicateOperationTest, NegativeMultiplication) {
    std::unique_ptr<MultiplicateOperation> mul = std::make_unique<MultiplicateOperation>(-3, -5);
    EXPECT_DOUBLE_EQ(mul->getResult(), 15);
}

TEST(MultiplicateOperationTest, MixedMultiplication) {
    std::unique_ptr<MultiplicateOperation> mul = std::make_unique<MultiplicateOperation>(-3, 5);
    EXPECT_DOUBLE_EQ(mul->getResult(), -15);
}

TEST(MultiplicateOperationTest, ZeroMultiplication) {
    std::unique_ptr<MultiplicateOperation> mul = std::make_unique<MultiplicateOperation>(0, 5);
    EXPECT_DOUBLE_EQ(mul->getResult(), 0);
}

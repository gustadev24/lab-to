#include <gtest/gtest.h>
#include "operations/multiplicate.h"

TEST(MultiplicateOperationTest, BasicMultiplication) {
    MultiplicateOperation* mul = new MultiplicateOperation(3, 5);
    EXPECT_DOUBLE_EQ(mul->getResult(), 15);
    delete mul;
}

TEST(MultiplicateOperationTest, NegativeMultiplication) {
    MultiplicateOperation* mul = new MultiplicateOperation(-3, -5);
    EXPECT_DOUBLE_EQ(mul->getResult(), 15);
    delete mul;
}

TEST(MultiplicateOperationTest, MixedMultiplication) {
    MultiplicateOperation* mul = new MultiplicateOperation(-3, 5);
    EXPECT_DOUBLE_EQ(mul->getResult(), -15);
    delete mul;
}

TEST(MultiplicateOperationTest, ZeroMultiplication) {
    MultiplicateOperation* mul = new MultiplicateOperation(0, 5);
    EXPECT_DOUBLE_EQ(mul->getResult(), 0);
    delete mul;
}

#include <gtest/gtest.h>
#include "operations/multiplicate.h"

TEST(MultiplicateOperationTest, BasicMultiplication) {
    MultiplicateOperation mul(3, 5);
    EXPECT_DOUBLE_EQ(mul.getResult(), 15);
}

TEST(MultiplicateOperationTest, NegativeMultiplication) {
    MultiplicateOperation mul(-3, -5);
    EXPECT_DOUBLE_EQ(mul.getResult(), 15);
}

TEST(MultiplicateOperationTest, MixedMultiplication) {
    MultiplicateOperation mul(-3, 5);
    EXPECT_DOUBLE_EQ(mul.getResult(), -15);
}

TEST(MultiplicateOperationTest, ZeroMultiplication) {
    MultiplicateOperation mul(0, 5);
    EXPECT_DOUBLE_EQ(mul.getResult(), 0);
}

#include <gtest/gtest.h>
#include "operations/divide.h"

TEST(DivideOperationTest, DivideByZero) {
    EXPECT_THROW(DivideOperation(3, 0), std::runtime_error);
}

TEST(DivideOperationTest, BasicDivision) {
    DivideOperation div(6, 3);
    EXPECT_DOUBLE_EQ(div.getResult(), 2);
}

TEST(DivideOperationTest, NegativeDivision) {
    DivideOperation div(-6, -3);
    EXPECT_DOUBLE_EQ(div.getResult(), 2);
}

TEST(DivideOperationTest, MixedDivision) {
    DivideOperation div(-6, 3);
    EXPECT_DOUBLE_EQ(div.getResult(), -2);
}

TEST(DivideOperationTest, FractionalDivision) {
    DivideOperation div(7, 2);
    EXPECT_DOUBLE_EQ(div.getResult(), 3.5);
}

TEST(DivideOperationTest, ZeroNumerator) {
    DivideOperation div(0, 5);
    EXPECT_DOUBLE_EQ(div.getResult(), 0);
}

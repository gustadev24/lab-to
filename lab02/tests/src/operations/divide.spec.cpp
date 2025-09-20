#include <gtest/gtest.h>
#include "operations/divide.h"

TEST(DivideOperationTest, DivideByZero) {
    DivideOperation* div = nullptr;
    EXPECT_THROW(div = new DivideOperation(3, 0), std::runtime_error);
}

TEST(DivideOperationTest, BasicDivision) {
    DivideOperation* div = new DivideOperation(6, 3);
    EXPECT_DOUBLE_EQ(div->getResult(), 2);
    delete div;
}

TEST(DivideOperationTest, NegativeDivision) {
    DivideOperation* div = new DivideOperation(-6, -3);
    EXPECT_DOUBLE_EQ(div->getResult(), 2);
    delete div;
}

TEST(DivideOperationTest, MixedDivision) {
    DivideOperation* div = new DivideOperation(-6, 3);
    EXPECT_DOUBLE_EQ(div->getResult(), -2);
    delete div;
}

TEST(DivideOperationTest, FractionalDivision) {
    DivideOperation* div = new DivideOperation(7, 2);
    EXPECT_DOUBLE_EQ(div->getResult(), 3.5);
    delete div;
}

TEST(DivideOperationTest, ZeroNumerator) {
    DivideOperation* div = new DivideOperation(0, 5);
    EXPECT_DOUBLE_EQ(div->getResult(), 0);
    delete div;
}

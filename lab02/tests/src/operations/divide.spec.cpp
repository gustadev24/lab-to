#include <gtest/gtest.h>
#include "operations/divide.h"
#include <memory>

TEST(DivideOperationTest, DivideByZero) {
    EXPECT_THROW(std::make_unique<DivideOperation>(3, 0), std::runtime_error);
}

TEST(DivideOperationTest, BasicDivision) {
    std::unique_ptr<DivideOperation> div = std::make_unique<DivideOperation>(6, 3);
    EXPECT_DOUBLE_EQ(div->getResult(), 2);
}

TEST(DivideOperationTest, NegativeDivision) {
    std::unique_ptr<DivideOperation> div = std::make_unique<DivideOperation>(-6, -3);
    EXPECT_DOUBLE_EQ(div->getResult(), 2);
}

TEST(DivideOperationTest, MixedDivision) {
    std::unique_ptr<DivideOperation> div = std::make_unique<DivideOperation>(-6, 3);
    EXPECT_DOUBLE_EQ(div->getResult(), -2);
}

TEST(DivideOperationTest, FractionalDivision) {
    std::unique_ptr<DivideOperation> div = std::make_unique<DivideOperation>(7, 2);
    EXPECT_DOUBLE_EQ(div->getResult(), 3.5);
}

TEST(DivideOperationTest, ZeroNumerator) {
    std::unique_ptr<DivideOperation> div = std::make_unique<DivideOperation>(0, 5);
    EXPECT_DOUBLE_EQ(div->getResult(), 0);
}

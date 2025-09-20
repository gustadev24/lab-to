#include "calculator.h"
#include <gtest/gtest.h>
#include <string>

TEST(CalculatorTest, ComputeBasicExpressions) {
  Calculator* calculator = new Calculator();

  // Test case 1: "12+34"
  EXPECT_DOUBLE_EQ(calculator->compute("12+34"), 46.0);

  // Test case 2: "42+1+34"
  EXPECT_DOUBLE_EQ(calculator->compute("42+1+34"), 77.0);

  // Test case 3: "1+2+3+4+5+6"
  EXPECT_DOUBLE_EQ(calculator->compute("1+2+3+4+5+6"), 21.0);

  delete calculator;
}

TEST(CalculatorTest, ComputeWithAllOperations) {
  Calculator* calculator = new Calculator();

  // Test case 1: "12+34-5*6/2"
  EXPECT_DOUBLE_EQ(calculator->compute("12+34-5*6/2"), 31.0);

  // Test case 2: "100/4+3*2-1"
  EXPECT_DOUBLE_EQ(calculator->compute("100/4+3*2-1"), 30.0);

  // Test case 3: "50-10*2+8/4"
  EXPECT_DOUBLE_EQ(calculator->compute("50-10*2+8/4"), 32.0);

  delete calculator;
}

TEST(CalculatorTest, ComputeWithNegativeNumbers) {
  Calculator* calculator = new Calculator();

  // Test case 1: "-5+10"
  EXPECT_DOUBLE_EQ(calculator->compute("-5+10"), 5.0);

  // Test case 2: "3+-2+7"
  EXPECT_DOUBLE_EQ(calculator->compute("3+-2+7"), 8.0);

  // Test case 3: "15+-10+5"
  EXPECT_DOUBLE_EQ(calculator->compute("15+-10+5"), 10.0);

  delete calculator;
}

TEST(CalculatorTest, ComputeWithSpaces) {
  Calculator* calculator = new Calculator();

  // Test case 1: " 12 + 34 "
  EXPECT_DOUBLE_EQ(calculator->compute(" 12 + 34 "), 46.0);

  // Test case 2: " 42 + 1 + 34 "
  EXPECT_DOUBLE_EQ(calculator->compute(" 42 + 1 + 34 "), 77.0);

  // Test case 3: " 1 + 2 + 3 + 4 + 5 + 6 "
  EXPECT_DOUBLE_EQ(calculator->compute(" 1 + 2 + 3 + 4 + 5 + 6 "), 21.0);

  delete calculator;
}

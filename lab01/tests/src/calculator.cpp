#include "calculator.h"
#include <gtest/gtest.h>
#include <string>

TEST(CalculatorTest, ComputeBasicExpressions) {
  Calculator calculator;

  // Test case 1: "12+34"
  EXPECT_DOUBLE_EQ(calculator.compute("12+34"), 46.0);

  // Test case 2: "42+1+34"
  EXPECT_DOUBLE_EQ(calculator.compute("42+1+34"), 77.0);

  // Test case 3: "1+2+3+4+5+6"
  EXPECT_DOUBLE_EQ(calculator.compute("1+2+3+4+5+6"), 21.0);
}

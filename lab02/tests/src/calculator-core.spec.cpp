#include "calculator-core.h"
#include <gtest/gtest.h>

TEST(CalculatorCoreTest, ComputeBasic) {
  CalculatorCore* solver = new CalculatorCore();
  solver->solve({"3", "4", "+", "2", "+"});
  EXPECT_DOUBLE_EQ(solver->getResult(), 9.0);
  delete solver;
}

TEST(CalculatorCoreTest, ComputeInvalid) {
  CalculatorCore* solver = new CalculatorCore();
  EXPECT_THROW(solver->solve({"12", "+", "*", "34"}), std::runtime_error);
  EXPECT_THROW(solver->solve({"abc", "+", "12"}), std::runtime_error);
  delete solver;
}

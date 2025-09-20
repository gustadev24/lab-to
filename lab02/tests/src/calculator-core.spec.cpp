#include "calculator-core.h"
#include <gtest/gtest.h>
#include <memory>

TEST(CalculatorCoreTest, ComputeBasic) {
  std::unique_ptr<CalculatorCore> solver = std::make_unique<CalculatorCore>();
  solver->solve({"3", "4", "+", "2", "+"});
  EXPECT_DOUBLE_EQ(solver->getResult(), 9.0);
}

TEST(CalculatorCoreTest, ComputeInvalid) {
  std::unique_ptr<CalculatorCore> solver = std::make_unique<CalculatorCore>();
  EXPECT_THROW(solver->solve({"12", "+", "*", "34"}), std::runtime_error);
  EXPECT_THROW(solver->solve({"abc", "+", "12"}), std::runtime_error);
}

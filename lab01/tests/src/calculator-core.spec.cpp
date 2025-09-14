#include "calculator-core.h"
#include <gtest/gtest.h>

TEST(CalculatorCoreTest, ComputeBasic) {
  CalculatorCore solver;
  solver.solve({"3", "4", "+", "2", "+"});
  EXPECT_DOUBLE_EQ(solver.getResult(), 9.0);
}

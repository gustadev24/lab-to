#pragma once
#include <gtest/gtest_prod.h>
#include <optional>
#include <string>
#include "calculator-core.h"
#include "calculator-parser.h"
#include "calculator-history.h"

class Calculator {
  private:
    const std::string input;
    CalculatorParser parser;
    CalculatorCore solver;
    CalculatorHistory history;
    std::optional<double> result;

    FRIEND_TEST(CalculatorTest, ComputeBasicExpressions);

  public:
    Calculator();
    double compute(const std::string& input);
    double getResult() const;
};

#pragma once
#include <gtest/gtest_prod.h>
#include <optional>
#include <string>
#include <memory>
#include "calculator-core.h"
#include "calculator-parser.h"
#include "calculator-history.h"

class Calculator {
  private:
    const std::string input;
    std::unique_ptr<CalculatorParser> parser;
    std::unique_ptr<CalculatorCore> solver;
    std::unique_ptr<CalculatorHistory> history;
    std::optional<double> result;

    FRIEND_TEST(CalculatorTest, ComputeBasicExpressions);

  public:
    Calculator();
    double compute(const std::string& input);
    double getResult() const;
    CalculatorHistory getHistory() const;
};

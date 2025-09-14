#pragma once
#include <gtest/gtest_prod.h>
#include <optional>
#include <string>
#include "calculator-core.h"
#include "calculator-parser.h"

class Calculator {
  private:
    const std::string input;
    CalculatorParser parser;
    CalculatorCore solver;
    std::optional<double> result;

    void solve();

  public:
    Calculator();
    double compute(const std::string& input);
    double getResult() const;
};

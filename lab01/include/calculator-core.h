#pragma once
#include <gtest/gtest_prod.h>
#include <optional>
#include <string>
#include <vector>

class CalculatorCore {
  private:
    std::optional<double> result;

    double inferOperation(const std::string& op, double left, double right);

    double add(std::initializer_list<double> nums);

    FRIEND_TEST(CalculatorCoreTest, ComputeBasic);


  public:
    CalculatorCore();

    double solve(std::vector<std::string> postfixExp);
    double getResult() const;
};

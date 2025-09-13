#pragma once
#include <optional>
#include <string>

class Calculator {
  private:
    std::optional<double> result;

    void compute();

    double add(std::initializer_list<double> nums);

  public:
    Calculator(std::string n1, std::string n2, std::string op);
    Calculator(double n1, double n2, std::string op);

    double getResult() const;
};

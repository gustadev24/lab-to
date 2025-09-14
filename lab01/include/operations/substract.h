#pragma once
#include <optional>

class SubstractOperation {
  private:
    double leftOperand;
    double rightOperand;
    std::optional<double> result;

    void compute();

  public:
    SubstractOperation(double a, double b);

    double getResult() const;
};

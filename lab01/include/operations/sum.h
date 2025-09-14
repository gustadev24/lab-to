#pragma once
#include <optional>

class SumOperation {
  private:
    double leftOperand;
    double rightOperand;
    std::optional<double> result;

    void compute();

  public:
    SumOperation(double a, double b);

    double getResult() const;
};

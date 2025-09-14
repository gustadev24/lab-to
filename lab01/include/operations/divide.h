#pragma once
#include <optional>

class DivideOperation {
  private:
    double leftOperand;
    double rightOperand;
    std::optional<double> result;

    void compute();

  public:
    DivideOperation(double a, double b);

    double getResult() const;
};

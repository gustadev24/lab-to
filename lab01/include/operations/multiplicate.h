#pragma once
#include <optional>

class MultiplicateOperation {
  private:
    double leftOperand;
    double rightOperand;
    std::optional<double> result;

    void compute();

  public:
    MultiplicateOperation(double a, double b);

    double getResult() const;
};

#pragma once
#include <optional>
class Operation {
  protected:
    double leftOperand;
    double rightOperand;
    std::optional<double> result;

    virtual void compute() = 0;

    Operation(double a, double b);

    public:
      virtual ~Operation() = default;
      virtual double getResult() const;
};

#pragma once
#include "operations/operation.h"

class SumOperation: public Operation {
  protected:
    void compute() override;
  public:
    SumOperation(double a, double b);
};

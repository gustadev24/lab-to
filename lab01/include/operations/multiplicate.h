#pragma once
#include "operations/operation.h"

class MultiplicateOperation
: public Operation {
  private:
    void compute() override;
  public:
    MultiplicateOperation(double a, double b);
};

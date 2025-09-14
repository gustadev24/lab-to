#pragma once
#include "operations/operation.h"

class DivideOperation: public Operation {
  private:
    void compute() override;
  public:
    DivideOperation(double a, double b);
};

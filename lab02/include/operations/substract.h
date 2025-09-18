#pragma once
#include "operations/operation.h"

class SubstractOperation: public Operation {
  private:
    void compute() override;
  public:
    SubstractOperation(double a, double b);
};

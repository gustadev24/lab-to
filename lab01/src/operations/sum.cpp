#include "operations/sum.h"

SumOperation::SumOperation(double a, double b): Operation(a, b) {
  this->compute();
}

void SumOperation::compute() {
  this->result = this->leftOperand + this->rightOperand;
}

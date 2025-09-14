#include "operations/substract.h"

SubstractOperation::SubstractOperation(double a, double b): Operation(a, b) {
  this->compute();
}

void SubstractOperation::compute() {
  this->result = this->leftOperand - this->rightOperand;
}

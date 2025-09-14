#include "operations/multiplicate.h"

MultiplicateOperation::MultiplicateOperation(double a, double b): Operation(a, b) {
  this->compute();
}

void MultiplicateOperation::compute() {
  this->result = this->leftOperand * this->rightOperand;
}

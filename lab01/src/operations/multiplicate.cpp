#include "operations/multiplicate.h"
#include <stdexcept>

MultiplicateOperation::MultiplicateOperation(double a, double b) {
  this->leftOperand = a;
  this->rightOperand = b;
  this->compute();
}

void MultiplicateOperation::compute() {
  this->result = this->leftOperand * this->rightOperand;
}

double MultiplicateOperation::getResult() const {
  if (!this->result.has_value()) {
    throw std::runtime_error("Result not computed");
  }
  return this->result.value();
}

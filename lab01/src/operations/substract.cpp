#include "operations/substract.h"
#include <stdexcept>

SubstractOperation::SubstractOperation(double a, double b) {
  this->leftOperand = a;
  this->rightOperand = b;
  this->compute();
}

void SubstractOperation::compute() {
  this->result = this->leftOperand - this->rightOperand;
}

double SubstractOperation::getResult() const {
  if (!this->result.has_value()) {
    throw std::runtime_error("Result not computed");
  }
  return this->result.value();
}

#include "operations/sum.h"
#include <stdexcept>

SumOperation::SumOperation(double a, double b) {
  this->leftOperand = a;
  this->rightOperand = b;
  this->compute();
}

void SumOperation::compute() {
  this->result = this->leftOperand + this->rightOperand;
}

double SumOperation::getResult() const {
  if (!this->result.has_value()) {
    throw std::runtime_error("Result not computed");
  }
  return this->result.value();
}

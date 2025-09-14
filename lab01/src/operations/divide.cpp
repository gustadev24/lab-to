#include "operations/divide.h"
#include <stdexcept>

DivideOperation::DivideOperation(double a, double b) {
  this->leftOperand = a;
  this->rightOperand = b;
  this->compute();
}

void DivideOperation::compute() {
  if (this->rightOperand == 0) {
    throw std::runtime_error("Division by zero");
  }
  this->result = this->leftOperand / this->rightOperand;
}

double DivideOperation::getResult() const {
  if (!this->result.has_value()) {
    throw std::runtime_error("Result not computed");
  }
  return this->result.value();
}

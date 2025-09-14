#include "operations/divide.h"
#include <stdexcept>

DivideOperation::DivideOperation(double a, double b): Operation(a, b) {
  this->compute();
}

void DivideOperation::compute() {
  if (this->rightOperand == 0) {
    throw std::runtime_error("Division by zero");
  }
  this->result = this->leftOperand / this->rightOperand;
}

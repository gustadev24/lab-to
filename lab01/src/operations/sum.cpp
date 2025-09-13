#include "operations/sum.h"
#include <stdexcept>

void SumOperation::compute() {
  double sum = 0;
  for (double v : values)
    sum += v;
  this->result = sum;
}

double SumOperation::getResult() const {
  if (!this->result.has_value()) {
    throw std::runtime_error("Result not computed");
  }
  return this->result.value();
}

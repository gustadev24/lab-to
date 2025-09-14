#include "calculator.h"
#include <string>

Calculator::Calculator() : input(""), parser(), result(), solver() {}

double Calculator::compute(const std::string& input) {
  // 1. Parse expression
  std::vector<std::string> postfix = this->parser.parse(input);
  // 2. Solve the expression
  this->result = this->solver.solve(postfix);
  return getResult();
}

double Calculator::getResult() const {
  if (!this->result.has_value()) {
    throw std::runtime_error("Result not computed");
  }
  return this->result.value();
}

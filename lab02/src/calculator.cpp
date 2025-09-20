#include "calculator.h"
#include <string>
#include <memory>

Calculator::Calculator() : input(""), parser(nullptr), result(), solver(nullptr), history(nullptr) {
    parser = std::make_unique<CalculatorParser>();
    solver = std::make_unique<CalculatorCore>();
    history = std::make_unique<CalculatorHistory>();
}

double Calculator::compute(const std::string& input) {
  // 1. Parse expression
  std::vector<std::string> postfix = this->parser->parse(input);
  // 2. Solve the expression
  this->result = this->solver->solve(postfix);
  // 3. Save an entry in the history
  this->history->addEntry(input, this->getResult());
  return getResult();
}

double Calculator::getResult() const {
  if (!this->result.has_value()) {
    throw std::runtime_error("Result not computed");
  }
  return this->result.value();
}

CalculatorHistory Calculator::getHistory() const {
  return *this->history;
}

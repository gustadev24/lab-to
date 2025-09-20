#include "calculator.h"
#include <string>

Calculator::Calculator() : input(""), parser(nullptr), result(), solver(nullptr), history(nullptr) {
    parser = new CalculatorParser();
    solver = new CalculatorCore();
    history = new CalculatorHistory();
}

Calculator::~Calculator() {
    delete parser;
    delete solver;
    delete history;
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

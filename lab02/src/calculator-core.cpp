#include "calculator-core.h"
#include "calculator.h"
#include "operations/divide.h"
#include "operations/multiplicate.h"
#include "operations/operation.h"
#include "operations/substract.h"
#include "operations/sum.h"
#include <stack>
#include <stdexcept>
#include <memory>

CalculatorCore::CalculatorCore() : result() {}

double CalculatorCore::solve(std::vector<std::string> postfixExp) {
  std::stack<std::string> stack;
  for (std::string token : postfixExp) {
    if (std::regex_match(token, CalculatorParser::IS_NUMBER)) {
      stack.push(token);
    } else {
      if (stack.size() < 2) {
        throw std::runtime_error("Invalid expression: insufficient values for operation " + token);
      }
      double right = std::stod(stack.top());
      stack.pop();
      double left = std::stod(stack.top());
      stack.pop();

      double result = inferOperation(token, left, right);
      stack.push(std::to_string(result));
    }
  }

  if (stack.size() != 1) {
    throw std::runtime_error("Invalid expression: leftover values in stack");
  }
  this->result = std::stod(stack.top());
  stack.pop();
  return this->getResult();
}

double CalculatorCore::inferOperation(const std::string& op, double left, double right) {
  std::unique_ptr<Operation> exec = nullptr;
  if (op == "+") {
    exec = std::make_unique<SumOperation>(left, right);
  } else if (op == "-") {
    exec = std::make_unique<SubstractOperation>(left, right);
  } else if (op == "*") {
    exec = std::make_unique<MultiplicateOperation>(left, right);
  } else if (op == "/") {
    exec = std::make_unique<DivideOperation>(left, right);
  }
  if (exec == nullptr)
    throw std::runtime_error("Unknown operation: " + op);

  this->result = exec->getResult();
  return this->getResult();

}

double CalculatorCore::getResult() const {
  if (!this->result.has_value()) {
    throw std::runtime_error("Result not computed");
  }
  return this->result.value();
}

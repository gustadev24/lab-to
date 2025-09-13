#include "calculator.h"
#include "operations/sum.h"
#include <initializer_list>
#include <stdexcept>

Calculator::Calculator(double n1, double n2, std::string op) {
  if (op == "+") {
    this->result = this->add({n1, n2});
  } else {
    throw std::runtime_error("Unknown operator: " + op);
  }
}

Calculator::Calculator(std::string n1, std::string n2, std::string op) {
  try {
    double num1 = std::stod(n1);
    double num2 = std::stod(n2);
    Calculator(num1, num2, op);
  } catch (const std::invalid_argument& e) {
    throw std::runtime_error("Invalid number format");
  } catch (const std::out_of_range& e) {
    throw std::runtime_error("Number out of range");
  }
}

double Calculator::add(std::initializer_list<double> nums) {
  SumOperation sum(nums);
  return sum.getResult();
}

double Calculator::getResult() const {
  if (!this->result.has_value()) {
    throw std::runtime_error("Result not computed");
  }
  return this->result.value();
}

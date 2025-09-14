#include "calculator-history.h"

CalculatorHistory::CalculatorHistory() : entries() {}

void CalculatorHistory::addEntry(const std::string& input, const double result) {
  this->entries.push_back(input + " = " + std::to_string(result));
}

std::string CalculatorHistory::getHistory() const {
  std::string history;
  for (const std::string& entry : this->entries) {
    history += entry + "\n";
  }
  return history;
}

void CalculatorHistory::clearHistory() {
  this->entries.clear();
}

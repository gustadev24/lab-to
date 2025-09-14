#include "calculator-history.h"
#include <iomanip>
#include <sstream>

CalculatorHistory::CalculatorHistory() : entries() {}

void CalculatorHistory::addEntry(const std::string& input, const double result) {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(6) << result;  // 6 decimals max
  std::string str = oss.str();

  // remove trailing zeros
  str.erase(str.find_last_not_of('0') + 1, std::string::npos);

  // remove trailing dot if left alone
  if(!str.empty() && str.back() == '.') {
      str.pop_back();
  }
  this->entries.push_back(input + " = " + str);
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

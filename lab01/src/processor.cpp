#include "processor.h"
#include <regex>
#include <string>
#include <vector>

OperationsProcessor::OperationsProcessor(const std::string& input): input(input) {
  this->compute();
}

void OperationsProcessor::clear() {
  this->postfix.clear();
  this->tokens.clear();
}

void OperationsProcessor::tokenize() {
  std::string currentToken;
  std::string pendingSign;
  std::regex validOperators("[\\+\\-\\*\\/\\(\\)]");
  for (char c : this->input) {
    if (c == ' ') continue;

    std::string currentChar(1, c);

    if (std::regex_match(currentChar, validOperators)) {
      if (!currentToken.empty()) {
        this->tokens.push_back(currentToken);
        currentToken.clear();
      }
      if (currentChar == "(" || currentChar == ")") {
        this->tokens.push_back(currentChar);
        continue;
      }

      bool allowedPlace = this->tokens.empty() || this->tokens.back() == "(" ||
                          std::regex_match(this->tokens.back(), validOperators);

      if ((currentChar == "+" || currentChar == "-") && allowedPlace) {
        pendingSign += currentChar;
        continue;
      }

      if ((currentChar == "*" || currentChar == "/") && allowedPlace) {
          throw std::runtime_error("Invalid operator sequence: unexpected " + currentChar);
      }

      this->tokens.push_back(currentChar);
    } else {
      if (!pendingSign.empty()) {
        // normalize the sign sequence before attaching to number
        int minusCount = std::count(pendingSign.begin(), pendingSign.end(), '-');
        if (minusCount % 2 == 1)
          currentToken = "-";
        pendingSign.clear();
      }
      currentToken += c;
    }
  }
  if (!currentToken.empty()) {
    this->tokens.push_back(currentToken);
  }
}

void OperationsProcessor::parse() {
  // 1. Clear rest objects from previous computations
  this->clear();
  // 2. Split tokens from the raw input
  this->tokenize();
  // 3. Create postfix expression
  this->toPostfix();
}

double OperationsProcessor::compute() {
  // 1. Parse expression
  this->parse();
  // 2. Use a stack to compute
}

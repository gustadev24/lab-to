#include "processor.h"
#include "calculator.h"
#include "operations/sum.h"
#include <regex>
#include <stack>
#include <string>
#include <vector>

const std::regex OperationsProcessor::VALID_OPERATORS("[\\+\\-\\*\\/]");
const std::regex OperationsProcessor::IS_NUMBER("^[-\\+]?\\d+(\\.\\d+)?$");

OperationsProcessor::OperationsProcessor(const std::string& input, bool compute): input(input) {
  if (compute)
    this->compute();
}

void OperationsProcessor::clear() {
  this->postfix.clear();
  this->tokens.clear();
}

void OperationsProcessor::tokenize() {
  std::string currentToken;
  std::string pendingSign;
  for (char c : this->input) {
    if (c == ' ') continue;

    std::string currentChar(1, c);

    bool isParenthesis = (currentChar == "(" || currentChar == ")");
    if (std::regex_match(currentChar, VALID_OPERATORS) || isParenthesis) {
      if (!currentToken.empty()) {
        this->tokens.push_back(currentToken);
        currentToken.clear();
      }
      if (isParenthesis) {
        this->tokens.push_back(currentChar);
        continue;
      }

      bool allowedPlace = this->tokens.empty() || this->tokens.back() == "(" ||
                          std::regex_match(this->tokens.back(), VALID_OPERATORS);

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

void OperationsProcessor::compute() {
  // 1. Parse expression
  this->parse();
  // 2. Solve the expression
  this->solve();
}

void OperationsProcessor::solve() {
  std::stack<std::string> stack;
  for (std::string token : this->postfix) {
    if (std::regex_match(token, IS_NUMBER)) {
      stack.push(token);
    } else {
      if (stack.size() < 2) {
        throw std::runtime_error("Invalid expression: insufficient values for operation " + token);
      }
      double right = std::stod(stack.top());
      stack.pop();
      double left = std::stod(stack.top());
      stack.pop();

      double result;
      Calculator calc;
      if (token == "+") {
        result = calc.add({left, right});
      }
      // } else if (token == "-") {
      //   result = left - right;
      // } else if (token == "*") {
      //   result = left * right;
      // } else if (token == "/") {
      //   if (right == 0) {
      //     throw std::runtime_error("Division by zero");
      //   }
      //   result = left / right;
      // } else {
      //   throw std::runtime_error("Unknown operator: " + token);
      // }
      stack.push(std::to_string(result));
    }
  }

  if (stack.size() != 1) {
    throw std::runtime_error("Invalid expression: leftover values in stack");
  }
  this->result = std::stod(stack.top());
  stack.pop();
}

double OperationsProcessor::getResult() const {
  return 0;
}

const std::vector<std::string>& OperationsProcessor::getTokens() const {
  return this->tokens;
}

const std::vector<std::string>& OperationsProcessor::getPostfix() const {
  return this->postfix;
}

void OperationsProcessor::toPostfix() {
  std::stack<std::string> stack;
  for (auto& token : this->tokens) {
    if (std::regex_match(token, IS_NUMBER)) {
      this->postfix.push_back(token);
      continue;
    }

    if (std::regex_match(token, VALID_OPERATORS)) {
      while(!stack.empty() && std::regex_match(stack.top(), VALID_OPERATORS)) {
        std::string top = stack.top();
        if (this->precedence(top) >= this->precedence(token)) {
          stack.pop();
          this->postfix.push_back(top);
        } else break;
      }
      stack.push(token);
      continue;
    }

    if (token == "(") {
      stack.push(token);
      continue;
    }

    if(token == ")") {
      while (!stack.empty() && stack.top() != "(") {
        this->postfix.push_back(stack.top());
        stack.pop();
      }
      if (stack.empty()) {
        throw std::runtime_error("Mismatched parentheses");
      }
      // Pop the '(' from the stack
      stack.pop();
      continue;
    }

    throw std::runtime_error("Invalid token: " + token);
  }
  while (!stack.empty()) {
    if (stack.top() == "(") {
      throw std::runtime_error("Mismatched parentheses");
    }
    this->postfix.push_back(stack.top());
    stack.pop();
  }
}

int OperationsProcessor::precedence(const std::string& op) {
  if (op == "+" || op == "-") return 1;
  if (op == "*" || op == "/") return 2;
  return 0;
}

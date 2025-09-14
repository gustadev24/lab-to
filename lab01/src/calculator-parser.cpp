#include "calculator-parser.h"
#include <regex>

const std::regex CalculatorParser::VALID_OPERATORS("[\\+\\-\\*\\/]");
const std::regex CalculatorParser::IS_NUMBER("^[-\\+]?\\d+(\\.\\d+)?$");

CalculatorParser::CalculatorParser() : rawInput(""), tokens(), postfix() {}

std::vector<std::string> CalculatorParser::parse(const std::string& input) {
  this->rawInput = input;
  this->clear();
  this->tokenize();
  this->toPostfix();
  return this->postfix;
}

void CalculatorParser::clear() {
  this->tokens.clear();
  this->postfix.clear();
}

void CalculatorParser::tokenize() {
  std::string currentToken;
  std::string pendingSign;
  for (char c : this->rawInput) {
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

void CalculatorParser::toPostfix() {
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

int CalculatorParser::precedence(const std::string& op) {
  if (op == "+" || op == "-") return 1;
  if (op == "*" || op == "/") return 2;
  return 0;
}

std::vector<std::string> CalculatorParser::getTokens() const {
  return this->tokens;
}

std::vector<std::string> CalculatorParser::getPostfix() const {
  return this->postfix;
}

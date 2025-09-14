#include "calculator.h"
#include <iostream>
#include <regex>
#include <string>

int main() {
  std::cout << "Welcome to Calculator!" << std::endl;
  std::cout << "Write 'exit' to end the program" << std::endl;
  bool wantContinue = true;
  std::regex exitPattern("exit", std::regex::icase);
  Calculator calc;
  do {
    std::cout << "Enter an operation:" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    if (std::regex_match(input, exitPattern)) {
      wantContinue = false;
    }

    if (wantContinue) {
      try {
        double result = calc.compute(input);
        std::cout << "Result: " << result << std::endl;
      } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
      }
    }

  } while (wantContinue);
  std::cout << "History:\n" << calc.getHistory().getHistory() << std::endl;
  std::cout << "Exiting Calculator. Goodbye!" << std::endl;
}

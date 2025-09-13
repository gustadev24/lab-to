#include "processor.h"
#include <iostream>

int main() {
  OperationsProcessor processor;
  std::string input;

  std::cout << "Enter an addition expression (e.g., 1 + 2 + 3): ";
  std::getline(std::cin, input);

  try {
    double result = processor.process(input);
    std::cout << "Result: " << result << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}

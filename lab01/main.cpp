#include "calculator.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int main() {
  std::cout << "Welcome to Calculator!" << std::endl;
  std::cout << "- Write 'exit' to end the program" << std::endl;
  std::cout << "- Write 'read' to read from a 'operations.txt file'" << std::endl;
  bool wantContinue = true;
  std::regex exitPattern("exit", std::regex::icase);
  std::regex readPattern("read", std::regex::icase);
  Calculator calc;
  do {
    std::cout << "Enter an operation:" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    if (std::regex_match(input, exitPattern)) {
      wantContinue = false;
    }

    if (std::regex_match(input, readPattern)) {
      // write in resultados.txt file
      std::ifstream file("operaciones.txt");
      if (!file.is_open()) {
        std::cout << "Error: could not open file 'operaciones.txt'" << std::endl;
        continue;
      }

      // open output file
      std::ofstream out("resultados.txt");
      if (!out.is_open()) {
        std::cout << "Error: could not open file 'resultados.txt'" << std::endl;
        continue;
      }

      std::cout << "Reading from 'operaciones.txt' and writing to 'resultados.txt' ..." << std::endl;

      std::string line;
      while (std::getline(file, line)) {
        try {
          double result = calc.compute(line);
          std::cout << line << " = " << result << std::endl;
          out << line << " = " << result << std::endl;
        } catch(const std::exception& e) {
          std::cout << "Error in line '" << line << "': " << e.what() << std::endl;
          out << "Error in line '" << line << "': " << e.what() << std::endl;
        }
      }
      continue;
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

#include "calculator.h"
#include <fstream>
#include <iostream>
#include <string>
#include <memory>

int main() {
  std::cout << "Welcome to Calculator!" << std::endl;
  std::cout << "Choose an option (1-4):" << std::endl;
  bool wantContinue = true;
  std::unique_ptr<Calculator> calc = std::make_unique<Calculator>();
  do {
    std::cout << "1. Ingresar operación." << std::endl;
    std::cout << "2. Mostrar historial." << std::endl;
    std::cout << "3. Leer operaciones desde archivo." << std::endl;
    std::cout << "4. Salir." << std::endl;

    std::string choice;
    std::getline(std::cin, choice);

    if (choice == "4") {
      wantContinue = false;
      break;
    } else if (choice == "3") {
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
          double result = calc->compute(line);
          std::cout << line << " = " << result << std::endl;
          out << line << " = " << result << std::endl;
        } catch(const std::exception& e) {
          std::cout << "Error in line '" << line << "': " << e.what() << std::endl;
          out << "Error in line '" << line << "': " << e.what() << std::endl;
        }
      }
      continue;
    } else if (choice == "2") {
      std::cout << "History:\n" << calc->getHistory().getHistory() << std::endl;
      continue;
    } else if (choice == "1") {
      std::cout << "Enter an operation:" << std::endl;
      std::string input;
      std::getline(std::cin, input);
      try {
        double result = calc->compute(input);
        std::cout << "Result: " << result << std::endl;
      } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
      }
    } else {
      std::cout << "Invalid choice. Please enter a number between 1 and 4." << std::endl;
      continue;
    }
  } while (true);
  std::cout << "History:\n" << calc->getHistory().getHistory() << std::endl;
  std::cout << "Exiting Calculator. Goodbye!" << std::endl;
}

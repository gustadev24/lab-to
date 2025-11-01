#include "include/aritmetica.h"
#include "include/mayor.h"
#include <iostream>

int main() {
  std::cout << "Welcome to Templates!" << std::endl;
  char x = mayorDe<char>('e', 'z');
  int y = mayorDe<int>(9, 4);

  std::cout << "Caracter mayor: " << x << std::endl;
  std::cout << "Numero mayor: " << y << std::endl;
  return 0;
}

#include "include/contendor.h"
#include <iostream>

int main() {
  std::cout << "Welcome to Templates!" << std::endl;
  Contendor<int> cint(5);
  Contendor<char> cchar('t');
  std::cout << cint.add() << std::endl;
  std::cout << cchar.uppercase() << std::endl;
  return 0;
}

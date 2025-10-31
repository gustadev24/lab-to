#include "include/aritmetica.h"
#include <iostream>

int main() {
  std::cout << "Welcome to Templates!" << std::endl;
  std::cout << aritmetica<int>(10, 45) << std::endl;
  std::cout << aritmetica<double>(3.45, 8.10) << std::endl;
  std::cout << aritmetica<float>(0.14f, 0.147f) << std::endl;
  return 0;
}

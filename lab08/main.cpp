#include "include/comun.h"
#include <iostream>

int main() {
  std::cout << "Welcome to Templates!" << std::endl;
  Comun1<int, 5> objInt;
  Comun1<double, 5> objFloat;
  Comun1<> obj;
  objInt.set(0, 10);
  objFloat.set(2, 3.1);

  std::cout << objInt.get(0) << std::endl;
  std::cout << objFloat.get(2) << std::endl;
  std::cout << obj.get(4) << std::endl;

  return 0;
}

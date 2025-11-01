#include "include/contenedor.h"
#include <iostream>

int main() {
  std::cout << "Welcome to Templates!" << std::endl;
  Contenedor<int> z;
  z.metodo2(10, 0);
  z.metodo2(50, 1);
  z.metodo2(60, 2);
  z.metodo2(70, 3);

  z.mostrar();
  return 0;
}

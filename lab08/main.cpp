#include "include/pila.h"
#include <iostream>

int main() {
  std::cout << "Welcome to Templates!" << std::endl;
  Pila<int> pila1(4);
  pila1.insertar(1);
  pila1.insertar(3);
  pila1.mostrarPila();

  Pila<char> pila2(4);
  pila2.insertar('a');
  pila2.insertar('b');
  pila2.insertar('c');
  pila2.mostrarPila();
  return 0;
}

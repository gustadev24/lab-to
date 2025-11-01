#include "include/list.h"
#include <iostream>

int main() {
  std::cout << "Welcome to Templates!" << std::endl;
  // Secuencia de edades
  List<int> ageList;
  ageList.add(25);
  ageList.add(30);
  ageList.add(22, 1); // Insertar 22 en el índice 1
  std::cout << "Ages in the list:" << std::endl;
  ageList.display();

  // Secuencia de palabras
  List<std::string> wordList;
  wordList.add("Hello");
  wordList.add("World");
  wordList.add("C++", 1); // Insertar "C++" en el índice 1
  wordList.add("Templates");
  wordList.remove(2); // Eliminar el elemento en el índice 2 ("World")
  std::cout << "Words in the list:" << std::endl;
  wordList.display();
  return 0;
}

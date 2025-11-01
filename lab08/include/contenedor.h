#include <iostream>
template <typename T> class Contenedor {
public:
  T metodo1(int xx) { return array[xx]; }
  void metodo2(T val, int i) { array[i] = val; }
  void mostrar() const;

private:
  T array[4];
};

template <typename T> void Contenedor<T>::mostrar() const {
  for (int i = 0; i < 4; i++) {
    std::cout << array[i] << " ";
  }
  std::cout << std::endl;
}

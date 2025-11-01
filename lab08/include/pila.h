#include <iostream>
template <typename T> class Pila {
public:
  Pila(int nelem = 10);
  void insertar(T);
  void mostrarPila();

private:
  int nelementos;
  T *cadena;
  int limite;
};

template <typename T> Pila<T>::Pila(int nelem) {
  nelementos = nelem;
  cadena = new T(nelementos);
  limite = 0;
}

template <typename T> void Pila<T>::insertar(T elem) {
  if (limite < nelementos)
    cadena[limite++] = elem;
}

template <typename T> void Pila<T>::mostrarPila() {
  for (int i = 0; i < limite; i++) {
    std::cout << cadena[i] << ", ";
  }
  std::cout << std::endl;
}

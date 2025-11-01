
using namespace std;

template <class T> class Contendor {
  T elemento;

public:
  Contendor(T arg) { elemento = arg; }
  T add() { return ++elemento; }
};

template <> class Contendor<char> {
  char elemento;

public:
  Contendor(char arg) { elemento = arg; }
  char uppercase() {
    if ((elemento >= 'a') && (elemento <= 'z')) {
      elemento += 'A' - 'a';
    }
    return elemento;
  }
};

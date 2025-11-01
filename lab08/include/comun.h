template <class T = char, int N = 8> class Comun1 {
  T bloque[N];

public:
  void set(int num, T tval);
  T get(int num);
};

template <class T, int N> void Comun1<T, N>::set(int num, T tval) {
  bloque[num] = tval;
}
template <class T, int N> T Comun1<T, N>::get(int num) { return bloque[num]; }

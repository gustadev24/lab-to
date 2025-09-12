#include <iostream>

using namespace std;

double sum(double a, double b) {
    return a + b;
}
template< typename... Rest>
double sum(double a, double b, Rest... rest) {
    return a + b + (rest + ...);
}

int main() {
  bool next = false;
  double res = 0;
  do {
    double n;
    cout << "Enter a number: " << endl;
    cin >> n;
    res = sum(res, n);
    cout << "Continue? (1 for yes, 0 for no): ";
    cin >> next;
  }while (next);

  cout << "The result is: " << res << endl;

  return 0;
}

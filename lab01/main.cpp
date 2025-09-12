#include "operations/sum.h"
#include <iostream>

int main() {
    SumOperation sum({1.0, 2.0, 3.5});
    std::cout << sum.compute() << "\n";
}

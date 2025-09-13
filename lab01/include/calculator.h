#pragma once
#include <initializer_list>
#include "operations/sum.h"

using namespace std;

class Calculator {
  public:
    double add(initializer_list<double> nums);

    template<typename Iterator>
    double add(Iterator begin, Iterator end) {
      SumOperation sum(begin, end);
      return sum.compute();
    };
};

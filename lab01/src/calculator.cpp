#include "calculator.h"
#include "operations/sum.h"
#include <initializer_list>

double Calculator::add(initializer_list<double> nums) {
  SumOperation sum(nums);
  return sum.getResult();
}

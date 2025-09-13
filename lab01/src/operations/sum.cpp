#include "operations/sum.h"

double SumOperation::compute() const {
  double sum = 0;
  for (double v : values)
    sum += v;
  return sum;
}

#include "operations/sum.h"
#include <initializer_list>
#include <numeric>

using namespace std;

SumOperation::SumOperation(initializer_list<double> nums): values(nums) {}

double SumOperation::compute() const {
return accumulate(values.begin(), values.end(), 0.0);
}

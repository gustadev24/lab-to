#pragma once
#include <vector>
using namespace std;

class SumOperation {
  private:
    vector<double> values;

  public:

    SumOperation(initializer_list<double> nums): values(nums) {};

    template<typename Iterator>
    SumOperation(Iterator begin, Iterator end): values(begin, end) {};

    template<typename Container>
    SumOperation(const Container& container): values(container.begin(), container.end()) {};

    double compute() const;
};

#pragma once
#include <vector>

class SumOperation {
  private:
    std::vector<double> values;

  public:

    SumOperation(std::initializer_list<double> nums): values(nums) {};

    template<typename Iterator>
    SumOperation(Iterator begin, Iterator end): values(begin, end) {};

    template<typename Container>
    SumOperation(const Container& container): values(container.begin(), container.end()) {};

    double compute() const;
};

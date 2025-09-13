#pragma once
#include <optional>
#include <vector>

class SumOperation {
  private:
    std::vector<double> values;
    std::optional<double> result;

    void compute();

  public:

    SumOperation(std::initializer_list<double> nums): values(nums) {
      compute();
    };

    template<typename Iterator>
    SumOperation(Iterator begin, Iterator end): values(begin, end) {
      compute();
    };

    template<typename Container>
    SumOperation(const Container& container): SumOperation(container.begin(), container.end()) {};

    double getResult() const;
};

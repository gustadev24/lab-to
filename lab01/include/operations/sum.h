#include <initializer_list>
#include <vector>
using namespace std;

class SumOperation {
  private:
    vector<double> values;

  public:
    SumOperation(initializer_list<double> nums);

    double compute() const;
};

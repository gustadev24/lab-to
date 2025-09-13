#include "processor.h"
#include "calculator.h"
#include <sstream>
#include <vector>
#include <stdexcept>

using namespace std;

double OperationsProcessor::process(const string& input) {
    istringstream iss(input);
    vector<double> numbers;
    char op;
    double value;

    if (!(iss >> value)) {
        throw invalid_argument("Invalid input");
    }
    numbers.push_back(value);

    while (iss >> op >> value) {
        if (op != '+') {
            throw invalid_argument("Only + is supported for now");
        }
        numbers.push_back(value);
    }

    Calculator calc;
    return calc.add(numbers.begin(), numbers.end());
}

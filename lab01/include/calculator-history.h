#include <string>
#include <vector>
class CalculatorHistory {
  private:
    std::vector<std::string> entries;
  public:
    CalculatorHistory();

    void addEntry(const std::string& input, const double result);
    std::string getHistory() const;
    void clearHistory();
};

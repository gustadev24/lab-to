#pragma once
#include <optional>
#include <string>
#include <vector>

class OperationsProcessor {
  private:
    const std::string input;
    std::vector<std::string> postfix;
    std::vector<std::string> tokens;
    std::optional<double> result;

    void parse();
    void clear();
    void tokenize();
  public:
    OperationsProcessor(const std::string& input);
    double getResult() const;
};

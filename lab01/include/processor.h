#pragma once
#include <gtest/gtest_prod.h>
#include <optional>
#include <string>
#include <vector>

class OperationsProcessor {
  private:
    const std::string input;
    std::vector<std::string> postfix;
    std::vector<std::string> tokens;
    std::optional<double> result;

    void compute();
    void parse();
    // imp
    void clear();
    // imp
    void tokenize();

    void toPostfix();

    FRIEND_TEST(OperationsProcessorTest, TokenizeBasic);

  public:
  // imp
    OperationsProcessor(const std::string& input, bool compute = true);
    double getResult() const;
    const std::vector<std::string>& getTokens() const;
    const std::vector<std::string>& getPostfix() const;
};

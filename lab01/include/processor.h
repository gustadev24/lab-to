#pragma once
#include <gtest/gtest_prod.h>
#include <optional>
#include <regex>
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

    void solve();

    int precedence(const std::string& op);

    FRIEND_TEST(OperationsProcessorTest, TokenizeBasic);
    FRIEND_TEST(OperationsProcessorTest, PostfixBasic);
    FRIEND_TEST(OperationsProcessorTest, ComputeBasic);

  public:

    static const std::regex VALID_OPERATORS;
    static const std::regex IS_NUMBER;


    OperationsProcessor(const std::string& input, bool compute = true);
    double getResult() const;
    const std::vector<std::string>& getTokens() const;
    const std::vector<std::string>& getPostfix() const;
};

#include <gtest/gtest_prod.h>
#include <regex>
#include <string>
#include <vector>

class CalculatorParser {
  private:
    std::string rawInput;
    std::vector<std::string> tokens;
    std::vector<std::string> postfix;

    void toPostfix();
    void tokenize();

    int precedence(const std::string& op);

    FRIEND_TEST(CalculatorParserTest, TokenizeBasic);
    FRIEND_TEST(CalculatorParserTest, PostfixBasic);

  public:
    static const std::regex VALID_OPERATORS;
    static const std::regex IS_NUMBER;

    CalculatorParser();

    std::vector<std::string> parse(const std::string& input);
    void clear();

    std::vector<std::string> getTokens() const;
    std::vector<std::string> getPostfix() const;

};

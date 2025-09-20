#include "calculator.h"
#include <gtest/gtest.h>
#include <vector>
#include <memory>

TEST(CalculatorParserTest, TokenizeBasic) {
    std::unique_ptr<CalculatorParser> parser = std::make_unique<CalculatorParser>();
    parser->parse("3 + -4 * 2");
    std::vector<std::string> tokens = parser->getTokens();
    ASSERT_EQ(tokens.size(), 5);
    EXPECT_EQ(tokens[0], "3");
    EXPECT_EQ(tokens[1], "+");
    EXPECT_EQ(tokens[2], "-4");
    EXPECT_EQ(tokens[3], "*");
    EXPECT_EQ(tokens[4], "2");
}

TEST(CalculatorParserTest, PostfixBasic) {
  std::unique_ptr<CalculatorParser> parser = std::make_unique<CalculatorParser>();
  parser->parse("3 + 4 * 2");
  std::vector<std::string> postfix = parser->getPostfix();

  ASSERT_EQ(postfix.size(), 5);
  EXPECT_EQ(postfix[0], "3");
  EXPECT_EQ(postfix[1], "4");
  EXPECT_EQ(postfix[2], "2");
  EXPECT_EQ(postfix[3], "*");
  EXPECT_EQ(postfix[4], "+");
}

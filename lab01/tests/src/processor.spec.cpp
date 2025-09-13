#include <gtest/gtest.h>
#include "processor.h"

TEST(OperationsProcessorTest, TokenizeBasic) {
    OperationsProcessor op("3 + -4 * 2", false);
    op.tokenize();
    ASSERT_EQ(op.tokens.size(), 5);
    EXPECT_EQ(op.tokens[0], "3");
    EXPECT_EQ(op.tokens[1], "+");
    EXPECT_EQ(op.tokens[2], "-4");
    EXPECT_EQ(op.tokens[3], "*");
    EXPECT_EQ(op.tokens[4], "2");
}

TEST(OperationsProcessorTest, PostfixBasic) {
  OperationsProcessor op("3 + 4 * 2", false);
  op.tokenize();
  op.toPostfix();
  ASSERT_EQ(op.postfix.size(), 5);
  EXPECT_EQ(op.postfix[0], "3");
  EXPECT_EQ(op.postfix[1], "4");
  EXPECT_EQ(op.postfix[2], "2");
  EXPECT_EQ(op.postfix[3], "*");
  EXPECT_EQ(op.postfix[4], "+");
}

TEST(OperationsProcessorTest, ComputeBasic) {
  OperationsProcessor op("3 + 4 + 2");
  std::cout << "Result: " << op.getResult() << std::endl;
  EXPECT_DOUBLE_EQ(op.getResult(), 9.0);
}

#include <gtest/gtest.h>
#include "processor.h"

TEST(OperationsProcessorTest, TokenizeBasic) {
    OperationsProcessor op("3 + -4 * 2", false);
    op.tokenize();
    // print tokens object
    for (const auto& token : op.tokens) {
        std::cout << token << std::endl;
    }
    ASSERT_EQ(op.tokens.size(), 5);
    EXPECT_EQ(op.tokens[0], "3");
    EXPECT_EQ(op.tokens[1], "+");
    EXPECT_EQ(op.tokens[2], "-4");
    EXPECT_EQ(op.tokens[3], "*");
    EXPECT_EQ(op.tokens[4], "2");
}

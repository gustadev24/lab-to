// Create tests for substractOperation
#include <gtest/gtest.h>
#include "operations/substract.h"

TEST(SubstractOperationTest, BasicSubstract) {
    SubstractOperation* sub = new SubstractOperation(5, 3);
    EXPECT_DOUBLE_EQ(sub->getResult(), 2);
    delete sub;
}

TEST(SubstractOperationTest, NegativeSubstract) {
    SubstractOperation* sub = new SubstractOperation(-5, -3);
    EXPECT_DOUBLE_EQ(sub->getResult(), -2);
    delete sub;
}

TEST(SubstractOperationTest, MixedSubstract) {
    SubstractOperation* sub = new SubstractOperation(5, -3);
    EXPECT_DOUBLE_EQ(sub->getResult(), 8);
    delete sub;
}

TEST(SubstractOperationTest, ZeroSubstract) {
    SubstractOperation* sub = new SubstractOperation(0, 0);
    EXPECT_DOUBLE_EQ(sub->getResult(), 0);
    delete sub;
}

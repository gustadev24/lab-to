// Create tests for substractOperation
#include <gtest/gtest.h>
#include "operations/substract.h"
#include <memory>

TEST(SubstractOperationTest, BasicSubstract) {
    std::unique_ptr<SubstractOperation> sub = std::make_unique<SubstractOperation>(5, 3);
    EXPECT_DOUBLE_EQ(sub->getResult(), 2);
}

TEST(SubstractOperationTest, NegativeSubstract) {
    std::unique_ptr<SubstractOperation> sub = std::make_unique<SubstractOperation>(-5, -3);
    EXPECT_DOUBLE_EQ(sub->getResult(), -2);
}

TEST(SubstractOperationTest, MixedSubstract) {
    std::unique_ptr<SubstractOperation> sub = std::make_unique<SubstractOperation>(5, -3);
    EXPECT_DOUBLE_EQ(sub->getResult(), 8);
}

TEST(SubstractOperationTest, ZeroSubstract) {
    std::unique_ptr<SubstractOperation> sub = std::make_unique<SubstractOperation>(0, 0);
    EXPECT_DOUBLE_EQ(sub->getResult(), 0);
}

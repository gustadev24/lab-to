#include <gtest/gtest.h>
#include "operations/divide.h"

TEST(DivideOperationTest, DivideByZero) {
    EXPECT_THROW(DivideOperation(3, 0), std::runtime_error);
}

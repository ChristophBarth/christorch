#include <gtest/gtest.h>
#include "christorch/tensor/tensor.h"

TEST(TensorTest, SizeAndGetSet) {
    christorch::Tensor t({1.0, 2.0, 3.0});
    EXPECT_EQ(t.size(), 3);
    EXPECT_DOUBLE_EQ(t.get(0), 1.0);
    t.get(1) = 42.0;
    EXPECT_DOUBLE_EQ(t.get(1), 42.0);
}

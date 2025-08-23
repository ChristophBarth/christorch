#include <gtest/gtest.h>
#include "christorch/tensor/tensor.h"
#include "christorch/ops/add.h"

TEST(AddOpTest, Elementwise) {
    christorch::Tensor a({1.0, 2.0, 3.0});
    christorch::Tensor b({10.0, 20.0, 30.0});
    auto c = christorch::add(a,b);
    ASSERT_EQ(c.size(), 3);
    EXPECT_DOUBLE_EQ(c.get(0), 11.0);
    EXPECT_DOUBLE_EQ(c.get(1), 22.0);
    EXPECT_DOUBLE_EQ(c.get(2), 33.0);
}

TEST(AddOpTest, SizeMismatchThrows) {
    christorch::Tensor a({1.0, 2.0});
    christorch::Tensor b({1.0});
    EXPECT_THROW(christorch::add(a,b), std::runtime_error);
}

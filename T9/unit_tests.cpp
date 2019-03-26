#include <fstream>
#include <iostream>
#include <string>

// add custom build step
// command - ctest
// arguments -VV

#include <gtest/gtest.h>
namespace {
class TestT9 : public ::testing::Test {
 public:
  void SetUp() override {}
};

TEST_F(TestT9, test1) {
  // EXPECT_TRUE(res);
}

}  // namespace

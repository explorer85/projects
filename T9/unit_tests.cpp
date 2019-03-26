#include <fstream>
#include <iostream>
#include <string>

// add custom build step
// command - ctest
// arguments -VV

#include <gtest/gtest.h>
#include "message_parser.h"
namespace {
class TestT9 : public ::testing::Test {
 public:
  void SetUp() override {}
};

TEST_F(TestT9, testhi) { EXPECT_EQ("44 444", parseMessage("hi")); }
TEST_F(TestT9, testyes) { EXPECT_EQ("999337777", parseMessage("yes")); }
TEST_F(TestT9, testfoobar) {
  EXPECT_EQ("333666 6660 022 2777", parseMessage("foo  bar"));
}
TEST_F(TestT9, helloworld) {
  EXPECT_EQ("4433555 555666096667775553", parseMessage("hello world"));
}
}  // namespace

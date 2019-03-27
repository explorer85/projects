#include <fstream>
#include <iostream>
#include <string>

// add custom build step
// command - ctest
// arguments -VV

#include <gtest/gtest.h>
#include "message_parser.h"

using namespace t9spelling;
namespace {
class TestT9 : public ::testing::Test {
 public:
  void SetUp() override {}
};

TEST_F(TestT9, testOutOfRange) { EXPECT_EQ("44 444", parseMessage("$hi$")); }

class TestT9DataSet
    : public ::testing::TestWithParam<::std::tuple<std::string, std::string>> {
  // You can implement all the usual fixture class members here.
  // To access the test parameter, call GetParam() from class
  // TestWithParam<T>.
};

using ::testing::Bool;
using ::testing::Combine;
using ::testing::Values;
using ::testing::ValuesIn;

std::vector<std::tuple<std::string, std::string>> v{
    {"44 444", "hi"},
    {"999337777", "yes"},
    {"333666 6660 022 2777", "foo  bar"},
    {"4433555 555666096667775553", "hello world"}

};
INSTANTIATE_TEST_SUITE_P(InstantiationName, TestT9DataSet, ValuesIn(v));

TEST_P(TestT9DataSet, testparse) {
  std::string input;
  std::string excepted;
  std::tie(excepted, input) = GetParam();
  std::string output = parseMessage(input);
  EXPECT_EQ(excepted, output);
}

}  // namespace

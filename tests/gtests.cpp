/**
 * An example gtests
 * version number 1.04
 *
 *  Testing
 *  - class COUNT    default ctor doesn't exist         1.01.00
 *  - directories    project structure                  1.02.00
 *
 */

#include <gtest/gtest.h>
#include <iostream>

#include "../src/Count.hpp"
#include "../src/Print.hpp"
#include "../src/helper.hpp"

class TestFixture : public ::testing::Test
{
protected:
  TestFixture () {}

  void
  SetUp () override
  {
  }

  void
  TearDown () override
  {
  }

  ~TestFixture () {}
};

TEST_F (TestFixture, Test) {}

int
main (int argc, char* argv[])
{
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
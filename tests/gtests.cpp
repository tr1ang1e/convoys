/**
 * An example gtests
 * version number 1.04
 *
 *  Testing
 *  - class COUNT    default ctor doesn't exist         1.01.00
 *  - directories    project structure                  1.02.00
 *  - printepoch()   print function for testing         1.03.00
 *
 */

#include <gtest/gtest.h>
#include <vector>
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

TEST (TestPrintepoch, FirstTest)
{
  std::vector<char> epoch(625, 'x');
  for (int i = 0; i < 625; ++i)
  {
    fu::printepoch(epoch, 25);
    epoch[i] = 0;
    fu::delayprocess(35);
    fu::resetterminal();
  }
}

int
main (int argc, char* argv[])
{
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
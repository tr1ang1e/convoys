/**
 * An example gtests
 * version number 1.04
 *
 *  Testing
 *  - class COUNT    default ctor doesn't exist         1.01.00
 *  - directories    project structure                  1.02.00
 *  - printepoch()   print function for testing         1.03.00
 *  - GridClass      ctors                              2.01.00
 *
 */

#include <gtest/gtest.h>
#include <vector>
#include <iostream>

#include "../src/GreedClass.hpp"
#include "../src/Print.hpp"
#include "../src/helper.hpp"

class TestGridClass : public ::testing::Test
{
protected:
  TestGridClass () {}

  void
  SetUp () override
  {
  }

  void
  TearDown () override
  {
  }

  ~TestGridClass () {}
};

TEST_F (TestGridClass, CTORs) 
{
  EXPECT_FALSE(me::ISCTOR0<GridClass>);
  EXPECT_TRUE((me::ISCTOR1<GridClass, int>));

  // check if grid.size() is correct
}

TEST_F (TestGridClass, SetStartPicture)
{
  EXPECT_TRUE((me::ISSETSTARTPICTURE1<GridClass, std::vector<int>, void>));
  
}

int
main (int argc, char* argv[])
{

  bool b = false;

  if (b)
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

  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
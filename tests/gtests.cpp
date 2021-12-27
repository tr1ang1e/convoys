/**
 * An example gtests
 * version number 1.04
 *
 *  Testing
 *  - class COUNT    default ctor doesn't exist         1.01.00
 *  - directories    project structure                  1.02.00
 *  - printepoch()   print function for testing         1.03.00
 *  - GridClass      ctors                              2.01.00
 *  - GridClass      ctors                              2.02.00
 *  - gtests         error massages shorter             2.02.01
 *
 *  Error codes
 *  01 = exists but forbidden
 *  02 = doesn't exist but necessary
 *
 */

#include <gtest/gtest.h>

#include <cstdint>
#include <iostream>
#include <vector>

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
  EXPECT_FALSE (me::ISCTOR0<GridClass>)             <<  "> 01_error";
  EXPECT_TRUE ((me::ISCTOR1<GridClass, uint16_t>))  <<  "> 02_error";

  GridClass Grid1 (0);
  EXPECT_EQ (Grid1.GetGridSize (), 0);
  EXPECT_EQ (Grid1.GetAliveCellsNumber (), 0);

  GridClass Grid2 (4);
  EXPECT_EQ (Grid2.GetGridSize (), 16);
  EXPECT_EQ (Grid2.GetAliveCellsNumber (), 0);

  GridClass Grid3 (16);
  EXPECT_EQ (Grid3.GetGridSize (), 256);
  EXPECT_EQ (Grid3.GetAliveCellsNumber (), 0);
}

TEST_F (TestGridClass, GetGridSize)
{
  EXPECT_TRUE ((me::ISGETGRIDSIZE0<GridClass, uint32_t>))  << "> 02_error";
}

TEST_F (TestGridClass, GetAliveSellsNumber)
{
  EXPECT_TRUE ((me::ISGETALIVECELLSNUMBER0<GridClass, uint32_t>))  << "> 02_error";
}

TEST_F (TestGridClass, SetStartPicture)
{
  EXPECT_TRUE ((me::ISSETSTARTPICTURE1<GridClass, std::vector<int>, void>));
}

int
main (int argc, char* argv[])
{

  bool b = false;

  if (b)
    {
      std::vector<char> epoch (625, 'x');
      for (int i = 0; i < 625; ++i)
        {
          fu::printepoch (epoch, 25);
          epoch[i] = 0;
          fu::delayprocess (35);
          fu::resetterminal ();
        }
    }

  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
/**
 * An example gtests
 * version number 1.04
 *
 *  Testing
 *  - gtests         add existance checking possibility     1.01.00
 *  - project        project structure                      1.02.00
 *  - gtests         print function for testing             1.03.00
 *  - GridClass      ctors                                  2.01.00
 *  - GridClass      ctors                                  2.02.00
 *  - gtests         error massages shorter                 2.02.01
 *  - gtests         split gtests helper header             2.02.02
 *  - gtests         add constancy checking possibility     2.02.03
 *
 *  Error codes
 *  01 = exists but forbidden
 *  02 = doesn't exist but necessary
 *  03 = wrong return value
 *  04 = comparison failed
 *  05 = wrong constancy
 *
 */

#include "../src/FunctHelper.hpp"
#include "../src/MacroHelper.hpp"
#include <gtest/gtest.h>

#include <cstdint>
#include <iostream>
#include <vector>

#include "../src/GreedClass.hpp"
#include "../src/Print.hpp"

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
  EXPECT_FALSE (me::ISCTOR0<GridClass>) << "> 01_error";
  EXPECT_TRUE ((me::ISCTOR1<GridClass, uint16_t>)) << "> 02_error";

  // for testing if ctors set grid size correctly
  EXPECT_TRUE ((me::ISGETGRIDSIZE0<GridClass, uint32_t>)) << "> 02_error";

  GridClass grid1 (0);
  EXPECT_EQ (grid1.GetGridSize (), 0);
  EXPECT_EQ (grid1.GetAliveCellsNumber (), 0);

  GridClass grid2 (4);
  EXPECT_EQ (grid2.GetGridSize (), 16);
  EXPECT_EQ (grid2.GetAliveCellsNumber (), 0);

  GridClass grid3 (16);
  EXPECT_EQ (grid3.GetGridSize (), 256);
  EXPECT_EQ (grid3.GetAliveCellsNumber (), 0);
}

TEST_F (TestGridClass, SetStartEpoch)
{
  EXPECT_TRUE ((me::ISSETSTARTEPOCH1<GridClass, std::vector<uint16_t>, void>))
      << "> 02_error";

  GridClass grid (16);
  std::vector<uint16_t> startEpoch
      = { 87, 88, 102, 104, 118, 133, 134, 139, 140, 153, 156, 169, 170 };
  grid.SetStartEpoch (startEpoch);

  EXPECT_EQ (grid.GetAliveCellsNumber (), 13) << "> 03_error";
  EXPECT_TRUE (fu::comparecellspositions (startEpoch, grid)) << "> 04_error";
}

TEST_F (TestGridClass, GetAliveSellsNumber)
{
  EXPECT_TRUE ((me::ISGETALIVECELLSNUMBER0<GridClass, uint32_t>)) << "> 02_error";
}

TEST_F (TestGridClass, GetCurrentEpoch)
{
  EXPECT_TRUE ((me::ISGETCURRENTEPOCH0<GridClass, std::vector<char>>)) << "> 02_error";
}

TEST_F (TestGridClass, IsMethodConst)
{
  EXPECT_TRUE ((ISMETHODCONST (GridClass, GetGridSize))) << "> 05_error";
  EXPECT_TRUE ((ISMETHODCONST (GridClass, GetAliveCellsNumber))) << "> 05_error";
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
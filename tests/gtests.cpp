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
 *  - GridClass      SetStartEpoch                          2.03.00
 *  - gtests         TestGridClass using                    2.03.01
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
  GridClass permanent;
  GridClass loop;
  GridClass motion;

  std::vector<uint16_t> startEpoch1;
  std::vector<uint16_t> startEpoch2;
  std::vector<uint16_t> startEpoch3;

  TestGridClass ()
      : permanent{ GridClass (16) }, loop{ GridClass (16) }, motion{ GridClass (16) }
  {
  }

  void
  SetUp () override
  {
    startEpoch1 = { 87, 88, 102, 104, 118, 133, 134, 139, 140, 153, 156, 169, 170 };
    permanent.SetStartEpoch (startEpoch1);

    startEpoch2 = { 74, 89, 91, 104, 108, 119, 123, 134, 138, 149, 153, 166, 168, 183 };
    loop.SetStartEpoch (startEpoch2);

    startEpoch3 = { 61, 75, 76, 92, 93 };
    motion.SetStartEpoch (startEpoch3);
  }
};

TEST_F (TestGridClass, GetInfoAboutGrid)
{
  EXPECT_TRUE ((me::ISGETGRIDSIZE0<GridClass, uint32_t>)) << "> 02_error";
  EXPECT_TRUE ((me::ISGETALIVECELLSNUMBER0<GridClass, uint32_t>)) << "> 02_error";
  EXPECT_TRUE ((me::ISGETCURRENTEPOCH0<GridClass, std::vector<char>>)) << "> 02_error";
}

TEST_F (TestGridClass, IsInfoMethodConst)
{
  EXPECT_TRUE ((ISMETHODCONST (GridClass, GetGridSize))) << "> 05_error";
  EXPECT_TRUE ((ISMETHODCONST (GridClass, GetAliveCellsNumber))) << "> 05_error";
  EXPECT_TRUE ((ISMETHODCONST (GridClass, GetCurrentEpoch))) << "> 05_error";
}

TEST_F (TestGridClass, CTORs)
{

  // ctors existance
  EXPECT_FALSE (me::ISCTOR0<GridClass>) << "> 01_error";
  ASSERT_TRUE ((me::ISCTOR1<GridClass, uint16_t>)) << "> 02_error";
  ASSERT_TRUE ((me::ISCTOR2<GridClass, uint16_t, uint16_t>)) << "> 02_error";

  // testing actual grid size after initializing
  GridClass grid1 (0);
  EXPECT_EQ (grid1.GetGridSize (), 0);
  EXPECT_EQ (grid1.GetAliveCellsNumber (), 0);

  GridClass grid2 (16);
  EXPECT_EQ (grid2.GetGridSize (), 256);
  EXPECT_EQ (grid2.GetAliveCellsNumber (), 0);

  GridClass grid3 (0, 0);
  EXPECT_EQ (grid3.GetGridSize (), 0);
  EXPECT_EQ (grid3.GetAliveCellsNumber (), 0);

  GridClass grid4 (240, 160);
  EXPECT_EQ (grid4.GetGridSize (), 38400);
  EXPECT_EQ (grid4.GetAliveCellsNumber (), 0);
}

TEST_F (TestGridClass, SetStartEpoch)
{
  EXPECT_TRUE ((me::ISSETSTARTEPOCH1<GridClass, std::vector<uint16_t>, void>))
      << "> 02_error";

  EXPECT_EQ (permanent.GetAliveCellsNumber (), 13) << "> 03_error";
  EXPECT_TRUE (fu::comparecellspositions (startEpoch1, permanent)) << "> 04_error";

  EXPECT_EQ (loop.GetAliveCellsNumber (), 14) << "> 03_error";
  EXPECT_TRUE (fu::comparecellspositions (startEpoch2, loop)) << "> 04_error";

  EXPECT_EQ (motion.GetAliveCellsNumber (), 5) << "> 03_error";
  EXPECT_TRUE (fu::comparecellspositions (startEpoch3, motion)) << "> 04_error";
}

int
main (int argc, char* argv[])
{

  // testing animation in terminal
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
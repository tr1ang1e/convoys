/**
 * An example gtests
 * version number 1.04
 *
 *  Testing
 *  - gtests         add existance checking possibility     1.01.00
 *  - project        project structure                      1.02.00
 *  - gtests         print function for testing             1.03.00
 *  - getest         GridClass ctors                        2.01.00
 *  - GridClass      ctors                                  2.02.00
 *  - gtests         error massages shorter                 2.02.01
 *  - gtests         split gtests helper header             2.02.02
 *  - gtests         add constancy checking possibility     2.02.03
 *  - GridClass      SetStartEpoch                          2.03.00
 *  - gtests         TestGridClass using                    2.03.01
 *  - gtests         GridClass::CountNextEpoch exists       2.04.00
 *  - gtests         error massage shorter                  2.04.01
 *  - GridClass      ctors fixed                            2.04.02
 *  - GridClass      SetStartEpoch fixed                    2.04.03
 *  - gtests         comparecellspositions fixed            2.04.04
 *  - gtests         iftestgridisvalid fixed                2.04.05
 *  - GridClass      CountNextEpoch                         2.05.00
 *  - GridClass      remove cellchar field                  2.05.01
 *  - gtests         GridClass::CountNextEpoch is tested    2.05.02
 *  - GridClass      wrong naming fixed                     2.05.03
 *  - project        static library for gtests              2.05.04
 *  - gtests         comparecellspositions fixed            2.05.05
 *  - gtests         PrintClass ctors                       3.01.00
 *  - PrintClass     ctors                                  3.02.00
 *  - PrintClass     ResetTerminal                          3.03.00
 *  - PrintClass     SetChars                               3.04.00
 *  - GridClass      GetLineSize                            3.04.01
 *  - gtest          test.sh output is corrected            3.04.02
 *  - GridClass      CountNextEpoch fixed                   3.04.03
 *  - PrintClass     PrintEpoch                             3.05.00
 *  - PrintClass     PrintEpochNum                          3.05.01
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

#include "../src/GridClass.hpp"
#include "../src/PrintClass.hpp"

class TestGridClass : public ::testing::Test
{
protected:
  GridClass permanent;
  GridClass loop;
  GridClass motion;

  std::vector<uint32_t> permanent_startepoch;
  std::vector<uint32_t> loop_startepoch;
  std::vector<uint32_t> motion_startepoch;

  TestGridClass ()
      : permanent{ GridClass (16) }, loop{ GridClass (16) }, motion{ GridClass (16) }
  {
  }

  void
  SetUp () override
  {
    permanent_startepoch
        = { 87, 88, 102, 104, 118, 133, 134, 139, 140, 153, 156, 169, 170 };
    permanent.SetStartEpoch (permanent_startepoch);

    loop_startepoch
        = { 74, 89, 91, 104, 108, 119, 123, 134, 138, 149, 153, 166, 168, 183 };
    loop.SetStartEpoch (loop_startepoch);

    motion_startepoch = { 46, 60, 61, 77, 78 };
    motion.SetStartEpoch (motion_startepoch);
  }
};

// clang-format off

TEST_F (TestGridClass, CTORs)
{

  // ctors existance
  EXPECT_FALSE (me::ISCTOR0<GridClass>)                         << "> 01";
  ASSERT_TRUE ((me::ISCTOR1<GridClass, uint32_t>))              << "> 02";
  ASSERT_TRUE ((me::ISCTOR2<GridClass, uint32_t, uint32_t>))    << "> 02";

  // testing actual grid size after initializing
  GridClass grid1 (0);
  EXPECT_EQ (grid1.GetGridSize (), 0)             << "> 03";
  EXPECT_EQ (grid1.GetAliveCellsNumber (), 0)     << "> 03";

  GridClass grid2 (16);
  EXPECT_EQ (grid2.GetGridSize (), 257)           << "> 03";
  EXPECT_EQ (grid2.GetAliveCellsNumber (), 0)     << "> 03";

  GridClass grid3 (0, 0);
  EXPECT_EQ (grid3.GetGridSize (), 0)             << "> 03";
  EXPECT_EQ (grid3.GetAliveCellsNumber (), 0)     << "> 03";

  GridClass grid4 (240, 160);
  EXPECT_EQ (grid4.GetGridSize (), 38401)         << "> 03";
  EXPECT_EQ (grid4.GetAliveCellsNumber (), 0)     << "> 03";
}

TEST_F (TestGridClass, GetInfoAboutGrid)
{
  EXPECT_TRUE ((me::ISGETGRIDSIZE0<GridClass, uint32_t>))               << "> 02";
  EXPECT_TRUE ((me::ISGETLINESIZE0<GridClass, uint32_t>))               << "> 02";
  EXPECT_TRUE ((me::ISGETALIVECELLSNUMBER0<GridClass, uint32_t>))       << "> 02";
  EXPECT_TRUE ((me::ISGETCURRENTEPOCH0<GridClass, std::vector<bool>>))  << "> 02";
  EXPECT_TRUE ((me::ISGETEPOCHNUM0<GridClass, uint32_t>))               << "> 02";

  EXPECT_EQ (permanent.GetGridSize (), 257)     << "> 04";
  EXPECT_EQ (loop.GetLineSize (), 16)           << "> 04";
  EXPECT_EQ (motion.GetAliveCellsNumber (), 5)  << "> 04";
  EXPECT_EQ (motion.GetEpochNum(), 0)           << "> 04";
}

TEST_F (TestGridClass, AreInfoMethodsConst)
{
  EXPECT_TRUE ((ISMETHODCONST (GridClass, GetGridSize)))                << "> 05";
  EXPECT_TRUE ((ISMETHODCONST (GridClass, GetLineSize)))                << "> 05";
  EXPECT_TRUE ((ISMETHODCONST (GridClass, GetAliveCellsNumber)))        << "> 05";
  EXPECT_TRUE ((ISMETHODCONST (GridClass, GetCurrentEpoch)))            << "> 05";
  EXPECT_TRUE ((ISMETHODCONST (GridClass, GetEpochNum)))                << "> 05";
}

TEST_F (TestGridClass, SetStartEpoch)
{
  ASSERT_TRUE ((me::ISSETSTARTEPOCH1<GridClass, std::vector<uint32_t>, void>)) << "> 02";

  EXPECT_EQ (permanent.GetAliveCellsNumber (), permanent_startepoch.size ())   << "> 03";
  EXPECT_TRUE (fu::comparecellspositions (permanent_startepoch, permanent))    << "> 04";

  EXPECT_EQ (loop.GetAliveCellsNumber (), loop_startepoch.size ())             << "> 03";
  EXPECT_TRUE (fu::comparecellspositions (loop_startepoch, loop))              << "> 04";

  EXPECT_EQ (motion.GetAliveCellsNumber (), motion_startepoch.size ())         << "> 03";
  EXPECT_TRUE (fu::comparecellspositions (motion_startepoch, motion))          << "> 04";
}

TEST_F (TestGridClass, CountNextEpoch)
{
  ASSERT_TRUE ((me::ISCOUNTNEXTEPOCH0<GridClass, void>)) << "> 02";

  // check permanent grid
  int permanent_epochstocheck = 4;
  std::vector<std::vector<uint32_t>> permanent_expectedepochs (permanent_epochstocheck, permanent_startepoch);
  fu::testcountnextepoch ("permanent", permanent, permanent_expectedepochs, permanent_epochstocheck);
  EXPECT_EQ (permanent.GetEpochNum(), 4)  << "> 04";

  // check loop grid
  int loop_epochstocheck = 9;
  std::vector<std::vector<uint32_t>> loop_expectedepochs (loop_epochstocheck);
  loop_expectedepochs [0] = loop_startepoch;
  loop_expectedepochs [1] = { 74,  89,  90,  91, 104, 106, 107, 108, 119, 123, 134, 138, 149, 150, 151, 153, 166, 167, 168, 183 };
  loop_expectedepochs [2] = { 73,  74,  75,  92, 104, 108, 119, 121, 124, 133, 136, 138, 149, 153, 165, 182, 183, 184 };
  loop_expectedepochs [3] = { 58,  74,  75,  89, 90,  92,  104, 107, 108, 109, 119, 121, 123, 134, 136, 138, 148, 149, 150, 153, 165, 167, 168, 182, 183, 199 };
  loop_expectedepochs [4] = { 58,  59,  89,  93, 104, 109, 119, 121, 123, 134, 136, 138, 148, 153, 164, 168, 198, 199 };
  loop_expectedepochs [5] = { 74, 104, 105, 106, 108, 119, 121, 122, 135, 136, 138, 149, 151, 152, 153, 183 };
  loop_expectedepochs [6] = { 90,  91, 104, 106, 107, 119, 138, 150, 151, 153, 166, 167 };
  loop_expectedepochs [7] = { 89,  90,  91, 105, 106, 107, 121, 122, 123, 134, 135, 136, 150, 151, 152, 166, 167, 168 };
  loop_expectedepochs [8] = loop_startepoch;
  fu::testcountnextepoch ("loop", loop, loop_expectedepochs, loop_epochstocheck);
  EXPECT_EQ (loop.GetEpochNum(), 9)  << "> 04";

  // check motion grid
  int motion_epochstocheck = 9;
  std::vector<std::vector<uint32_t>> motion_expectedepochs (motion_epochstocheck);
  motion_expectedepochs[0] = motion_startepoch;
  motion_expectedepochs[1] = { 45, 60, 76, 77, 78 };
  motion_expectedepochs[2] = { 60, 62, 76, 77, 93 };
  motion_expectedepochs[3] = { 60, 76, 78, 92, 93 };
  motion_expectedepochs[4] = { 61, 75, 76, 92, 93 };
  motion_expectedepochs[5] = { 60, 75, 91, 92, 93 };
  motion_expectedepochs[6] = { 75, 77, 91, 92, 108 };
  motion_expectedepochs[7] = { 75, 91, 93, 107, 108 };
  motion_expectedepochs[8] = { 76, 90, 91, 107, 108 };
  fu::testcountnextepoch ("motion", motion, motion_expectedepochs, motion_epochstocheck);
  EXPECT_EQ (motion.GetEpochNum(), 9)  << "> 04";
}

// clang-format on

class TestPrintClass : public ::testing::Test
{

protected:
  GridClass grid;
  PrintClass printer;

  TestPrintClass () : grid{ GridClass (16) }, printer{ &grid } {}

  void
  SetUp () override
  {
    std::vector<uint32_t> startepoch
        = { 74, 89, 91, 104, 108, 119, 123, 134, 138, 149, 153, 166, 168, 183 };
    grid.SetStartEpoch (startepoch);
  }
};

// clang-format off

TEST_F (TestPrintClass, CTORs)
{
  EXPECT_FALSE(me::ISCTOR0<PrintClass>)                         << "> 01";
  EXPECT_FALSE((me::ISCTOR1<PrintClass, GridClass>))            << "> 01";
  ASSERT_TRUE((me::ISCTOR1<PrintClass, GridClass* const> ))     << "> 02";
  
  EXPECT_NE(printer.GetGrid(), nullptr);
}

TEST_F (TestPrintClass, GetInfoAboutPrinter)
{
  EXPECT_TRUE((me::ISGETGRID0<PrintClass, const GridClass*>))  << "> 02";
}

TEST_F (TestPrintClass, AreInfoMethodsConst)
{
  EXPECT_TRUE((ISMETHODCONST(PrintClass, GetGrid)))            << "> 05";
}

TEST_F (TestPrintClass, DefaultTerminal)
{
  EXPECT_TRUE ((me::ISSETCHARS2<PrintClass, char, char, void>))              << "> 02";
  EXPECT_TRUE ((me::ISRESETTERMINAL0<PrintClass, void>))                     << "> 02";
  EXPECT_TRUE ((me::ISPRINTEPOCH0<PrintClass, void>))                        << "> 02";
  EXPECT_TRUE ((me::ISPRINTEPOCHNUM0<PrintClass, void>))                     << "> 02";
  EXPECT_TRUE ((me::ISSETFRAMESPERSECOND1<PrintClass, uint32_t, void>))      << "> 02";
}

// clang-format on

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
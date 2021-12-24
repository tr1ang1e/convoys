/**
 * An example gtests
 * version number 1.04
 *
 *  Testing
 *  - drilling down into google 'primer'   1.01
 *  - memory leaking when using ASSERT_*   1.02
 *  - compare ASSERT_* and EXPECT_*        1.03
 *  - check if method exists               1.04
 *  - create helper header                 1.05
 *  - default ctor + virtual dtor exist    1.06
 *
 */

#include <gtest/gtest.h>
#include <iostream>

#include "_exls.hpp"   // delete '_' from the header name
#include "_helper.hpp" // delete '_' from the header name

class TestFixture : public ::testing::Test
{
protected:
  CLASS* tf_obj;
  bool tf_isdtorv;

  TestFixture () : tf_obj{ nullptr }, tf_isdtorv{ false } {}

  void
  SetUp () override
  {
  }

  void
  TearDown () override
  {
  }

  ~TestFixture ()
  {
    if (tf_obj)
      delete tf_obj;
  }
};

TEST_F (TestFixture, DTOR)
{

  BASE* obj = new CLASS (&tf_isdtorv);
  delete obj;
  EXPECT_EQ (tf_isdtorv, true) << "> VIRTUAL DTOR DOESN'T EXIST";
}

TEST_F (TestFixture, CTOR)
{
  EXPECT_EQ (me::ISCTOR0<CLASS>, true) << "> DEFAULT CTOR DOESN'T EXIST";
}

TEST_F (TestFixture, ISFUNCT1)
{

  EXPECT_EQ ((me::ISFUNCT1<CLASS, int, void>), true) << "> DOESN'T EXIST";
  EXPECT_EQ ((me::ISFUNCT1<CLASS, float, void>), false)
      << "> EXPLICIT CONVERSION";
}

int
main (int argc, char* argv[])
{
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
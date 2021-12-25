/**
 * An example gtests
 * version number 1.04
 *
 *  Testing
 *  - class COUNT    default ctor doesn't exist         1.01.00
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

  TestFixture () : tf_obj{ nullptr } {}

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

TEST_F (TestFixture, MACROTEST)
{
  EXPECT_TRUE ((me::ISCTOR2<CLASS, int, int>))
      << "> [ CLASS::CLASS(int, int) ] DOESN'T EXIST";
  EXPECT_FALSE ((me::ISCTOR2<CLASS, float, int>))
      << "> [ CLASS::CLASS(int, int) ] IMPLICIT CAST";

  EXPECT_TRUE ((me::ISCTOR0<CLASS>)) << "> [ CLASS::CLASS() ] DOESN'T EXIST";
  EXPECT_TRUE ((me::ISFUNCT1<CLASS, int, void>))
      << "> [ void CLASS::funct(int) ] DOESN'T EXIST";
}

int
main (int argc, char* argv[])
{
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
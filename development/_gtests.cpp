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

#include "_helper.hpp"    // delete '_' from the header name
#include "_exls.hpp"      // delete '_' from the header name



class TestFixture : public ::testing::Test
{
  protected:

    CLASS* tf_obj;
    bool tf_isdtorv; 

    TestFixture( ) : tf_obj {nullptr}, tf_isdtorv {false}
    {
    }

    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    ~TestFixture( )
    {
      if (tf_obj) delete tf_obj;
    }
};

TEST_F (TestFixture, CTOR)
{
  EXPECT_FALSE (me::ISCTOR0<CLASS>) << "> DEFAULT CTOR EXIST";
}



int
main (int argc, char *argv[])
{
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
#include <gtest/gtest.h>

class BoilerplateFixture : public ::testing::Test
{
  protected:
    
    BoilerplateFixture( )
    {
    }

    void 
    SetUp() override   
    {
    }

    void 
    TearDown() override  
    {
    }

  ~ BoilerplateFixture( )
    {
    }

};

TEST_F (BoilerplateFixture, TestName)
{
}
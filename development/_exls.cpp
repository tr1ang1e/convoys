#include <iostream>
#include <string>

#include "_exls.hpp"

BASE::BASE(bool* isdtorv_arg)
: isdtorv {isdtorv_arg}
{
  std::cout << ": BASE CTOR" << std::endl;
}

BASE::~BASE()
{
  std::cout << ": BASE DTOR" << std::endl;
}

CLASS::CLASS(bool* isdtorv_ar) 
: BASE(isdtorv_ar)
{
  std::cout << ": CLASS DTOR" << std::endl;
}

CLASS::~CLASS()
{
  if (isdtorv) *isdtorv = true;
  std::cout << ": CLASS DTOR" << std::endl;
}

void 
CLASS::funct(const int&)
{
}


// int main( )
// {
  
//   bool test = false;

//   BASE* b = new CLASS(&test);
//   delete b;
  
//   std::cout << test << std::endl;

// }
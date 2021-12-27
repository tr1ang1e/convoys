/**
 * Helper .hpp to implement additional entities
 *
 *  Namespaces
 *  [me] ifmethodexists = checking name + arg types + return value type
 *
 *
 */

#pragma once

// required headers
#include <iostream>
#include <concepts>
#include <utility>
#include <vector>
#include <thread>

namespace functions
{
  // processing delay
  void delayprocess(const unsigned int& millisec)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(millisec));
  }
  
  // ECS sequence = *ESC*c 
  void resetterminal()
  {
    const char ESC = 0x1B;
    const char CLEAN = 0x63; 
    std::cout << ESC << CLEAN;
  }
  
  // print epoch to terminal
  void printepoch(const std::vector<char>& field, const int& width)
  {
    resetterminal();  // clean terminal and back cursor to the 0x0 position
    
    // print epoch
    int i = 0;
    for (const auto& el : field)
    {
      if (i % width) std::cout << el;
      else std::cout << el << std::endl;
      ++i;
    }
  }
}



// clang-format off

// default constructor
#define ISCTOR0()                 \
  template <typename CLASS>       \
  concept ISCTOR0 =               \
  requires( )                     \
  {                               \
    CLASS();                      \
  };            


// ctor with 1 input argument
#define ISCTOR1()                                                           \
  template <typename CLASS, typename ARG1>                                  \
  concept ISCTOR1 =                                                         \
  requires( )                                                               \
  {                                                                         \
    CLASS(std::declval<ARG1>());                                            \
  }; 

// ctor with 2 input arguments
#define ISCTOR2()                                                           \
  template <typename CLASS, typename ARG1, typename ARG2>                   \
  concept ISCTOR2 =                                                         \
  requires( )                                                               \
  {                                                                         \
    CLASS(std::declval<ARG1>(), std::declval<ARG2>());                      \
  }; 

// method with 1 input argument
#define ISMETHOD1(METHOD, method)                                                         \
  template <typename CLASS, typename ARG1, typename RET>                                  \
  concept IS ## METHOD ## 1 =                                                             \
  requires( )                                                                             \
  {                                                                                       \
    { std::declval<CLASS>().method(std::declval<ARG1>()) } -> std::same_as<RET>;          \
  };

// clang-format on


namespace ifmethodexists
{

/**
 * Made using concepts
 * Concept name >> ISNAME1
 *    IS = prefix
 *    NAME = method name
 *    1 = number of methos arguments
 *
 * Template parameters
 *    CLASS = class for method existing checking
 *    ARGN  = types of adrguments ( N = 1, 2, ... )
 *    RET   = return value type
 *
 * Usage. Concept converts to bool:
 * bool b = ISNAME1<MyClass, int, int>
 *
 */

ISCTOR0 ();
ISCTOR1 ();
ISCTOR2 ();

ISMETHOD1 (FUNCT, funct);
ISMETHOD1 (SETSTARTPICTURE, SetStartPicture);

}

// short namespace aliases
namespace fu = functions;
namespace me = ifmethodexists;
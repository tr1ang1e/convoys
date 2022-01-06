/**
 * Helper .hpp to implement additional entities
 *
 *  Namespaces
 *  [me] ifmethodexists = checking: name, arg types, return value type, is const
 *       actual list:
 *       ISCTOR0, ISCTOR1, ISCTOR2
 *       ISMETHOD0, ISMETHOD1
 *       ISMETHODCONST
 *
 *  Made using concepts
 *  Concept name >> ISNAME1
 *    IS = prefix
 *    NAME = method name
 *    1 = number of methos arguments
 *
 *  Template parameters
 *    CLASS = class for method existing checking
 *    ARGN  = types of adrguments ( N = 1, 2, ... )
 *    RET   = return value type
 *
 *  Usage. Concept converts to bool:
 *  bool b = ISNAME1<MyClass, int, int>
 *
 */

#pragma once

// required headers
#include <concepts>
#include <utility>

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

// method with 0 input arguments
#define ISMETHOD0(METHOD, method)                                           \
  template <typename CLASS, typename RET>                                   \
  concept IS ## METHOD ## 0 =                                               \
  requires( )                                                               \
  {                                                                         \
    { std::declval<CLASS>().method() } -> std::same_as<RET>;                \
  };

// method with 1 input argument
#define ISMETHOD1(METHOD, method)                                                         \
  template <typename CLASS, typename ARG1, typename RET>                                  \
  concept IS ## METHOD ## 1 =                                                             \
  requires( )                                                                             \
  {                                                                                       \
    { std::declval<CLASS>().method(std::declval<ARG1>()) } -> std::same_as<RET>;          \
  };

// method with 2 input arguments
#define ISMETHOD2(METHOD, method)                                                         \
  template <typename CLASS, typename ARG1, typename ARG2, typename RET>                   \
  concept IS ## METHOD ## 2 =                                                             \
  requires( )                                                                             \
  {                                                                                       \
    { std::declval<CLASS>().method(std::declval<ARG1>(), std::declval<ARG2>()) }          \
    -> std::same_as<RET>;                                                                 \
  };

// method constancy
#define ISMETHODCONST(CLASS, METHOD)  \
me::ISMETHODCONST<CLASS, decltype(&CLASS::METHOD)>


// macro
namespace ifmethodexists
{

ISCTOR0 ();
ISCTOR1 ();
ISCTOR2 ();

// GridClass
ISMETHOD0 (GETGRIDSIZE, GetGridSize);
ISMETHOD0 (GETLINESIZE, GetLineSize);
ISMETHOD0 (GETCURRENTEPOCH, GetCurrentEpoch);
ISMETHOD0 (GETALIVECELLSNUMBER, GetAliveCellsNumber);
ISMETHOD0 (GETEPOCHNUM, GetEpochNum);
ISMETHOD0 (COUNTNEXTEPOCH, CountNextEpoch);
ISMETHOD0 (GETCURRENTEPOCHCITERS, GetCurrentEpochCiters);
ISMETHOD1 (SETSTARTEPOCH, SetStartEpoch);


// PrintClass
ISMETHOD0 (GETGRID, GetGrid);
ISMETHOD0 (RESETTERMINAL, ResetTerminal);
ISMETHOD0 (PRINTEPOCH, PrintEpoch);
ISMETHOD0 (PRINTEPOCHNUM, PrintEpochNum);
ISMETHOD0 (GETALIVECHAR, GetAliveChar);
ISMETHOD0 (GETDEADCHAR, GetDeadChar);
ISMETHOD0 (GETDELAY, GetDelay);
ISMETHOD1 (SETFRAMESPERSECOND, SetFramesPerSecond);
ISMETHOD2 (SETCHARS, SetChars);

}

// as is
namespace ifmethodexists
{

template <typename CLASS, typename METHOD, typename ... ARGS>
concept ISMETHODCONST =
requires(METHOD method, ARGS ... args)
{
  (std::declval<CLASS const>().*method)(args ...);
};

}

// short namespace aliases
namespace me = ifmethodexists;

// clang-format on
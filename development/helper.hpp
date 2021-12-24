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
#include <concepts>
#include <utility>

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

// clang-format off

  // default constructor
  template <typename CLASS>
  concept ISCTOR0 =    
  requires( )
  {
    // CLASS* obj = new CLASS;
    CLASS();
  };

  template <typename CLASS, typename ARG1, typename RET>
  concept ISFUNCT1 =
  requires( )
  {
    { CLASS().funct(std::declval<ARG1>()) } -> std::same_as<RET>;
  };

// clang-format on

}

// short namespace aliases
namespace me = ifmethodexists;
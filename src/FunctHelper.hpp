/**
 * Helper .hpp to implement additional entities
 *
 *  Namespaces
 *  [fu] functions =
 *       delayprocess
 *       resetterminal
 *       printepoch
 *       iftestgridisvalid
 *       comparecellspositions
 *       testcountnextepoch
 *
 */

#pragma once

// required headers
#include "GridClass.hpp"
#include <concepts>
#include <string>
#include <vector>

namespace functions
{

// debug by marks printing
template <typename T>
concept MARK = std::is_same<T, const char*>::value || std::is_same<T, int>::value;

// debug by marks printing
template <MARK T> void mark (T);

// processing delay
void delayprocess (const unsigned int&);

// ECS sequence = *ESC*c
void resetterminal ();

// print epoch to terminal
void printepoch (const std::vector<char>&, const int&);

// check if test (manual) grid is valid
bool iftestgridisvalid (std::vector<uint32_t>&, const GridClass&);

// check: cell is alive but shouldn't be
bool wrongalive (const std::vector<uint32_t>&, std::vector<bool>);

// check: cell should be alive but is not
bool wrongdead (const std::vector<uint32_t>&, std::vector<bool>);

// compare manual entered cells positions with actual alive cells positions
bool comparecellspositions (std::vector<uint32_t>&, const GridClass&);

// test given number of counted and expected epochs
void testcountnextepoch (const std::string, GridClass&,
                         std::vector<std::vector<uint32_t>>, const int);

}

// short namespace aliases
namespace fu = functions;
/**
 * Helper .hpp to implement additional entities
 *
 *  Namespaces
 *  [fu] functions =
 *       delayprocess
 *       resetterminal
 *       printepoch
 *       comparecellspositions
 *
 */

#pragma once

// required headers
#include "GreedClass.hpp"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>

namespace functions
{

// processing delay
void
delayprocess (const unsigned int& millisec)
{
  std::this_thread::sleep_for (std::chrono::milliseconds (millisec));
}

// ECS sequence = *ESC*c
void
resetterminal ()
{
  const char ESC = 0x1B;
  const char CLEAN = 0x63;
  std::cout << ESC << CLEAN;
}

// print epoch to terminal
void
printepoch (const std::vector<char>& field, const int& width)
{
  resetterminal (); // clean terminal and back cursor to the 0x0 position

  // print epoch
  int i = 0;
  for (const auto& el : field)
    {
      if (i % width)
        std::cout << el;
      else
        std::cout << el << std::endl;
      ++i;
    }
}

// compare manual alive cells positions with actual alive cells positions
bool
comparecellspositions (const std::vector<uint16_t>& manual, const GridClass& grid)
{
  bool same = true;

  uint32_t gridsize = grid.GetGridSize ();
  std::vector<char> currentepoch = grid.GetCurrentEpoch ();

  auto begin = manual.begin ();
  auto end = manual.end ();

  // if alive cells are expected (cell is alive but shouldn't be)
  for (int idx = 0; idx < gridsize; ++idx)
    {
      if (currentepoch[idx])
        {
          auto found = std::binary_search (begin, end, idx);
          if (!found)
            {
              same = false;
              return same;
            }
        }
    }

  // if expected cells are alive (cell should be alive but is not)
  for (const auto& el : manual)
    {
      if (!currentepoch[el])
        {
          same = false;
          return same;
        }
    }

  return same;
}

}

// short namespace aliases
namespace fu = functions;
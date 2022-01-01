/**
 * Helper .hpp to implement additional entities
 *
 *  Namespaces
 *  [fu] functions =
 *       delayprocess
 *       resetterminal
 *       printepoch
 *       comparecellspositions
 *       testcountnextepoch
 *
 */

#pragma once

// required headers
#include "GridClass.hpp"
#include <algorithm>
#include <concepts>
#include <cstdint>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

namespace functions
{

// debug by marks printing
template <typename T>
concept MARK = std::is_same<T, const char*>::value || std::is_same<T, int>::value;

// debug by marks printing
template <MARK T>
void
mark (T massage)
{
  std::cout << "> MARK : " << massage << std::endl;
}

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

// check if test (manual) grid is valid
bool
iftestgridisvalid (std::vector<uint32_t>& manual, const GridClass& grid)
{

  // check if test (manual) grid is empty (empty is valid)
  if (!manual.size ())
    return true;

  // check if every value in the test (manual) grid is less than grid size
  uint32_t max_idx = *std::max_element (manual.begin (), manual.end ());
  if (max_idx >= grid.GetGridSize ())
    {
      std::cout << "> Some of test grid values greater than max tested grid index"
                << std::endl;
      std::cout << ">   max test value = " << max_idx << std::endl;
      std::cout << ">   tested grid size = " << grid.GetGridSize () << std::endl;
      return false;
    }

  return true;
}

// compare manual entered cells positions with actual alive cells positions
bool
comparecellspositions (std::vector<uint32_t>& manual, const GridClass& grid)
{
  bool same = true;

  if (!iftestgridisvalid (manual, grid))
    {
      same = false;
      return same;
    }

  std::sort (manual.begin (), manual.end ());
  uint32_t gridsize = grid.GetGridSize ();
  std::vector<bool> currentepoch = grid.GetCurrentEpoch ();

  auto begin = manual.begin ();
  auto end = manual.end ();
  // if alive cells are not expected (cell is alive but shouldn't be)
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

  // if expected cells are not alive (cell should be alive but is not)
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

// test given number of counted and expected epochs
void
testcountnextepoch (const std::string grid_name, GridClass& grid,
                    std::vector<std::vector<uint32_t>> expectedepochs, const int epochs)
{
  std::cout << "> TEST GRID = " << grid_name << std::endl;
  for (int i = 0; i < epochs; ++i)
    {
      std::cout << "> EPOCH NUMBER = " << i << std::endl;
      EXPECT_EQ (grid.GetAliveCellsNumber (), expectedepochs[i].size ()) << "> 03";
      EXPECT_TRUE (comparecellspositions (expectedepochs[i], grid)) << "> 04";
      grid.CountNextEpoch ();
    }
}

}

// short namespace aliases
namespace fu = functions;
#pragma once

#include <cstdint>
#include <string>
#include <vector>

class GridClass
{
  using Grid = std::vector<bool>;
  Grid grid;
  Grid next;

  using Side = uint32_t;
  Side x;
  Side y;

  uint32_t epochnum = 0;

public:
  GridClass () = delete;
  GridClass (Side);
  GridClass (Side, Side);

  void SetStartEpoch (const std::vector<Side>&);
  void CountNextEpoch ();

  // get info methods
  uint32_t GetGridSize () const;
  uint32_t GetLineSize () const;
  uint32_t GetAliveCellsNumber () const;
  Grid GetCurrentEpoch () const;
  uint32_t GetEpochNum () const;

  using Citer = std::vector<bool>::const_iterator;
  std::pair<Citer, Citer> GetCurrentEpochCiters () const;

private:
  void CreateGrid ();
  bool CheckNeighbours (uint32_t);
};
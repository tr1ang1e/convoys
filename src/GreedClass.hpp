#pragma once

#include <cstdint>
#include <string>
#include <vector>

class GridClass
{
  using Grid = std::vector<char>;
  Grid grid;
  Grid next;

  using Side = uint32_t;
  Side x;
  Side y;

  uint32_t epochnum = 0;
  char cellchar = 'x';

public:
  GridClass () = delete;
  GridClass (Side);
  GridClass (Side, Side);

  void SetStartEpoch (const std::vector<Side>&);
  uint32_t GetGridSize () const;
  uint32_t GetAliveCellsNumber () const;
  Grid GetCurrentEpoch () const;
  uint32_t GetEpochNum () const;
  void CountNextEpoch ();

private:
  void CreateGrid ();
  bool CheckNeighbours(uint32_t);
};
#pragma once

#include <cstdint>
#include <string>
#include <vector>

class GridClass
{
  using Grid = std::vector<char>;
  Grid grid;
  Grid temp;

  using Side = uint16_t;
  Side x;
  Side y;

  uint16_t epochnum = 0;
  char cellchar = 'x';

public:
  GridClass () = delete;
  GridClass (const Side& side);
  GridClass (const Side& _x, const Side& _y);

  void SetStartEpoch (const std::vector<uint16_t>& alivecells);
  uint32_t GetGridSize () const;
  uint32_t GetAliveCellsNumber () const;
  Grid GetCurrentEpoch () const;
  uint16_t GetEpochNum () const;
  void CountNextEpoch ();
};
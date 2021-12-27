#pragma once

#include <cstdint>
#include <vector>

class GridClass
{
  using Grid = std::vector<char>;
  Grid grid;

  char cellchar = 'x';

public:
  GridClass () = delete;
  GridClass (const uint16_t& side);

  uint32_t GetGridSize () const;
  void SetStartEpoch (const std::vector<uint16_t>& alivecells);
  uint32_t GetAliveCellsNumber () const;
  Grid GetCurrentEpoch () const;
};
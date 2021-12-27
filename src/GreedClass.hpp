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

  uint32_t GetGridSize ();
  uint32_t GetAliveCellsNumber ();
  void SetStartPicture (const std::vector<int>& alivecells);
};
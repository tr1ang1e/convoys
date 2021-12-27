#pragma once

class GridClass
{
  using Grid = std::vector<char>;
  Grid grid;

  public:

  GridClass () = delete;
  GridClass (const int& side);
  
  void SetStartPicture(const std::vector<int>& alivecells);

};
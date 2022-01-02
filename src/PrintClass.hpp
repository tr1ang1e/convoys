#pragma once

#include "GridClass.hpp"

class PrintClass
{

  GridClass* const grid;

public:

  PrintClass () = delete;
  PrintClass (GridClass*);

  const GridClass* GetGrid() const;

};
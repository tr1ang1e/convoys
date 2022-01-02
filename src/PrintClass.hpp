#pragma once

#include "GridClass.hpp"

class PrintClass
{

  GridClass* const grid;

public:
  PrintClass () = delete;
  PrintClass (GridClass*);

  void ResetTerminal ();

  // get info methods
  const GridClass* GetGrid () const;

private:
};
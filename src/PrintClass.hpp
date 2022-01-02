#pragma once

#include "GridClass.hpp"

class PrintClass
{

  GridClass* const grid;
  const uint32_t grid_size;
  const uint32_t line_size;

  char alive_char;
  char dead_char;

public:
  PrintClass () = delete;
  PrintClass (GridClass*);

  void SetChars (char, char);
  void ResetTerminal ();
  void PrintEpoch ();

  // get info methods
  const GridClass* GetGrid () const;

private:
};
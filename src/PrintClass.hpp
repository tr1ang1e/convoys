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

  // settings
  void SetChars (char, char);
  void SetFramesPerSecond (const uint64_t);

  // printing
  void ResetTerminal ();
  void PrintEpoch ();
  void PrintEpochNum ();

  // get info methods
  const GridClass* GetGrid () const;

private:
};
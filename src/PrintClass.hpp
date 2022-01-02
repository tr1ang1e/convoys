#pragma once

#include "GridClass.hpp"

class PrintClass
{

  GridClass* const grid;
  const uint32_t grid_size;
  const uint32_t line_size;

  char alive_char;
  char dead_char;
  uint32_t delay;

public:
  PrintClass () = delete;
  PrintClass (GridClass*);

  // settings
  void SetChars (char, char);
  void SetFramesPerSecond (const uint32_t);

  // printing
  void ResetTerminal ();
  void PrintEpoch ();
  void PrintEpochNum ();

  // get info methods
  const GridClass* GetGrid () const;
  char GetAliveChar () const;
  char GetDeadChar () const;
  uint32_t GetDelay () const;

private:
};
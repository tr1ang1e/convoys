#pragma once

template <typename T> concept INTONLY = std::same_as<int, T>;

class CLASS
{
public:
  CLASS () = default;

  template <INTONLY T> CLASS (const T&, const T&);

  template <typename T> void funct (T) = delete;

  void funct (const int&);

  ~CLASS () = default;
};
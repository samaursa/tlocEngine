#ifndef TLOC_ALGORITHMS_H
#define TLOC_ALGORITHMS_H

namespace tloc
{
  template <typename T>
  void Swap(T& a, T& b)
  {
    T c(a); a = b; b = c;
  }
}

#endif
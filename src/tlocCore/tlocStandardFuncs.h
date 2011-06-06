#ifndef ADDITIONAL_FUNCTIONS_H
#define ADDITIONAL_FUNCTIONS_H

namespace tloc
{
  template <typename T>
  void Swap(T& a, T& b)
  {
    T c(a); a = b; b = c;
  }
}

#endif
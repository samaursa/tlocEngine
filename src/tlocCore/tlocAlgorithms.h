#ifndef TLOC_ALGORITHMS_H
#define TLOC_ALGORITHMS_H

namespace tloc
{
  template <typename T>
  void Swap(T& a, T& b)
  {
    T c(a); a = b; b = c;
  }

  // Copies the range of elements [aRangeBegin, aRangeEnd) to aCopyTo and returns
  // an iterator to the end of the destination range
  template <typename T_InputIterator, typename T_OutputIterator>
  T_OutputIterator Copy(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                        T_OutputIterator aCopyTo)
  {
    while (aRangeBegin != aRangeEnd)
    {
      *aCopyTo = *aRangeBegin;
      ++aCopyTo;
      ++aRangeBegin;
    }

    return aCopyTo;
  }

  template <typename T_InputIterator, typename T>
  void Fill(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
            const T& aValue)
  {
    while (aRangeBegin != aRangeEnd)
    {
      *aRangeBegin = aValue;
      ++aRangeBegin;
    }
  }
}

#endif
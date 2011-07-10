#ifndef TLOC_ALGORITHMS_H
#define TLOC_ALGORITHMS_H

//------------------------------------------------------------------------
// Fine grain control to enable/disable assertions in algorithms

#ifndef TLOC_DISABLE_ASSERT_ARRAY
# define TLOC_ASSERT_ALGORITHMS(_Expression, _Msg) TLOC_ASSERT_LOW_LEVEL(_Expression, _Msg)
#else
# define TLOC_ASSERT_ALGORITHMS(_Expression, _Msg)
#endif

namespace tloc
{
  template <typename T>
  void Swap(T& a, T& b)
  {
    T c(a); a = b; b = c;
  }

  // Copies the range of elements [aRangeBegin, aRangeEnd) to aCopyTo and returns
  // an iterator to the end of the destination range
  // 5 4 6 7 2 3 8 4 5 6 7
  // ^                     ^
  // aRangeBegin           aRangeEnd (copy 5,4,6,7,2,3,8,4,5,6,7 inclusive)
  template <typename T_InputIterator, typename T_OutputIterator>
  T_OutputIterator Copy(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                        T_OutputIterator aDestRangeBegin)
  {
    TLOC_ASSERT_ALGORITHMS(aDestRangeBegin < aRangeBegin || aDestRangeBegin > aRangeEnd,
      "Output iterator is within the begin/end range (data over-writing)! - "
      L"Try Copy_Backward");
    TLOC_ASSERT_ALGORITHMS(aRangeBegin <= aRangeEnd,
      "aRangeBegin > aRangeEnd (infinite loop)!");

    while (aRangeBegin != aRangeEnd)
    {
      *(aDestRangeBegin++) = *(aRangeBegin++);
    }

    return aDestRangeBegin;
  }

  // Copies the range of elements [aRangeBegin, aRangeEnd) to aCopyTo and returns
  // an iterator to the first element in the destination range.
  // aDestRangeEnd must be past-the-end element of the destination range.
  // 5 4 6 7 2 3 8 4 5 6 7
  // ^                     ^
  // aRangeBegin           aRangeEnd (copy 5,4,6,7,2,3,8,4,5,6,7 inclusive)
  //
  // 1 2 3 4 5 6 7 8
  //                 ^
  //                 aDestRangeEnd (past-the-end, which is 8)
  template <typename T_InputIterator, typename T_OutputIterator>
  T_OutputIterator Copy_Backward(T_InputIterator aRangeBegin,
                                 T_InputIterator aRangeEnd,
                                 T_OutputIterator aDestRangeEnd)
  {
    TLOC_ASSERT_ALGORITHMS(aDestRangeEnd < aRangeBegin || aDestRangeEnd > aRangeEnd,
      "Output past-the-end iterator is within the begin/end range (data "
      L"over-writing)! - Try Copy");
    TLOC_ASSERT_ALGORITHMS(aRangeBegin <= aRangeEnd,
      "aRangeBegin > aRangeEnd (infinite loop)");

    while (aRangeEnd != aRangeBegin)
    {
      *(--aDestRangeEnd) = *(--aRangeEnd);
    }

    return aDestRangeEnd;
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
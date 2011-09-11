#ifndef TLOC_ALGORITHMS_H
#define TLOC_ALGORITHMS_H

#include "tlocTypeTraits.h"

//------------------------------------------------------------------------
// Fine grain control to enable/disable assertions in algorithms

#ifndef TLOC_DISABLE_ASSERT_ARRAY
# define TLOC_ASSERT_ALGORITHMS(_Expression, _Msg) TLOC_ASSERT_LOW_LEVEL(_Expression, _Msg)
#else
# define TLOC_ASSERT_ALGORITHMS(_Expression, _Msg)
#endif

namespace tloc
{
  //------------------------------------------------------------------------
  // Min / Max

  template <typename T>
  TL_I const T& tlMin(const T& a, const T& b);

  template <typename T>
  TL_I void tlSwap(T& a, T& b);

  //------------------------------------------------------------------------
  // Modifying sequence operations

  // Copies the range of elements [aRangeBegin, aRangeEnd) to aCopyTo and returns
  // an iterator to the end of the destination range
  // 5 4 6 7 2 3 8 4 5 6 7
  // ^                     ^
  // aRangeBegin           aRangeEnd (copy 5,4,6,7,2,3,8,4,5,6,7 inclusive)
  template <typename T_InputIterator, typename T_OutputIterator>
  TL_I T_OutputIterator tlCopy(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                               T_OutputIterator aDestRangeBegin);

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
  TL_I T_OutputIterator tlCopy_Backward(T_InputIterator aRangeBegin,
                                        T_InputIterator aRangeEnd,
                                        T_OutputIterator aDestRangeEnd);

  template <typename T_InputIterator, typename T>
  TL_I void tlFill(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                   const T& aValue);

  namespace detail
  {
    //------------------------------------------------------------------------
    // Copy() helpers

    typedef type_false IsNotArith;
    typedef type_true  IsArith;

    template <typename T_InputIterator, typename T_OutputIterator>
    TL_I T_OutputIterator tlCopy(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                                 T_OutputIterator aDestRangeBegin, IsNotArith);

    template <typename T_InputIterator, typename T_OutputIterator>
    TL_I T_OutputIterator tlCopy(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                                 T_OutputIterator aDestRangeBegin, IsArith);

    //------------------------------------------------------------------------
    // Fill helpers

    template <typename T>
    struct CharTest
    {
      typedef type_false result;
    };

    template <>
    struct CharTest <char8>
    {
      typedef type_true result;
    };

    typedef type_false IsNotChar;
    typedef type_true  IsChar;

    template <typename T_InputIterator, typename T>
    TL_I void tlFill( T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                      const T& aValue, IsNotChar );

    template <typename T_InputIterator, typename T>
    TL_I void tlFill( T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                      const T& aValue, IsChar );
  }
}

#include "tlocAlgorithms.inl"

#endif
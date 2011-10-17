#ifndef TLOC_ALGORITHMS_H
#define TLOC_ALGORITHMS_H

#include "tlocBase.h"
#include "tlocTypeTraits.h"
#include "tlocIterator.h"
#include "tlocPair.h"

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
  // Non-modifying sequence operations

  template <typename T_InputIterator, typename T_Function>
  T_Function for_each(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                      T_Function aFunc);

  template <typename T_InputIterator, typename T>
  T_InputIterator find(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                       const T& aValue);

  template <typename T_InputIterator, typename T_Predicate>
  T_InputIterator find_if(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                          T_Predicate aPred);

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 find_end(T_ForwardIterator1 aRangeToSearchBegin,
                              T_ForwardIterator1 aRangeToSearchEnd,
                              T_ForwardIterator2 aRangeToFindBegin,
                              T_ForwardIterator2 aRangeToFindEnd);

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
  T_ForwardIterator1 find_end(T_ForwardIterator1 aRangeToSearchBegin,
                              T_ForwardIterator1 aRangeToSearchEnd,
                              T_ForwardIterator2 aRangeToFindBegin,
                              T_ForwardIterator2 aRangeToFindEnd,
                              T_BinaryPredicate  aPred);

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 find_first_of(T_ForwardIterator1 aRangeToSearchBegin,
                                   T_ForwardIterator1 aRangeToSearchEnd,
                                   T_ForwardIterator2 aRangeToFindBegin,
                                   T_ForwardIterator2 aRangeToFindEnd);

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
  T_ForwardIterator1 find_first_of(T_ForwardIterator1 aRangeToSearchBegin,
                                   T_ForwardIterator1 aRangeToSearchEnd,
                                   T_ForwardIterator2 aRangeToFindBegin,
                                   T_ForwardIterator2 aRangeToFindEnd,
                                   T_BinaryPredicate  aPred);

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 find_first_not_of(T_ForwardIterator1 aRangeToSearchBegin,
                                       T_ForwardIterator1 aRangeToSearchEnd,
                                       T_ForwardIterator2 aRangeToFindBegin,
                                       T_ForwardIterator2 aRangeToFindEnd);

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
  T_ForwardIterator1 find_first_not_of(T_ForwardIterator1 aRangeToSearchBegin,
                                       T_ForwardIterator1 aRangeToSearchEnd,
                                       T_ForwardIterator2 aRangeToFindBegin,
                                       T_ForwardIterator2 aRangeToFindEnd,
                                       T_BinaryPredicate  aPred);

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 find_last_not_of(T_ForwardIterator1 aRangeToSearchBegin,
                                      T_ForwardIterator1 aRangeToSearchEnd,
                                      T_ForwardIterator2 aRangeToFindBegin,
                                      T_ForwardIterator2 aRangeToFindEnd);

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
  T_ForwardIterator1 find_last_not_of(T_ForwardIterator1 aRangeToSearchBegin,
                                      T_ForwardIterator1 aRangeToSearchEnd,
                                      T_ForwardIterator2 aRangeToFindBegin,
                                      T_ForwardIterator2 aRangeToFindEnd,
                                      T_BinaryPredicate  aPred);

  template <typename T_InputIterator, typename T>
  tl_size count(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                const T& aValue);

  template <typename T_InputIterator, typename T_Predicate>
  tl_size count_if(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                   T_Predicate aPred);

  template <typename T_InputIterator1, typename T_InputIterator2>
  Pair<T_InputIterator1, T_InputIterator2>
    mismatch(T_InputIterator1 aRangeBegin, T_InputIterator1 aRangeEnd,
             T_InputIterator2 aRangeToCompare);

  template <typename T_InputIterator1, typename T_InputIterator2, typename T_BinaryPred>
  Pair<T_InputIterator1, T_InputIterator2>
    mismatch(T_InputIterator1 aRangeBegin, T_InputIterator1 aRangeEnd,
             T_InputIterator2 aRangeToCompare, T_BinaryPred aPred);

  template <typename T_InputIterator1, typename T_InputIterator2>
  bool equal(T_InputIterator1 aRangeBegin, T_InputIterator1 aRangeEnd,
             T_InputIterator2 aRangeToCompare);

  template <typename T_InputIterator1, typename T_InputIterator2, typename T_BinaryPred>
  bool equal(T_InputIterator1 aRangeBegin, T_InputIterator1 aRangeEnd,
             T_InputIterator2 aRangeToCompare, T_BinaryPred aPred);

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 search(T_ForwardIterator1 aRangeToSearchBegin,
                            T_ForwardIterator1 aRangeToSearchEnd,
                            T_ForwardIterator2 aRangeToFindBegin,
                            T_ForwardIterator2 aRangeToFindEnd);

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
  T_ForwardIterator1 search(T_ForwardIterator1 aRangeToSearchBegin,
                            T_ForwardIterator1 aRangeToSearchEnd,
                            T_ForwardIterator2 aRangeToFindBegin,
                            T_ForwardIterator2 aRangeToFindEnd,
                            T_BinaryPredicate  aPred);

  template <typename T_ForwardIterator, typename T_Size, typename T>
  T_ForwardIterator search_n(T_ForwardIterator aRangeToSearchBegin,
                             T_ForwardIterator aRangeToSearchEnd,
                             T_Size aCount, const T& aValue);

  template <typename T_ForwardIterator, typename T_Size, typename T,
            typename T_BinaryPred>
  T_ForwardIterator search_n(T_ForwardIterator aRangeToSearchBegin,
                             T_ForwardIterator aRangeToSearchEnd,
                             T_Size aCount, const T& aValue,
                             T_BinaryPred aPred);

  //------------------------------------------------------------------------
  // Min / Max

  template <typename T_Value>
  TL_I const T_Value& tlMin(const T_Value& a, const T_Value& b);

  template <typename T>
  TL_I const T& tlMax(const T& a, const T& b);

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
  TL_I T_OutputIterator copy(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
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
  TL_I T_OutputIterator copy_backward(T_InputIterator aRangeBegin,
                                      T_InputIterator aRangeEnd,
                                      T_OutputIterator aDestRangeEnd);

  template <typename T_InputIterator, typename T>
  TL_I void fill(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                 const T& aValue);

  namespace detail
  {
    //------------------------------------------------------------------------
    // Copy() helpers

    typedef type_false IsNotArith;
    typedef type_true  IsArith;

    template <typename T_InputIterator, typename T_OutputIterator>
    TL_I T_OutputIterator copy(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                               T_OutputIterator aDestRangeBegin, IsNotArith);

    template <typename T_InputIterator, typename T_OutputIterator>
    TL_I T_OutputIterator copy(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                               T_OutputIterator aDestRangeBegin, IsArith);

    //------------------------------------------------------------------------
    // Fill helpers

    typedef type_false IsNotChar;
    typedef type_true  IsChar;

    template <typename T_InputIterator, typename T>
    TL_I void fill( T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                    const T& aValue, IsNotChar );

    template <typename T_InputIterator, typename T>
    TL_I void fill( T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                    const T& aValue, IsChar );

    //````````````````````````````````````````````````````````````````````````
    // find helpers

    template <typename T_InputIterator, typename T>
    T_InputIterator find(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                         const T& aValue, IsNotChar);

    template <typename T_InputIterator, typename T>
    T_InputIterator find(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                         const T& aValue, IsChar);
  }
}

#include "tlocAlgorithms.inl"

#endif
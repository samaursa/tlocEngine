#ifndef TLOC_ALGORITHMS_H
#define TLOC_ALGORITHMS_H

#include "tlocBase.h"
#include "tlocTypeTraits.h"
#include "tlocIterator.h"
#include "tlocPair.h"

//------------------------------------------------------------------------
// Fine grain control to enable/disable assertions in algorithms

#ifndef TLOC_DISABLE_ASSERT_ARRAY
# define TLOC_ASSERT_ALGORITHMS(_Expression, _Msg) \
  TLOC_ASSERT_LOW_LEVEL(_Expression, _Msg)
#else
# define TLOC_ASSERT_ALGORITHMS(_Expression, _Msg)
#endif

namespace tloc { namespace core {
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

  template <typename T_InputIterator1, typename T_InputIterator2,
            typename T_BinaryPred>
  Pair<T_InputIterator1, T_InputIterator2>
    mismatch(T_InputIterator1 aRangeBegin, T_InputIterator1 aRangeEnd,
             T_InputIterator2 aRangeToCompare, T_BinaryPred aPred);

  template <typename T_InputIterator1, typename T_InputIterator2>
  bool equal(T_InputIterator1 aRangeBegin, T_InputIterator1 aRangeEnd,
             T_InputIterator2 aRangeToCompare);

  template <typename T_InputIterator1, typename T_InputIterator2,
            typename T_BinaryPred>
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
  // Sorting

  ///-------------------------------------------------------------------------
  /// @brief
  /// Quicksort where the left most element is selected as the pivot. On
  /// a large linked list, this may be a better choice than a random
  /// selection. This is also the default technique used for non random
  /// access containers.
  ///-------------------------------------------------------------------------
  struct sort_quicksort_leftpivot{};

  ///-------------------------------------------------------------------------
  /// @brief
  /// Quicksort where the left most element is selected as the pivot. On
  /// a large linked list, this may be a better choice than a random
  /// selection.
  ///-------------------------------------------------------------------------
  struct sort_quicksort_rightpivot{};

  ///-------------------------------------------------------------------------
  /// @brief
  /// Quicksort where the middle element is selected as the pivot. This
  /// is not the best choice for a linked list.
  ///-------------------------------------------------------------------------
  struct sort_quicksort_middlepivot{};

  ///-------------------------------------------------------------------------
  /// @brief
  /// The default Quicksort variant that is used on random access
  /// containers. This may not be the best choice for linked lists.
  ///-------------------------------------------------------------------------
  struct sort_quicksort_randompivot{};

  ///-------------------------------------------------------------------------
  /// @brief
  /// Will select the leftpivot sort or randompivot sort depending on the
  /// type of container and its size.
  ///-------------------------------------------------------------------------
  struct sort_quicksort_autoselect{};

  ///-------------------------------------------------------------------------
  /// @brief Use when seek time is a bottleneck (for example disk access)
  ///-------------------------------------------------------------------------
  struct sort_mergesort{};

  ///-------------------------------------------------------------------------
  /// @brief
  /// Use for small data sets and/or data sets that are nearly sorted. If
  /// autosort is used, this algorithm is selected for smaller
  /// containers. STABLE IN-PLACE ONLINE.
  ///-------------------------------------------------------------------------
  struct sort_insertionsort{};

  ///-------------------------------------------------------------------------
  /// @brief
  /// Use only when low memory consumption is desired and the container
  /// is nearly sorted.
  ///-------------------------------------------------------------------------
  struct sort_bubblesort{};

  struct sort_autoselect{};

  // The default sort function. It sorts using random quicksort. See overloaded
  // sort function for using a different sorting algorithm.
  template <typename T_InputIterator>
  void sort(T_InputIterator aFirst, T_InputIterator aLast);

  // The sorting function can sort with multiple different techniques. Use
  // sort_autoselect to automatically select the best sorting algorithm for
  // the given container. Some techniques may not be compatible with the given
  // container
  template <typename T_InputIterator, typename T_SortAlgorithm>
  void sort(T_InputIterator aFirst, T_InputIterator aLast,
            T_SortAlgorithm);

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
  TL_I T_OutputIterator copy(T_InputIterator aRangeBegin,
                             T_InputIterator aRangeEnd,
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
    TL_I T_OutputIterator copy(T_InputIterator aRangeBegin,
                               T_InputIterator aRangeEnd,
                               T_OutputIterator aDestRangeBegin, IsNotArith);

    template <typename T_InputIterator, typename T_OutputIterator>
    TL_I T_OutputIterator copy(T_InputIterator aRangeBegin,
                               T_InputIterator aRangeEnd,
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

    //------------------------------------------------------------------------
    // find helpers

    template <typename T_InputIterator, typename T>
    T_InputIterator find(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                         const T& aValue, IsNotChar);

    template <typename T_InputIterator, typename T>
    T_InputIterator find(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                         const T& aValue, IsChar);

    //------------------------------------------------------------------------
    // Sort helpers

    ///-------------------------------------------------------------------------
    /// @brief
    /// Auto select the best quicksort for the given container type. Note
    /// that if you know the container size is small, random quicksort
    /// will provide the best results.
    ///
    /// @param  aFirst Range begin iterator.
    /// @param  aLast  Range past the end iterator.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast,
                sort_quicksort_autoselect);

    // This quicksort helper will select a random pivot. It is considered one
    // of the most efficient sorting methods

    ///-------------------------------------------------------------------------
    /// @brief
    /// This quicksort helper will select a random pivot. It is
    /// considered one of the most efficient sorting methods.
    ///
    /// @param  aFirst Range begin iterator.
    /// @param  aLast  Range past the end iterator.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast,
                sort_quicksort_randompivot);

    // This quicksort helper will select the pivot somewhere in the middle of the
    // container. This is not an efficient method for a random List<>

    ///-------------------------------------------------------------------------
    /// @brief
    /// This quicksort helper will select the pivot somewhere in the
    /// middle of the. container. This is not an efficient method for a
    /// random List&lt;&gt;
    ///
    /// @param  aFirst Range begin iterator.
    /// @param  aLast  Range past the end iterator.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast,
                sort_quicksort_middlepivot);

    // This quicksort helper will select the right most element (or aLast - 1)
    // as the pivot. This is not an efficient method for a not-so-random container
    // (user other pivot methods)

    ///-------------------------------------------------------------------------
    /// @brief
    /// This quicksort helper will select the right most element (or
    /// aLast - 1) as the pivot. This is not an efficient method for a
    /// not-so-random container (user other pivot methods)
    ///
    /// @param  aFirst Range begin iterator.
    /// @param  aLast  Range past the end iterator.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast,
                sort_quicksort_rightpivot);

    ///-------------------------------------------------------------------------
    /// @brief
    /// This quicksort helper assumes that the pivot is the first
    /// iterator and aLast is the past-the-end iterator. This is not an
    /// efficient method for a not-so-random container (use other pivot
    /// methods)
    ///
    /// @param  aFirst Range begin iterator.
    /// @param  aLast  Range past the end iterator.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast,
                sort_quicksort_leftpivot);

    typedef     type_false  IsComplexItr;
    typedef     type_true   IsRawItr;

    template <typename T_InputIterator>
    void DoQuicksortLeftPivot(T_InputIterator aFirst, T_InputIterator aLast,
                              IsRawItr);

    template <typename T_InputIterator>
    void DoQuicksortLeftPivot(T_InputIterator aFirst, T_InputIterator aLast,
                              IsComplexItr);

    ///-------------------------------------------------------------------------
    /// @brief
    /// Quicksort helper. This will perform the leftpivot quicksort on
    /// the given type. We need the quicksort helper because of raw and
    /// complex iterators and their value types.
    ///
    /// @param  aFirst Range begin iterator
    /// @param  aLast  Range past the end iterator
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_ValueType>
    void DoQuicksort(T_InputIterator aFirst, T_InputIterator aLast, T_ValueType);

    /*template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast,
                sort_insertionsort);*/

    template <typename T_InputIterator>
    void DoInsertionSort(T_InputIterator aFirst, T_InputIterator aLast,
                         IsRawItr);

    template <typename T_InputIterator>
    void DoInsertionSort(T_InputIterator aFirst, T_InputIterator aLast,
                         IsComplexItr);

    template <typename T_InputIterator, typename T_ValueType>
    void DoInsertionSort(T_InputIterator aFirst, T_InputIterator aLast,
                         T_ValueType);
  }

};};

#endif
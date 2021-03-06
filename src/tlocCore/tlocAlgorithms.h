#ifndef TLOC_ALGORITHMS_H
#define TLOC_ALGORITHMS_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/tlocAssert.h>
#include <tlocCore/tlocPair.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/iterators/tlocIterator.h>
#include <tlocCore/types/tlocTypeTraits.h>

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

  ///-------------------------------------------------------------------------
  /// @brief
  /// Verifies that the range is valid.
  ///
  /// @note  Work ONLY on raw iterators, this function is compiled out
  /// when dealing with complex iterators. Since this is a special
  /// function that is only used for assertions, it is named like a macro.
  ///
  /// @param  a_begin The start of the range.
  /// @param  a_end   The end of the range.
  ///-------------------------------------------------------------------------
  template <typename T_Iterator>
  void
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(T_Iterator a_begin, T_Iterator a_end);

  template <typename T_Container, typename T_Function>
  T_Function
    for_each_all(T_Container& a_container, T_Function a_func);

  template <typename T_InputIterator, typename T_Function>
  T_Function
    for_each(T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
             T_Function aFunc);

  template <typename T_Container, typename T>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container)
    find_all(T_Container& a_container, T const & a_value);

  template <typename T_Container, typename T_Predicate>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container)
    find_if_all(T_Container& a_container, T_Predicate a_pred);

  template <typename T_Container, typename T_Predicate>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container)
    find_if_not_all(T_Container& a_container, T_Predicate a_pred);

  template <typename T_InputIterator, typename T>
  T_InputIterator
    find(T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
         T const & a_value);

  template <typename T_InputIterator, typename T_Predicate>
  T_InputIterator
    find_if(T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
            T_Predicate a_pred);

  template <typename T_InputIterator, typename T_Predicate>
  T_InputIterator
    find_if_not(T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
                T_Predicate a_pred);

  template <typename T_Container1, typename T_Container2>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1)
    find_end_all(T_Container1& a_toSearch, T_Container2& a_toFind);

  template <typename T_Container1, typename T_Container2, typename T_BinaryPred>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1)
    find_end_all(T_Container1& a_toSearch, T_Container2& a_toFind,
                 T_BinaryPred a_pred);

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1
    find_end(T_ForwardIterator1 a_rangeToSearchBegin,
             T_ForwardIterator1 a_rangeToSearchEnd,
             T_ForwardIterator2 a_rangeToFindBegin,
             T_ForwardIterator2 a_rangeToFindEnd);

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
  T_ForwardIterator1
    find_end(T_ForwardIterator1 a_rangeToSearchBegin,
             T_ForwardIterator1 a_rangeToSearchEnd,
             T_ForwardIterator2 a_rangeToFindBegin,
             T_ForwardIterator2 a_rangeToFindEnd,
             T_BinaryPredicate  a_pred);

  template <class T_ForwardIterator, class T_Value>
  T_ForwardIterator
    find_end(T_ForwardIterator a_begin, T_ForwardIterator a_end,
             const T_Value& a_value);

  template <typename T_Container, class T_Value>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container)
    find_end_all(T_Container& a_toSearch, const T_Value& a_value);

  template <class T_ForwardIterator, class T_Predicate>
  T_ForwardIterator
    find_if_end(T_ForwardIterator a_begin, T_ForwardIterator a_end,
                T_Predicate a_pred);

  template <class T_Container, class T_Predicate>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container)
    find_if_end_all(T_Container& a_container, T_Predicate a_pred);

  template <typename T_Container1, typename T_Container2>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1)
    find_first_of_all(T_Container1& a_toSearch,
                      T_Container2& a_toFind);

 template <typename T_Container1, typename T_Container2,
           typename T_BinaryPredicate>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1)
    find_first_of_all(T_Container1& a_toSearch,
                      T_Container2& a_toFind,
                      T_BinaryPredicate   a_pred);

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1
    find_first_of(T_ForwardIterator1 a_rangeToSearchBegin,
                  T_ForwardIterator1 a_rangeToSearchEnd,
                  T_ForwardIterator2 a_rangeToFindBegin,
                  T_ForwardIterator2 a_rangeToFindEnd);

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
  T_ForwardIterator1
    find_first_of(T_ForwardIterator1 a_rangeToSearchBegin,
                  T_ForwardIterator1 a_rangeToSearchEnd,
                  T_ForwardIterator2 a_rangeToFindBegin,
                  T_ForwardIterator2 a_rangeToFindEnd,
                  T_BinaryPredicate  a_pred);

  template <typename T_Container1, typename T_Container2>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1)
    find_first_not_of_all(T_Container1& a_toSearch,
                          T_Container2& a_toFind);

 template <typename T_Container1, typename T_Container2,
           typename T_BinaryPredicate>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1)
    find_first_not_of_all(T_Container1& a_toSearch,
                          T_Container2& a_toFind,
                          T_BinaryPredicate   a_pred);

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1
    find_first_not_of(T_ForwardIterator1 a_rangeToSearchBegin,
                      T_ForwardIterator1 a_rangeToSearchEnd,
                      T_ForwardIterator2 a_rangeToFindBegin,
                      T_ForwardIterator2 a_rangeToFindEnd);

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
  T_ForwardIterator1
    find_first_not_of(T_ForwardIterator1 a_rangeToSearchBegin,
                      T_ForwardIterator1 a_rangeToSearchEnd,
                      T_ForwardIterator2 a_rangeToFindBegin,
                      T_ForwardIterator2 a_rangeToFindEnd,
                      T_BinaryPredicate  a_pred);

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1
    find_last_not_of(T_ForwardIterator1 a_rangeToSearchBegin,
                     T_ForwardIterator1 a_rangeToSearchEnd,
                     T_ForwardIterator2 a_rangeToFindBegin,
                     T_ForwardIterator2 a_rangeToFindEnd);

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
  T_ForwardIterator1
    find_last_not_of(T_ForwardIterator1 a_rangeToSearchBegin,
                     T_ForwardIterator1 a_rangeToSearchEnd,
                     T_ForwardIterator2 a_rangeToFindBegin,
                     T_ForwardIterator2 a_rangeToFindEnd,
                     T_BinaryPredicate  a_pred);

  template <typename T_Container, typename T>
  tl_size
    count_all(T_Container a_container, T const & a_value);

  template <typename T_InputIterator, typename T>
  tl_size
    count(T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
          T const & a_value);

  template <typename T_Container, typename T_Predicate>
  tl_size
    count_if_all(T_Container a_container, T_Predicate a_pred);

  template <typename T_InputIterator, typename T_Predicate>
  tl_size
    count_if(T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
                   T_Predicate a_pred);

  template <typename T_Container1, typename T_InputItr>
  Pair<TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1), T_InputItr>
    mismatch_all(T_Container1& a_toSearch, T_InputItr a_toCompare);

  template <typename T_Container1, typename T_InputItr, typename T_BinaryPred>
  Pair<TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1),  T_InputItr>
    mismatch_all(T_Container1& a_toSearch, T_InputItr a_toCompare,
                 T_BinaryPred a_pred);

  template <typename T_InputIterator1, typename T_InputIterator2>
  Pair<T_InputIterator1, T_InputIterator2>
    mismatch(T_InputIterator1 a_rangeBegin, T_InputIterator1 a_rangeEnd,
             T_InputIterator2 aRangeToCompare);

  template <typename T_InputIterator1, typename T_InputIterator2,
            typename T_BinaryPred>
  Pair<T_InputIterator1, T_InputIterator2>
    mismatch(T_InputIterator1 a_rangeBegin, T_InputIterator1 a_rangeEnd,
             T_InputIterator2 aRangeToCompare, T_BinaryPred a_pred);

  template <typename T_Container1, typename T_InputItr>
  bool
    equal_all(T_Container1& a_toSearch, T_InputItr a_toCompare);

  template <typename T_Container1, typename T_InputItr, typename T_BinaryPred>
  bool
    equal_all(T_Container1& a_toSearch, T_InputItr a_toCompare,
              T_BinaryPred a_pred);

  template <typename T_InputIterator1, typename T_InputIterator2>
  bool
    equal(T_InputIterator1 a_rangeBegin, T_InputIterator1 a_rangeEnd,
          T_InputIterator2 aRangeToCompare);

  template <typename T_InputIterator1, typename T_InputIterator2,
            typename T_BinaryPred>
  bool
    equal(T_InputIterator1 a_rangeBegin, T_InputIterator1 a_rangeEnd,
          T_InputIterator2 aRangeToCompare, T_BinaryPred a_pred);

  template <typename T_ForwardIterator, typename T>
  Pair<T_ForwardIterator, T_ForwardIterator>
    equal_range(T_ForwardIterator a_first, T_ForwardIterator a_last,
                const T& a_value);

  template <typename T_ForwardIterator, typename T, typename T_Compare>
  Pair<T_ForwardIterator, T_ForwardIterator>
    equal_range(T_ForwardIterator a_first, T_ForwardIterator a_last,
                const T& a_value, T_Compare a_comp);

  template <typename T_Container, typename T>
  Pair<TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container), 
       TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container)>
    equal_range_all(T_Container& a_cont, const T& a_value);

  template <typename T_Container, typename T, typename T_Compare>
  Pair<TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container), 
       TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container)>
    equal_range_all(T_Container& a_cont, const T& a_value, T_Compare a_comp);

  template <typename T_RandomAccessContainer>
  void
    random_shuffle_all(T_RandomAccessContainer& a_toShuffle);

  template <typename T_RandomAccessContainer, typename T_RandomNumberGenerator>
  void
    random_shuffle_all(T_RandomAccessContainer& a_toShuffle,
                       T_RandomNumberGenerator a_rnd);

  template <typename T_RandomAccessIterator>
  void
    random_shuffle(T_RandomAccessIterator a_first,
                   T_RandomAccessIterator a_last);

  // T_RandomNumberGenerator takes in a number n (of type tl_size) and and
  // generates a random number between 0...n.
  template <typename T_RandomAccessIterator, class T_RandomNumberGenerator>
  void
    random_shuffle(T_RandomAccessIterator a_first,
                   T_RandomAccessIterator a_last,
                   T_RandomNumberGenerator a_rng);

  template <typename T_ForwardIterator, typename T>
  bool 
    binary_search(T_ForwardIterator a_first, T_ForwardIterator a_last,
                  const T& a_value);

  template <typename T_ForwardIterator, typename T, typename T_Compare>
  bool 
    binary_search(T_ForwardIterator a_first, T_ForwardIterator a_last,
                  const T& a_value, T_Compare a_compare);

  template <typename T_Container, typename T>
  bool 
    binary_search_all(T_Container& a_toSearch,
                      const T& a_value);

  template <typename T_Container, typename T, typename T_Compare>
  bool 
    binary_search_all(T_Container& a_toSearch,
                      const T& a_value, T_Compare a_compare);

  template <typename T_ForwardIterator>
  T_ForwardIterator
    min_element(T_ForwardIterator a_first, T_ForwardIterator a_last);

  template <typename T_ForwardIterator, typename T_Compare>
  T_ForwardIterator
    min_element(T_ForwardIterator a_first, T_ForwardIterator a_last, 
                T_Compare a_comp);

  template <typename T_Container>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container)
    min_element_all(T_Container& a_cont);

  template <typename T_Container, typename T_Compare>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container)
    min_element_all(T_Container& a_cont, T_Compare a_comp);

  template <typename T_ForwardIterator>
  T_ForwardIterator
    max_element(T_ForwardIterator a_first, T_ForwardIterator a_last);

  template <typename T_ForwardIterator, typename T_Compare>
  T_ForwardIterator
    max_element(T_ForwardIterator a_first, T_ForwardIterator a_last, 
                T_Compare a_comp);

  template <typename T_Container>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container)
    max_element_all(T_Container& a_cont);

  template <typename T_Container, typename T_Compare>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container)
    max_element_all(T_Container& a_cont, T_Compare a_comp);

  template <typename T_Container1, typename T_Container2>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1)
    search_all(T_Container1& a_toSearch, T_Container2& a_toFind);

  template <typename T_Container1, typename T_Container2,
            typename T_BinaryPredicate>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1)
    search_all(T_Container1& a_toSearch, T_Container2& a_toFind,
               T_BinaryPredicate a_pred);

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1
    search(T_ForwardIterator1 a_rangeToSearchBegin,
           T_ForwardIterator1 a_rangeToSearchEnd,
           T_ForwardIterator2 a_rangeToFindBegin,
           T_ForwardIterator2 a_rangeToFindEnd);

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
  T_ForwardIterator1
    search(T_ForwardIterator1 a_rangeToSearchBegin,
           T_ForwardIterator1 a_rangeToSearchEnd,
           T_ForwardIterator2 a_rangeToFindBegin,
           T_ForwardIterator2 a_rangeToFindEnd,
           T_BinaryPredicate  a_pred);

  template <typename T_Container, typename T_Size, typename T>
  typename T_Container::iterator
    search_n_all(T_Container& a_toSearch, T_Size a_count, T const & a_value);

  template <typename T_Container, typename T_Size, typename T,
            typename T_BinaryPred>
  typename T_Container::iterator
    search_n_all(T_Container& a_toSearch, T_Size a_count, T const & a_value,
                 T_BinaryPred a_pred);

  template <typename T_ForwardIterator, typename T_Size, typename T>
  T_ForwardIterator
    search_n(T_ForwardIterator a_rangeToSearchBegin,
             T_ForwardIterator a_rangeToSearchEnd,
             T_Size a_count, T const & a_value);

  template <typename T_ForwardIterator, typename T_Size, typename T,
            typename T_BinaryPred>
  T_ForwardIterator
    search_n(T_ForwardIterator a_rangeToSearchBegin,
             T_ForwardIterator a_rangeToSearchEnd,
             T_Size a_count, T const & a_value,
             T_BinaryPred a_pred);

  //------------------------------------------------------------------------
  // Modifiers (some are non-standard)

  template <typename T_Container, typename T>
  typename T_Container::iterator
    remove_all(T_Container& a_in, T const & a_value);

  template <typename T_Container, typename T_UnaryPred>
  typename T_Container::iterator
    remove_if_all(T_Container& a_in, T_UnaryPred a_pred);

  template <typename T_ForwardItr, typename T>
  T_ForwardItr
    remove(T_ForwardItr a_begin, T_ForwardItr a_end, T const & a_value);

  template <typename T_ForwardItr, typename T_UnaryPred>
  T_ForwardItr
    remove_if(T_ForwardItr a_begin, T_ForwardItr a_end,
              T_UnaryPred a_pred);

  template <typename T_Container1, typename T_OutputItr, typename T>
  T_OutputItr
    remove_copy_all(T_Container1& a_in, T_OutputItr a_out,
                    T const & a_value);

  template <typename T_Container1, typename T_OutputItr, typename T_UnaryPred>
  T_OutputItr
    remove_copy_if_all(T_Container1& a_in, T_OutputItr a_out,
                       T_UnaryPred a_pred);

  template <typename T_InputItr, typename T_OutputItr, typename T>
  T_OutputItr
    remove_copy(T_InputItr a_begin, T_InputItr a_end,
                T_OutputItr a_output, T const & a_value);

  template <typename T_InputItr, typename T_OutputItr, typename T_UnaryPred>
  T_OutputItr
    remove_copy_if(T_InputItr a_begin, T_InputItr a_end,
                   T_OutputItr a_output, T_UnaryPred a_pred);

  template <typename T_Container, typename T>
  void
    replace_all(T_Container& a_in, T const & a_oldValue, T const & a_newValue);

  template <typename T_Container, typename T_UnaryPred, typename T>
  void
    replace_if_all(T_Container& a_in, T_UnaryPred a_pred, T const & a_newValue);

  template <typename T_ForwardItr, typename T>
  void
    replace(T_ForwardItr a_begin, T_ForwardItr a_end,
            T const & a_oldValue, T const & a_newValue);

  template <typename T_ForwardItr, typename T_UnaryPred, typename T>
  void
    replace_if(T_ForwardItr a_begin, T_ForwardItr a_end,
               T_UnaryPred a_pred, T const & a_newValue);

  template <typename T_Container1, typename T_OutputItr, typename T>
  T_OutputItr
    replace_copy_all(T_Container1& a_in, T_OutputItr a_out,
                     T const & a_oldValue, T const & a_newValue);

  template <typename T_Container1, typename T_OutputItr, typename T_UnaryPred,
            typename T>
  T_OutputItr
    replace_copy_if_all(T_Container1& a_in, T_OutputItr a_out,
                        T_UnaryPred a_pred, T const & a_newValue);

  template <typename T_InputItr, typename T_OutputItr, typename T>
  T_OutputItr
    replace_copy(T_InputItr a_begin, T_InputItr a_end,
                 T_OutputItr a_output, T const & a_oldValue,
                 T const & a_newValue);

  template <typename T_InputItr, typename T_OutputItr, typename T_UnaryPred,
            typename T>
  T_OutputItr
    replace_copy_if(T_InputItr a_begin, T_InputItr a_end,
                    T_OutputItr a_output, T_UnaryPred a_pred,
                    T const & a_newValue);

  template <typename T_ForwardItr>
  T_ForwardItr
    unique(T_ForwardItr a_begin, T_ForwardItr a_end);

  template <typename T_ForwardItr, typename T_BinaryPred>
  T_ForwardItr
    unique(T_ForwardItr a_begin, T_ForwardItr a_end, T_BinaryPred);

  template <typename T_Container>
  typename T_Container::iterator
    unique_all(T_Container& a_inOut);

  template <typename T_Container1, typename T_Container2>
  void
    unique_copy_all(T_Container1& a_in, T_Container2& a_out);

  ///-------------------------------------------------------------------------
  /// @brief Removes duplicate elements.
  ///
  /// @param  a_pred        Binary predicate that returns true if values are
  ///                       same.
  ///-------------------------------------------------------------------------
  template <typename T_Container1, typename T_Container2, typename T_BinaryPred>
  void
    unique_copy_all(T_Container1& a_in, T_Container2& a_out,
                    T_BinaryPred);

  ///-------------------------------------------------------------------------
  /// @brief Removes duplicate elements only if they are found in a_matchList
  ///-------------------------------------------------------------------------
  template <typename T_Container1, typename T_Container2, typename T_Container3>
  void
    unique_copy_only_all (T_Container1& a_in, T_Container2& a_out,
                          T_Container3& a_matchList);

  ///-------------------------------------------------------------------------
  /// @brief Removes duplicate elements only if they are found in a_matchList
  ///
  /// @param  a_pred        Binary predicate that returns true if values are
  ///                       same.
  ///-------------------------------------------------------------------------
  template <typename T_Container1, typename T_Container2, typename T_Container3,
            typename T_BinaryPred>
  void
    unique_copy_only_all (T_Container1& a_in, T_Container2& a_out,
                          T_Container3& a_matchList, T_BinaryPred);

  //------------------------------------------------------------------------
  // Sorting

  // The base is needed to distinguish sorting algorithsm from T_Compare
  // function object (needed because otherwise the functions have the same
  // signature)
  struct sort_base{};

  ///-------------------------------------------------------------------------
  /// @brief
  /// Quicksort where the left most element is selected as the pivot. On
  /// a large linked list, this may be a better choice than a random
  /// selection. This is also the default technique used for non random
  /// access containers.
  ///-------------------------------------------------------------------------
  struct sort_quicksort_leftpivot : public sort_base {};

  ///-------------------------------------------------------------------------
  /// @brief
  /// Quicksort where the left most element is selected as the pivot. On
  /// a large linked list, this may be a better choice than a random
  /// selection.
  ///-------------------------------------------------------------------------
  struct sort_quicksort_rightpivot : public sort_base {};

  ///-------------------------------------------------------------------------
  /// @brief
  /// Quicksort where the middle element is selected as the pivot. This
  /// is not the best choice for a linked list.
  ///-------------------------------------------------------------------------
  struct sort_quicksort_middlepivot : public sort_base {};

  ///-------------------------------------------------------------------------
  /// @brief
  /// The default Quicksort variant that is used on random access
  /// containers. This may not be the best choice for linked lists.
  ///-------------------------------------------------------------------------
  struct sort_quicksort_randompivot : public sort_base {};

  ///-------------------------------------------------------------------------
  /// @brief
  /// Will select the leftpivot sort or randompivot sort depending on the
  /// type of container and its size.
  ///-------------------------------------------------------------------------
  struct sort_quicksort_autoselect : public sort_base {};

  ///-------------------------------------------------------------------------
  /// @brief Use when seek time is a bottleneck (for example disk access)
  ///-------------------------------------------------------------------------
  struct sort_mergesort : public sort_base {};

  ///-------------------------------------------------------------------------
  /// @brief Use when merge sort and low memory consumption is required.
  ///-------------------------------------------------------------------------
  struct sort_merge_insertionsort : public sort_base {};

  ///-------------------------------------------------------------------------
  /// @brief
  /// Use for small data sets and/or data sets that are nearly sorted. If
  /// autosort is used, this algorithm is selected for smaller
  /// containers. STABLE IN-PLACE ONLINE.
  ///-------------------------------------------------------------------------
  struct sort_insertionsort : public sort_base {};

  ///-------------------------------------------------------------------------
  /// @brief
  /// Use only when low memory consumption is desired and the container
  /// is nearly sorted.
  ///-------------------------------------------------------------------------
  struct sort_bubblesort : public sort_base {};

  struct sort_autoselect : public sort_base {};

  // The default sort function. It sorts using random quicksort. See overloaded
  // sort function for using a different sorting algorithm.
  template <typename T_InputIterator>
  void
    sort(T_InputIterator a_first, T_InputIterator a_last);

  template <typename T_InputIterator, typename T_Compare_or_SortAlgorithm>
  void
    sort(T_InputIterator a_first, T_InputIterator a_last,
         T_Compare_or_SortAlgorithm a_comp);

  // The sorting function can sort with multiple different techniques. Use
  // sort_autoselect to automatically select the best sorting algorithm for
  // the given container. Some techniques may not be compatible with the given
  // container

  // Commented because of the above function (same signature) - left here just
  // to make it clear that this is what it is 'supposed' to be like

  //template <typename T_InputIterator, typename T_SortAlgorithm>
  //void
  //  sort(T_InputIterator a_first, T_InputIterator a_last,
  //       T_SortAlgorithm);

  template <typename T_InputIterator, typename T_SortAlgorithm,
            typename T_Compare>
  void
    sort(T_InputIterator a_first, T_InputIterator a_last, T_Compare a_comp,
         T_SortAlgorithm);

  template <typename T_Container>
  void
    sort_all(T_Container& a_toSort);

  template <typename T_Container, typename T_Compare_or_SortAlgorithm>
  void
    sort_all(T_Container& a_toSort,
         T_Compare_or_SortAlgorithm a_comp);

  template <typename T_Container, typename T_SortAlgorithm,
            typename T_Compare>
  void
    sort_all(T_Container a_toSort, T_Compare a_comp, T_SortAlgorithm);

  //------------------------------------------------------------------------
  // Min / Max

  template <typename T_Value>
  const T_Value&
    tlMin(const T_Value& a, const T_Value& b);

  template <typename T>
  T const &
    tlMax(T const & a, T const & b);

  template <typename T, typename T2>
  T
    Clamp(T a_value, T2 a_low, T2 a_high);

  template <typename T, typename T2, typename T_BinaryPred>
  T
    Clamp(T a_value, T2 a_low, T2 a_high, T_BinaryPred a_pred);

  //------------------------------------------------------------------------
  // Modifying sequence operations

  // Copies the range of elements [a_rangeBegin, a_rangeEnd) to aCopyTo and returns
  // an iterator to the end of the destination range
  // 5 4 6 7 2 3 8 4 5 6 7
  // ^                     ^
  // a_rangeBegin           a_rangeEnd (copy 5,4,6,7,2,3,8,4,5,6,7 inclusive)
  template <typename T_InputIterator, typename T_OutputIterator>
  T_OutputIterator
    copy(T_InputIterator a_rangeBegin,
         T_InputIterator a_rangeEnd,
         T_OutputIterator a_destRangeBegin);

  template <typename T_Container, typename T_OutputIterator>
  T_OutputIterator
    copy_all(T_Container& a_toCopy, T_OutputIterator a_destRangeBegin);

  // Copies the range of elements [a_rangeBegin, a_rangeEnd) to aCopyTo and returns
  // an iterator to the first element in the destination range.
  // aDestRangeEnd must be past-the-end element of the destination range.
  // 5 4 6 7 2 3 8 4 5 6 7
  // ^                     ^
  // a_rangeBegin           a_rangeEnd (copy 5,4,6,7,2,3,8,4,5,6,7 inclusive)
  //
  // 1 2 3 4 5 6 7 8
  //                 ^
  //                 aDestRangeEnd (past-the-end, which is 8)
  template <typename T_InputIterator, typename T_OutputIterator>
  T_OutputIterator
    copy_backward(T_InputIterator a_rangeBegin,
                  T_InputIterator a_rangeEnd,
                  T_OutputIterator aDestRangeEnd);

  template <typename T_Container, typename T_OutputIterator>
  T_OutputIterator
    copy_backward_all(T_Container& a_toCopy,
                      T_OutputIterator a_destRangeBegin);

  template <typename T_Container, typename T>
  void
    fill_all(T_Container& a_toFill, T const & a_value);

  template <typename T_InputIterator, typename T>
  void
    fill(T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
         T const & a_value);

  template <typename T_Container, typename T_Count, typename T>
  void
    fill_n_all(T_Container& a_toFill, T_Count a_count, T const & a_value);

  template <typename T_OutputIterator, typename T_Count, typename T_ValueType>
  void
    fill_n(T_OutputIterator a_first, T_Count a_count,
           const T_ValueType& a_value);

  template <typename T>
  void
    swap(T& a, T& b);

  template <typename T_Container, typename T>
  typename T_Container::iterator
    lower_bound_all(T_Container& a_toSearch, T const & a_value);

  template <typename T_Container, typename T, typename T_BinaryPred>
  typename T_Container::iterator
    lower_bound_all(T_Container& a_toSearch, T const & a_value,
                    T_BinaryPred a_pred);

  template <typename T_ForwardIterator, typename T>
  T_ForwardIterator
    lower_bound(T_ForwardIterator a_first,
                T_ForwardIterator a_last, T const & a_value);

  template <typename T_ForwardIterator, typename T, typename T_BinaryPred>
  T_ForwardIterator
    lower_bound(T_ForwardIterator a_first, T_ForwardIterator a_last,
                T const & a_value, T_BinaryPred a_comp);

  template <typename T_Container, typename T>
  typename T_Container::iterator
    upper_bound_all(T_Container& a_toSearch, T const & a_value);

  template <typename T_Container, typename T, typename T_BinaryPred>
  typename T_Container::iterator
    upper_bound_all(T_Container& a_toSearch, T const & a_value,
                    T_BinaryPred a_pred);

  template <typename T_ForwardIterator, typename T>
  T_ForwardIterator
    upper_bound(T_ForwardIterator a_first,
                T_ForwardIterator a_last, T const & a_value);

  template <typename T_ForwardIterator, typename T, typename T_BinaryPred>
  T_ForwardIterator
    upper_bound(T_ForwardIterator a_first, T_ForwardIterator a_last,
                T const & a_value, T_BinaryPred a_comp);

  // Does not work on associative containers
  template <typename T_ForwardItr>
  void
    delete_ptrs(T_ForwardItr a_first, T_ForwardItr a_last);

  template <class T_InputIterator, class T_OutputIterator, class T_UnaryPred>
  T_OutputIterator
    transform (T_InputIterator a_first, T_InputIterator a_last,
               T_OutputIterator a_result, T_UnaryPred a_op);

  template <class T_InputIterator1, class T_InputIterator2,
            class T_OutputIterator, class T_BinaryPred>
  T_OutputIterator
    transform (T_InputIterator1 a_first1, T_InputIterator1 a_last,
               T_InputIterator2 a_first2, T_OutputIterator a_result,
               T_BinaryPred a_binary_op);

  template <class T_Container1, class T_Container2, class T_UnaryPred>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container2)
    transform_all(T_Container1& a_toTransform,
                  T_Container2& a_result, T_UnaryPred a_op);

  template <class T_Container1, class T_Container2, class T_Container3,
            class T_BinaryPred>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container3)
    transform_all(T_Container1& a_toTransform, T_Container2& a_toTransformWith,
                  T_Container3& a_result,
                  T_BinaryPred a_binary_op);

  namespace detail
  {
    typedef	type_false IsComplexItr;
    typedef	type_true	 IsRawItr;

    typedef	type_false IsNotArith;
    typedef	type_true	 IsArith;

    typedef	type_false IsNotChar;
    typedef	type_true	 IsChar;

    typedef type_true  IsSortingAlgorithm;
    typedef type_false IsCompareFunctionObject;

    // ------------------------------------------------------------------------
    //  Range verification helpers: for raw iterators we check the range, for
    //  complex iterators, we ignore the call.

    template <typename T_Iterator>
    void
      DoVerifyRange(T_Iterator a_begin, T_Iterator a_end, IsRawItr);

    template <typename T_Iterator>
    void
      DoVerifyRange(T_Iterator a_begin, T_Iterator a_end, IsComplexItr);

    //------------------------------------------------------------------------
    // Copy() helpers

    template <typename T_InputIterator, typename T_OutputIterator>
    T_OutputIterator
      DoCopy(T_InputIterator  a_rangeBegin, T_InputIterator  a_rangeEnd,
             T_OutputIterator a_destRangeBegin, IsNotArith);

    template <typename T_InputIterator, typename T_OutputIterator>
    T_OutputIterator
      DoCopy(T_InputIterator	a_rangeBegin, T_InputIterator  a_rangeEnd,
             T_OutputIterator a_destRangeBegin, IsArith);

    template <typename T_InputIterator, typename T_OutputIterator>
    void
      DoCopyBackwardChecks(T_InputIterator a_rangeBegin,
                           T_InputIterator a_rangeEnd,
                           T_OutputIterator a_destRangeEnd, IsRawItr);

    template <typename T_InputIterator, typename T_OutputIterator>
    void
      DoCopyBackwardChecks(T_InputIterator a_rangeBegin,
                           T_InputIterator a_rangeEnd,
                           T_OutputIterator a_destRangeEnd, IsComplexItr);

    //------------------------------------------------------------------------
    // Fill helpers

    template <typename T_InputIterator, typename T>
    void
      DoFill( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
              T const & a_value, IsNotChar );

    template <typename T_InputIterator, typename T>
    void
      DoFill( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
              T const & a_value, IsChar );

    //------------------------------------------------------------------------
    // fill_n helpers

    template <typename T_OutputIterator, typename T_Count, typename T_ValueType>
    void
      DoFill_n(T_OutputIterator a_first, T_Count a_count,
               const T_ValueType& a_value, IsNotChar);

    template <typename T_OutputIterator, typename T_Count, typename T_ValueType>
    void
      DoFill_n(T_OutputIterator a_first, T_Count a_count,
               const T_ValueType& a_value, IsChar);

    template <typename T_OutputIterator, typename T_Count, typename T_ValueType>
    void
      DoFill_n(T_OutputIterator a_first, T_Count a_count,
               const T_ValueType& a_value, random_access_iterator_tag);

    template <typename T_OutputIterator, typename T_Count, typename T_ValueType>
    void
      DoFill_n(T_OutputIterator a_first, T_Count a_count,
               const T_ValueType& a_value, input_iterator_tag);

    //------------------------------------------------------------------------
    // find helpers

    template <typename T_InputIterator, typename T>
    T_InputIterator
      DoFind(T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
             T const & a_value, IsNotChar);

    template <typename T_InputIterator, typename T>
    T_InputIterator
      DoFind(T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
             T const & a_value, IsChar);

    //------------------------------------------------------------------------
    // Sort helpers

    // -----------------------------------------------------------------------
    // Helper for one of the sort functions which must select between a sort
    // algorithm and a comparison function object

    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortWithAlgorithmOrCompareFunc(T_InputIterator a_first,
                                       T_InputIterator a_last,
                                       T_Compare a_comp,
                                       IsCompareFunctionObject);

    template <typename T_InputIterator, typename T_SortAlgorithm>
    void
      DoSortWithAlgorithmOrCompareFunc(T_InputIterator a_first,
                                       T_InputIterator a_last,
                                       T_SortAlgorithm a_comp,
                                       IsSortingAlgorithm);

    ///-------------------------------------------------------------------------
    /// @brief
    /// Auto select the best quicksort for the given container type. Note
    /// that if you know the container size is small, random quicksort
    /// will provide the best results.
    ///
    /// @param  a_first Range begin iterator.
    /// @param  a_last  Range past the end iterator.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortWithAlgorithm(T_InputIterator a_first, T_InputIterator a_last,
                          sort_quicksort_autoselect, T_Compare);

    // This quicksort helper will select a random pivot. It is considered one
    // of the most efficient sorting methods

    ///-------------------------------------------------------------------------
    /// @brief
    /// This quicksort helper will select a random pivot. It is
    /// considered one of the most efficient sorting methods.
    ///
    /// @param  a_first Range begin iterator.
    /// @param  a_last  Range past the end iterator.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortWithAlgorithm(T_InputIterator a_first, T_InputIterator a_last,
                          sort_quicksort_randompivot, T_Compare);

    // This quicksort helper will select the pivot somewhere in the middle of the
    // container. This is not an efficient method for a random List<>

    ///-------------------------------------------------------------------------
    /// @brief
    /// This quicksort helper will select the pivot somewhere in the
    /// middle of the. container. This is not an efficient method for a
    /// random List&lt;&gt;
    ///
    /// @param  a_first Range begin iterator.
    /// @param  a_last  Range past the end iterator.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortWithAlgorithm(T_InputIterator a_first, T_InputIterator a_last,
                          sort_quicksort_middlepivot, T_Compare);

    // This quicksort helper will select the right most element (or a_last - 1)
    // as the pivot. This is not an efficient method for a not-so-random container
    // (user other pivot methods)

    ///-------------------------------------------------------------------------
    /// @brief
    /// This quicksort helper will select the right most element (or
    /// a_last - 1) as the pivot. This is not an efficient method for a
    /// not-so-random container (user other pivot methods)
    ///
    /// @param  a_first Range begin iterator.
    /// @param  a_last  Range past the end iterator.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortWithAlgorithm(T_InputIterator a_first, T_InputIterator a_last,
                          sort_quicksort_rightpivot, T_Compare);

    ///-------------------------------------------------------------------------
    /// @brief
    /// This quicksort helper assumes that the pivot is the first
    /// iterator and a_last is the past-the-end iterator. This is not an
    /// efficient method for a not-so-random container (use other pivot
    /// methods)
    ///
    /// @param  a_first Range begin iterator.
    /// @param  a_last  Range past the end iterator.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortWithAlgorithm(T_InputIterator a_first, T_InputIterator a_last,
                          sort_quicksort_leftpivot, T_Compare);

    template <typename T_InputIterator, typename T_Compare>
    void
      DoQuicksortLeftPivot(T_InputIterator a_first, T_InputIterator a_last,
                           IsRawItr, T_Compare);

    template <typename T_InputIterator, typename T_Compare>
    void
      DoQuicksortLeftPivot(T_InputIterator a_first, T_InputIterator a_last,
                           IsComplexItr, T_Compare);

    ///-------------------------------------------------------------------------
    /// Quicksort helper. This will perform the leftpivot quicksort on the
    /// given type. We need the quicksort helper because of raw and complex
    /// iterators and their value types.
    ///
    /// @param  a_first      Range begin iterator.
    /// @param  a_last       Range past the end iterator.
    /// @param  parameter3  The value type.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_ValueType, typename T_Compare>
    void
      DoQuicksort(T_InputIterator a_first, T_InputIterator a_last,
                  T_ValueType, T_Compare);

    ///-------------------------------------------------------------------------
    /// Insertionsort Helper. This function will do insertion sort with a set
    /// of iterators.
    ///
    /// @param  a_first      Range begin iterator.
    /// @param  a_last       Range past the end iterator.
    /// @param  parameter3  Insertionsort identifier.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortWithAlgorithm(T_InputIterator a_first, T_InputIterator a_last,
                          sort_insertionsort, T_Compare);

    ///-------------------------------------------------------------------------
    /// Insertionsort helper. This function will do insertion sort with a set
    /// of iterators, provided the iterator type is known as raw.
    ///
    /// @param  a_first      Range begin iterator.
    /// @param  a_last       Range past the end iterator.
    /// @param  parameter3  Raw iterator identifier.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_Compare>
    void
      DoInsertionsortWithItrType(T_InputIterator a_first,
                                 T_InputIterator a_last, IsRawItr, T_Compare);

    ///-------------------------------------------------------------------------
    /// Insertionsort helper. This function will do insertion sort with a set
    /// of iterators, provided the iterator type is known as raw.
    ///
    /// @param  a_first      Range begin iterator.
    /// @param  a_last       Range past the end iterator.
    /// @param  parameter3  Complex iterator identifier.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_Compare>
    void
      DoInsertionsortWithItrType(T_InputIterator a_first,
                                 T_InputIterator a_last,
                                 IsComplexItr, T_Compare);

    ///-------------------------------------------------------------------------
    /// Insertionsort helper. This function performs the actual insertion
    /// sort with the provided range of iterators and the value type.
    ///
    /// @param  a_first      Range begin iterator.
    /// @param  a_last       Range past the end iterator.
    /// @param  parameter3  The value type.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_ValueType, typename T_Compare>
    void
      DoInsertionsortWithValueType(T_InputIterator a_first,
                                   T_InputIterator a_last,
                                   T_ValueType, T_Compare);

    ///-------------------------------------------------------------------------
    /// Preforms mergesort on a set of iterators.
    ///
    /// @param  a_first      Range begin iterator.
    /// @param  a_last       Range past the end iterator.
    /// @param  parameter3  Mergesort identifier.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortWithAlgorithm(T_InputIterator a_first, T_InputIterator a_last,
                          sort_mergesort, T_Compare);

    ///-------------------------------------------------------------------------
    /// Performs mergesort provided that the iterators are complex.
    ///
    /// @param  a_first      Range begin iterator.
    /// @param  a_last       Range past the end iterator.
    /// @param  parameter3  Complex iterator identifier.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_Compare>
    void
      DoMergesortWithItrType(T_InputIterator a_first, T_InputIterator a_last,
                             IsComplexItr, T_Compare);

    ///-------------------------------------------------------------------------
    /// Performs mergesort provided that the iterators are raw.
    ///
    /// @param  a_first      Range begin iterator.
    /// @param  a_last       Range past the end iterator.
    /// @param  parameter3  Raw iterator identifier.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_Compare>
    void
      DoMergesortWithItrType(T_InputIterator a_first, T_InputIterator a_last,
                             IsRawItr, T_Compare);

    ///-------------------------------------------------------------------------
    /// performs mergesort if the value type of the iterator is known.
    ///
    /// @param  a_first      Range begin iterator.
    /// @param  a_last       Range past the end iterator.
    /// @param  parameter3  The Value Type.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_ValueType, typename T_Compare>
    void
      DoMergesortWithValueType(T_InputIterator a_first, T_InputIterator a_last,
                               T_ValueType, T_Compare);

    ///-------------------------------------------------------------------------
    /// Performs mergesort on a container. Note: This function will not work
    /// if the container is empty.
    ///
    /// @param  a_unsorted and unsorted container.
    ///
    /// @return Returns a copy of the sorted container.
    ///-------------------------------------------------------------------------
    template <typename T_Container, typename T_Compare>
    T_Container
      DoMergesort(T_Container& a_unsorted, T_Compare);

    ///-------------------------------------------------------------------------
    /// Merges two sorted containers into a container and returns it.
    ///
    /// @param  a_left   The left container.
    /// @param  a_right  The right container.
    ///
    /// @return Merged container.
    ///-------------------------------------------------------------------------
    template <typename T_Container, typename T_Compare>
    T_Container
      DoMerge(T_Container& a_left, T_Container& a_right, T_Compare);

    ///-------------------------------------------------------------------------
    /// Performs "merge insertion sort" on a set of iterators.
    ///
    /// @param  a_first      Range begin iterator.
    /// @param  a_last       Range past the end iterator.
    /// @param  parameter3  MergeInsertionSort identifier.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortWithAlgorithm(T_InputIterator a_first, T_InputIterator a_last,
                          sort_merge_insertionsort, T_Compare);

    ///-------------------------------------------------------------------------
    /// Performs "Merge Insertion Sort" on a set of iterators. Note: This
    /// function will only work if the list is not empty.
    ///
    /// @param  a_first  Range begin iterator.
    /// @param  a_last   Range past the end iterator.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_Compare>
    void
      DoMergeInsertionSort(T_InputIterator a_first, T_InputIterator a_last,
                           T_Compare);

    ///-------------------------------------------------------------------------
    /// Merges two sorted neighboring containers together with only their
    /// iterators. Note: The containers must be together as part of a bigger
    /// container for this function to work.
    ///
    /// @param  a_leftFirst  Iterator that defines the beginning of the left
    ///                     list.
    /// @param  a_rightFirst Iterator that defines the beginning of the right
    ///                     list.
    /// @param  a_last       Iterator that defines the end of the right list.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_Compare>
    void
      DoMergeInsertion(T_InputIterator a_leftFirst, T_InputIterator a_rightFirst,
                       T_InputIterator a_last, T_Compare);

    ///-------------------------------------------------------------------------
    /// Takes the first element in the provided iterator range and places it
    /// in the remaining sorted container. This is provided that the iterator
    /// type is known as complex. Note: Except for the first element the
    /// container must be sorted from lowest to highest value.
    ///
    /// @param  a_first      Range begin iterator.
    /// @param  a_last       Range past the end iterator.
    /// @param  parameter3  Complex iterator identifier.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortFirstElementWithItrType(T_InputIterator a_first,
                                    T_InputIterator a_last,
                                    IsComplexItr, T_Compare);

    ///-------------------------------------------------------------------------
    /// Takes the first element in the provided iterator range and places it
    /// in the remaining sorted container. This is provided that the iterator
    /// type is known as raw. Note: Except for the first element the container
    /// must be sorted from lowest to highest value.
    ///
    /// @param  a_first      Range begin iterator.
    /// @param  a_last       Range past the end iterator.
    /// @param  parameter3  Complex iterator identifier.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortFirstElementWithItrType(T_InputIterator a_first,
                                    T_InputIterator a_last,
                                    IsRawItr, T_Compare);

    ///-------------------------------------------------------------------------
    /// Takes the first element in the provided iterator range and places it
    /// in the remaining sorted container. This is provided that the iterator
    /// value type is known. Note: Except for the first element the container
    /// must be sorted from lowest to highest value.
    ///
    /// @param  a_first      Range begin iterator.
    /// @param  a_last       Range past the end iterator.
    /// @param  parameter3  Complex iterator identifier.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_ValueType, typename T_Compare>
    void
      DoSortFirstElementWithValueType(T_InputIterator a_first,
                                      T_InputIterator a_last,
                                      T_ValueType, T_Compare);

    ///-------------------------------------------------------------------------
    /// Performs Bubblesort on a range of iterators.
    ///
    /// @param  a_first      Range begin iterator.
    /// @param  a_last       Range past the end iterator.
    /// @param  parameter3  Bubblesort identifier.
    ///-------------------------------------------------------------------------
    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortWithAlgorithm(T_InputIterator a_first, T_InputIterator a_last,
                          sort_bubblesort, T_Compare);

  }

};};

#endif
#ifndef TLOC_ALGORITHMS_INL
#define TLOC_ALGORITHMS_INL

#ifndef TLOC_ALGORITHMS_H
#error "Must include header before including the inline file"
#endif

#include <cstring>

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocPair.inl.h>
#include <tlocCore/iterators/tlocIterator.inl.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocArray.inl.h>
#include <tlocCore/rng/tlocRandom.h>
#include <tlocCore/tlocFunctional.h>

namespace tloc { namespace core {

  // TODO: Make all find functions specialized for char* and use memcmp

  //------------------------------------------------------------------------
  // Range verifier - only works on raw iterators, ignores complex iterators

  template <typename T_Iterator>
  void TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(T_Iterator a_begin, T_Iterator a_end)
  {
    typedef typename Loki::Int2Type<Loki::TypeTraits<T_Iterator>::isPointer> itr_type;
    detail::DoVerifyRange(a_begin, a_end, itr_type());
  }

  //------------------------------------------------------------------------
  // Non-modifying sequence operations

  template <typename T_Container, typename T_Function>
  T_Function
    for_each_all(T_Container& a_container, T_Function a_func)
  {
    return for_each(a_container.begin(), a_container.end(), a_func);
  }

  template <typename T_InputIterator, typename T_Function>
  T_Function
    for_each( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
                       T_Function aFunc )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

    const tl_size rangeSize = distance(a_rangeBegin, a_rangeEnd);

    for (u32 i = 0; i < rangeSize; ++i)
    {
      aFunc(*a_rangeBegin);
      ++a_rangeBegin;
    }

    return aFunc;
  }

  template <typename T_Container, typename T>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container)
    find_all(T_Container& a_container, T const & a_value)
  {
    return find(a_container.begin(), a_container.end(), a_value);
  }

  template <typename T_Container, typename T_Predicate>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container)
   find_if_all(T_Container& a_container, T_Predicate a_pred)
  {
    return find_if(a_container.begin(), a_container.end(), a_pred);
  }

  template <typename T_InputIterator, typename T>
  T_InputIterator
    find( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
          T const & a_value )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

    // We assume that the inputs are pointers. If they point to data that is a
    // single byte (a char) then use memset
    typedef typename Loki::TypeTraits<T_InputIterator>::PointeeType inputDeref;
    typedef typename Loki::IsSameType<inputDeref, char8> charTestResult;
    typedef typename Loki::Int2Type<charTestResult::value> IsChar8;

    return detail::DoFind(a_rangeBegin, a_rangeEnd, a_value, IsChar8());
  }

  template <typename T_Container, typename T_Predicate>
  typename T_Container::iterator
    find_if(T_Container a_container, const T_Predicate& a_pred)
  {
    return find_if(a_container.begin(), a_container.end(), a_pred);
  }

  template <typename T_InputIterator, typename T_Predicate>
  T_InputIterator
    find_if( T_InputIterator a_rangeBegin,
             T_InputIterator a_rangeEnd, T_Predicate a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

    while (a_rangeBegin != a_rangeEnd)
    {
      if (a_pred(*a_rangeBegin)) break;
      ++a_rangeBegin;
    }

    return a_rangeBegin;
  }

  template <typename T_Container1, typename T_Container2>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1)
    find_end_all_all(T_Container1& a_toSearch, T_Container2& a_toFind)
  {
    return find_end(a_toSearch.begin(), a_toSearch.end(), a_toFind.begin(),
                    a_toFind.end());
  }

  template <typename T_Container1, typename T_Container2, typename T_BinaryPred>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1)
    find_end_all_all(T_Container1& a_toSearch,
                     T_Container2& a_toFind,
                     T_BinaryPred a_pred)
  {
    return find_end(a_toSearch.begin(), a_toSearch.end(), a_toFind.begin(),
      a_toFind.end(), a_pred);
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1
    find_end( T_ForwardIterator1 a_rangeToSearchBegin,
              T_ForwardIterator1 a_rangeToSearchEnd,
              T_ForwardIterator2 a_rangeToFindBegin,
              T_ForwardIterator2 a_rangeToFindEnd )
  {
    return find_end(a_rangeToSearchBegin, a_rangeToSearchEnd, a_rangeToFindBegin,
      a_rangeToFindEnd, equal_to<typename iterator_traits<T_ForwardIterator1>::value_type>());
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
    typename T_BinaryPredicate>
  T_ForwardIterator1
    find_end( T_ForwardIterator1 a_rangeToSearchBegin,
              T_ForwardIterator1 a_rangeToSearchEnd,
              T_ForwardIterator2 a_rangeToFindBegin,
              T_ForwardIterator2 a_rangeToFindEnd,
              T_BinaryPredicate a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToSearchBegin, a_rangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToFindBegin, a_rangeToFindEnd);

    const tl_size sourceSize = distance(a_rangeToSearchBegin, a_rangeToSearchEnd);
    const tl_size compareSize = distance(a_rangeToFindBegin, a_rangeToFindEnd);

    T_ForwardIterator1 retItr = a_rangeToSearchEnd;

    if (sourceSize >= compareSize)
    {
      T_ForwardIterator1 sourceItr;
      T_ForwardIterator2 compareItr;
      T_ForwardIterator1 sourceLimit = a_rangeToSearchEnd - compareSize + 1;

      while (a_rangeToSearchBegin != sourceLimit)
      {
        sourceItr = a_rangeToSearchBegin;
        compareItr = a_rangeToFindBegin;
        while (compareItr != a_rangeToFindEnd)
        {
          if (!a_pred(*sourceItr, *compareItr)) { break; }
          ++compareItr;
          ++sourceItr;
        }

        if (compareItr == a_rangeToFindEnd)
        {
          retItr = a_rangeToSearchBegin;
        }

        ++a_rangeToSearchBegin;
      }
    }

    return retItr;
  }

  template <class T_ForwardIterator, class T_Value>
  T_ForwardIterator
    find_end(T_ForwardIterator a_begin, T_ForwardIterator a_end,
             const T_Value& a_value)
  {
    return find_if_end(a_begin, a_end, core::equal_to_stored<T_Value>(a_value));
  }

  template <typename T_Container, class T_Value>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container)
    find_end_all(T_Container& a_toSearch, const T_Value& a_value)
  {
    return find_end(a_toSearch.begin(), a_toSearch.end(), a_value);
  }

  template <class T_ForwardIterator, class T_Predicate>
  T_ForwardIterator
    find_if_end(T_ForwardIterator a_begin, T_ForwardIterator a_end,
                T_Predicate a_pred)
  {
    T_ForwardIterator itrToRet = a_end;
    while (a_begin != a_end)
    {
      if ( a_pred(*a_begin) )
      {
        itrToRet = a_begin;
      }

      ++a_begin;
    }

    return itrToRet;
  }

  template <class T_Container, class T_Predicate>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container)
    find_if_end_all(T_Container& a_container, T_Predicate a_pred)
  {
    find_if_end(a_container.begin(), a_container.end(), a_pred);
  }

  template <typename T_Container1, typename T_Container2>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1)
    find_first_of_all(T_Container1& a_toSearch,
                      T_Container2& a_toFind)
  {
    return find_first_of(a_toSearch.begin(), a_toSearch.end(), a_toFind.begin(),
                         a_toFind.end());
  }

 template <typename T_Container1, typename T_Container2,
           typename T_BinaryPredicate>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1)
    find_first_of_all(T_Container1& a_toSearch,
                      T_Container2& a_toFind,
                      T_BinaryPredicate   a_pred)
 {
   typedef typename T_Container1::value_type cont_value_type;
   return find_first_of(a_toSearch.begin(), a_toSearch.end(), a_toFind.begin(),
                        a_toFind.end(), equal_to<cont_value_type>());
 }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1
    find_first_of( T_ForwardIterator1 a_rangeToSearchBegin,
                   T_ForwardIterator1 a_rangeToSearchEnd,
                   T_ForwardIterator2 a_rangeToFindBegin,
                   T_ForwardIterator2 a_rangeToFindEnd )
  {
    return find_first_of(a_rangeToSearchBegin, a_rangeToSearchEnd,
      a_rangeToFindBegin, a_rangeToFindEnd,
      equal_to<typename iterator_traits<T_ForwardIterator1>::value_type>());
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
  T_ForwardIterator1
    find_first_of( T_ForwardIterator1 a_rangeToSearchBegin,
                   T_ForwardIterator1 a_rangeToSearchEnd,
                   T_ForwardIterator2 a_rangeToFindBegin,
                   T_ForwardIterator2 a_rangeToFindEnd,
                   T_BinaryPredicate a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToSearchBegin, a_rangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToFindBegin, a_rangeToFindEnd);

    T_ForwardIterator2 compareItr;

    while (a_rangeToSearchBegin != a_rangeToSearchEnd)
    {
      compareItr = a_rangeToFindBegin;
      while (compareItr != a_rangeToFindEnd)
      {
        if (a_pred(*a_rangeToSearchBegin, *compareItr))
        {
          return a_rangeToSearchBegin;
        }
        ++compareItr;
      }

      ++a_rangeToSearchBegin;
    }

    return a_rangeToSearchEnd;
  }

  template <typename T_Container1, typename T_Container2>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1)
    find_first_not_of_all(T_Container1& a_toSearch,
                          T_Container2& a_toFind)
  {
    return find_first_not_of(a_toSearch.begin(), a_toSearch.end(),
                             a_toFind.begin(), a_toFind.end());
  }

 template <typename T_Container1, typename T_Container2,
           typename T_BinaryPredicate>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1)
    find_first_not_of_all(T_Container1& a_toSearch,
                          T_Container2& a_toFind,
                          T_BinaryPredicate   a_pred)
 {
   typedef typename T_Container1::value_type cont_value_type;
   return find_first_not_of
     (a_toSearch.begin(), a_toSearch.end(), a_toFind.begin(),
      a_toFind.end(), equal_to<cont_value_type>());
 }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1
    find_first_not_of( T_ForwardIterator1 a_rangeToSearchBegin,
                       T_ForwardIterator1 a_rangeToSearchEnd,
                       T_ForwardIterator2 a_rangeToFindBegin,
                       T_ForwardIterator2 a_rangeToFindEnd )
  {
    return find_first_not_of(a_rangeToSearchBegin, a_rangeToSearchEnd,
      a_rangeToFindBegin, a_rangeToFindEnd,
      equal_to<typename iterator_traits<T_ForwardIterator1>::value_type>());
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
  T_ForwardIterator1
    find_first_not_of( T_ForwardIterator1 a_rangeToSearchBegin,
                       T_ForwardIterator1 a_rangeToSearchEnd,
                       T_ForwardIterator2 a_rangeToFindBegin,
                       T_ForwardIterator2 a_rangeToFindEnd,
                       T_BinaryPredicate a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToSearchBegin, a_rangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToFindBegin, a_rangeToFindEnd);

    T_ForwardIterator2 compareItr;

    while (a_rangeToSearchBegin != a_rangeToSearchEnd)
    {
      compareItr = a_rangeToFindBegin;

      while (compareItr != a_rangeToFindEnd)
      {
        if (a_pred(*compareItr, *a_rangeToSearchBegin)) { break; }

        ++compareItr;
      }

      if (compareItr == a_rangeToFindEnd)
      {
        return a_rangeToSearchBegin;
      }

      ++a_rangeToSearchBegin;
    }

    return a_rangeToSearchEnd;
  }

  template <typename T_Container1, typename T_Container2>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1)
    find_last_not_of_all(T_Container1& a_toSearch,
                         T_Container2& a_toFind)
  {
    return find_last_not_of(a_toSearch.begin(), a_toSearch.end(),
                            a_toFind.begin(), a_toFind.end());
  }

 template <typename T_Container1, typename T_Container2,
           typename T_BinaryPredicate>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1)
    find_last_not_of_all(T_Container1& a_toSearch,
                         T_Container2& a_toFind,
                         T_BinaryPredicate   a_pred)
 {
   typedef typename T_Container1::value_type cont_value_type;
   return find_last_not_of
     (a_toSearch.begin(), a_toSearch.end(), a_toFind.begin(),
      a_toFind.end(), equal_to<cont_value_type>());
 }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1
    find_last_not_of( T_ForwardIterator1 a_rangeToSearchBegin,
                      T_ForwardIterator1 a_rangeToSearchEnd,
                      T_ForwardIterator2 a_rangeToFindBegin,
                      T_ForwardIterator2 a_rangeToFindEnd )
  {
     return find_last_not_of(a_rangeToSearchBegin, a_rangeToSearchEnd,
      a_rangeToFindBegin, a_rangeToFindEnd,
      equal_to<typename iterator_traits<T_ForwardIterator1>::value_type>());
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
  T_ForwardIterator1
    find_last_not_of( T_ForwardIterator1 a_rangeToSearchBegin,
                      T_ForwardIterator1 a_rangeToSearchEnd,
                      T_ForwardIterator2 a_rangeToFindBegin,
                      T_ForwardIterator2 a_rangeToFindEnd,
                      T_BinaryPredicate a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToSearchBegin, a_rangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToFindBegin, a_rangeToFindEnd);

    const tl_size searchSize = distance(a_rangeToSearchBegin, a_rangeToSearchEnd);
    const tl_size findSize = distance(a_rangeToFindBegin, a_rangeToFindEnd);

    T_ForwardIterator1 ret = a_rangeToSearchEnd;

    if (findSize > 0)
    {
      for (u32 i = 0; i < searchSize; ++i)
      {
        u32 j = 0;
        for (; j < findSize; ++j)
        {
          if ( a_pred(*(a_rangeToSearchBegin + i), *(a_rangeToFindBegin + j)) )
          {
            break;
          }
        }

        if (j == findSize)
        {
          ret = a_rangeToSearchBegin + i;
        }
      }
    }

    return ret;
  }

  template <typename T_Container, typename T>
  tl_size
    count_all(T_Container a_container, T const & a_value)
  {
    return count(a_container.begin(), a_container.end(), a_value);
  }

  template <typename T_InputIterator, typename T>
  tl_size
    count( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
           T const & a_value )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

    const tl_size rangeSize = a_rangeEnd - a_rangeBegin;
    tl_size count = 0;

    for (u32 i = 0; i < rangeSize; ++i)
    {
      if (a_rangeBegin[i] == a_value) ++count;
    }

    return count;
  }

  template <typename T_Container, typename T_Predicate>
  tl_size
    count_if_all(T_Container a_container, T_Predicate a_pred)
  {
    return count_if(a_container.begin(), a_container.end(), a_pred);
  }

  template <typename T_InputIterator, typename T_Predicate>
  tl_size
    count_if( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
              T_Predicate a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

    const tl_size rangeSize = a_rangeEnd - a_rangeBegin;
    tl_size count = 0;

    for (u32 i = 0; i < rangeSize; ++i)
    {
      if (a_pred(a_rangeBegin[i])) ++count;
    }

    return count;
  }

  template <typename T_Container1, typename T_InputItr>
  Pair<TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1), T_InputItr>
    mismatch_all(T_Container1& a_toSearch, T_InputItr a_toCompare)
  {
    return mismatch(a_toSearch.begin(), a_toSearch.end(), a_toCompare);
  }

  template <typename T_Container, typename T_InputItr, typename T_BinaryPred>
  Pair<TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container), T_InputItr>
    mismatch_all(T_Container& a_toSearch, T_InputItr a_toCompare,
                 T_BinaryPred a_pred)
  {
    typedef typename T_Container::value_type cont_value_type;
    return mismatch(a_toSearch.begin(), a_toSearch.end(), a_toCompare,
                    equal_to<cont_value_type>() );
  }

  template <typename T_InputIterator1, typename T_InputIterator2>
  Pair<T_InputIterator1, T_InputIterator2>
    mismatch( T_InputIterator1 a_rangeBegin, T_InputIterator1 a_rangeEnd,
              T_InputIterator2 a_rangeToCompare )
  {
    typedef typename iterator_traits<T_InputIterator1>::value_type  itr_value_type;
    return mismatch(a_rangeBegin, a_rangeEnd, a_rangeToCompare,
                    equal_to<itr_value_type>());
  }

  template <typename T_InputIterator1, typename T_InputIterator2, typename T_BinaryPred>
  Pair<T_InputIterator1, T_InputIterator2>
    mismatch( T_InputIterator1 a_rangeBegin, T_InputIterator1 a_rangeEnd,
              T_InputIterator2 a_rangeToCompare, T_BinaryPred a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

    while (a_rangeBegin != a_rangeEnd)
    {
      if (!a_pred(*a_rangeBegin,*a_rangeToCompare))
        break;

      ++a_rangeBegin;
      ++a_rangeToCompare;
    }

    return MakePair(a_rangeBegin, a_rangeToCompare);
  }

  template <typename T_Container1, typename T_InputItr>
  bool
    equal_all(T_Container1& a_toSearch, T_InputItr a_toCompare)
  {
    return equal(a_toSearch.begin(), a_toSearch.end(), a_toCompare);
  }

  template <typename T_Container, typename T_InputItr, typename T_BinaryPred>
  bool
    equal_all(T_Container& a_toSearch, T_InputItr a_toCompare,
              T_BinaryPred a_pred)
  {
    typedef typename T_Container::value_type cont_value_type;
    return equal(a_toSearch.begin(), a_toSearch.end(), a_toCompare,
                  equal_to<cont_value_type>() );
  }

  template <typename T_InputIterator1, typename T_InputIterator2>
  bool
    equal( T_InputIterator1 a_rangeBegin, T_InputIterator1 a_rangeEnd,
           T_InputIterator2 a_rangeToCompare )
  {
    return equal(a_rangeBegin, a_rangeEnd, a_rangeToCompare,
      equal_to<typename iterator_traits<T_InputIterator1>::value_type>());
  }

  template <typename T_InputIterator1, typename T_InputIterator2,
            typename T_BinaryPred>
  bool
  equal( T_InputIterator1 a_rangeBegin, T_InputIterator1 a_rangeEnd,
         T_InputIterator2 a_rangeToCompare, T_BinaryPred a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

    while (a_rangeBegin != a_rangeEnd)
    {
      if (!a_pred(*a_rangeBegin,*a_rangeToCompare)) { return false; }

      ++a_rangeBegin;
      ++a_rangeToCompare;
    }

    return true;
  }

  template <typename T_RandomAccessContainer>
  void
    random_shuffle_all(T_RandomAccessContainer& a_toShuffle)
  {
    random_shuffle(a_toShuffle.begin(), a_toShuffle.end());
  }

  template <typename T_RandomAccessContainer, typename T_RandomNumberGenerator>
  void
    random_shuffle_all(T_RandomAccessContainer& a_toShuffle,
                       T_RandomNumberGenerator a_rnd)
  {
    random_shuffle(a_toShuffle.begin(), a_toShuffle.end(), a_rnd);
  }

  template <typename T_RandomAccessIterator>
  void
    random_shuffle(T_RandomAccessIterator a_first,
                   T_RandomAccessIterator a_last)
  {
    typename iterator_traits<T_RandomAccessIterator>::difference_type
      rangeSize, i;
    rangeSize = a_last - a_first;

    typedef typename rng::rng_default::int_type int_type;
    for (i = rangeSize - 1; i > 0; --i)
    {
      swap(a_first[i],
        a_first[rng::g_defaultRNG.GetRandomInteger
        (static_cast<int_type>(i) + 1)]);
    }
  }

  template <typename T_RandomAccessIterator, class T_RandomNumberGenerator>
  void
    random_shuffle(T_RandomAccessIterator a_first,
                   T_RandomAccessIterator a_last,
                   T_RandomNumberGenerator a_rng)
  {
    typename iterator_traits<T_RandomAccessIterator>::difference_type
      rangeSize, i;
    rangeSize = a_last - a_first;

    for (i = rangeSize - 1; i > 0; --i)
    {
      swap(a_first[i], a_first[a_rng(static_cast<tl_size>(i) + 1)]);
    }
  }

  template <typename T_Container1, typename T_Container2>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1)
    search_all(T_Container1& a_toSearch, T_Container2& a_toFind)
  {
    return search(a_toSearch.begin(), a_toSearch.end(), a_toFind.begin(),
                  a_toFind.end());
  }

  template <typename T_Container1, typename T_Container2,
            typename T_BinaryPredicate>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1)
    search_all(T_Container1& a_toSearch, T_Container2& a_toFind,
               T_BinaryPredicate a_pred)
  {
    return search(a_toSearch.begin(), a_toSearch.end(), a_toFind.begin(),
                  a_toFind.end(), a_pred);
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1
    search( T_ForwardIterator1 a_rangeToSearchBegin,
            T_ForwardIterator1 a_rangeToSearchEnd,
            T_ForwardIterator2 a_rangeToFindBegin,
            T_ForwardIterator2 a_rangeToFindEnd )
  {
    typedef typename
      iterator_traits<T_ForwardIterator1>::value_type itr_value_type;
    return search(a_rangeToSearchBegin, a_rangeToSearchEnd, a_rangeToFindBegin,
      a_rangeToFindEnd, equal_to<itr_value_type>());
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
  T_ForwardIterator1
    search( T_ForwardIterator1 a_rangeToSearchBegin,
    T_ForwardIterator1 a_rangeToSearchEnd,
    T_ForwardIterator2 a_rangeToFindBegin,
    T_ForwardIterator2 a_rangeToFindEnd,
    T_BinaryPredicate a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToSearchBegin, a_rangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToFindBegin, a_rangeToFindEnd);

    const tl_size sourceSize = distance(a_rangeToSearchBegin, a_rangeToSearchEnd);
    const tl_size compareSize = distance(a_rangeToFindBegin, a_rangeToFindEnd);
    T_ForwardIterator1 sourceLimit = a_rangeToSearchEnd - compareSize + 1;

    T_ForwardIterator1 sourceItr;
    T_ForwardIterator2 compareItr;

    if (sourceSize >= compareSize)
    {
      while (a_rangeToSearchBegin != sourceLimit)
      {
        sourceItr = a_rangeToSearchBegin;
        compareItr = a_rangeToFindBegin;
        while (compareItr != a_rangeToFindEnd)
        {
          if (!a_pred(*sourceItr, *compareItr)) { break; }
          ++sourceItr;
          ++compareItr;
        }

        if (compareItr == a_rangeToFindEnd)
        {
          return a_rangeToSearchBegin;
        }

        ++a_rangeToSearchBegin;
      }
    }

    return a_rangeToSearchEnd;
  }

  template <typename T_Container, typename T_Size, typename T>
  typename T_Container::iterator
    search_n_all(T_Container& a_toSearch, T_Size a_count, T const & a_value)
  {
    return search_n(a_toSearch.begin(), a_toSearch.end(), a_count, a_value);
  }

  template <typename T_Container, typename T_Size, typename T,
            typename T_BinaryPred>
  typename T_Container::iterator
    search_n_all(T_Container& a_toSearch, T_Size a_count, T const & a_value,
                 T_BinaryPred a_pred)
  {
    return search_n(a_toSearch.begin(), a_toSearch.end(), a_count, a_value,
                    a_pred);
  }

  template <typename T_ForwardIterator, typename T_Size, typename T>
  T_ForwardIterator
    search_n( T_ForwardIterator a_rangeToSearchBegin,
              T_ForwardIterator a_rangeToSearchEnd,
              T_Size a_count, T const & a_value )
  {
    typedef typename
      iterator_traits<T_ForwardIterator>::value_type itr_value_type;
    return search_n(a_rangeToSearchBegin, a_rangeToSearchEnd, a_count, a_value,
                  equal_to<itr_value_type>());
  }

  template <typename T_ForwardIterator, typename T_Size, typename T,
            typename T_BinaryPred>
  T_ForwardIterator
    search_n( T_ForwardIterator a_rangeToSearchBegin,
              T_ForwardIterator a_rangeToSearchEnd,
              T_Size a_count, T const & a_value,
              T_BinaryPred a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToSearchBegin, a_rangeToSearchEnd);

    const tl_size sourceSize = distance(a_rangeToSearchBegin, a_rangeToSearchEnd);

    if (sourceSize >= (tl_size)a_count)
    {
      T_ForwardIterator sourceLimit = a_rangeToSearchEnd - a_count + 1;

      T_ForwardIterator retItr = a_rangeToSearchEnd;
      T_ForwardIterator retItrEnd;

      while(a_rangeToSearchBegin != sourceLimit)
      {
        retItr = a_rangeToSearchBegin;
        retItrEnd = a_rangeToSearchBegin + a_count;
        while (retItr != retItrEnd)
        {
          if (!a_pred(*retItr, a_value) ) { break; }
          ++retItr;
        }

        if (retItr == retItrEnd)
        {
          return a_rangeToSearchBegin;
        }

        ++a_rangeToSearchBegin;
      }
    }

    return a_rangeToSearchEnd;
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <typename T_Container, typename T>
  typename T_Container::iterator
    remove_all(T_Container& a_in, T const & a_value)
  {
    return remove(a_in.begin(), a_in.end(), a_value);
  }

  template <typename T_Container, typename T_Pred>
  typename T_Container::iterator
    remove_if_all(T_Container& a_in, T_Pred a_pred)
  {
    return remove_if(a_in.begin(), a_in.end(), a_pred);
  }

  template <typename T_ForwardItr, typename T>
  T_ForwardItr
    remove(T_ForwardItr a_begin, T_ForwardItr a_end, T const & a_value)
  {
    // See NOTES_ITERATOR_VALUE_TYPE_TYPEDEF @ eof
    typedef typename iterator_traits<T_ForwardItr>::value_type itr_value_type;

    return remove_if(a_begin, a_end, equal_to_stored<itr_value_type>(a_value));
  }

  template <typename T_ForwardItr, typename T_Pred>
  T_ForwardItr
    remove_if(T_ForwardItr a_begin, T_ForwardItr a_end, T_Pred a_pred)
  {
    T_ForwardItr result = a_begin;
    for (; a_begin != a_end; ++a_begin)
    {
      if (a_pred(*a_begin) == false)
      {
        *result = *a_begin;
        ++result;
      }
    }
    return result;
  }


  template <typename T_Container1, typename T_OutputItr, typename T>
  T_OutputItr
    remove_copy_all(T_Container1& a_in, T_OutputItr a_out, T const & a_value)
  {
    remove_copy(a_in.begin(), a_in.end(), a_out, a_value);
  }

  template <typename T_Container1, typename T_OutputItr, typename T_UnaryPred>
  T_OutputItr
    remove_copy_if_all(T_Container1& a_in, T_OutputItr a_out, T_UnaryPred a_pred)
  {
    remove_copy_if(a_in.begin(), a_in.end(), a_out, a_pred);
  }

  template <typename T_InputItr, typename T_OutputItr, typename T>
  T_OutputItr
    remove_copy(T_InputItr a_begin, T_InputItr a_end,
                T_OutputItr a_output, T const & a_value)
  {
    // See NOTES_ITERATOR_VALUE_TYPE_TYPEDEF @ eof
    typedef typename iterator_traits<T_InputItr>::value_type itr_value_type;

    return remove_copy_if(a_begin, a_end, a_output,
                          equal_to_stored<itr_value_type>(a_value));
  }

  template <typename T_InputItr, typename T_OutputItr, typename T_Pred>
  T_OutputItr
    remove_copy_if(T_InputItr a_begin, T_InputItr a_end,
                   T_OutputItr a_output, T_Pred a_pred)
  {
    for (; a_begin != a_end; ++a_begin)
    {
      if (a_pred(*a_begin) == false)
      {
        *a_output = *a_begin;
        ++a_output;
      }
    }

    return a_output;
  }

  template <typename T_Container, typename T>
  void
    replace_all(T_Container& a_in, T const & a_oldValue, T const & a_newValue)
  {
    replace(a_in.begin(), a_in.end(), a_oldValue, a_newValue);
  }

  template <typename T_Container, typename T_Pred, typename T>
  void
    replace_if_all(T_Container& a_in, T_Pred a_pred, T const & a_newValue)
  {
    replace_if(a_in.begin(), a_in.end(), a_pred, a_newValue);
  }

  template <typename T_ForwardItr, typename T>
  void
    replace(T_ForwardItr a_begin, T_ForwardItr a_end,
            T const & a_oldValue, T const & a_newValue)
  {
    typedef typename
      iterator_traits<T_ForwardItr>::value_type itr_value_type;
    replace_if(a_begin, a_end,
               equal_to_stored<itr_value_type>(a_oldValue), a_newValue);
  }

  template <typename T_ForwardItr, typename T_Pred, typename T>
  void
    replace_if(T_ForwardItr a_begin, T_ForwardItr a_end,
               T_Pred a_pred, T const & a_newValue)
  {
    for (; a_begin != a_end; ++a_begin)
    {
      if (a_pred(*a_begin))
      { *a_begin = a_newValue; }
    }
  }


  template <typename T_Container1, typename T_OutputItr, typename T>
  T_OutputItr
    replace_copy_all(T_Container1& a_in, T_OutputItr a_out,
                     T const & a_oldValue, T const & a_newValue)
  {
    return replace_copy(a_in.begin(), a_in.end(), a_out, a_oldValue, a_newValue);
  }

  template <typename T_Container1, typename T_OutputItr, typename T_UnaryPred,
            typename T>
  T_OutputItr
    replace_copy_if_all(T_Container1& a_in, T_OutputItr a_out,
                        T_UnaryPred a_pred, T const & a_newValue)
  {
    replace_copy_if(a_in.begin(), a_in.end(), a_out, a_pred, a_newValue);
  }

  template <typename T_InputItr, typename T_OutputItr, typename T>
  T_OutputItr
    replace_copy(T_InputItr a_begin, T_InputItr a_end,
                 T_OutputItr a_output, T const & a_oldValue,
                 T const & a_newValue)
  {
    typedef typename
      iterator_traits<T_InputItr>::value_type itr_value_type;
    return replace_copy_if(a_begin, a_end, a_output,
                           equal_to_stored<itr_value_type>(a_oldValue),
                           a_newValue);
  }

  template <typename T_InputItr, typename T_OutputItr, typename T_Pred,
            typename T>
  T_OutputItr
    replace_copy_if(T_InputItr a_begin, T_InputItr a_end,
                    T_OutputItr a_output, T_Pred a_pred,
                    T const & a_newValue)
  {
    for (; a_begin != a_end; ++a_begin, ++a_output)
    {
      if (a_pred(*a_begin))
      { *a_output = a_newValue; }
      else
      { *a_output = *a_begin; }
    }

    return a_output;
  }

  template <typename T_ForwardItr>
  T_ForwardItr
    unique(T_ForwardItr a_first, T_ForwardItr a_end)
  {
    unique(a_first, a_end,
           equal_to<typename iterator_traits<T_ForwardItr>::value_type>());
  }

  template <typename T_ForwardItr, typename T_BinaryPred>
  T_ForwardItr
    unique(T_ForwardItr a_first, T_ForwardItr a_end, T_BinaryPred)
  {
    T_ForwardItr prevItr = a_first++;

    for (; a_first != a_end; ++a_first)
    {
      if (T_BinaryPred()(*a_first, *prevItr) == false)
      {
        ++prevItr;
        *prevItr = *a_first;
      }
    }

    return ++prevItr;
  }

  template <typename T_Container>
  typename T_Container::iterator
    unique_all(T_Container& a_inOut)
  {
    return unique(a_inOut.being(), a_inOut.end());
  }

  template <typename T_Container1, typename T_Container2>
  void
    unique_copy_all(T_Container1& a_in, T_Container2& a_out)
  {
    typedef typename T_Container1::value_type value_type;
    unique_copy_all(a_in, a_out, equal_to<value_type>());
  }

  template <typename T_Container1, typename T_Container2, typename T_BinaryPred>
  void
    unique_copy_all(T_Container1& a_in, T_Container2& a_out,
                       T_BinaryPred)
  {
    typedef typename T_Container1::const_iterator     itr_type_1;
    typedef typename T_Container1::value_type         value_type_1;
    typedef typename T_Container2::value_type         value_type_2;

    TLOC_STATIC_ASSERT( (Loki::IsSameType<value_type_1, value_type_2>::value),
      Container_value_type_must_match);

    a_out.push_back( *(a_in.begin()) );

    itr_type_1 prevItr  = a_in.begin();
    itr_type_1 itr      = a_in.begin(); advance(itr, 1);
    itr_type_1 itrEnd   = a_in.end();

    for (; itr != itrEnd; ++itr)
    {
      if (T_BinaryPred()(*itr, *prevItr) == false)
      {
        a_out.push_back(*itr);
        prevItr = itr;
      }
    }
  }

  template <typename T_Container1, typename T_Container2, typename T_Container3>
  void
    unique_copy_only_all(T_Container1& a_in, T_Container2& a_out,
                         T_Container3& a_dupList)
  {
    typedef typename T_Container1::value_type value_type;
    unique_copy_only_all(a_in, a_out, a_dupList,
                                          equal_to<value_type>());
  }

  template <typename T_Container1, typename T_Container2, typename T_Container3,
            typename T_BinaryPred>
  void
    unique_copy_only_all(T_Container1& a_in, T_Container2& a_out,
                         T_Container3& a_dupList, T_BinaryPred)
  {
    typedef TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container1) itr_type_1;
    typedef typename T_Container1::value_type         value_type_1;

    typedef typename T_Container2::value_type         value_type_2;

    typedef TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container3) itr_type_3;
    typedef typename T_Container3::value_type         value_type_3;

    TLOC_STATIC_ASSERT( (Loki::IsSameType<value_type_1, value_type_2>::value),
      Container_value_type_must_match);
    TLOC_STATIC_ASSERT( (Loki::IsSameType<value_type_1, value_type_3>::value),
      Container_value_type_must_match);

    a_out.push_back( *(a_in.begin()) );

    itr_type_1 prevItr  = a_in.begin();
    itr_type_1 itr      = a_in.begin(); advance(itr, 1);
    itr_type_1 itrEnd   = a_in.end();

    for (; itr != itrEnd; ++itr)
    {
      itr_type_3 itrDup = find_all(a_dupList, *itr);
      if (itrDup != a_dupList.end())
      {
        if (T_BinaryPred()(*itr, *prevItr) == false)
        {
          a_out.push_back(*itr);
          prevItr = itr;
        }
      }
      else
      {
        a_out.push_back(*itr);
        prevItr = itr;
      }
    }
  }

  //------------------------------------------------------------------------
  // Sorting

  template <typename T_InputIterator>
  void
    sort(T_InputIterator a_first, T_InputIterator a_last)
  {
    typedef typename PointeeType<T_InputIterator>::value_type value_type;
    sort(a_first, a_last, less<value_type>());
  }

  template <typename T_InputIterator, typename T_Compare_or_SortAlgorithm>
  void
    sort(T_InputIterator a_first, T_InputIterator a_last,
         T_Compare_or_SortAlgorithm a_comp)
  {
    typedef Loki::Int2Type
      <Loki::Conversion<T_Compare_or_SortAlgorithm, sort_base>::exists>
      compare_or_sort;

    detail::DoSortWithAlgorithmOrCompareFunc
      (a_first, a_last, a_comp, compare_or_sort());
  }

  template <typename T_InputIterator, typename T_SortAlgorithm,
            typename T_Compare>
  void
    sort(T_InputIterator a_first, T_InputIterator a_last, T_Compare a_comp,
         T_SortAlgorithm a_sortAlg)
  {
    typedef typename PointeeType<T_InputIterator>::value_type value_type;
    detail::DoSortWithAlgorithm(a_first, a_last, a_sortAlg, a_comp);
  }

  //------------------------------------------------------------------------
  // Min / Max

  template <typename T>
  T const&
    tlMin(T const & a, T const & b)
  {
    return a < b ? a : b;
  }

  template <typename T>
  T const&
    tlMax(T const & a, T const & b)
  {
    return a < b ? b : a;
  }

  template <typename T, typename T2>
  T
    Clamp(T a_value, T2 a_low, T2 a_high)
  {
    return Clamp(a_value, a_low, a_high, core::less<T>());
  }

  template <typename T, typename T2, typename T_BinaryPred>
  T
    Clamp(T a_value, T2 a_low, T2 a_high, T_BinaryPred a_pred)
  {
    return a_pred(a_high, a_value) ? a_high :
           a_pred(a_value, a_low) ? a_low : a_value;
  }

  //------------------------------------------------------------------------
  // Modifying sequence operations

  template <typename T_InputIterator, typename T_OutputIterator>
  T_OutputIterator
    copy(T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
         T_OutputIterator aDestRangeBegin)
  {
    // We assume that the inputs are pointers. We can then find out whether they
    // are integral pointers or complex
    typedef typename Loki::TypeTraits<T_InputIterator>::PointeeType inputDeref;
    typedef typename Loki::TypeTraits<T_OutputIterator>::PointeeType outputDeref;
    typedef typename Loki::TypeTraits<inputDeref> inputUnknown;
    typedef typename Loki::TypeTraits<outputDeref> outputUknown;
    typedef typename Loki::Int2Type<inputUnknown::isArith && outputUknown::isArith> inputArith;

    return detail::DoCopy(a_rangeBegin, a_rangeEnd, aDestRangeBegin, inputArith());
  }

  template <typename T_Container, typename T_OutputIterator>
  T_OutputIterator
    copy_all(T_Container& a_toCopy,
             T_OutputIterator a_destRangeBegin)
  {
    return copy(a_toCopy.begin(), a_toCopy.end(), a_destRangeBegin);
  }

  template <typename T_InputIterator, typename T_OutputIterator>
  T_OutputIterator
    copy_backward(T_InputIterator a_rangeBegin,
                  T_InputIterator a_rangeEnd,
                  T_OutputIterator aDestRangeEnd)
  {
    typedef typename Loki::Int2Type<Loki::TypeTraits<T_InputIterator>::isPointer> input_type;
    typedef typename Loki::Int2Type<Loki::TypeTraits<T_OutputIterator>::isPointer> output_type;
    typedef typename Loki::Select<input_type::value && output_type::value,
      detail::IsRawItr, detail::IsComplexItr>::Result  itr_type;

    detail::DoCopyBackwardChecks(a_rangeBegin, a_rangeEnd, aDestRangeEnd, itr_type());

    while (a_rangeEnd != a_rangeBegin)
    {
      --aDestRangeEnd;
      --a_rangeEnd;
      *(aDestRangeEnd) = *(a_rangeEnd);
    }

    return aDestRangeEnd;
  }

  template <typename T_Container, typename T_OutputIterator>
  T_OutputIterator
    copy_backward_all(T_Container& a_toCopy,
                      T_OutputIterator a_destRangeBegin)
  {
    return copy_backward_all(a_toCopy.begin(), a_toCopy.end(), a_destRangeBegin);
  }

  template <typename T_Container, typename T>
  void
    fill_all(T_Container& a_toFill, T const & a_value)
  {
    fill(a_toFill.begin(), a_toFill.end(), a_value);
  }

  template <typename T_InputIterator, typename T>
  void
    fill(T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
         T const & a_value)
  {
    // We assume that the inputs are pointers. If they point to data that is a
    // single byte (a char) then use memset
    typedef typename Loki::TypeTraits<T_InputIterator>::PointeeType inputDeref;
    typedef typename Loki::IsSameType<inputDeref, char8> charTestResult;
    typedef typename Loki::Int2Type<charTestResult::value> IsChar8;

    detail::DoFill(a_rangeBegin, a_rangeEnd, a_value, IsChar8());

  }

  template <typename T_Container, typename T_Count, typename T>
  void
    fill_n_all(T_Container& a_toFill, T_Count a_count, T const & a_value)
  {
    fill_n(a_toFill.begin(), a_toFill.end(), a_count, a_value);
  }

  template <typename T_OutputIterator, typename T_Count, typename T_ValueType>
  void
    fill_n(T_OutputIterator a_first, T_Count a_count,
           const T_ValueType& a_value)
  {
    // We assume that the inputs are pointers. If they point to data that is a
    // single byte (a char) then use memset
    typedef typename Loki::TypeTraits<T_OutputIterator>::PointeeType inputDeref;
    typedef typename Loki::IsSameType<inputDeref, char8> charTestResult;
    typedef typename Loki::Int2Type<charTestResult::value> IsChar8;

    detail::DoFill_n(a_first, a_count, a_value, IsChar8());
  }

  template <typename T>
  void
    swap(T& a, T& b)
  {
    T c(a); a = b; b = c;
  }

  template <typename T_Container, typename T>
  typename T_Container::iterator
    lower_bound_all(T_Container& a_toSearch, T const & a_value)
  {
    return lower_bound(a_toSearch.begin(), a_toSearch.end(), a_value);
  }

  template <typename T_Container, typename T, typename T_BinaryPred>
  typename T_Container::iterator
    lower_bound_all(T_Container& a_toSearch, T const & a_value,
                    T_BinaryPred a_pred)
  {
    return lower_bound(a_toSearch.begin(), a_toSearch.end(), a_value, a_pred);
  }

  template <typename T_ForwardIterator, typename T>
  T_ForwardIterator
    lower_bound(T_ForwardIterator a_first,
                T_ForwardIterator a_last, T const & a_value)
  {
    return lower_bound(a_first, a_last, a_value, less<T>());
  }

  template <typename T_ForwardIterator, typename T, typename T_BinaryPred>
  T_ForwardIterator
    lower_bound(T_ForwardIterator a_first, T_ForwardIterator a_last,
                T const& a_value, T_BinaryPred a_comp)
  {
    T_ForwardIterator itr;
    typename iterator_traits<T_ForwardIterator>::difference_type count, step;

    count = distance(a_first, a_last);

    while (count > 0)
    {
      itr = a_first;
      step = count / 2;
      advance(itr, step);

      if (a_comp(*itr, a_value))
      {
        a_first = ++itr;
        count -= step - 1;
      }
      else
      {
        count = step;
      }
    }

    return a_first;
  }

  template <typename T_ForwardItr>
  void
    delete_ptrs(T_ForwardItr a_first, T_ForwardItr a_last)
  {
    typedef typename iterator_traits<T_ForwardItr>::pointer pointer_type;
    TLOC_STATIC_ASSERT(Loki::TypeTraits<pointer_type>::isPointer,
      Function_only_works_with_iterators_storing_simple_pointers);

    for (; a_first != a_last; ++a_first)
    {
      delete *a_first;
    }
  }

  template <class T_InputIterator, class T_OutputIterator, class T_UnaryPred>
  T_OutputIterator
    transform (T_InputIterator a_first, T_InputIterator a_last,
               T_OutputIterator a_result, T_UnaryPred a_op)
  {
    while(a_first != a_last)
    {
      *a_result = a_op(*a_first);
      ++a_result;
      ++a_first;
    }

    return a_result;
  }

  template <class T_InputIterator1, class T_InputIterator2,
  class T_OutputIterator, class T_BinaryPred>
    T_OutputIterator
    transform (T_InputIterator1 a_first1, T_InputIterator1 a_last1,
               T_InputIterator2 a_first2, T_OutputIterator a_result,
               T_BinaryPred a_binary_op)
  {
    while(a_first1 != a_last1)
    {
      *a_result = a_binary_op(*a_first1, *a_first2);
      ++a_result;
      ++a_first1; ++a_first2;
    }

    return a_result;
  }

  template <class T_Container1, class T_Container2, class T_UnaryPred>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container2)
    transform_all(T_Container1& a_toTransform,
                  T_Container2& a_result, T_UnaryPred a_op)
  {
    TLOC_ASSERT_LOW_LEVEL(a_toTransform.size() <= a_result.size(),
      "Result container not big enough");
    return
      core::transform(a_toTransform.begin(), a_toTransform.end(),
                      a_result.begin(), a_op);
  }

  template <class T_Container1, class T_Container2, class T_Container3,
            class T_BinaryPred>
  TLOC_TYPE_TRAITS_CONTAINER_ITERATOR_SELECT(T_Container3)
    transform_all(T_Container1& a_toTransform,
                  T_Container2& a_toTransformWith,
                  T_Container3& a_result,
                  T_BinaryPred a_binary_op)
  {
    TLOC_ASSERT_LOW_LEVEL(a_toTransform.size() == a_toTransformWith.size(),
      "Container sizes don't match");
    TLOC_ASSERT_LOW_LEVEL(a_toTransform.size() <= a_result.size(),
      "Result container not big enough");

    return
      core::transform(a_toTransform.begin(), a_toTransform.end(),
                      a_toTransformWith.begin(), a_result.begin(), a_binary_op);
  }

  //////////////////////////////////////////////////////////////////////////
  // Internal use only

  namespace detail
  {
    //------------------------------------------------------------------------
    // Range verification for raw iterators

    template <typename T_Iterator>
    void
      DoVerifyRange(T_Iterator a_begin, T_Iterator a_end, IsRawItr)
    {
      TLOC_UNUSED_2(a_begin, a_end);
      TLOC_ASSERT_ALGORITHMS( a_begin <= a_end,
                              "Invalid range (a_rangeBegin > a_rangeEnd)!");
    }

    template <typename T_Iterator>
    void
      DoVerifyRange(T_Iterator, T_Iterator, IsComplexItr)
    {
      // Do nothing, since we cannot verify non-pointer iterators in a fast way
    }

    //------------------------------------------------------------------------
    // Copy() helpers

    template <typename T_InputIterator, typename T_OutputIterator>
    T_OutputIterator
      DoCopy(T_InputIterator a_rangeBegin,
             T_InputIterator a_rangeEnd,
             T_OutputIterator aDestRangeBegin, IsNotArith)
    {
      while (a_rangeBegin != a_rangeEnd)
      {
        *(aDestRangeBegin++) = *(a_rangeBegin++);
      }

      return aDestRangeBegin;
    }

    template <typename T_InputIterator, typename T_OutputIterator>
    T_OutputIterator
      DoCopy(T_InputIterator a_rangeBegin,
             T_InputIterator a_rangeEnd,
             T_OutputIterator aDestRangeBegin, IsArith)
    {
      // We need the size of what the pointer is pointing to, not the pointer
      // itself
      typedef typename Loki::TypeTraits<T_InputIterator>::PointeeType inputDeref;

      tl_size rangeSize = a_rangeEnd - a_rangeBegin;
      memmove( aDestRangeBegin, a_rangeBegin,
        (tl_size)(rangeSize) * sizeof(inputDeref) );
      return aDestRangeBegin + rangeSize;
    }

    template <typename T_InputIterator, typename T_OutputIterator>
    void
      DoCopyBackwardChecks(T_InputIterator a_rangeBegin,
                           T_InputIterator a_rangeEnd,
                           T_OutputIterator a_destRangeEnd, IsRawItr)
    {
      TLOC_ASSERT_ALGORITHMS(a_destRangeEnd < a_rangeBegin || a_destRangeEnd > a_rangeEnd,
        "Output past-the-end iterator is within the begin/end range (data "
        "over-writing)! - Try Copy");
      TLOC_ASSERT_ALGORITHMS(a_rangeBegin <= a_rangeEnd,
        "a_rangeBegin > a_rangeEnd (infinite loop)");

      TLOC_UNUSED_3(a_rangeBegin, a_rangeEnd, a_destRangeEnd);
    }

    template <typename T_InputIterator, typename T_OutputIterator>
    void
      DoCopyBackwardChecks(T_InputIterator,
                           T_InputIterator,
                           T_OutputIterator, IsComplexItr)
    {
      // Do nothing, since we cannot verify non-pointer iterators in a fast way
    }

    //------------------------------------------------------------------------
    // Fill helpers

    template <typename T_InputIterator, typename T>
    void
      DoFill( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
              T const & a_value, IsNotChar )
    {
      while (a_rangeBegin != a_rangeEnd)
      {
        *a_rangeBegin = a_value;
        ++a_rangeBegin;
      }
    }

    template <typename T_InputIterator, typename T>
    void
      DoFill( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
              T const & a_value, IsChar )
    {
      memset(a_rangeBegin, a_value, sizeof(T) * (a_rangeEnd - a_rangeBegin));
    }

    template <typename T_OutputIterator, typename T_Count, typename T_ValueType>
    void
      DoFill_n(T_OutputIterator a_first, T_Count a_count,
               const T_ValueType& a_value, IsNotChar)
    {
      typedef typename iterator_traits<T_OutputIterator>::iterator_category
        iterator_category;

      // The correct fill_n() will be called depending on whether the output
      // iterator has a random or lesser tag associated with it.
      DoFill_n(a_first, a_count, a_value, iterator_category());
    }

    template <typename T_OutputIterator, typename T_Count, typename T_ValueType>
    void
      DoFill_n(T_OutputIterator a_first, T_Count a_count,
               const T_ValueType& a_value, IsChar)
    {
      memset(a_first, a_value, (tl_size)a_count);
    }

    template <typename T_OutputIterator, typename T_Count, typename T_ValueType>
    void
      DoFill_n(T_OutputIterator a_first, T_Count a_count,
               const T_ValueType& a_value, random_access_iterator_tag)
    {
      // Grabbing a range by adding to a_first and using fill is faster than
      // using two variables in a for loop. This is only possible if the output
      // iterator has a random tag.
      tloc::core::fill(a_first, a_first + a_count, a_value);
    }

    template <typename T_OutputIterator, typename T_Count, typename T_ValueType>
    void
      DoFill_n(T_OutputIterator a_first, T_Count a_count,
               const T_ValueType& a_value, input_iterator_tag)
    {
      for (/* */; a_count > 0; --a_count, ++a_first)
      {
        *a_first = a_value;
      }
    }

    template <typename T_InputIterator, typename T>
    T_InputIterator
      DoFind( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
              T const & a_value, IsNotChar )
    {
      TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

      while (a_rangeBegin != a_rangeEnd)
      {
        if (*a_rangeBegin == a_value) break;
        ++a_rangeBegin;
      }

      return a_rangeBegin;
    }

    template <typename T_InputIterator, typename T>
    T_InputIterator
      DoFind( T_InputIterator a_rangeBegin,
              T_InputIterator a_rangeEnd,
              T const & a_value, IsChar )
    {
      TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

      T_InputIterator retVal =
        (char8*)memchr(a_rangeBegin, a_value, sizeof(char8) *
                       (tl_size)(a_rangeEnd - a_rangeBegin));
      return retVal ? retVal : a_rangeEnd;
    }

    //------------------------------------------------------------------------
    // Sort helpers

    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortWithAlgorithmOrCompareFunc(T_InputIterator a_first,
                                       T_InputIterator a_last,
                                       T_Compare a_comp,
                                       IsCompareFunctionObject)
    {
      typedef typename PointeeType<T_InputIterator>::value_type value_type;
      DoSortWithAlgorithm(a_first, a_last, sort_quicksort_randompivot(), a_comp);
    }

    template <typename T_InputIterator, typename T_SortAlgorithm>
    void
      DoSortWithAlgorithmOrCompareFunc(T_InputIterator a_first,
                                       T_InputIterator a_last,
                                       T_SortAlgorithm a_sortAlgorithm,
                                       IsSortingAlgorithm)
    {
      typedef typename PointeeType<T_InputIterator>::value_type value_type;
      DoSortWithAlgorithm(a_first, a_last, a_sortAlgorithm, less<value_type>());
    }

    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortWithAlgorithm(T_InputIterator a_first, T_InputIterator a_last,
                          sort_quicksort_autoselect, T_Compare a_compare)
    {
    }

    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortWithAlgorithm(T_InputIterator a_first, T_InputIterator a_last,
                          sort_quicksort_randompivot, T_Compare a_compare)
    {
      const tl_ptrdiff size      = tloc::core::distance(a_first, a_last);

      if (size < 2)
      { return; }

      const tl_ptrdiff randomPiv =
        rng::g_defaultRNG.GetRandomInteger(0, (rng::rng_default::int_type)size);

      T_InputIterator randItr = a_first;
      tloc::core::advance(randItr, randomPiv);

      core::swap(*a_first, *randItr);
      DoSortWithAlgorithm(a_first, a_last, sort_quicksort_leftpivot(), a_compare);
    }

    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortWithAlgorithm(T_InputIterator a_first, T_InputIterator a_last,
                          sort_quicksort_middlepivot, T_Compare a_compare)
    {
      const tl_ptrdiff size      = tloc::core::distance(a_first, a_last);

      if (size < 2)
      { return; }

      const tl_ptrdiff halfSize = size / 2;

      T_InputIterator midItr = a_first;
      tloc::core::advance(midItr, halfSize);

      core::swap(*a_first, *midItr);
      DoSortWithAlgorithm(a_first, a_last, sort_quicksort_leftpivot(), a_compare);
    }

    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortWithAlgorithm(T_InputIterator a_first, T_InputIterator a_last,
                          sort_quicksort_rightpivot, T_Compare a_compare)
    {
      const tl_ptrdiff size      = tloc::core::distance(a_first, a_last);

      if (size < 2)
      { return; }

      // Swap the rightpivot with the left most element. We can then call
      // quicksort_leftpivot
      T_InputIterator rightPivot = a_last;
      --rightPivot;

      core::swap(*a_first, *rightPivot);
      DoSortWithAlgorithm(a_first, a_last, sort_quicksort_leftpivot(), a_compare);
    }

    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortWithAlgorithm(T_InputIterator a_first, T_InputIterator a_last,
                          sort_quicksort_leftpivot, T_Compare a_compare)
    {
      typedef typename Loki::TypeTraits<T_InputIterator> unknown_type;
      typedef typename Loki::Int2Type<unknown_type::isPointer> pointer_type;

      DoQuicksortLeftPivot(a_first, a_last, pointer_type(), a_compare);
    }

    template <typename T_InputIterator, typename T_Compare>
    void
      DoQuicksortLeftPivot(T_InputIterator a_first, T_InputIterator a_last,
                           IsRawItr, T_Compare a_compare)
    {
      typedef typename Loki::TypeTraits<T_InputIterator>::PointeeType value_type;
      DoQuicksort(a_first, a_last, value_type(), a_compare);
    }

    template <typename T_InputIterator, typename T_Compare>
    void
      DoQuicksortLeftPivot(T_InputIterator a_first, T_InputIterator a_last,
                           IsComplexItr, T_Compare a_compare)
    {
      // It is assumed, since the inputer iterator is complex, it has a typedef
      // for value_type. If there is a COMPILE ERROR here then the complex
      // object is either not an iterator OR does not have a value_type typedef
      DoQuicksort(a_first, a_last, typename T_InputIterator::value_type(),
                  a_compare);
    }

    template <typename T_InputIterator, typename T_ValueType,
              typename T_Compare>
    void
      DoQuicksort(T_InputIterator a_first, T_InputIterator a_last, T_ValueType,
                  T_Compare a_compare)
    {
      if (a_first == a_last) { return; }

      T_ValueType pivot = *a_first;

      T_InputIterator startItr = a_first;
      T_InputIterator endItr   = a_last--;

      T_InputIterator currItr  = a_first;

      while (a_first != a_last)
      {
        if (currItr == a_first)
        {
          if (a_compare(*a_last, pivot)) // if (*a_last < pivot)
          {
            *a_first = *a_last;
            ++a_first;
            currItr = a_last;
          }
          else
          {
            --a_last;
          }
        }
        else
        {
          if (a_compare(pivot, *a_first)) // if (*a_first > pivot)
          {
            *a_last = *a_first;
            --a_last;
            currItr = a_first;
          }
          else
          {
            ++a_first;
          }
        }
      }

      *a_first = pivot;
      if (startItr != a_first)
      {
        DoSortWithAlgorithm(startItr, a_first,
                            sort_quicksort_leftpivot(), a_compare);
      }
      if (++a_last != endItr)
      {
        DoSortWithAlgorithm(a_last, endItr,
                            sort_quicksort_leftpivot(), a_compare);
      }
    }

    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortWithAlgorithm(T_InputIterator a_first, T_InputIterator a_last,
                          sort_insertionsort, T_Compare a_compare)
    {
      typedef typename Loki::TypeTraits<T_InputIterator> unknown_type;
      typedef typename Loki::Int2Type<unknown_type::isPointer> pointer_type;

      DoInsertionsortWithItrType(a_first, a_last, pointer_type(), a_compare);
    }

    template <typename T_InputIterator, typename T_Compare>
    void
      DoInsertionsortWithItrType(T_InputIterator a_first, T_InputIterator a_last,
                                 IsRawItr, T_Compare a_compare)
    {
      typedef typename Loki::TypeTraits<T_InputIterator>::PointeeType value_type;
      DoInsertionsortWithValueType(a_first,a_last, value_type(), a_compare);
    }

    template <typename T_InputIterator, typename T_Compare>
    void
      DoInsertionsortWithItrType(T_InputIterator a_first, T_InputIterator a_last,
                                 IsComplexItr, T_Compare a_compare)
    {
      DoInsertionsortWithValueType(a_first, a_last,
                                   typename T_InputIterator::value_type(),
                                   a_compare);
    }

    template <typename T_InputIterator, typename T_ValueType, typename T_Compare>
    void
      DoInsertionsortWithValueType(T_InputIterator a_first,
                                   T_InputIterator a_last,
                                   T_ValueType, T_Compare a_compare)
    {
      if (a_first != a_last)
      {
        T_InputIterator unsortedItr = a_first;
        ++unsortedItr;

        T_InputIterator currentItr;
        T_InputIterator currentItrMinusOne;

        T_ValueType currentValue;

        for (/* */; unsortedItr != a_last; ++unsortedItr)
        {
          currentItr = unsortedItr;
          currentValue = *currentItr;

          currentItrMinusOne = currentItr;
          --currentItrMinusOne;

          while (currentItr != a_first
                 && a_compare(currentValue, *currentItrMinusOne)) // && *currentItrMinusOne > currentValue)
          {
            *currentItr = *currentItrMinusOne;

            currentItr = currentItrMinusOne;
            --currentItrMinusOne;
          }

          *currentItr = currentValue;
        }
      }
    }

    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortWithAlgorithm(T_InputIterator a_first, T_InputIterator a_last,
                          sort_mergesort, T_Compare a_compare)
    {
      typedef typename Loki::TypeTraits<T_InputIterator> unknown_type;
      typedef typename Loki::Int2Type<unknown_type::isPointer> pointer_type;

      DoMergesortWithItrType(a_first, a_last, pointer_type(), a_compare);
    }

    template <typename T_InputIterator, typename T_Compare>
    void
      DoMergesortWithItrType(T_InputIterator a_first, T_InputIterator a_last,
                             IsComplexItr, T_Compare a_compare)
    {
      DoMergesortWithValueType(a_first, a_last,
                               typename T_InputIterator::value_type(),
                               a_compare);
    }

    template <typename T_InputIterator, typename T_Compare>
    void
      DoMergesortWithItrType(T_InputIterator a_first, T_InputIterator a_last,
                             IsRawItr, T_Compare a_compare)
    {
      typedef typename Loki::TypeTraits<T_InputIterator>::PointeeType value_type;

      DoMergesortWithValueType(a_first, a_last, value_type(), a_compare);
    }

    template <typename T_InputIterator, typename T_ValueType,
              typename T_Compare>
    void
      DoMergesortWithValueType(T_InputIterator a_first, T_InputIterator a_last,
                               T_ValueType, T_Compare a_compare)
    {
      if (a_first != a_last)
      {
        const tl_ptrdiff size = tloc::core::distance(a_first, a_last);
        typedef containers::Array<T_ValueType> T_Container;
        T_Container unsortedArray(size);

        tloc::core::copy(a_first, a_last, unsortedArray.begin());

        T_Container sortedArray = DoMergesort(unsortedArray, a_compare);
        //unsortedArray = DoMergesort(unsortedArray);

        tloc::core::copy(sortedArray.begin(), sortedArray.end(), a_first);
        //tloc::core::copy(unsortedArray.begin(), unsortedArray.end(), a_first);
      }
    }

    template <typename T_Container, typename T_Compare>
    T_Container
      DoMergesort(T_Container& aUnsorted, T_Compare a_compare)
    {
      const tl_size size = aUnsorted.size();
      if ((size - 1) != 0)
      {
        TLOC_ASSERT_LOW_LEVEL(size > 1, "Size is <= 1");

        typename T_Container::const_iterator first = aUnsorted.begin();
        typename T_Container::const_iterator last = aUnsorted.end();

        tl_size halfSize = size / 2;

        typename T_Container::const_iterator midItr = first;
        tloc::core::advance(midItr, halfSize);

        T_Container leftSide(halfSize);
        T_Container rightSide(size - halfSize);

        tloc::core::copy(first, midItr, leftSide.begin());
        tloc::core::copy(midItr, last, rightSide.begin());

        T_Container LeftSideSorted = DoMergesort(leftSide, a_compare);
        T_Container RightSideSorted = DoMergesort(rightSide, a_compare);

        return DoMerge(LeftSideSorted, RightSideSorted, a_compare);
      }
      else
      {
        return aUnsorted;
      }
    }

    template <typename T_Container, typename T_Compare>
    T_Container
      DoMerge(T_Container& aLeftFirst, T_Container& aRightFirst,
              T_Compare a_compare)
    {
      const typename T_Container::size_type size = aLeftFirst.size() + aRightFirst.size();
      T_Container mergedContainer(size);

      typename T_Container::const_iterator leftItr   = aLeftFirst.begin();
      typename T_Container::const_iterator rightItr  = aRightFirst.begin();
      typename T_Container::iterator mergedItr       = mergedContainer.begin();

      const typename T_Container::const_iterator endLeftItr   = aLeftFirst.end();
      const typename T_Container::const_iterator endRightItr  = aRightFirst.end();

      while ((leftItr != endLeftItr) && (rightItr != endRightItr))
      {
        if (a_compare(*leftItr, *rightItr)) //if (*leftItr < *rightItr)
        {
          *mergedItr = *leftItr;
          ++leftItr;
        }
        else
        {
          *mergedItr = *rightItr;
          ++rightItr;
        }
        ++mergedItr;
      }

      while (leftItr != endLeftItr)
      {
        *mergedItr = *leftItr;
        ++leftItr;
        ++mergedItr;
      }

      while (rightItr != endRightItr)
      {
        *mergedItr = *rightItr;
        ++rightItr;
        ++mergedItr;
      }

      return mergedContainer;
    }

    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortWithAlgorithm(T_InputIterator a_first, T_InputIterator a_last,
                          sort_merge_insertionsort, T_Compare a_compare)
    {
      if (a_first != a_last)
      {
        DoMergeInsertionSort(a_first, a_last, a_compare);
      }
    }

    template <typename T_InputIterator, typename T_Compare>
    void
      DoMergeInsertionSort(T_InputIterator a_first, T_InputIterator a_last,
                           T_Compare a_compare)
    {
      const tl_ptrdiff size = tloc::core::distance(a_first, a_last);
      if ((size - 1) != 0)
      {
        const tl_ptrdiff halfSize = size / 2;
        T_InputIterator midItr = a_first;
        tloc::core::advance(midItr, halfSize);

        DoMergeInsertionSort(a_first, midItr, a_compare);
        DoMergeInsertionSort(midItr, a_last, a_compare);
        DoMergeInsertion(a_first, midItr, a_last, a_compare);
      }
    }

    template <typename T_InputIterator, typename T_Compare>
    void
      DoMergeInsertion(T_InputIterator aLeftFirst, T_InputIterator aRightFirst,
                       T_InputIterator a_last, T_Compare a_compare)
    {
      typedef typename Loki::TypeTraits<T_InputIterator> unknown_type;
      typedef typename Loki::Int2Type<unknown_type::isPointer> pointer_type;

      for (/* */; aLeftFirst != aRightFirst; ++aLeftFirst)
      {
        if (a_compare(*aRightFirst, *aLeftFirst)) // if (*aLeftFirst > *aRightFirst)
        {
          core::swap(*aLeftFirst, *aRightFirst);
          DoSortFirstElementWithItrType(aRightFirst, a_last, pointer_type(),
                                        a_compare);
        }
      }
    }

    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortFirstElementWithItrType(T_InputIterator a_first,
                                    T_InputIterator a_last,
                                    IsComplexItr, T_Compare a_compare)
    {
      DoSortFirstElementWithValueType(a_first, a_last,
                                      typename T_InputIterator::value_type(),
                                      a_compare);
    }

    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortFirstElementWithItrType(T_InputIterator a_first,
                                    T_InputIterator a_last,
                                    IsRawItr, T_Compare a_compare)
    {
      typedef typename Loki::TypeTraits<T_InputIterator>::PointeeType value_type;

      DoSortFirstElementWithValueType(a_first, a_last, value_type(), a_compare);
    }

    template <typename T_InputIterator, typename T_ValueType, typename T_Compare>
    void
      DoSortFirstElementWithValueType(T_InputIterator a_first,
                                      T_InputIterator a_last,
                                      T_ValueType, T_Compare a_compare)
    {
      T_ValueType valueToBeSorted = *a_first;

      T_InputIterator currentItr = a_first;
      T_InputIterator currentItrPlusOne = currentItr;
      ++currentItrPlusOne;

      while (currentItrPlusOne != a_last &&
             a_compare(*currentItrPlusOne,valueToBeSorted))
      {
        *currentItr = *currentItrPlusOne;
        ++currentItr;
        ++currentItrPlusOne;
      }

      *currentItr = valueToBeSorted;
    }

    template <typename T_InputIterator, typename T_Compare>
    void
      DoSortWithAlgorithm(T_InputIterator a_first, T_InputIterator a_last,
                          sort_bubblesort, T_Compare a_compare)
    {
      T_InputIterator endOfUnsortedItr;
      T_InputIterator currentItr;
      T_InputIterator currentItrPlusOne;

      bool swapped;

      for (endOfUnsortedItr = a_last; endOfUnsortedItr != a_first; --endOfUnsortedItr)
      {
        currentItr = a_first;
        currentItrPlusOne = currentItr;
        ++currentItrPlusOne;

        swapped = false;

        for (/* */;
             currentItrPlusOne != endOfUnsortedItr;
             currentItr = currentItrPlusOne, ++currentItrPlusOne)
        {
          if (a_compare(*currentItrPlusOne, *currentItr)) // if (*currentItr > *currentItrPlusOne)
          {
            core::swap(*currentItr, *currentItrPlusOne);
            swapped = true;
          }
        }

        if (!swapped)
        {
          break;
        }
      }
    }

  }

};};

#endif

//////////////////////////////////////////////////////////////////////////
// NOTES
//
// These notes are put here to avoid cluttering the code above
//
// NOTES_ITERATOR_VALUE_TYPE_TYPEDEF
//    Why use itr_value_type?
//    We need to make equal_to_stored the same type as the iterator's type,
//    otherwise we may get warnings of casting from itr_value_type to T when
//    the predicate is called in remove_if()

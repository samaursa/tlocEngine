#ifndef TLOC_ALGORITHMS_INL
#define TLOC_ALGORITHMS_INL

#ifndef TLOC_ALGORITHMS_H
#error "Must include header before including the inline file"
#endif

#include "tlocAlgorithms.h"
#include "tlocIterator.inl"
#include "tlocPair.inl"
#include "tlocArray.inl"

#include "tlocRandom.h"

namespace tloc { namespace core {

  // TODO: Make all find functions specialized for char* and use memcmp

  //------------------------------------------------------------------------
  // Range verifier - only works on raw iterators, ignores complex iterators 

  template <typename T_Iterator>
  void TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(T_Iterator a_begin, T_Iterator a_end)
  {
    typedef Loki::Int2Type<Loki::TypeTraits<T_Iterator>::isPointer> itr_type;
    detail::DoVerifyRange(a_begin, a_end, itr_type());
  }

  //------------------------------------------------------------------------
  // Non-modifying sequence operations

  template <typename T_Container, typename T_Function>
  T_Function for_each(T_Container a_container, T_Function a_func)
  {
    return for_each(a_container.begin(), a_container.end(), a_func);
  }

  template <typename T_InputIterator, typename T_Function>
  T_Function for_each( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
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
  typename T_Container::iterator find(T_Container a_container, const T& a_value)
  {
    return find(a_container.begin(), a_container.end(), a_value);
  }

  template <typename T_InputIterator, typename T>
  T_InputIterator find( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
                        const T& a_value )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

    // We assume that the inputs are pointers. If they point to data that is a
    // single byte (a char) then use memset
    typedef Loki::TypeTraits<T_InputIterator>::PointeeType inputDeref;
    typedef Loki::IsSameType<inputDeref, char8> charTestResult;
    typedef Loki::Int2Type<charTestResult::value> IsChar8;

    return detail::DoFind(a_rangeBegin, a_rangeEnd, a_value, IsChar8());
  }

  template <typename T_Container, typename T_Predicate>
  typename T_Container::iterator find_if(T_Container a_container, 
                                         const T_Predicate& a_pred)
  {
    return find_if(a_container.begin(), a_container.end(), a_pred);
  }

  template <typename T_InputIterator, typename T_Predicate>
  T_InputIterator find_if( T_InputIterator a_rangeBegin,
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


  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 find_end( T_ForwardIterator1 a_rangeToSearchBegin,
                               T_ForwardIterator1 a_rangeToSearchEnd,
                               T_ForwardIterator2 a_rangeToFindBegin,
                               T_ForwardIterator2 a_rangeToFindEnd )
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
          if (*sourceItr != *compareItr) { break; }
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

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
    typename T_BinaryPredicate>
  T_ForwardIterator1 find_end( T_ForwardIterator1 a_rangeToSearchBegin,
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

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 find_first_of( T_ForwardIterator1 a_rangeToSearchBegin,
                                    T_ForwardIterator1 a_rangeToSearchEnd,
                                    T_ForwardIterator2 a_rangeToFindBegin,
                                    T_ForwardIterator2 a_rangeToFindEnd )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToSearchBegin, a_rangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToFindBegin, a_rangeToFindEnd);

    T_ForwardIterator2 compareItr;

    while (a_rangeToSearchBegin != a_rangeToSearchEnd)
    {
      compareItr = a_rangeToFindBegin;
      while (compareItr != a_rangeToFindEnd)
      {
        if (*a_rangeToSearchBegin == *compareItr)
        {
          return a_rangeToSearchBegin;
        }
        ++compareItr;
      }

      ++a_rangeToSearchBegin;
    }

    return a_rangeToSearchEnd;
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
  T_ForwardIterator1 find_first_of( T_ForwardIterator1 a_rangeToSearchBegin,
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

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 find_first_not_of( T_ForwardIterator1 a_rangeToSearchBegin,
                                        T_ForwardIterator1 a_rangeToSearchEnd,
                                        T_ForwardIterator2 a_rangeToFindBegin,
                                        T_ForwardIterator2 a_rangeToFindEnd )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToSearchBegin, a_rangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToFindBegin, a_rangeToFindEnd);

    T_ForwardIterator2 compareItr;

    while (a_rangeToSearchBegin != a_rangeToSearchEnd)
    {
      compareItr = a_rangeToFindBegin;

      while (compareItr != a_rangeToFindEnd)
      {
        if (*compareItr == *a_rangeToSearchBegin) { break; }

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

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
  T_ForwardIterator1 find_first_not_of( T_ForwardIterator1 a_rangeToSearchBegin,
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

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 find_last_not_of( T_ForwardIterator1 a_rangeToSearchBegin,
                                       T_ForwardIterator1 a_rangeToSearchEnd,
                                       T_ForwardIterator2 a_rangeToFindBegin,
                                       T_ForwardIterator2 a_rangeToFindEnd )
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
          if ( *(a_rangeToSearchBegin + i) == *(a_rangeToFindBegin + j))
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

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
    typename T_BinaryPredicate>
    T_ForwardIterator1 find_last_not_of( T_ForwardIterator1 a_rangeToSearchBegin,
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
  tl_size count(T_Container a_container, const T& a_value)
  {
    return count(a_container.begin(), a_container.end(), a_value);
  }

  template <typename T_InputIterator, typename T>
  tl_size count( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
                 const T& a_value )
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
  tl_size count_if(T_Container a_container, T_Predicate a_pred)
  {
    return count_if(a_container.begin(), a_container.end(), a_pred);
  }

  template <typename T_InputIterator, typename T_Predicate>
  tl_size count_if( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
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

  template <typename T_InputIterator1, typename T_InputIterator2>
  Pair<T_InputIterator1, T_InputIterator2>
    mismatch( T_InputIterator1 a_rangeBegin, T_InputIterator1 a_rangeEnd,
              T_InputIterator2 a_rangeToCompare )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

    while (a_rangeBegin != a_rangeEnd)
    {
      if (*a_rangeBegin != *a_rangeToCompare)
        break;

      ++a_rangeBegin;
      ++a_rangeToCompare;
    }

    return MakePair(a_rangeBegin, a_rangeToCompare);
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

  template <typename T_InputIterator1, typename T_InputIterator2>
  bool equal( T_InputIterator1 a_rangeBegin, T_InputIterator1 a_rangeEnd,
              T_InputIterator2 a_rangeToCompare )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

    while (a_rangeBegin != a_rangeEnd)
    {
      if (*a_rangeBegin != *a_rangeToCompare) { return false; }

      ++a_rangeBegin;
      ++a_rangeToCompare;
    }

    return true;
  }

  template <typename T_InputIterator1, typename T_InputIterator2,
            typename T_BinaryPred>
  bool equal( T_InputIterator1 a_rangeBegin, T_InputIterator1 a_rangeEnd,
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

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 search( T_ForwardIterator1 a_rangeToSearchBegin,
                             T_ForwardIterator1 a_rangeToSearchEnd,
                             T_ForwardIterator2 a_rangeToFindBegin,
                             T_ForwardIterator2 a_rangeToFindEnd )
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
          if (*sourceItr != *compareItr) { break; }
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

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
    T_ForwardIterator1 search( T_ForwardIterator1 a_rangeToSearchBegin,
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

  template <typename T_ForwardIterator, typename T_Size, typename T>
  T_ForwardIterator search_n( T_ForwardIterator a_rangeToSearchBegin,
                              T_ForwardIterator a_rangeToSearchEnd,
                              T_Size aCount, const T& a_value )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToSearchBegin, a_rangeToSearchEnd);

    const tl_size sourceSize = distance(a_rangeToSearchBegin, a_rangeToSearchEnd);

    if (sourceSize >= (tl_size)aCount)
    {
      T_ForwardIterator sourceLimit = a_rangeToSearchEnd - aCount + 1;

      T_ForwardIterator retItr = a_rangeToSearchEnd;
      T_ForwardIterator retItrEnd;

      while(a_rangeToSearchBegin != sourceLimit)
      {
        retItr = a_rangeToSearchBegin;
        retItrEnd = a_rangeToSearchBegin + aCount;
        while (retItr != retItrEnd)
        {
          if (*retItr != a_value) { break; }
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

  template <typename T_ForwardIterator, typename T_Size, typename T,
            typename T_BinaryPred>
    T_ForwardIterator search_n( T_ForwardIterator a_rangeToSearchBegin,
                                T_ForwardIterator a_rangeToSearchEnd,
                                T_Size aCount, const T& a_value,
                                T_BinaryPred a_pred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeToSearchBegin, a_rangeToSearchEnd);

    const tl_size sourceSize = distance(a_rangeToSearchBegin, a_rangeToSearchEnd);

    if (sourceSize >= (tl_size)aCount)
    {
      T_ForwardIterator sourceLimit = a_rangeToSearchEnd - aCount + 1;

      T_ForwardIterator retItr = a_rangeToSearchEnd;
      T_ForwardIterator retItrEnd;

      while(a_rangeToSearchBegin != sourceLimit)
      {
        retItr = a_rangeToSearchBegin;
        retItrEnd = a_rangeToSearchBegin + aCount;
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
  // Sorting

  template <typename T_InputIterator>
  void sort(T_InputIterator aFirst, T_InputIterator aLast)
  {
    detail::DoSort(aFirst, aLast, sort_quicksort_randompivot());
  }  

  template <typename T_InputIterator, typename T_SortAlgorithm>
  void sort(T_InputIterator aFirst, T_InputIterator aLast, 
            T_SortAlgorithm aSortAlg)
  {
    detail::DoSort(aFirst, aLast, aSortAlg); 
  }

  //------------------------------------------------------------------------
  // Min / Max

  template <typename T>
  TL_I const T& tlMin(const T& a, const T& b)
  {
    return a < b ? a : b;
  }

  template <typename T>
  TL_I const T& tlMax(const T& a, const T& b)
  {
    return a < b ? b : a;
  }

  //------------------------------------------------------------------------
  // Modifying sequence operations

  template <typename T_InputIterator, typename T_OutputIterator>
  TL_I T_OutputIterator copy(T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
                             T_OutputIterator aDestRangeBegin)
  {
    // We assume that the inputs are pointers. We can then find out whether they
    // are integral pointers or complex
    typedef Loki::TypeTraits<T_InputIterator>::PointeeType inputDeref;
    typedef Loki::TypeTraits<T_OutputIterator>::PointeeType outputDeref;
    typedef Loki::TypeTraits<inputDeref> inputUnknown;
    typedef Loki::TypeTraits<outputDeref> outputUknown;
    typedef Loki::Int2Type<inputUnknown::isArith && outputUknown::isArith> inputArith;

    return detail::DoCopy(a_rangeBegin, a_rangeEnd, aDestRangeBegin, inputArith());
  }

  template <typename T_InputIterator, typename T_OutputIterator>
  TL_I T_OutputIterator copy_backward(T_InputIterator a_rangeBegin,
                                      T_InputIterator a_rangeEnd,
                                      T_OutputIterator aDestRangeEnd)
  {
    typedef Loki::Int2Type<Loki::TypeTraits<T_InputIterator>::isPointer> input_type;
    typedef Loki::Int2Type<Loki::TypeTraits<T_OutputIterator>::isPointer> output_type;
    typedef Loki::Select<input_type::value && output_type::value, 
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

  template <typename T_InputIterator, typename T>
  TL_I void fill(T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
                 const T& a_value)
  {
    // We assume that the inputs are pointers. If they point to data that is a
    // single byte (a char) then use memset
    typedef Loki::TypeTraits<T_InputIterator>::PointeeType inputDeref;
    typedef Loki::IsSameType<inputDeref, char8> charTestResult;
    typedef Loki::Int2Type<charTestResult::value> IsChar8;

    detail::DoFill(a_rangeBegin, a_rangeEnd, a_value, IsChar8());

  }

  template <typename T_OutputIterator, typename T_Count, typename T_ValueType>
  TL_I void fill_n(T_OutputIterator a_first, T_Count a_count, 
                   const T_ValueType& a_value)
  {
    // We assume that the inputs are pointers. If they point to data that is a
    // single byte (a char) then use memset
    typedef Loki::TypeTraits<T_OutputIterator>::PointeeType inputDeref;
    typedef Loki::IsSameType<inputDeref, char8> charTestResult;
    typedef Loki::Int2Type<charTestResult::value> IsChar8;

    detail::DoFill_n(a_first, a_count, a_value, IsChar8());
  }

  template <typename T>
  TL_I void tlSwap(T& a, T& b)
  {
    T c(a); a = b; b = c;
  }

  template <typename T_ForwardIterator, typename T>
  T_ForwardIterator lower_bound(T_ForwardIterator a_first, 
    T_ForwardIterator a_last, const T& a_value)
  {
    T_ForwardIterator itr;
    iterator_traits<T_ForwardIterator>::difference_type count, step;

    count = distance(a_first, a_last);

    while (count > 0)
    {
      itr = a_first;
      step = count / 2;
      advance(itr, step);

      if (*itr < a_value)
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

  template <typename T_ForwardIterator, typename T, typename T_BinaryPred>
  T_ForwardIterator lower_bound(T_ForwardIterator a_first, 
    T_ForwardIterator a_last, const T& a_value, T_BinaryPred a_comp)
  {
    T_ForwardIterator itr;
    iterator_traits<T_ForwardIterator>::difference_type count, step;

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

  //////////////////////////////////////////////////////////////////////////
  // Internal use only

  namespace detail
  {
    //------------------------------------------------------------------------
    // Range verification for raw iterators

    template <typename T_Iterator>
    void DoVerifyRange(T_Iterator a_begin, T_Iterator a_end, IsRawItr)
    {
      TLOC_UNUSED_2(a_begin, a_end);
      TLOC_ASSERT_ALGORITHMS( a_begin <= a_end, 
                              "Invalid range (a_rangeBegin > a_rangeEnd)!");
    }

    template <typename T_Iterator>
    void DoVerifyRange(T_Iterator, T_Iterator, IsComplexItr)
    {
      // Do nothing, since we cannot verify non-pointer iterators in a fast way 
    }

    //------------------------------------------------------------------------
    // Copy() helpers

    template <typename T_InputIterator, typename T_OutputIterator>
    TL_I T_OutputIterator DoCopy(T_InputIterator a_rangeBegin, 
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
    TL_I T_OutputIterator DoCopy(T_InputIterator a_rangeBegin, 
                                 T_InputIterator a_rangeEnd, 
                                 T_OutputIterator aDestRangeBegin, IsArith)
    {
      // We need the size of what the pointer is pointing to, not the pointer
      // itself
      typedef Loki::TypeTraits<T_InputIterator>::PointeeType inputDeref;

      tl_size rangeSize = a_rangeEnd - a_rangeBegin;
      memmove( aDestRangeBegin, a_rangeBegin,
        (tl_size)(rangeSize) * sizeof(inputDeref) );
      return aDestRangeBegin + rangeSize;
    }

    template <typename T_InputIterator, typename T_OutputIterator>
    TL_I void DoCopyBackwardChecks(T_InputIterator a_rangeBegin,
                                   T_InputIterator a_rangeEnd,
                                   T_OutputIterator a_destRangeEnd, IsRawItr)
    {
      TLOC_ASSERT_ALGORITHMS(a_destRangeEnd < a_rangeBegin || a_destRangeEnd > a_rangeEnd,
        "Output past-the-end iterator is within the begin/end range (data "
        L"over-writing)! - Try Copy");
      TLOC_ASSERT_ALGORITHMS(a_rangeBegin <= a_rangeEnd,
        "a_rangeBegin > a_rangeEnd (infinite loop)");

      TLOC_UNUSED_3(a_rangeBegin, a_rangeEnd, a_destRangeEnd);
    }

    template <typename T_InputIterator, typename T_OutputIterator>
    TL_I void DoCopyBackwardChecks(T_InputIterator,
                                   T_InputIterator,
                                   T_OutputIterator, IsComplexItr)
    {
      // Do nothing, since we cannot verify non-pointer iterators in a fast way 
    }

    //------------------------------------------------------------------------
    // Fill helpers

    template <typename T_InputIterator, typename T>
    TL_I void DoFill( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
                      const T& a_value, IsNotChar )
    {
      while (a_rangeBegin != a_rangeEnd)
      {
        *a_rangeBegin = a_value;
        ++a_rangeBegin;
      }
    }

    template <typename T_InputIterator, typename T>
    TL_I void DoFill( T_InputIterator a_rangeBegin, T_InputIterator a_rangeEnd,
                      const T& a_value, IsChar )
    {
      memset(a_rangeBegin, a_value, sizeof(T) * (a_rangeEnd - a_rangeBegin));
    }

    template <typename T_OutputIterator, typename T_Count, typename T_ValueType>
    TL_I void DoFill_n(T_OutputIterator a_first, T_Count a_count, 
                     const T_ValueType& a_value, IsNotChar)
    {
      typedef iterator_traits<T_OutputIterator>::iterator_category 
        iterator_category;

      // The correct fill_n() will be called depending on whether the output
      // iterator has a random or lesser tag associated with it. 
      DoFill_n(a_first, a_count, a_value, iterator_category());
    }

    template <typename T_OutputIterator, typename T_Count, typename T_ValueType>
    TL_I void DoFill_n(T_OutputIterator a_first, T_Count a_count, 
                     const T_ValueType& a_value, IsChar)
    {
      memset(a_first, a_value, (tl_size)a_count);
    }

    template <typename T_OutputIterator, typename T_Count, typename T_ValueType>
    TL_I void DoFill_n(T_OutputIterator a_first, T_Count a_count, 
                     const T_ValueType& a_value, random_access_iterator_tag)
    {
      // Grabbing a range by adding to a_first and using fill is faster than
      // using two variables in a for loop. This is only possible if the output
      // iterator has a random tag. 
      tloc::core::fill(a_first, a_first + a_count, a_value);
    }

    template <typename T_OutputIterator, typename T_Count, typename T_ValueType>
    TL_I void DoFill_n(T_OutputIterator a_first, T_Count a_count, 
                     const T_ValueType& a_value, input_iterator_tag)
    {
      for (/* */; a_count > 0; --a_count, ++a_first)
      {
        *a_first = a_value;
      }
    }

    template <typename T_InputIterator, typename T>
    T_InputIterator DoFind( T_InputIterator a_rangeBegin,
                            T_InputIterator a_rangeEnd,
                            const T& a_value, IsNotChar )
    {
      TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

      while (a_rangeBegin != a_rangeEnd)
      {
        if (*a_rangeBegin == a_value) break;
        ++a_rangeBegin;
      }

      return a_rangeBegin;
    }

    template <typename T_InputIterator>
    T_InputIterator DoFind( T_InputIterator a_rangeBegin,
                            T_InputIterator a_rangeEnd,
                            const char8& a_value, IsChar )
    {
      TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(a_rangeBegin, a_rangeEnd);

      return (char8*)memchr(a_rangeBegin, a_value, sizeof(char8) *
                            (tl_size)(a_rangeEnd - a_rangeBegin));
    }

    //------------------------------------------------------------------------
    // Sort helpers

    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast, 
                   sort_quicksort_autoselect)
    {
    }

    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast, 
                   sort_quicksort_randompivot)
    {
      const tl_ptrdiff size      = tloc::core::distance(aFirst, aLast);
      const tl_ptrdiff randomPiv = g_defaultRNG.GetRandomInteger(0, 
                                                  (rng_default::int_type)size);

      T_InputIterator randItr = aFirst;
      tloc::core::advance(randItr, randomPiv);

      tlSwap(*aFirst, *randItr);
      DoSort(aFirst, aLast, sort_quicksort_leftpivot() );
    }

    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast, 
                   sort_quicksort_middlepivot)
    {
      const tl_ptrdiff halfSize = tloc::core::distance(aFirst, aLast) / 2;

      T_InputIterator midItr = aFirst;
      tloc::core::advance(midItr, halfSize);

      tlSwap(*aFirst, *midItr);
      DoSort(aFirst, aLast, sort_quicksort_leftpivot() );
    }

    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast, 
                   sort_quicksort_rightpivot)
    {
      // Swap the rightpivot with the left most element. We can then call
      // quicksort_leftpivot
      T_InputIterator rightPivot = aLast;
      --rightPivot;

      tlSwap(*aFirst, *rightPivot);
      DoSort(aFirst, aLast, sort_quicksort_leftpivot() );
    }

    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast, 
                   sort_quicksort_leftpivot)
    {
      typedef Loki::TypeTraits<T_InputIterator> unknown_type;
      typedef Loki::Int2Type<unknown_type::isPointer> pointer_type;

      DoQuicksortLeftPivot(aFirst, aLast, pointer_type());
    }

    template <typename T_InputIterator>
    void DoQuicksortLeftPivot(T_InputIterator aFirst, T_InputIterator aLast, 
                              IsRawItr)
    {
      typedef Loki::TypeTraits<T_InputIterator>::PointeeType value_type;
      DoQuicksort(aFirst, aLast, value_type()); 
    }

    template <typename T_InputIterator>
    void DoQuicksortLeftPivot(T_InputIterator aFirst, T_InputIterator aLast, 
                              IsComplexItr)
    {
      // It is assumed, since the inputer iterator is complex, it has a typedef
      // for value_type. If there is a COMPILE ERROR here then the complex
      // object is either not an iterator OR does not have a value_type typedef
      DoQuicksort(aFirst, aLast, T_InputIterator::value_type());
    }

    template <typename T_InputIterator, typename T_ValueType>
    void DoQuicksort(T_InputIterator aFirst, T_InputIterator aLast, T_ValueType)
    {
      if (aFirst == aLast) { return; }

      T_ValueType pivot = *aFirst;

      T_InputIterator startItr = aFirst;
      T_InputIterator endItr   = aLast--;

      T_InputIterator currItr  = aFirst;

      while (aFirst != aLast)
      {
        if (currItr == aFirst)
        {
          if (*aLast < pivot)
          {
            *aFirst = *aLast;
            ++aFirst;
            currItr = aLast;
          }
          else
          {
            --aLast;
          }
        }
        else
        {
          if (*aFirst > pivot)
          {
            *aLast = *aFirst;
            --aLast;
            currItr = aFirst;
          }
          else
          {
            ++aFirst;
          }
        }
      }

      *aFirst = pivot;
      if (startItr != aFirst) 
      { DoSort(startItr, aFirst, sort_quicksort_leftpivot() ); }
      if (++aLast != endItr)
      { DoSort(aLast, endItr, sort_quicksort_leftpivot() ); }
    }

    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast,
      sort_insertionsort)
    {
      typedef Loki::TypeTraits<T_InputIterator> unknown_type;
      typedef Loki::Int2Type<unknown_type::isPointer> pointer_type;

      DoInsertionsortWithItrType(aFirst, aLast, pointer_type());
    }

    template <typename T_InputIterator>
    void DoInsertionsortWithItrType(T_InputIterator aFirst, T_InputIterator aLast, 
      IsRawItr)
    {
      typedef Loki::TypeTraits<T_InputIterator>::PointeeType value_type;
      DoInsertionsortWithValueType(aFirst,aLast, value_type());
    }

    template <typename T_InputIterator>
    void DoInsertionsortWithItrType(T_InputIterator aFirst, T_InputIterator aLast, 
      IsComplexItr)
    {
      DoInsertionsortWithValueType(aFirst, aLast, T_InputIterator::value_type());
    }

    template <typename T_InputIterator, typename T_ValueType>
    void DoInsertionsortWithValueType(T_InputIterator aFirst, 
                                      T_InputIterator aLast,
                                      T_ValueType)
    {
      if (aFirst != aLast)
      {
        T_InputIterator unsortedItr = aFirst;
        ++unsortedItr;

        T_InputIterator currentItr;
        T_InputIterator currentItrMinusOne;

        T_ValueType currentValue;

        for (/* */; unsortedItr != aLast; ++unsortedItr)
        {
          currentItr = unsortedItr;
          currentValue = *currentItr;

          currentItrMinusOne = currentItr;
          --currentItrMinusOne;
          
          while (currentItr != aFirst 
                 && *currentItrMinusOne > currentValue)
          {
            *currentItr = *currentItrMinusOne;

            currentItr = currentItrMinusOne;
            --currentItrMinusOne;
          }

          *currentItr = currentValue;
        }
      }
    }

    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast, sort_mergesort)
    {
      typedef Loki::TypeTraits<T_InputIterator> unknown_type;
      typedef Loki::Int2Type<unknown_type::isPointer> pointer_type;

      DoMergesortWithItrType(aFirst, aLast, pointer_type());
    }

    template <typename T_InputIterator>
    void DoMergesortWithItrType(T_InputIterator aFirst, T_InputIterator aLast,
                     IsComplexItr)
    {
      DoMergesortWithValueType(aFirst, aLast, T_InputIterator::value_type());
    }

    template <typename T_InputIterator>
    void DoMergesortWithItrType(T_InputIterator aFirst, T_InputIterator aLast,
                     IsRawItr)
    {
      typedef Loki::TypeTraits<T_InputIterator>::PointeeType value_type;

      DoMergesortWithValueType(aFirst, aLast, value_type());
    }

    template <typename T_InputIterator, typename T_ValueType>
    void DoMergesortWithValueType(T_InputIterator aFirst, T_InputIterator aLast,
                     T_ValueType)
    {
      if (aFirst != aLast)
      {
        const tl_ptrdiff size = tloc::core::distance(aFirst, aLast);
        typedef Array<T_ValueType> T_Container;
        T_Container unsortedArray(size);

        tloc::core::copy(aFirst, aLast, unsortedArray.begin());

        T_Container sortedArray = DoMergesort(unsortedArray);
        //unsortedArray = DoMergesort(unsortedArray);

        tloc::core::copy(sortedArray.begin(), sortedArray.end(), aFirst);
        //tloc::core::copy(unsortedArray.begin(), unsortedArray.end(), aFirst);
      }
    }

    template <typename T_Container>
    T_Container DoMergesort(const T_Container& aUnsorted)
    {
      const tl_size size = aUnsorted.size();
      if ((size - 1) != 0)
      {
        TLOC_ASSERT_LOW_LEVEL(size > 1, "Size is <= 1");

        T_Container::const_iterator first = aUnsorted.begin();
        T_Container::const_iterator last = aUnsorted.end();

        tl_size halfSize = size / 2;

        T_Container::const_iterator midItr = first;
        tloc::core::advance(midItr, halfSize);

        T_Container leftSide(halfSize);
        T_Container rightSide(size - halfSize);

        tloc::core::copy(first, midItr, leftSide.begin());
        tloc::core::copy(midItr, last, rightSide.begin());

        T_Container LeftSideSorted = DoMergesort(leftSide);
        T_Container RightSideSorted = DoMergesort(rightSide);

        return DoMerge(LeftSideSorted, RightSideSorted);
      }
      else
      {
        return aUnsorted;
      }
    }

    template <typename T_Container>
    T_Container DoMerge(const T_Container& aLeftFirst, 
                        const T_Container& aRightFirst)
    {
      const T_Container::size_type size = aLeftFirst.size() + aRightFirst.size();
      T_Container mergedContainer(size);

      T_Container::const_iterator leftItr   = aLeftFirst.begin();
      T_Container::const_iterator rightItr  = aRightFirst.begin();
      T_Container::iterator mergedItr       = mergedContainer.begin();

      const T_Container::const_iterator endLeftItr   = aLeftFirst.end();
      const T_Container::const_iterator endRightItr  = aRightFirst.end();

      while ((leftItr != endLeftItr) && (rightItr != endRightItr))
      {
        if (*leftItr < *rightItr)
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

    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast,
                sort_merge_insertionsort)
    {
      if (aFirst != aLast)
      {
        DoMergeInsertionSort(aFirst, aLast);
      }
    }

    template <typename T_InputIterator>
    void DoMergeInsertionSort(T_InputIterator aFirst, T_InputIterator aLast)
    {
      const tl_ptrdiff size = tloc::core::distance(aFirst, aLast);
      if ((size - 1) != 0)
      {
        const tl_ptrdiff halfSize = size / 2;
        T_InputIterator midItr = aFirst;
        tloc::core::advance(midItr, halfSize);

        DoMergeInsertionSort(aFirst, midItr);
        DoMergeInsertionSort(midItr, aLast);
        DoMergeInsertion(aFirst, midItr, aLast);
      }
    }

    template <typename T_InputIterator>
    void DoMergeInsertion(T_InputIterator aLeftFirst,
                          T_InputIterator aRightFirst,
                          T_InputIterator aLast)
    {
      typedef Loki::TypeTraits<T_InputIterator> unknown_type;
      typedef Loki::Int2Type<unknown_type::isPointer> pointer_type;

      for (/* */; aLeftFirst != aRightFirst; ++aLeftFirst)
      {
        if (*aLeftFirst > *aRightFirst)
        {
          tlSwap(*aLeftFirst, *aRightFirst);
          DoSortFirstElementWithItrType(aRightFirst, aLast, pointer_type());
        }
      }
    }

    template <typename T_InputIterator>
    void DoSortFirstElementWithItrType(T_InputIterator aFirst, 
                                       T_InputIterator aLast,
                                       IsComplexItr)
    {
      DoSortFirstElementWithValueType(aFirst, 
                                      aLast, 
                                      T_InputIterator::value_type());
    }

    template <typename T_InputIterator>
    void DoSortFirstElementWithItrType(T_InputIterator aFirst, 
                                       T_InputIterator aLast,
                                       IsRawItr)
    {
      typedef Loki::TypeTraits<T_InputIterator>::PointeeType value_type;

      DoSortFirstElementWithValueType(aFirst, aLast, value_type());
    }

    template <typename T_InputIterator, typename T_ValueType>
    void DoSortFirstElementWithValueType(T_InputIterator aFirst, 
                                         T_InputIterator aLast,
                                         T_ValueType)
    {
      T_ValueType valueToBeSorted = *aFirst;

      T_InputIterator currentItr = aFirst;
      T_InputIterator currentItrPlusOne = currentItr;
      ++currentItrPlusOne;

      while (currentItrPlusOne != aLast && *currentItrPlusOne < valueToBeSorted)
      {
        *currentItr = *currentItrPlusOne;
        ++currentItr;
        ++currentItrPlusOne;
      }

      *currentItr = valueToBeSorted;
    }

    template <typename T_InputIterator>
    void DoSort(T_InputIterator aFirst, T_InputIterator aLast, 
                sort_bubblesort)
    {
      T_InputIterator endOfUnsortedItr;
      T_InputIterator currentItr;
      T_InputIterator currentItrPlusOne;
      
      bool swapped;

      for (endOfUnsortedItr = aLast; endOfUnsortedItr != aFirst; --endOfUnsortedItr)
      {
        currentItr = aFirst;
        currentItrPlusOne = currentItr;
        ++currentItrPlusOne;

        swapped = false;

        for (/* */; 
             currentItrPlusOne != endOfUnsortedItr; 
             currentItr = currentItrPlusOne, ++currentItrPlusOne)
        {
          if (*currentItr > *currentItrPlusOne)
          {
            tlSwap(*currentItr, *currentItrPlusOne);
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
#ifndef TLOC_ALGORITHMS_INL
#define TLOC_ALGORITHMS_INL

#ifndef TLOC_ALGORITHMS_H
#error "Must include header before including the inline file"
#endif

#include "tlocIterator.inl"
#include "tlocPair.inl"
#include "tlocArray.inl"

#include "tlocRandom.h"

namespace tloc { namespace core {

  // TODO: Make all find functions specialized for char* and use memcmp

  //------------------------------------------------------------------------
  // Macros

#define TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(_Begin, _End) \
  TLOC_ASSERT_ALGORITHMS(_Begin <= _End, "Invalid range (aRangeBegin > aRangeEnd)!")

  //------------------------------------------------------------------------
  // Non-modifying sequence operations

  template <typename T_InputIterator, typename T_Function>
  T_Function for_each( T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                       T_Function aFunc )
  {
    typedef Loki::TypeTraits<T_InputIterator> itrType;

    TLOC_STATIC_ASSERT(itrType::isPointer, tlForEach_cannot_be_used_with_non_pointer_iterators);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeBegin, aRangeEnd);

    const tl_size rangeSize = aRangeEnd - aRangeBegin;

    for (u32 i = 0; i < rangeSize; ++i)
    {
      aFunc(*aRangeBegin);
      ++aRangeBegin;
    }

    return aFunc;
  }

  template <typename T_InputIterator, typename T>
  T_InputIterator find( T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                        const T& aValue )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeBegin, aRangeEnd);

    // We assume that the inputs are pointers. If they point to data that is a
    // single byte (a char) then use memset
    typedef Loki::TypeTraits<T_InputIterator>::PointeeType inputDeref;
    typedef Loki::IsSameType<inputDeref, char8> charTestResult;
    typedef Loki::Int2Type<charTestResult::value> IsChar8;

    return detail::find(aRangeBegin, aRangeEnd, aValue, IsChar8());
  }

  template <typename T_InputIterator, typename T_Predicate>
  T_InputIterator find_if( T_InputIterator aRangeBegin,
                           T_InputIterator aRangeEnd, T_Predicate aPred )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeBegin, aRangeEnd);

    while (aRangeBegin != aRangeEnd)
    {
      if (aPred(*aRangeBegin)) break;
      ++aRangeBegin;
    }

    return aRangeBegin;
  }


  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 find_end( T_ForwardIterator1 aRangeToSearchBegin,
                               T_ForwardIterator1 aRangeToSearchEnd,
                               T_ForwardIterator2 aRangeToFindBegin,
                               T_ForwardIterator2 aRangeToFindEnd )
  {
    typedef Loki::TypeTraits<T_ForwardIterator1> itrType;

    TLOC_STATIC_ASSERT(itrType::isPointer, tlFindEnd_cannot_be_used_with_non_pointer_iterators);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToSearchBegin, aRangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToFindBegin, aRangeToFindEnd);

    const tl_size sourceSize = distance(aRangeToSearchBegin, aRangeToSearchEnd);
    const tl_size compareSize = distance(aRangeToFindBegin, aRangeToFindEnd);

    T_ForwardIterator1 retItr = aRangeToSearchEnd;

    if (sourceSize >= compareSize)
    {
      T_ForwardIterator1 sourceItr;
      T_ForwardIterator2 compareItr;
      T_ForwardIterator1 sourceLimit = aRangeToSearchEnd - compareSize + 1;

      while (aRangeToSearchBegin != sourceLimit)
      {
        sourceItr = aRangeToSearchBegin;
        compareItr = aRangeToFindBegin;
        while (compareItr != aRangeToFindEnd)
        {
          if (*sourceItr != *compareItr) { break; }
          ++compareItr;
          ++sourceItr;
        }

        if (compareItr == aRangeToFindEnd)
        {
          retItr = aRangeToSearchBegin;
        }

        ++aRangeToSearchBegin;
      }
    }

    return retItr;
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
    typename T_BinaryPredicate>
  T_ForwardIterator1 find_end( T_ForwardIterator1 aRangeToSearchBegin,
                               T_ForwardIterator1 aRangeToSearchEnd,
                               T_ForwardIterator2 aRangeToFindBegin,
                               T_ForwardIterator2 aRangeToFindEnd,
                               T_BinaryPredicate aPred )
  {
    typedef Loki::TypeTraits<T_ForwardIterator1> itrType;

    TLOC_STATIC_ASSERT(itrType::isPointer, tlFindEnd_cannot_be_used_with_non_pointer_iterators);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToSearchBegin, aRangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToFindBegin, aRangeToFindEnd);

    const tl_size sourceSize = distance(aRangeToSearchBegin, aRangeToSearchEnd);
    const tl_size compareSize = distance(aRangeToFindBegin, aRangeToFindEnd);

    T_ForwardIterator1 retItr = aRangeToSearchEnd;

    if (sourceSize >= compareSize)
    {
      T_ForwardIterator1 sourceItr;
      T_ForwardIterator2 compareItr;
      T_ForwardIterator1 sourceLimit = aRangeToSearchEnd - compareSize + 1;

      while (aRangeToSearchBegin != sourceLimit)
      {
        sourceItr = aRangeToSearchBegin;
        compareItr = aRangeToFindBegin;
        while (compareItr != aRangeToFindEnd)
        {
          if (!aPred(*sourceItr, *compareItr)) { break; }
          ++compareItr;
          ++sourceItr;
        }

        if (compareItr == aRangeToFindEnd)
        {
          retItr = aRangeToSearchBegin;
        }

        ++aRangeToSearchBegin;
      }
    }

    return retItr;
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 find_first_of( T_ForwardIterator1 aRangeToSearchBegin,
                                    T_ForwardIterator1 aRangeToSearchEnd,
                                    T_ForwardIterator2 aRangeToFindBegin,
                                    T_ForwardIterator2 aRangeToFindEnd )
  {
    typedef Loki::TypeTraits<T_ForwardIterator1> itrType;

    TLOC_STATIC_ASSERT(itrType::isPointer, tlFindEnd_cannot_be_used_with_non_pointer_iterators);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToSearchBegin, aRangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToFindBegin, aRangeToFindEnd);

    T_ForwardIterator2 compareItr;

    while (aRangeToSearchBegin != aRangeToSearchEnd)
    {
      compareItr = aRangeToFindBegin;
      while (compareItr != aRangeToFindEnd)
      {
        if (*aRangeToSearchBegin == *compareItr)
        {
          return aRangeToSearchBegin;
        }
        ++compareItr;
      }

      ++aRangeToSearchBegin;
    }

    return aRangeToSearchEnd;
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
  T_ForwardIterator1 find_first_of( T_ForwardIterator1 aRangeToSearchBegin,
                                    T_ForwardIterator1 aRangeToSearchEnd,
                                    T_ForwardIterator2 aRangeToFindBegin,
                                    T_ForwardIterator2 aRangeToFindEnd,
                                    T_BinaryPredicate aPred )
  {
    typedef Loki::TypeTraits<T_ForwardIterator1> itrType;

    TLOC_STATIC_ASSERT(itrType::isPointer, tlFindEnd_cannot_be_used_with_non_pointer_iterators);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToSearchBegin, aRangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToFindBegin, aRangeToFindEnd);

    T_ForwardIterator2 compareItr;

    while (aRangeToSearchBegin != aRangeToSearchEnd)
    {
      compareItr = aRangeToFindBegin;
      while (compareItr != aRangeToFindEnd)
      {
        if (aPred(*aRangeToSearchBegin, *compareItr))
        {
          return aRangeToSearchBegin;
        }
        ++compareItr;
      }

      ++aRangeToSearchBegin;
    }

    return aRangeToSearchEnd;
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 find_first_not_of( T_ForwardIterator1 aRangeToSearchBegin,
                                        T_ForwardIterator1 aRangeToSearchEnd,
                                        T_ForwardIterator2 aRangeToFindBegin,
                                        T_ForwardIterator2 aRangeToFindEnd )
  {
    typedef Loki::TypeTraits<T_ForwardIterator1> itrType;

    TLOC_STATIC_ASSERT(itrType::isPointer, tlFindEnd_cannot_be_used_with_non_pointer_iterators);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToSearchBegin, aRangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToFindBegin, aRangeToFindEnd);

    T_ForwardIterator2 compareItr;

    while (aRangeToSearchBegin != aRangeToSearchEnd)
    {
      compareItr = aRangeToFindBegin;

      while (compareItr != aRangeToFindEnd)
      {
        if (*compareItr == *aRangeToSearchBegin) { break; }

        ++compareItr;
      }

      if (compareItr == aRangeToFindEnd)
      {
        return aRangeToSearchBegin;
      }

      ++aRangeToSearchBegin;
    }

    return aRangeToSearchEnd;
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
  T_ForwardIterator1 find_first_not_of( T_ForwardIterator1 aRangeToSearchBegin,
                                        T_ForwardIterator1 aRangeToSearchEnd,
                                        T_ForwardIterator2 aRangeToFindBegin,
                                        T_ForwardIterator2 aRangeToFindEnd,
                                        T_BinaryPredicate aPred )
  {
    typedef Loki::TypeTraits<T_ForwardIterator1> itrType;

    TLOC_STATIC_ASSERT(itrType::isPointer, tlFindEnd_cannot_be_used_with_non_pointer_iterators);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToSearchBegin, aRangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToFindBegin, aRangeToFindEnd);

    T_ForwardIterator2 compareItr;

    while (aRangeToSearchBegin != aRangeToSearchEnd)
    {
      compareItr = aRangeToFindBegin;

      while (compareItr != aRangeToFindEnd)
      {
        if (aPred(*compareItr, *aRangeToSearchBegin)) { break; }

        ++compareItr;
      }

      if (compareItr == aRangeToFindEnd)
      {
        return aRangeToSearchBegin;
      }

      ++aRangeToSearchBegin;
    }

    return aRangeToSearchEnd;
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 find_last_not_of( T_ForwardIterator1 aRangeToSearchBegin,
                                       T_ForwardIterator1 aRangeToSearchEnd,
                                       T_ForwardIterator2 aRangeToFindBegin,
                                       T_ForwardIterator2 aRangeToFindEnd )
  {
    typedef Loki::TypeTraits<T_ForwardIterator1> itrType;

    TLOC_STATIC_ASSERT(itrType::isPointer, tlFindEnd_cannot_be_used_with_non_pointer_iterators);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToSearchBegin, aRangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToFindBegin, aRangeToFindEnd);

    const tl_size searchSize = distance(aRangeToSearchBegin, aRangeToSearchEnd);
    const tl_size findSize = distance(aRangeToFindBegin, aRangeToFindEnd);

    T_ForwardIterator1 ret = aRangeToSearchEnd;

    if (findSize > 0)
    {
      for (u32 i = 0; i < searchSize; ++i)
      {
        u32 j = 0;
        for (; j < findSize; ++j)
        {
          if ( *(aRangeToSearchBegin + i) == *(aRangeToFindBegin + j))
          {
            break;
          }
        }

        if (j == findSize)
        {
          ret = aRangeToSearchBegin + i;
        }
      }
    }

    return ret;
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
    typename T_BinaryPredicate>
    T_ForwardIterator1 find_last_not_of( T_ForwardIterator1 aRangeToSearchBegin,
                                         T_ForwardIterator1 aRangeToSearchEnd,
                                         T_ForwardIterator2 aRangeToFindBegin,
                                         T_ForwardIterator2 aRangeToFindEnd,
                                         T_BinaryPredicate aPred )
  {
    typedef Loki::TypeTraits<T_ForwardIterator1> itrType;

    TLOC_STATIC_ASSERT(itrType::isPointer, tlFindEnd_cannot_be_used_with_non_pointer_iterators);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToSearchBegin, aRangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToFindBegin, aRangeToFindEnd);

    const tl_size searchSize = distance(aRangeToSearchBegin, aRangeToSearchEnd);
    const tl_size findSize = distance(aRangeToFindBegin, aRangeToFindEnd);

    T_ForwardIterator1 ret = aRangeToSearchEnd;

    if (findSize > 0)
    {
      for (u32 i = 0; i < searchSize; ++i)
      {
        u32 j = 0;
        for (; j < findSize; ++j)
        {
          if ( aPred(*(aRangeToSearchBegin + i), *(aRangeToFindBegin + j)) )
          {
            break;
          }
        }

        if (j == findSize)
        {
          ret = aRangeToSearchBegin + i;
        }
      }
    }

    return ret;
  }

  template <typename T_InputIterator, typename T>
  tl_size count( T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                 const T& aValue )
  {
    typedef Loki::TypeTraits<T_InputIterator> itrType;

    TLOC_STATIC_ASSERT(itrType::isPointer, tlFindEnd_cannot_be_used_with_non_pointer_iterators);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeBegin, aRangeEnd);

    const tl_size rangeSize = aRangeEnd - aRangeBegin;
    tl_size count = 0;

    for (u32 i = 0; i < rangeSize; ++i)
    {
      if (aRangeBegin[i] == aValue) ++count;
    }

    return count;
  }

  template <typename T_InputIterator, typename T_Predicate>
  tl_size count_if( T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                    T_Predicate aPred )
  {
    typedef Loki::TypeTraits<T_InputIterator> itrType;

    TLOC_STATIC_ASSERT(itrType::isPointer, tlFindEnd_cannot_be_used_with_non_pointer_iterators);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeBegin, aRangeEnd);

    const tl_size rangeSize = aRangeEnd - aRangeBegin;
    tl_size count = 0;

    for (u32 i = 0; i < rangeSize; ++i)
    {
      if (aPred(aRangeBegin[i])) ++count;
    }

    return count;
  }

  template <typename T_InputIterator1, typename T_InputIterator2>
  Pair<T_InputIterator1, T_InputIterator2>
    mismatch( T_InputIterator1 aRangeBegin, T_InputIterator1 aRangeEnd,
              T_InputIterator2 aRangeToCompare )
  {
    typedef Loki::TypeTraits<T_InputIterator1> itrType;

    TLOC_STATIC_ASSERT(itrType::isPointer, tlFindEnd_cannot_be_used_with_non_pointer_iterators);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeBegin, aRangeEnd);

    while (aRangeBegin != aRangeEnd)
    {
      if (*aRangeBegin != *aRangeToCompare)
        break;

      ++aRangeBegin;
      ++aRangeToCompare;
    }

    return MakePair(aRangeBegin, aRangeToCompare);
  }

  template <typename T_InputIterator1, typename T_InputIterator2, typename T_BinaryPred>
  Pair<T_InputIterator1, T_InputIterator2>
    mismatch( T_InputIterator1 aRangeBegin, T_InputIterator1 aRangeEnd,
              T_InputIterator2 aRangeToCompare, T_BinaryPred aPred )
  {
    typedef Loki::TypeTraits<T_InputIterator1> itrType;

    TLOC_STATIC_ASSERT(itrType::isPointer, tlFindEnd_cannot_be_used_with_non_pointer_iterators);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeBegin, aRangeEnd);

    while (aRangeBegin != aRangeEnd)
    {
      if (!aPred(*aRangeBegin,*aRangeToCompare))
        break;

      ++aRangeBegin;
      ++aRangeToCompare;
    }

    return MakePair(aRangeBegin, aRangeToCompare);
  }

  template <typename T_InputIterator1, typename T_InputIterator2>
  bool equal( T_InputIterator1 aRangeBegin, T_InputIterator1 aRangeEnd,
              T_InputIterator2 aRangeToCompare )
  {
    typedef Loki::TypeTraits<T_InputIterator1> itrType;

    TLOC_STATIC_ASSERT(itrType::isPointer, tlFindEnd_cannot_be_used_with_non_pointer_iterators);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeBegin, aRangeEnd);

    while (aRangeBegin != aRangeEnd)
    {
      if (*aRangeBegin != *aRangeToCompare) { return false; }

      ++aRangeBegin;
      ++aRangeToCompare;
    }

    return true;
  }

  template <typename T_InputIterator1, typename T_InputIterator2,
            typename T_BinaryPred>
  bool equal( T_InputIterator1 aRangeBegin, T_InputIterator1 aRangeEnd,
              T_InputIterator2 aRangeToCompare, T_BinaryPred aPred )
  {
    typedef Loki::TypeTraits<T_InputIterator1> itrType;

    TLOC_STATIC_ASSERT(itrType::isPointer, tlFindEnd_cannot_be_used_with_non_pointer_iterators);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeBegin, aRangeEnd);

    while (aRangeBegin != aRangeEnd)
    {
      if (!aPred(*aRangeBegin,*aRangeToCompare)) { return false; }

      ++aRangeBegin;
      ++aRangeToCompare;
    }

    return true;
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 search( T_ForwardIterator1 aRangeToSearchBegin,
                             T_ForwardIterator1 aRangeToSearchEnd,
                             T_ForwardIterator2 aRangeToFindBegin,
                             T_ForwardIterator2 aRangeToFindEnd )
  {
    typedef Loki::TypeTraits<T_ForwardIterator1> itrType;

    TLOC_STATIC_ASSERT(itrType::isPointer, tlFindEnd_cannot_be_used_with_non_pointer_iterators);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToSearchBegin, aRangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToFindBegin, aRangeToFindEnd);

    const tl_size sourceSize = distance(aRangeToSearchBegin, aRangeToSearchEnd);
    const tl_size compareSize = distance(aRangeToFindBegin, aRangeToFindEnd);
    T_ForwardIterator1 sourceLimit = aRangeToSearchEnd - compareSize + 1;

    T_ForwardIterator1 sourceItr;
    T_ForwardIterator2 compareItr;

    if (sourceSize >= compareSize)
    {
      while (aRangeToSearchBegin != sourceLimit)
      {
        sourceItr = aRangeToSearchBegin;
        compareItr = aRangeToFindBegin;
        while (compareItr != aRangeToFindEnd)
        {
          if (*sourceItr != *compareItr) { break; }
          ++sourceItr;
          ++compareItr;
        }

        if (compareItr == aRangeToFindEnd)
        {
          return aRangeToSearchBegin;
        }

        ++aRangeToSearchBegin;
      }
    }

    return aRangeToSearchEnd;
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
    T_ForwardIterator1 search( T_ForwardIterator1 aRangeToSearchBegin,
                               T_ForwardIterator1 aRangeToSearchEnd,
                               T_ForwardIterator2 aRangeToFindBegin,
                               T_ForwardIterator2 aRangeToFindEnd,
                               T_BinaryPredicate aPred )
  {
    typedef Loki::TypeTraits<T_ForwardIterator1> itrType;

    TLOC_STATIC_ASSERT(itrType::isPointer, tlFindEnd_cannot_be_used_with_non_pointer_iterators);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToSearchBegin, aRangeToSearchEnd);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToFindBegin, aRangeToFindEnd);

    const tl_size sourceSize = distance(aRangeToSearchBegin, aRangeToSearchEnd);
    const tl_size compareSize = distance(aRangeToFindBegin, aRangeToFindEnd);
    T_ForwardIterator1 sourceLimit = aRangeToSearchEnd - compareSize + 1;

    T_ForwardIterator1 sourceItr;
    T_ForwardIterator2 compareItr;

    if (sourceSize >= compareSize)
    {
      while (aRangeToSearchBegin != sourceLimit)
      {
        sourceItr = aRangeToSearchBegin;
        compareItr = aRangeToFindBegin;
        while (compareItr != aRangeToFindEnd)
        {
          if (!aPred(*sourceItr, *compareItr)) { break; }
          ++sourceItr;
          ++compareItr;
        }

        if (compareItr == aRangeToFindEnd)
        {
          return aRangeToSearchBegin;
        }

        ++aRangeToSearchBegin;
      }
    }

    return aRangeToSearchEnd;
  }

  template <typename T_ForwardIterator, typename T_Size, typename T>
  T_ForwardIterator search_n( T_ForwardIterator aRangeToSearchBegin,
                              T_ForwardIterator aRangeToSearchEnd,
                              T_Size aCount, const T& aValue )
  {
    typedef Loki::TypeTraits<T_ForwardIterator> itrType;

    TLOC_STATIC_ASSERT(itrType::isPointer, tlFindEnd_cannot_be_used_with_non_pointer_iterators);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToSearchBegin, aRangeToSearchEnd);

    const tl_size sourceSize = distance(aRangeToSearchBegin, aRangeToSearchEnd);

    if (sourceSize >= (tl_size)aCount)
    {
      T_ForwardIterator sourceLimit = aRangeToSearchEnd - aCount + 1;

      T_ForwardIterator retItr = aRangeToSearchEnd;
      T_ForwardIterator retItrEnd;

      while(aRangeToSearchBegin != sourceLimit)
      {
        retItr = aRangeToSearchBegin;
        retItrEnd = aRangeToSearchBegin + aCount;
        while (retItr != retItrEnd)
        {
          if (*retItr != aValue) { break; }
          ++retItr;
        }

        if (retItr == retItrEnd)
        {
          return aRangeToSearchBegin;
        }

        ++aRangeToSearchBegin;
      }
    }

    return aRangeToSearchEnd;
  }

  template <typename T_ForwardIterator, typename T_Size, typename T,
            typename T_BinaryPred>
    T_ForwardIterator search_n( T_ForwardIterator aRangeToSearchBegin,
                                T_ForwardIterator aRangeToSearchEnd,
                                T_Size aCount, const T& aValue,
                                T_BinaryPred aPred )
  {
    typedef Loki::TypeTraits<T_ForwardIterator> itrType;

    TLOC_STATIC_ASSERT(itrType::isPointer, tlFindEnd_cannot_be_used_with_non_pointer_iterators);
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeToSearchBegin, aRangeToSearchEnd);

    const tl_size sourceSize = distance(aRangeToSearchBegin, aRangeToSearchEnd);

    if (sourceSize >= (tl_size)aCount)
    {
      T_ForwardIterator sourceLimit = aRangeToSearchEnd - aCount + 1;

      T_ForwardIterator retItr = aRangeToSearchEnd;
      T_ForwardIterator retItrEnd;

      while(aRangeToSearchBegin != sourceLimit)
      {
        retItr = aRangeToSearchBegin;
        retItrEnd = aRangeToSearchBegin + aCount;
        while (retItr != retItrEnd)
        {
          if (!aPred(*retItr, aValue) ) { break; }
          ++retItr;
        }

        if (retItr == retItrEnd)
        {
          return aRangeToSearchBegin;
        }

        ++aRangeToSearchBegin;
      }
    }

    return aRangeToSearchEnd;
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
  TL_I T_OutputIterator copy(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                             T_OutputIterator aDestRangeBegin)
  {
    // We assume that the inputs are pointers. We can then find out whether they
    // are integral pointers or complex
    typedef Loki::TypeTraits<T_InputIterator>::PointeeType inputDeref;
    typedef Loki::TypeTraits<T_OutputIterator>::PointeeType outputDeref;
    typedef Loki::TypeTraits<inputDeref> inputUnknown;
    typedef Loki::TypeTraits<outputDeref> outputUknown;
    typedef Loki::Int2Type<inputUnknown::isArith && outputUknown::isArith> inputArith;

    return detail::copy(aRangeBegin, aRangeEnd, aDestRangeBegin, inputArith());
  }

  template <typename T_InputIterator, typename T_OutputIterator>
  TL_I T_OutputIterator copy_backward(T_InputIterator aRangeBegin,
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
      --aDestRangeEnd;
      --aRangeEnd;
      *(aDestRangeEnd) = *(aRangeEnd);
    }

    return aDestRangeEnd;
  }

  template <typename T_InputIterator, typename T>
  TL_I void fill(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                 const T& aValue)
  {
    // We assume that the inputs are pointers. If they point to data that is a
    // single byte (a char) then use memset
    typedef Loki::TypeTraits<T_InputIterator>::PointeeType inputDeref;
    typedef Loki::IsSameType<inputDeref, char8> charTestResult;
    typedef Loki::Int2Type<charTestResult::value> IsChar8;

    detail::fill(aRangeBegin, aRangeEnd, aValue, IsChar8());

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
    // Copy() helpers

    template <typename T_InputIterator, typename T_OutputIterator>
    TL_I T_OutputIterator copy(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                               T_OutputIterator aDestRangeBegin, IsNotArith)
    {
      while (aRangeBegin != aRangeEnd)
      {
        *(aDestRangeBegin++) = *(aRangeBegin++);
      }

      return aDestRangeBegin;
    }

    template <typename T_InputIterator, typename T_OutputIterator>
    TL_I T_OutputIterator copy(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                               T_OutputIterator aDestRangeBegin, IsArith)
    {
      // We need the size of what the pointer is pointing to, not the pointer
      // itself
      typedef Loki::TypeTraits<T_InputIterator>::PointeeType inputDeref;

      tl_size rangeSize = aRangeEnd - aRangeBegin;
      memmove( aDestRangeBegin, aRangeBegin,
        (tl_size)(rangeSize) * sizeof(inputDeref) );
      return aDestRangeBegin + rangeSize;
    }

    //------------------------------------------------------------------------
    // Fill helpers

    template <typename T_InputIterator, typename T>
    TL_I void fill( T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                    const T& aValue, IsNotChar )
    {
      while (aRangeBegin != aRangeEnd)
      {
        *aRangeBegin = aValue;
        ++aRangeBegin;
      }
    }

    template <typename T_InputIterator, typename T>
    TL_I void fill( T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                    const T& aValue, IsChar )
    {
      memset(aRangeBegin, aValue, sizeof(T) * (aRangeEnd - aRangeBegin));
    }

    template <typename T_InputIterator, typename T>
    T_InputIterator find( T_InputIterator aRangeBegin,
                          T_InputIterator aRangeEnd,
                          const T& aValue, IsNotChar )
    {
      TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeBegin, aRangeEnd);

      while (aRangeBegin != aRangeEnd)
      {
        if (*aRangeBegin == aValue) break;
        ++aRangeBegin;
      }

      return aRangeBegin;
    }

    template <typename T_InputIterator>
    T_InputIterator find( T_InputIterator aRangeBegin,
                          T_InputIterator aRangeEnd,
                          const char8& aValue, IsChar )
    {
      TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeBegin, aRangeEnd);

      return (char8*)memchr(aRangeBegin, aValue, sizeof(char8) *
                            (tl_size)(aRangeEnd - aRangeBegin));
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
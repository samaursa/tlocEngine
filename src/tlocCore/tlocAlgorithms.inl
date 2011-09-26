namespace tloc
{
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

    const tl_size sourceSize = tlDistance(aRangeToSearchBegin, aRangeToSearchEnd);
    const tl_size compareSize = tlDistance(aRangeToFindBegin, aRangeToFindEnd);

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

    const tl_size sourceSize = tlDistance(aRangeToSearchBegin, aRangeToSearchEnd);
    const tl_size compareSize = tlDistance(aRangeToFindBegin, aRangeToFindEnd);

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

    const tl_size searchSize = tlDistance(aRangeToSearchBegin, aRangeToSearchEnd);
    const tl_size findSize = tlDistance(aRangeToFindBegin, aRangeToFindEnd);

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

    const tl_size searchSize = tlDistance(aRangeToSearchBegin, aRangeToSearchEnd);
    const tl_size findSize = tlDistance(aRangeToFindBegin, aRangeToFindEnd);

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

    const tl_size sourceSize = tlDistance(aRangeToSearchBegin, aRangeToSearchEnd);
    const tl_size compareSize = tlDistance(aRangeToFindBegin, aRangeToFindEnd);
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

    const tl_size sourceSize = tlDistance(aRangeToSearchBegin, aRangeToSearchEnd);
    const tl_size compareSize = tlDistance(aRangeToFindBegin, aRangeToFindEnd);
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

    const tl_size sourceSize = tlDistance(aRangeToSearchBegin, aRangeToSearchEnd);

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

    const tl_size sourceSize = tlDistance(aRangeToSearchBegin, aRangeToSearchEnd);

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
  // Min / Max

  template <typename T>
  TL_I const T& min(const T& a, const T& b)
  {
    return a < b ? a : b;
  }

  template <typename T>
  TL_I const T& tlMax(const T& a, const T& b)
  {
    return a < b ? b : a;
  }

  template <typename T>
  TL_I void swap(T& a, T& b)
  {
    T c(a); a = b; b = c;
  }

  //------------------------------------------------------------------------
  // Modifying sequence operations

  template <typename T_InputIterator, typename T_OutputIterator>
  TL_I T_OutputIterator copy(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                             T_OutputIterator aDestRangeBegin)
  {
    TLOC_ASSERT_ALGORITHMS(aDestRangeBegin < aRangeBegin || aDestRangeBegin > aRangeEnd,
      "Output iterator is within the begin/end range (data over-writing)! - "
      L"Try Copy_Backward");
    TLOC_ASSERT_ALGORITHMS(aRangeBegin <= aRangeEnd,
      "aRangeBegin > aRangeEnd (infinite loop)!");

    // We assume that the inputs are pointers. We can then find out whether they
    // are integral pointers or complex
    typedef Loki::TypeTraits<T_InputIterator>::PointeeType inputDeref;
    typedef Loki::TypeTraits<inputDeref> inputUnknown;
    typedef Loki::Int2Type<inputUnknown::isArith> inputArith;

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
  }
}
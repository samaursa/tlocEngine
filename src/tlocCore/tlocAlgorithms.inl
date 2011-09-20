namespace tloc
{
  //------------------------------------------------------------------------
  // Macros

#define TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(_Begin, _End) \
  TLOC_ASSERT_ALGORITHMS(aRangeBegin <= aRangeEnd, "Invalid range (aRangeBegin > aRangeEnd)!")

  //------------------------------------------------------------------------
  // Non-modifying sequence operations

  template <typename T_InputIterator, typename T_Function>
  T_Function tlForEach( T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
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
  T_InputIterator tlFind( T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                          const T& aValue )
  {
    TLOC_ASSERT_ALGORITHMS_VERIFY_RANGE(aRangeBegin, aRangeEnd);

    while (aRangeBegin != aRangeEnd)
    {
      if (*aRangeBegin == aValue) break;
      ++aRangeBegin;
    }

    return aRangeBegin;
  }

  template <typename T_InputIterator, typename T_Predicate>
  T_InputIterator tlFindIf( T_InputIterator aRangeBegin,
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
  T_ForwardIterator1 tlFindEnd( T_ForwardIterator1 aRangeToSearchBegin,
                                T_ForwardIterator1 aRangeToSearchEnd,
                                T_ForwardIterator2 aRangeToFindBegin,
                                T_ForwardIterator2 aRangeToFindEnd )
  {
    TLOC_ASSERT_WIP();
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
    typename T_BinaryPredicate>
    T_ForwardIterator1 tlFindEnd( T_ForwardIterator1 aRangeToSearchBegin,
                                  T_ForwardIterator1 aRangeToSearchEnd,
                                  T_ForwardIterator2 aRangeToFindBegin,
                                  T_ForwardIterator2 aRangeToFindEnd,
                                  T_BinaryPredicate aPred )
  {
    TLOC_ASSERT_WIP();
  }

  template <typename T_InputIterator, typename T>
  tl_ptrdiff tlCount( T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                      const T& aValue )
  {
    TLOC_ASSERT_WIP();
  }

  template <typename T_InputIterator, typename T_Predicate>
  tl_ptrdiff tlCountIf( T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                        T_Predicate aPred )
  {
    TLOC_ASSERT_WIP();
  }

  template <typename T_InputIterator1, typename T_InputIterator2>
  Pair<T_InputIterator1, T_InputIterator2>
    tlMismatch( T_InputIterator1 aRangeBegin, T_InputIterator1 aRangeEnd,
                T_InputIterator2 aRangeToCompare )
  {
    TLOC_ASSERT_WIP();
  }

  template <typename T_InputIterator1, typename T_InputIterator2, typename T_BinaryPred>
  Pair<T_InputIterator1, T_InputIterator2>
    tlMismatch( T_InputIterator1 aRangeBegin, T_InputIterator1 aRangeEnd,
                T_InputIterator2 aRangeToCompare, T_BinaryPred aPred )
  {
    TLOC_ASSERT_WIP();
  }

  template <typename T_InputIterator1, typename T_InputIterator2>
  bool tlEqual( T_InputIterator1 aRangeBegin, T_InputIterator1 aRangeEnd,
                T_InputIterator2 aRangeToCompare )
  {
    TLOC_ASSERT_WIP();
  }

  template <typename T_InputIterator1, typename T_InputIterator2,
            typename T_BinaryPred>
  bool tlEqual( T_InputIterator1 aRangeBegin, T_InputIterator1 aRangeEnd,
                T_InputIterator2 aRangeToCompare, T_BinaryPred aPred )
  {
    TLOC_ASSERT_WIP();
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2>
  T_ForwardIterator1 tlSearch( T_ForwardIterator1 aRangeToSearchBegin,
                               T_ForwardIterator1 aRangeToSearchEnd,
                               T_ForwardIterator2 aRangeToFindBegin,
                               T_ForwardIterator2 aRangeToFindEnd )
  {
    TLOC_ASSERT_WIP();
  }

  template <typename T_ForwardIterator1, typename T_ForwardIterator2,
            typename T_BinaryPredicate>
    T_ForwardIterator1 tlSearch( T_ForwardIterator1 aRangeToSearchBegin,
                                 T_ForwardIterator1 aRangeToSearchEnd,
                                 T_ForwardIterator2 aRangeToFindBegin,
                                 T_ForwardIterator2 aRangeToFindEnd,
                                 T_BinaryPredicate aPred )
  {
    TLOC_ASSERT_WIP();
  }

  template <typename T_ForwardIterator, typename T_Size, typename T>
  T_ForwardIterator tlSearchN( T_ForwardIterator aRangeToSearchBegin,
                               T_ForwardIterator aRangeToSearchEnd,
                               T_Size aCount, const T& aValue )
  {
    TLOC_ASSERT_WIP();
  }

  template <typename T_ForwardIterator, typename T_Size, typename T,
            typename T_BinaryPred>
    T_ForwardIterator tlSearchN( T_ForwardIterator aRangeToSearchBegin,
                                 T_ForwardIterator aRangeToSearchEnd,
                                 T_Size aCount, const T& aValue,
                                 T_BinaryPred aPred )
  {
    TLOC_ASSERT_WIP();
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

  template <typename T>
  TL_I void tlSwap(T& a, T& b)
  {
    T c(a); a = b; b = c;
  }

  //------------------------------------------------------------------------
  // Modifying sequence operations

  template <typename T_InputIterator, typename T_OutputIterator>
  TL_I T_OutputIterator tlCopy(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
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

    return detail::tlCopy(aRangeBegin, aRangeEnd, aDestRangeBegin, inputArith());
  }

  template <typename T_InputIterator, typename T_OutputIterator>
  TL_I T_OutputIterator tlCopy_Backward(T_InputIterator aRangeBegin,
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
  TL_I void tlFill(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                   const T& aValue)
  {
    // We assume that the inputs are pointers. If they point to data that is a
    // single byte (a char) then use memset
    typedef Loki::TypeTraits<T_InputIterator>::PointeeType inputDeref;
    typedef detail::CharTest<inputDeref>::result CharTestResult;

    detail::tlFill(aRangeBegin, aRangeEnd, aValue, CharTestResult());

  }

  //////////////////////////////////////////////////////////////////////////
  // Internal use only

  namespace detail
  {
    //------------------------------------------------------------------------
    // Copy() helpers

    template <typename T_InputIterator, typename T_OutputIterator>
    TL_I T_OutputIterator tlCopy(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                                 T_OutputIterator aDestRangeBegin, IsNotArith)
    {
      while (aRangeBegin != aRangeEnd)
      {
        *(aDestRangeBegin++) = *(aRangeBegin++);
      }

      return aDestRangeBegin;
    }

    template <typename T_InputIterator, typename T_OutputIterator>
    TL_I T_OutputIterator tlCopy(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
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
    TL_I void tlFill( T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                      const T& aValue, IsNotChar )
    {
      while (aRangeBegin != aRangeEnd)
      {
        *aRangeBegin = aValue;
        ++aRangeBegin;
      }
    }

    template <typename T_InputIterator, typename T>
    TL_I void tlFill( T_InputIterator aRangeBegin, T_InputIterator aRangeEnd,
                      const T& aValue, IsChar )
    {
      memset(aRangeBegin, aValue, sizeof(T) * (aRangeEnd - aRangeBegin));
    }
  }
}
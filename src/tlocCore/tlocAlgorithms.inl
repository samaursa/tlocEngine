namespace tloc
{
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
namespace tloc
{
  template <typename T_InputItr>
  TL_FI tl_size distance( T_InputItr aBegin, T_InputItr aEnd )
  {
    typedef Loki::TypeTraits<T_InputItr>   itrType;
    typedef Loki::Int2Type<itrType::isPointer>  itrTypeSelect;

    return detail::distance(aBegin, aEnd, itrTypeSelect());
  }


  template <typename T_InputItr, typename T_Distance>
  TL_FI void advance( T_InputItr aItr, T_Distance aN )
  {
    typedef typename iterator_traits<T_InputItr>::iterator_category itrCat;

    detail::advance(aItr, aN, itrCat());
  }

  //////////////////////////////////////////////////////////////////////////
  // Detail

  namespace detail
  {
    template <typename T_InputItr>
    TL_FI tl_size distance(T_InputItr aBegin, T_InputItr aEnd, IsPtrItr)
    {
      return (tl_size)(aEnd - aBegin);
    }

    template <typename T_InputItr>
    TL_FI tl_size distance(T_InputItr aBegin, T_InputItr aEnd, IsComplexItr)
    {
      TLOC_ASSERT_WIP();
    }

    template <typename T_InputItr, typename T_Distance>
    TL_FI void advance( T_InputItr aItr, T_Distance aN, input_iterator_tag )
    {
      TLOC_ASSERT_ITERATOR(aN >= 0,
        "Iterator can only advance in the positive direction!");

      while (aN) { ++aItr; --aN; }
    }

    template <typename T_InputItr, typename T_Distance>
    TL_FI void advance( T_InputItr aItr, T_Distance aN, bidirectional_iterator_tag )
    {
      if (n > 0)
      {
        while (aN) { ++aItr; --aN; }
      }
      else
      {
        while (aN) { ++aItr; ++aN; }
      }
    }

    template <typename T_InputItr, typename T_Distance>
    TL_FI void advance( T_InputItr aItr, T_Distance aN, random_access_iterator_tag )
    {
      aItr = aItr + aN;
    }
  };
};
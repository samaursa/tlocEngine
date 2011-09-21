namespace tloc
{
  template <typename T_InputItr>
  tl_size tlDistance( T_InputItr aBegin, T_InputItr aEnd )
  {
    typedef Loki::TypeTraits<T_InputItr>   itrType;
    typedef Loki::Int2Type<itrType::isPointer>  itrTypeSelect;

    return detail::tlDistance(aBegin, aEnd, itrTypeSelect());
  }

  namespace detail
  {
    template <typename T_InputItr>
    tl_size tlDistance(T_InputItr aBegin, T_InputItr aEnd, IsPtrItr)
    {
      return (tl_size)(aEnd - aBegin);
    }

    template <typename T_InputItr>
    tl_size tlDistance(T_InputItr aBegin, T_InputItr aEnd, IsComplexItr)
    {
      TLOC_ASSERT_WIP();
    }
  };
};
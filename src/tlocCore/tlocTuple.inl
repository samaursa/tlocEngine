namespace tloc
{

  //////////////////////////////////////////////////////////////////////////
  // Tuple<N>

  //------------------------------------------------------------------------
  // Macros

#define ITERATE_TUPLE for (u32 i = 0; i < T_Size; ++i)

  //------------------------------------------------------------------------
  // Constructors

  template <typename T, u32 T_Size>
  TL_FI Tuple<T, T_Size>::Tuple()
  {
  }

  template <typename T, u32 T_Size>
  TL_FI Tuple<T, T_Size>::Tuple(const Tuple<T, T_Size>& aTuple)
  {
    operator=(aTuple);
  }

  template <typename T, u32 T_Size>
  TL_FI Tuple<T, T_Size>::Tuple(const T& aValue)
  {
    Set(aValue);
  }

  //------------------------------------------------------------------------
  // Accessors

  template <typename T, u32 T_Size>
  TL_FI T& Tuple<T, T_Size>::operator [](s32 aIndex)
  {
    TLOC_ASSERT_LOW_LEVEL(aIndex < T_Size, "Index is out of bounds!");

    return m_values[aIndex];
  }

  template <typename T, u32 T_Size>
  TL_FI const T& Tuple<T, T_Size>::operator [](s32 aIndex) const
  {
    TLOC_ASSERT_LOW_LEVEL(aIndex < T_Size, "Index is out of bounds!");

    return m_values[aIndex];
  }

  template <typename T, u32 T_Size>
  TL_FI T& Tuple<T, T_Size>::Get(u32 aIndex)
  {
    TLOC_ASSERT_LOW_LEVEL(aIndex < T_Size, "Index is out of bounds!");

    return m_values[aIndex];
  }

  template <typename T, u32 T_Size>
  TL_FI const T& Tuple<T, T_Size>::Get(u32 aIndex) const
  {
    TLOC_ASSERT_LOW_LEVEL(aIndex < T_Size, "Index is out of bounds!");

    return m_values[aIndex];
  }

  template <typename T, u32 T_Size>
  TL_FI Tuple<T, T_Size>::operator T*()
  {
    return m_values;
  }

  template <typename T, u32 T_Size>
  TL_FI Tuple<T, T_Size>::operator const T*() const
  {
    return m_values;
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <typename T, u32 T_Size>
  void Tuple<T, T_Size>::Set(T aValue)
  {
    ITERATE_TUPLE
    {
      m_values[i] = aValue;
    }
  }

  template <typename T, u32 T_Size>
  void Tuple<T, T_Size>::Swap(Tuple<T, T_Size>& aVector)
  {
    ITERATE_TUPLE
    {
      tloc::Swap(m_values[i], aVector[i]);
    }
  }

  //------------------------------------------------------------------------
  // Operators

  template <typename T, u32 T_Size>
  TL_FI Tuple<T, T_Size>& Tuple<T, T_Size>::operator = (const Tuple<T, T_Size>& aTuple)
  {
    ITERATE_TUPLE
    {
      m_values[i] = aTuple[i];
    }

    return *this;
  }

  template <typename T, u32 T_Size>
  TL_FI bool tloc::Tuple<T, T_Size>::operator==( const Tuple<T, T_Size>& aTuple )
  {
    ITERATE_TUPLE
    {
      if (m_values[i] != aTuple[i]) { return false; }
    }

    return true;
  }

  template <typename T, u32 T_Size>
  TL_FI bool tloc::Tuple<T, T_Size>::operator!=( const Tuple<T, T_Size>& aTuple )
  {
    return !operator==(aTuple);
  }

};
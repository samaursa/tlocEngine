//////////////////////////////////////////////////////////////////////////
// Tuple<N>

//------------------------------------------------------------------------
// Macros

#define ITERATE_TUPLE for (u32 i = 0; i < T_SIZE; ++i)

//------------------------------------------------------------------------
// Constructors

template <typename T, u32 T_SIZE>
TL_FI Tuple<T, T_SIZE>::Tuple()
{
}

template <typename T, u32 T_SIZE>
TL_FI Tuple<T, T_SIZE>::Tuple(const Tuple<T, T_SIZE>& aTuple)
{
  operator=(aTuple);
}

template <typename T, u32 T_SIZE>
TL_FI Tuple<T, T_SIZE>::Tuple(const T& aValue)
{
  Set(aValue);
}

//------------------------------------------------------------------------
// Accessors

template <typename T, u32 T_SIZE>
TL_FI T& Tuple<T, T_SIZE>::operator [](s32 aIndex)
{
  TLOC_ASSERT_LOW_LEVEL(aIndex < T_SIZE, "Index is out of bounds!");

  return m_values[aIndex];
}

template <typename T, u32 T_SIZE>
TL_FI const T& Tuple<T, T_SIZE>::operator [](s32 aIndex) const
{
  TLOC_ASSERT_LOW_LEVEL(aIndex < T_SIZE, "Index is out of bounds!");

  return m_values[aIndex];
}

template <typename T, u32 T_SIZE>
TL_FI T& Tuple<T, T_SIZE>::Get(u32 aIndex)
{
  TLOC_ASSERT_LOW_LEVEL(aIndex < T_SIZE, "Index is out of bounds!");

  return m_values[aIndex];
}

template <typename T, u32 T_SIZE>
TL_FI const T& Tuple<T, T_SIZE>::Get(u32 aIndex) const
{
  TLOC_ASSERT_LOW_LEVEL(aIndex < T_SIZE, "Index is out of bounds!");

  return m_values[aIndex];
}

template <typename T, u32 T_SIZE>
TL_FI Tuple<T, T_SIZE>::operator T*()
{
  return m_values;
}

template <typename T, u32 T_SIZE>
TL_FI Tuple<T, T_SIZE>::operator const T*() const
{
  return m_values;
}

//------------------------------------------------------------------------
// Modifiers

template <typename T, u32 T_SIZE>
void Tuple<T, T_SIZE>::Set(T aValue)
{
  ITERATE_TUPLE
  {
    m_values[i] = aValue;
  }
}

template <typename T, u32 T_SIZE>
void Tuple<T, T_SIZE>::Swap(Tuple<T, T_SIZE>& aVector)
{
  ITERATE_TUPLE
  {
    tloc::Swap(m_values[i], aVector[i]);
  }
}

//------------------------------------------------------------------------
// Operators

template <typename T, u32 T_SIZE>
TL_FI Tuple<T, T_SIZE>& Tuple<T, T_SIZE>::operator = (const Tuple<T, T_SIZE>& aTuple)
{
  memcpy(m_values, aTuple, sizeof(T) * T_SIZE);
  return *this;
}
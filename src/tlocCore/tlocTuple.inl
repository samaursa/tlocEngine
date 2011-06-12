//------------------------------------------------------------------------
// Macros

#define ITERATE_TUPLE for (u32 i = 0; i < aSize; ++i)

//------------------------------------------------------------------------
// Constructors

template <typename T, u32 aSize>
Tuple<T, aSize>::Tuple()
{
}

template <typename T, u32 aSize>
Tuple<T, aSize>::Tuple(const T& aValue)
{
  ITERATE_TUPLE
  {
    values[i] = aValue;
  }
}

//------------------------------------------------------------------------
// Accessors

template <typename T, u32 aSize>
TL_FI T& Tuple<T, aSize>::operator [](s32 aIndex)
{
  TLOC_ASSERT_LOW_LEVEL(aIndex < aSize, "Index is out of bounds!");

  return values[aIndex];
}

template <typename T, u32 aSize>
TL_FI const T& Tuple<T, aSize>::operator [](s32 aIndex) const
{
  TLOC_ASSERT_LOW_LEVEL(aIndex < aSize, "Index is out of bounds!");

  return values[aIndex];
}

template <typename T, u32 aSize>
TL_FI T& Tuple<T, aSize>::Get(u32 aIndex)
{
  TLOC_ASSERT_LOW_LEVEL(aIndex < aSize, "Index is out of bounds!");

  return values[aIndex];
}

template <typename T, u32 aSize>
TL_FI const T& Tuple<T, aSize>::Get(u32 aIndex) const
{
  TLOC_ASSERT_LOW_LEVEL(aIndex < aSize, "Index is out of bounds!");

  return values[aIndex];
}

template <typename T, u32 aSize>
TL_FI Tuple<T, aSize>::operator T*()
{
  return values;
}

template <typename T, u32 aSize>
TL_FI Tuple<T, aSize>::operator const T*() const
{
  return values;
}

//------------------------------------------------------------------------
// Modifiers

template <typename T, u32 aSize>
void Tuple<T, aSize>::Set(T aValue)
{
  ITERATE_TUPLE
  {
    values[i] = aValue;
  }
}

template <typename T, u32 aSize>
void Tuple<T, aSize>::Swap(Tuple<T, aSize>& aVector)
{
  ITERATE_TUPLE
  {
    tloc::Swap(values[i], aVector[i]);
  }
}

//------------------------------------------------------------------------
// Operators

template <typename T, u32 aSize>
TL_FI Tuple<T, aSize>& Tuple<T, aSize>::operator = (const Tuple<T, aSize>& aTuple)
{
  ITERATE_TUPLE
  {
    values[i] = aTuple[i];
  }
  return *this;
}
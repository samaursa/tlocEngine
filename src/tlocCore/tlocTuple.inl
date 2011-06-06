template <typename T, tl_uint32 aSize>
Tuple<T, aSize>::Tuple()
{
}

template <typename T, tl_uint32 aSize>
Tuple<T, aSize>::Tuple(const T& aValue)
{
  ITERATE_TUPLE
  {
    values[i] = aValue;
  }
}

template <typename T, tl_uint32 aSize>
TL_FI T& Tuple<T, aSize>::operator [](tl_uint32 aIndex)
{
  TLOC_ASSERT_LOW_LEVEL(aIndex < aSize, "Index is out of bounds!");

  return values[aIndex];
}

template <typename T, tl_uint32 aSize>
TL_FI const T& Tuple<T, aSize>::operator [](tl_uint32 aIndex) const
{
  TLOC_ASSERT_LOW_LEVEL(aIndex < aSize, "Index is out of bounds!");

  return values[aIndex];
}

template <typename T, tl_uint32 aSize>
TL_FI Tuple<T, aSize>::operator T*()
{
  return values;
}

template <typename T, tl_uint32 aSize>
TL_FI Tuple<T, aSize>::operator const T*() const
{
  return values;
}
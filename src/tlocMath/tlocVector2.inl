//////////////////////////////////////////////////////////////////////////
// Vector2

template <typename T>
TL_FI Vector2<T>::Vector2()
{
}

template <typename T>
TL_FI Vector2<T>::Vector2(const T& aValue)
{
  m_values[0] = aValue;
  m_values[1] = aValue;
}

template <typename T>
TL_FI Vector2<T>::Vector2(const T& aX, const T& aY)
{
  m_values[0] = aX;
  m_values[1] = aY;
}

template <typename T>
TL_FI Vector2<T>::Vector2(const Vector2<T>& aVector)
{
  m_values[0] = aVector[0];
  m_values[1] = aVector[1];
}

template <typename T>
TL_FI Vector2<T>::Vector2(const Vector<T, 2>& aVector)
{
  m_values[0] = aVector[0];
  m_values[1] = aVector[1];
}
//////////////////////////////////////////////////////////////////////////
// Vector<N>

//------------------------------------------------------------------------
// Macros

#define ITERATE_VECTOR for (u32 i = 0; i < T_SIZE; ++i)

//------------------------------------------------------------------------
// Constructors

template <typename T, u32 T_SIZE>
TL_FI Vector<T, T_SIZE>::Vector()
{
}

template <typename T, u32 T_SIZE>
TL_FI Vector<T, T_SIZE>::Vector(const T& aValue) : Tuple(aValue)
{

}

template <typename T, u32 T_SIZE>
TL_FI Vector<T, T_SIZE>::Vector(const Vector<T, T_SIZE>& aVector)
{
  *this = aVector;
}

//------------------------------------------------------------------------
// Modifiers

template <typename T, u32 T_SIZE>
TL_FI void Vector<T, T_SIZE>::Zero()
{
  Set(0);
}

template <typename T, u32 T_SIZE>
TL_FI void Vector<T, T_SIZE>::Neg()
{
  ITERATE_VECTOR
  {
    m_values[i] = -m_values[i];
  }
}

template <typename T, u32 T_SIZE>
TL_FI void Vector<T, T_SIZE>::Neg(const Vector<T, T_SIZE>& aVector)
{
  operator=(aVector);
  Neg();
}

//------------------------------------------------------------------------
// Math Operations

template <typename T, u32 T_SIZE>
TL_FI void Vector<T, T_SIZE>::Add(const Vector<T, T_SIZE>& aVector)
{
  ITERATE_VECTOR
  {
    m_values[i] += aVector[i];
  }
}

template <typename T, u32 T_SIZE>
TL_FI void Vector<T, T_SIZE>::Add(const Vector<T, T_SIZE>& aVector1, 
                                 const Vector<T, T_SIZE>& aVector2)
{
  ITERATE_VECTOR
  {
    m_values[i] = aVector1[i] + aVector2[i];
  }
}

template <typename T, u32 T_SIZE>
TL_FI void Vector<T, T_SIZE>::Sub(const Vector<T, T_SIZE>& aVector)
{
  ITERATE_VECTOR
  {
    m_values[i] -= aVector[i];
  }
}

template <typename T, u32 T_SIZE>
TL_FI void Vector<T, T_SIZE>::Sub(const Vector<T, T_SIZE>& aVector1, 
                                 const Vector<T, T_SIZE>& aVector2)
{
  operator=(aVector1);
  Sub(aVector2);
}

template <typename T, u32 T_SIZE>
TL_FI void Vector<T, T_SIZE>::Mul(const Vector<T, T_SIZE>& aVector)
{
  ITERATE_VECTOR
  {
    m_values[i] *= aVector[i];
  }
}

template <typename T, u32 T_SIZE>
TL_FI void Vector<T, T_SIZE>::Mul(const Vector<T, T_SIZE>& aVector1, 
                                 const Vector<T, T_SIZE>& aVector2)
{
  operator=(aVector1);
  Mul(aVector2);
}

template <typename T, u32 T_SIZE>
TL_FI void Vector<T, T_SIZE>::Mul(const T aReal)
{
  ITERATE_VECTOR
  {
    m_values[i] *= aReal;
  }
}

template <typename T, u32 T_SIZE>
TL_FI void Vector<T, T_SIZE>::Div(const Vector<T, T_SIZE>& aVector)
{
  ITERATE_VECTOR
  {
    m_values[i] /= aVector[i];
  }
}

template <typename T, u32 T_SIZE>
TL_FI void Vector<T, T_SIZE>::Div(const Vector<T, T_SIZE>& aVector1, 
                                 const Vector<T, T_SIZE>& aVector2)
{
  operator=(aVector1);
  Div(aVector2);
}

template <typename T, u32 T_SIZE>
TL_FI void Vector<T, T_SIZE>::Div(const T aReal)
{
  ITERATE_VECTOR
  {
    m_values[i] /= aReal;
  }
}

template <typename T, u32 T_SIZE>
TL_FI void Vector<T, T_SIZE>::LengthSquared(T& aReal) const
{
  aReal = 0;

  ITERATE_VECTOR
  {
    aReal += (m_values[i] * m_values[i]);
  }
}

template <typename T, u32 T_SIZE>
TL_FI T Vector<T, T_SIZE>::LengthSquared() const
{
  T lengthSq; LengthSquared(lengthSq);
  return lengthSq;
}

template <typename T, u32 T_SIZE>
TL_FI void Vector<T, T_SIZE>::Length(T& aReal) const
{
  LengthSquared(aReal);
  aReal = sqrt(aReal);
}

template <typename T, u32 T_SIZE>
TL_FI T Vector<T, T_SIZE>::Length() const
{
  T length; Length(length);
  return length;
}

template <typename T, u32 T_SIZE>
TL_FI void Vector<T, T_SIZE>::Norm()
{
  T lLength; Length(lLength);

  if (lLength > 1e-08)
  {
    T lInvLength = (T)1.0 / lLength;

    ITERATE_VECTOR
    {
      m_values[i] *= lInvLength;
    }
  }
}

template <typename T, u32 T_SIZE>
TL_FI T Vector<T, T_SIZE>::NormLength()
{
  T lLength; Length(lLength);

  if (lLength > 1e-08)
  {
    T lInvLength = (T)1.0 / lLength;

    ITERATE_VECTOR
    {
      m_values[i] *= lInvLength;
    }
  }

  return lLength;
}

template <typename T, u32 T_SIZE>
TL_FI void Vector<T, T_SIZE>::Norm(const Vector<T, T_SIZE>& aVector)
{
  T lLength; aVector.Length(lLength);

  if (lLength > 1e-08)
  {
    T lInvLength = (T)1.0 / lLength;

    ITERATE_VECTOR
    {
      m_values[i] = aVector[i] * lInvLength;
    }
  }
}

template <typename T, u32 T_SIZE>
TL_FI T Vector<T, T_SIZE>::NormLength(const Vector<T, T_SIZE>& aVector)
{
  T lLength; aVector.Length(lLength);

  if (lLength > 1e-08)
  {
    T lInvLength = (T)1.0 / lLength;

    ITERATE_VECTOR
    {
      m_values[i] = aVector[i] * lInvLength;
    }
  }

  return lLength;
}

template <typename T, u32 T_SIZE>
TL_FI T Vector<T, T_SIZE>::Distance(const Vector<T, T_SIZE>& aVector) const
{
  Vector<T, T_SIZE> lTemp = *this;
  lTemp.Sub(aVector);
  
  T length;
  lTemp.Length(length);
  return length;
}

template <typename T, u32 T_SIZE>
TL_FI T Vector<T, T_SIZE>::DistanceSquared(const Vector<T, T_SIZE>& aVector) const
{
  Vector<T, T_SIZE> lTemp = *this;
  lTemp.Sub(aVector);

  T lengthSq;
  lTemp.LengthSquared(lengthSq);
  return lengthSq;
}

template <typename T, u32 T_SIZE>
TL_FI T Vector<T, T_SIZE>::Dot(const Vector<T, T_SIZE>& aVector) const
{
  T dotProd = 0;

  ITERATE_VECTOR
  {
    dotProd += m_values[i] * aVector[i];
  }

  return dotProd;
}

template <typename T, u32 T_SIZE>
TL_FI T Vector<T, T_SIZE>::DotAbs(const Vector<T, T_SIZE>& aVector) const
{
  T dotProd = Dot(aVector);
  return Math<T>::Abs(dotProd);
}

template <typename T, u32 T_SIZE>
TL_FI void Vector<T, T_SIZE>::Midpoint(const Vector<T, T_SIZE>& aVector)
{
  ITERATE_VECTOR
  {
    m_values[i] = (m_values[i] + aVector[i]) * (T)0.5;
  }
}

template <typename T, u32 T_SIZE>
TL_FI void Vector<T, T_SIZE>::Midpoint(const Vector<T, T_SIZE>& aVector1, 
                                      const Vector<T, T_SIZE>& aVector2)
{
  operator=(aVector1);
  Midpoint(aVector2);
}

//------------------------------------------------------------------------
// Comparisons

template <typename T, u32 T_SIZE>
TL_FI bool Vector<T, T_SIZE>::operator==(const Vector<T, T_SIZE>& aVector)
{
  ITERATE_VECTOR
  {
    if (!Math<T>::Approx(m_values[i], aVector[i])) return false;
  }

  return true;
}

template <typename T, u32 T_SIZE>
TL_FI bool Vector<T, T_SIZE>::operator!=(const Vector<T, T_SIZE>& aVector)
{
  return !operator==(aVector);
}

//------------------------------------------------------------------------
// Checks

template <typename T, u32 T_SIZE>
TL_FI bool Vector<T, T_SIZE>::IsValid()
{
  ITERATE_VECTOR
  {
    if (Math<T>::IsNaN(m_values[i])) return false;
  }

  return true;
}

template <typename T, u32 T_SIZE>
TL_FI bool Vector<T, T_SIZE>::IsZero()
{
  ITERATE_VECTOR
  {
    if (!Math<T>::Approx(m_values[i], 0)) return false;
  }

  return true;
}

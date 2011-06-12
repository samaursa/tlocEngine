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
TL_FI void Vector<T, T_SIZE>::FastNorm(const Vector<T, T_SIZE>& aVector)
{
  T lLength; aVector.LengthSquared(T);
  
  // Calculate length inverse
  float xhalf = 0.5f*lLength;
  int i = *(int*)&lLength; // get bits for floating value
  i = 0x5f375a86- (i>>1); // gives initial guess y0
  lLength = *(float*)&i; // convert bits back to float
  lLength = lLength*(1.5f-xhalf*lLength*lLength); // Newton step, repeating increases accuracy

  ITERATE_VECTOR
  {
    m_values[i] *= lLength;
  }
}

template <typename T, u32 T_SIZE>
TL_FI void Vector<T, T_SIZE>::FastNorm()
{
  T lLength; LengthSquared(lLength);

  // Calculate length inverse
  float xhalf = 0.5f*lLength;
  int i = *(int*)&lLength; // get bits for floating value
  i = 0x5f375a86- (i>>1); // gives initial guess y0
  lLength = *(float*)&i; // convert bits back to float
  lLength = lLength*(1.5f-xhalf*lLength*lLength); // Newton step, repeating increases accuracy

  ITERATE_VECTOR
  {
    m_values[i] *= lLength;
  }
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
  return Math::Abs(dotProd);
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
    if (!Math::Approx(m_values[i], aVector[i])) return false;
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
    if (Math::IsNaN<T>(m_values[i])) return false;
  }

  return true;
}

template <typename T, u32 T_SIZE>
TL_FI bool Vector<T, T_SIZE>::IsZero()
{
  ITERATE_VECTOR
  {
    if (!Math::Approx<T>(m_values[i], 0)) return false;
  }

  return true;
}

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

//////////////////////////////////////////////////////////////////////////
// Vector3

//------------------------------------------------------------------------
// Constructors

template <typename T>
TL_FI Vector3<T>::Vector3()
{
}

template <typename T>
TL_FI Vector3<T>::Vector3(const T& aValue)
{
  m_values[0] = aValue;
  m_values[1] = aValue;
  m_values[2] = aValue;
}

template <typename T>
TL_FI Vector3<T>::Vector3(const T& aX, const T& aY, const T& aZ)
{
  m_values[0] = aX;
  m_values[1] = aY;
  m_values[2] = aZ;
}

template <typename T>
TL_FI Vector3<T>::Vector3(const Vector3<T>& aVector)
{
  m_values[0] = aVector[0];
  m_values[1] = aVector[1];
  m_values[2] = aVector[2];
}

//------------------------------------------------------------------------
// Math operations

template <typename T>
TL_FI void Vector3<T>::Cross(const Vector3<T>& aVector)
{
  /*
  y * rkVector.z - z * rkVector.y,
  z * rkVector.x - x * rkVector.z,
  x * rkVector.y - y * rkVector.x);
  */

  Vector3<T> temp(*this);
  
  m_values[0] = temp[1] * aVector[2] - temp[2] * aVector[1];
  m_values[1] = temp[2] * aVector[0] - temp[0] * aVector[2];
  m_values[2] = temp[0] * aVector[1] - temp[1] * aVector[0];
}

template <typename T>
TL_FI void Vector3<T>::Cross(const Vector3<T>& aVector1, 
                             const Vector3<T>& aVector2)
{
  operator=(aVector1);
  Cross(aVector2);
}

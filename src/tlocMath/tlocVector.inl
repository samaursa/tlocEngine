//////////////////////////////////////////////////////////////////////////
// Vector<N>

//------------------------------------------------------------------------
// Constructors

template <typename T, u32 aSize>
Vector<T, aSize>::Vector()
{
}

template <typename T, u32 aSize>
Vector<T, aSize>::Vector(const T& aValue)
{
  ITERATE_VECTOR
  {
    values[i] = aValue;
  }
}

template <typename T, u32 aSize>
Vector<T, aSize>::Vector(const Vector<T, aSize>& aVector)
{
  *this = aVector;
}

//------------------------------------------------------------------------
// Modifiers

template <typename T, u32 aSize>
void Vector<T, aSize>::Zero()
{
  Set(0);
}

template <typename T, u32 aSize>
void Vector<T, aSize>::Neg()
{
  ITERATE_VECTOR
  {
    values[i] = -values[i];
  }
}

//------------------------------------------------------------------------
// Math Operations

template <typename T, u32 aSize>
TL_FI void Vector<T, aSize>::Add(const Vector<T, aSize>& aVector)
{
  ITERATE_VECTOR
  {
    values[i] += aVector[i];
  }
}

template <typename T, u32 aSize>
TL_FI void Vector<T, aSize>::Add(const Vector<T, aSize>& aVector1, 
                                 const Vector<T, aSize>& aVector2)
{
  ITERATE_VECTOR
  {
    values[i] = aVector1[i] + aVector2[i];
  }
}

template <typename T, u32 aSize>
TL_FI void Vector<T, aSize>::Sub(const Vector<T, aSize>& aVector)
{
  ITERATE_VECTOR
  {
    values[i] -= aVector[i];
  }
}

template <typename T, u32 aSize>
TL_FI void Vector<T, aSize>::Sub(const Vector<T, aSize>& aVector1, 
                                 const Vector<T, aSize>& aVector2)
{
  operator=(aVector1);
  Sub(aVector2);
}

template <typename T, u32 aSize>
TL_FI void Vector<T, aSize>::Mul(const Vector<T, aSize>& aVector)
{
  ITERATE_VECTOR
  {
    values[i] *= aVector[i];
  }
}

template <typename T, u32 aSize>
TL_FI void Vector<T, aSize>::Mul(const Vector<T, aSize>& aVector1, 
                                 const Vector<T, aSize>& aVector2)
{
  operator=(aVector1);
  Mul(aVector2);
}

template <typename T, u32 aSize>
TL_FI void Vector<T, aSize>::Mul(const T aReal)
{
  ITERATE_VECTOR
  {
    values[i] *= aReal;
  }
}

template <typename T, u32 aSize>
TL_FI void Vector<T, aSize>::Div(const Vector<T, aSize>& aVector)
{
  ITERATE_VECTOR
  {
    values[i] /= aVector[i];
  }
}

template <typename T, u32 aSize>
TL_FI void Vector<T, aSize>::Div(const Vector<T, aSize>& aVector1, 
                                 const Vector<T, aSize>& aVector2)
{
  operator=(aVector1);
  Div(aVector2);
}

template <typename T, u32 aSize>
TL_FI void Vector<T, aSize>::Div(const T aReal)
{
  ITERATE_VECTOR
  {
    values[i] /= aReal;
  }
}

template <typename T, u32 aSize>
TL_FI void Vector<T, aSize>::LengthSquared(T& aReal) const
{
  aReal = 0;

  ITERATE_VECTOR
  {
    aReal += (values[i] * values[i]);
  }
}

template <typename T, u32 aSize>
TL_FI T Vector<T, aSize>::LengthSquared() const
{
  T lengthSq; LengthSquared(lengthSq);
  return lengthSq;
}

template <typename T, u32 aSize>
TL_FI void Vector<T, aSize>::Length(T& aReal) const
{
  LengthSquared(aReal);
  aReal = sqrt(aReal);
}

template <typename T, u32 aSize>
TL_FI T Vector<T, aSize>::Length() const
{
  T length; Length(length);
  return length;
}

template <typename T, u32 aSize>
TL_FI void Vector<T, aSize>::Norm()
{
  T lLength; Length(lLength);

  if (lLength > 1e-08)
  {
    T lInvLength = (T)1.0 / lLength;

    ITERATE_VECTOR
    {
      values[i] *= lInvLength;
    }
  }
}

template <typename T, u32 aSize>
TL_FI T Vector<T, aSize>::NormLength()
{
  T lLength; Length(lLength);

  if (lLength > 1e-08)
  {
    T lInvLength = (T)1.0 / lLength;

    ITERATE_VECTOR
    {
      values[i] *= lInvLength;
    }
  }

  return lLength;
}

template <typename T, u32 aSize>
TL_FI void Vector<T, aSize>::Norm(const Vector<T, aSize>& aVector)
{
  T lLength; aVector.Length(lLength);

  if (lLength > 1e-08)
  {
    T lInvLength = (T)1.0 / lLength;

    ITERATE_VECTOR
    {
      values[i] = aVector[i] * lInvLength;
    }
  }
}

template <typename T, u32 aSize>
TL_FI T Vector<T, aSize>::NormLength(const Vector<T, aSize>& aVector)
{
  T lLength; aVector.Length(lLength);

  if (lLength > 1e-08)
  {
    T lInvLength = (T)1.0 / lLength;

    ITERATE_VECTOR
    {
      values[i] = aVector[i] * lInvLength;
    }
  }

  return lLength;
}

template <typename T, u32 aSize>
TL_FI void Vector<T, aSize>::FastNorm(const Vector<T, aSize>& aVector)
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
    values[i] *= lLength;
  }
}

template <typename T, u32 aSize>
TL_FI void Vector<T, aSize>::FastNorm()
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
    values[i] *= lLength;
  }
}

template <typename T, u32 aSize>
TL_FI T Vector<T, aSize>::Distance(const Vector<T, aSize>& aVector) const
{
  Vector<T, aSize> lTemp = *this;
  lTemp.Sub(aVector);
  
  T length;
  lTemp.Length(length);
  return length;
}

template <typename T, u32 aSize>
TL_FI T Vector<T, aSize>::DistanceSquared(const Vector<T, aSize>& aVector) const
{
  Vector<T, aSize> lTemp = *this;
  lTemp.Sub(aVector);

  T lengthSq;
  lTemp.LengthSquared(lengthSq);
  return lengthSq;
}

template <typename T, u32 aSize>
TL_FI T Vector<T, aSize>::Dot(const Vector<T, aSize>& aVector) const
{
  T dotProd = 0;

  ITERATE_VECTOR
  {
    dotProd += values[i] * aVector[i];
  }

  return dotProd;
}

template <typename T, u32 aSize>
TL_FI T Vector<T, aSize>::DotAbs(const Vector<T, aSize>& aVector) const
{
  T dotProd = Dot(aVector);
  return Math::Abs(dotProd);
}

template <typename T, u32 aSize>
TL_FI void Vector<T, aSize>::Midpoint(const Vector<T, aSize>& aVector)
{
  ITERATE_VECTOR
  {
    values[i] = (values[i] + aVector[i]) * (T)0.5;
  }
}

template <typename T, u32 aSize>
TL_FI void Vector<T, aSize>::Midpoint(const Vector<T, aSize>& aVector1, 
                                      const Vector<T, aSize>& aVector2)
{
  operator=(aVector1);
  Midpoint(aVector2);
}

//------------------------------------------------------------------------
// Comparisons

template <typename T, u32 aSize>
TL_FI bool Vector<T, aSize>::operator==(const Vector<T, aSize>& aVector)
{
  ITERATE_VECTOR
  {
    if (!Math::Approx(values[i], aVector[i])) return false;
  }

  return true;
}

template <typename T, u32 aSize>
TL_FI bool Vector<T, aSize>::operator!=(const Vector<T, aSize>& aVector)
{
  return !operator==(aVector);
}

//------------------------------------------------------------------------
// Checks

template <typename T, u32 aSize>
TL_FI bool Vector<T, aSize>::IsValid()
{
  ITERATE_VECTOR
  {
    if (Math::IsNaN<T>(values[i])) return false;
  }

  return true;
}

template <typename T, u32 aSize>
TL_FI bool Vector<T, aSize>::IsZero()
{
  ITERATE_VECTOR
  {
    if (!Math::Approx<T>(values[i], 0)) return false;
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////
// Vector2

template <typename T>
Vector2<T>::Vector2()
{
}

template <typename T>
Vector2<T>::Vector2(const T& aValue)
{
  values[0] = aValue;
  values[1] = aValue;
}

template <typename T>
Vector2<T>::Vector2(const T& aX, const T& aY)
{
  values[0] = aX;
  values[1] = aY;
}

template <typename T>
Vector2<T>::Vector2(const Vector2<T>& aVector)
{
  values[0] = aVector[0];
  values[1] = aVector[1];
}

//////////////////////////////////////////////////////////////////////////
// Vector3

//------------------------------------------------------------------------
// Constructors

template <typename T>
Vector3<T>::Vector3()
{
}

template <typename T>
Vector3<T>::Vector3(const T& aValue)
{
  values[0] = aValue;
  values[1] = aValue;
  values[2] = aValue;
}

template <typename T>
Vector3<T>::Vector3(const T& aX, const T& aY, const T& aZ)
{
  values[0] = aX;
  values[1] = aY;
  values[2] = aZ;
}

template <typename T>
Vector3<T>::Vector3(const Vector3<T>& aVector)
{
  values[0] = aVector[0];
  values[1] = aVector[1];
  values[2] = aVector[2];
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
  
  values[0] = temp[1] * aVector[2] - temp[2] * aVector[1];
  values[1] = temp[2] * aVector[0] - temp[0] * aVector[2];
  values[2] = temp[0] * aVector[1] - temp[1] * aVector[0];
}

template <typename T>
TL_FI void Vector3<T>::Cross(const Vector3<T>& aVector1, 
                             const Vector3<T>& aVector2)
{
  operator=(aVector1);
  Cross(aVector2);
}

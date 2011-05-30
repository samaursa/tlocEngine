//////////////////////////////////////////////////////////////////////////
// Constructors

template <typename T, FwUInt32 aSize>
Vector<T, aSize>::Vector()
{
  ITERATE_VECTOR
  {
    values[i] = 0;
  }
}

template <typename T, FwUInt32 aSize>
Vector<T, aSize>::Vector(T aValue)
{
  ITERATE_VECTOR
  {
    values[i] = aValue;
  }
}

template <typename T, FwUInt32 aSize>
Vector<T, aSize>::Vector(const Vector<T, aSize>& aVector)
{
  this = aVector;
}


//////////////////////////////////////////////////////////////////////////
// Accessors

template <typename T, FwUInt32 aSize>
T& Vector<T, aSize>::operator [](FwUInt32 aIndex)
{
  TLOC_ASSERT(aIndex < aSize, "Index out of bounds!");
  return values[aIndex];
}

template <typename T, FwUInt32 aSize>
const T& Vector<T, aSize>::operator [](FwUInt32 aIndex) const
{
  TLOC_ASSERT(aIndex < aSize, "Index out of bounds!");
  return values[aIndex];
}

//////////////////////////////////////////////////////////////////////////
// Modifiers

template <typename T, FwUInt32 aSize>
void Vector<T, aSize>::Zero()
{
  ITERATE_VECTOR
  {
    values[i] = 0;
  }
}

template <typename T, FwUInt32 aSize>
void Vector<T, aSize>::Swap(Vector<T, aSize>& aVector)
{
  ITERATE_VECTOR
  {
    tloc::swap(values[i], aVector[i]);
  }
}

template <typename T, FwUInt32 aSize>
void Vector<T, aSize>::Neg()
{
  ITERATE_VECTOR
  {
    values[i] = -values[i];
  }
}

template <typename T, FwUInt32 aSize>
FW_FI void Vector<T, aSize>::operator=( const Vector<T, aSize>& aVector )
{
  ITERATE_VECTOR
  {
    values[i] = aVector[i];
  }
}

//////////////////////////////////////////////////////////////////////////
// Math Operations

template <typename T, FwUInt32 aSize>
FW_FI void Vector<T, aSize>::Add(const Vector<T, aSize>& aVector)
{
  ITERATE_VECTOR
  {
    values[i] += aVector[i];
  }
}

template <typename T, FwUInt32 aSize>
FW_FI void Vector<T, aSize>::Add(const Vector<T, aSize>& aVector1, 
                                 const Vector<T, aSize>& aVector2)
{
  ITERATE_VECTOR
  {
    values[i] = aVector1[i] + aVector2[i];
  }
}

template <typename T, FwUInt32 aSize>
FW_FI void Vector<T, aSize>::Sub(const Vector<T, aSize>& aVector)
{
  ITERATE_VECTOR
  {
    values[i] -= aVector[i];
  }
}

template <typename T, FwUInt32 aSize>
FW_FI void Vector<T, aSize>::Sub(const Vector<T, aSize>& aVector1, 
                                 const Vector<T, aSize>& aVector2)
{
  operator=(aVector1);
  Sub(aVector2);
}

template <typename T, FwUInt32 aSize>
FW_FI void Vector<T, aSize>::Mul(const Vector<T, aSize>& aVector)
{
  ITERATE_VECTOR
  {
    values[i] *= aVector[i];
  }
}

template <typename T, FwUInt32 aSize>
FW_FI void Vector<T, aSize>::Mul(const Vector<T, aSize>& aVector1, 
                                 const Vector<T, aSize>& aVector2)
{
  operator=(aVector1);
  Mul(aVector2);
}

template <typename T, FwUInt32 aSize>
FW_FI void Vector<T, aSize>::Mul(const T aReal)
{
  ITERATE_VECTOR
  {
    values[i] *= aReal;
  }
}

template <typename T, FwUInt32 aSize>
FW_FI void Vector<T, aSize>::Div(const Vector<T, aSize>& aVector)
{
  ITERATE_VECTOR
  {
    values[i] /= aVector[i];
  }
}

template <typename T, FwUInt32 aSize>
FW_FI void Vector<T, aSize>::Div(const Vector<T, aSize>& aVector1, 
                                 const Vector<T, aSize>& aVector2)
{
  operator=(aVector1);
  Div(aVector2);
}

template <typename T, FwUInt32 aSize>
FW_FI void Vector<T, aSize>::Div(const T aReal)
{
  ITERATE_VECTOR
  {
    values[i] /= aReal;
  }
}

template <typename T, FwUInt32 aSize>
FW_FI void Vector<T, aSize>::LengthSquared(T& aReal) const
{
  aReal = 0;

  ITERATE_VECTOR
  {
    aReal += (values[i] * values[i]);
  }
}

template <typename T, FwUInt32 aSize>
FW_FI void Vector<T, aSize>::Length(T& aReal) const
{
  LengthSquared(aReal);
  aReal = sqrt(aReal);
}

template <typename T, FwUInt32 aSize>
FW_FI void Vector<T, aSize>::Norm()
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

template <typename T, FwUInt32 aSize>
FW_FI T Vector<T, aSize>::NormLength()
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

template <typename T, FwUInt32 aSize>
FW_FI void Vector<T, aSize>::Norm(const Vector<T, aSize>& aVector)
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

template <typename T, FwUInt32 aSize>
FW_FI void Vector<T, aSize>::NormLength(const Vector<T, aSize>& aVector)
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

template <typename T, FwUInt32 aSize>
FW_FI void Vector<T, aSize>::FastNorm(const Vector<T, aSize>& aVector)
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

template <typename T, FwUInt32 aSize>
FW_FI void Vector<T, aSize>::FastNorm()
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
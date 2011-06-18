namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Vector<N>

  //------------------------------------------------------------------------
  // Macros

#define ITERATE_VECTOR for (u32 i = 0; i < T_Size; ++i)

  //------------------------------------------------------------------------
  // Constructors

  template <typename T, u32 T_Size>
  TL_FI Vector<T, T_Size>::Vector()
  {
  }

  template <typename T, u32 T_Size>
  TL_FI Vector<T, T_Size>::Vector(const T& aValue) : Tuple(aValue)
  {

  }

  template <typename T, u32 T_Size>
  TL_FI Vector<T, T_Size>::Vector(const Vector<T, T_Size>& aVector)
  {
    *this = aVector;
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <typename T, u32 T_Size>
  TL_FI void Vector<T, T_Size>::Zero()
  {
    Set(0);
  }

  template <typename T, u32 T_Size>
  TL_FI void Vector<T, T_Size>::Neg()
  {
    ITERATE_VECTOR
    {
      m_values[i] = -m_values[i];
    }
  }

  template <typename T, u32 T_Size>
  TL_FI void Vector<T, T_Size>::Neg(const Vector<T, T_Size>& aVector)
  {
    operator=(aVector);
    Neg();
  }

  //------------------------------------------------------------------------
  // Math Operations

  template <typename T, u32 T_Size>
  TL_FI void Vector<T, T_Size>::Add(const Vector<T, T_Size>& aVector)
  {
    ITERATE_VECTOR
    {
      m_values[i] += aVector[i];
    }
  }

  template <typename T, u32 T_Size>
  TL_FI void Vector<T, T_Size>::Add(const Vector<T, T_Size>& aVector1, 
    const Vector<T, T_Size>& aVector2)
  {
    ITERATE_VECTOR
    {
      m_values[i] = aVector1[i] + aVector2[i];
    }
  }

  template <typename T, u32 T_Size>
  TL_FI void Vector<T, T_Size>::Sub(const Vector<T, T_Size>& aVector)
  {
    ITERATE_VECTOR
    {
      m_values[i] -= aVector[i];
    }
  }

  template <typename T, u32 T_Size>
  TL_FI void Vector<T, T_Size>::Sub(const Vector<T, T_Size>& aVector1, 
    const Vector<T, T_Size>& aVector2)
  {
    operator=(aVector1);
    Sub(aVector2);
  }

  template <typename T, u32 T_Size>
  TL_FI void Vector<T, T_Size>::Mul(const Vector<T, T_Size>& aVector)
  {
    ITERATE_VECTOR
    {
      m_values[i] *= aVector[i];
    }
  }

  template <typename T, u32 T_Size>
  TL_FI void Vector<T, T_Size>::Mul(const Vector<T, T_Size>& aVector1, 
    const Vector<T, T_Size>& aVector2)
  {
    operator=(aVector1);
    Mul(aVector2);
  }

  template <typename T, u32 T_Size>
  TL_FI void Vector<T, T_Size>::Mul(const T aReal)
  {
    ITERATE_VECTOR
    {
      m_values[i] *= aReal;
    }
  }

  template <typename T, u32 T_Size>
  TL_FI void Vector<T, T_Size>::Div(const Vector<T, T_Size>& aVector)
  {
    ITERATE_VECTOR
    {
      m_values[i] /= aVector[i];
    }
  }

  template <typename T, u32 T_Size>
  TL_FI void Vector<T, T_Size>::Div(const Vector<T, T_Size>& aVector1, 
    const Vector<T, T_Size>& aVector2)
  {
    operator=(aVector1);
    Div(aVector2);
  }

  template <typename T, u32 T_Size>
  TL_FI void Vector<T, T_Size>::Div(const T aReal)
  {
    ITERATE_VECTOR
    {
      m_values[i] /= aReal;
    }
  }

  template <typename T, u32 T_Size>
  TL_FI void Vector<T, T_Size>::LengthSquared(T& aReal) const
  {
    aReal = 0;

    ITERATE_VECTOR
    {
      aReal += (m_values[i] * m_values[i]);
    }
  }

  template <typename T, u32 T_Size>
  TL_FI T Vector<T, T_Size>::LengthSquared() const
  {
    T lengthSq; LengthSquared(lengthSq);
    return lengthSq;
  }

  template <typename T, u32 T_Size>
  TL_FI void Vector<T, T_Size>::Length(T& aReal) const
  {
    aReal = LengthSquared();
    aReal = Math<T>::Sqrt(aReal);
  }

  template <typename T, u32 T_Size>
  TL_FI T Vector<T, T_Size>::Length() const
  {
    T length; Length(length);
    return length;
  }

  template <typename T, u32 T_Size>
  TL_FI void Vector<T, T_Size>::Norm()
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

  template <typename T, u32 T_Size>
  TL_FI T Vector<T, T_Size>::NormLength()
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

  template <typename T, u32 T_Size>
  TL_FI void Vector<T, T_Size>::Norm(const Vector<T, T_Size>& aVector)
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

  template <typename T, u32 T_Size>
  TL_FI T Vector<T, T_Size>::NormLength(const Vector<T, T_Size>& aVector)
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

  template <typename T, u32 T_Size>
  TL_FI T Vector<T, T_Size>::Distance(const Vector<T, T_Size>& aVector) const
  {
    Vector<T, T_Size> lTemp = *this;
    lTemp.Sub(aVector);

    T length;
    lTemp.Length(length);
    return length;
  }

  template <typename T, u32 T_Size>
  TL_FI T Vector<T, T_Size>::DistanceSquared(const Vector<T, T_Size>& aVector) const
  {
    Vector<T, T_Size> lTemp = *this;
    lTemp.Sub(aVector);

    T lengthSq;
    lTemp.LengthSquared(lengthSq);
    return lengthSq;
  }

  template <typename T, u32 T_Size>
  TL_FI T Vector<T, T_Size>::Dot(const Vector<T, T_Size>& aVector) const
  {
    T dotProd = 0;

    ITERATE_VECTOR
    {
      dotProd += m_values[i] * aVector[i];
    }

    return dotProd;
  }

  template <typename T, u32 T_Size>
  TL_FI T Vector<T, T_Size>::DotAbs(const Vector<T, T_Size>& aVector) const
  {
    T dotProd = Dot(aVector);
    return Math<T>::Abs(dotProd);
  }

  template <typename T, u32 T_Size>
  TL_FI void Vector<T, T_Size>::Midpoint(const Vector<T, T_Size>& aVector)
  {
    ITERATE_VECTOR
    {
      m_values[i] = (m_values[i] + aVector[i]) * (T)0.5;
    }
  }

  template <typename T, u32 T_Size>
  TL_FI void Vector<T, T_Size>::Midpoint(const Vector<T, T_Size>& aVector1, 
    const Vector<T, T_Size>& aVector2)
  {
    operator=(aVector1);
    Midpoint(aVector2);
  }

  //------------------------------------------------------------------------
  // Comparisons

  template <typename T, u32 T_Size>
  TL_FI bool Vector<T, T_Size>::operator==(const Vector<T, T_Size>& aVector)
  {
    ITERATE_VECTOR
    {
      if (!Math<T>::Approx(m_values[i], aVector[i])) return false;
    }

    return true;
  }

  template <typename T, u32 T_Size>
  TL_FI bool Vector<T, T_Size>::operator!=(const Vector<T, T_Size>& aVector)
  {
    return !operator==(aVector);
  }

  //------------------------------------------------------------------------
  // Checks

  template <typename T, u32 T_Size>
  TL_FI bool Vector<T, T_Size>::IsValid()
  {
    ITERATE_VECTOR
    {
      if (Math<T>::IsNaN(m_values[i])) return false;
    }

    return true;
  }

  template <typename T, u32 T_Size>
  TL_FI bool Vector<T, T_Size>::IsZero()
  {
    ITERATE_VECTOR
    {
      if (!Math<T>::Approx(m_values[i], 0)) return false;
    }

    return true;
  }
};

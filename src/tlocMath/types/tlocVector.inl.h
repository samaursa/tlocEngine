#ifndef TLOC_VECTOR_N_INL
#define TLOC_VECTOR_N_INL

#ifndef TLOC_VECTOR_N_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/data_structures/tlocTuple.inl.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocMath/tlocMath.inl.h>

namespace tloc { namespace math { namespace types {

  namespace
  {
    template <typename T>
    TL_FI T GetInvSqrt(T a_value, p_vector::accurate)
    {
      return Math<T>::InvSqrt(a_value);
    }

    template <typename T>
    TL_FI T GetInvSqrt(T a_value, p_vector::fast)
    {
      return Math<T>::FastInvSqrt(a_value);
    }

    template <typename T>
    TL_FI T GetSqrt(T a_value, p_vector::accurate)
    {
      return Math<T>::Sqrt(a_value);
    }

    template <typename T>
    TL_FI T GetSqrt(T a_value, p_vector::fast)
    {
      return Math<T>::InvSqrt(a_value);
    }
  }

  //////////////////////////////////////////////////////////////////////////
  // Vector<N>

  ////////////////////////////////////////////////////////////////////////
  // Template Macros

#define VECTOR_TEMP typename T, tl_size T_Size
#define VECTOR_PARAMS T, T_Size
#define VECTOR_TYPE typename Vector<T, T_Size>

  //////////////////////////////////////////////////////////////////////////
  // Misc Macros

  // Note that we have tl_int and not tl_size for the iteration. This is because
  // the [] operator only accepts integers, so we have no choice (either that
  // or we cast the tl_size to tl_int, which defeats the purpose anyway)
#define ITERATE_VECTOR for (tl_int i = 0; i < T_Size; ++i)

  //------------------------------------------------------------------------
  // Constructors

  template <VECTOR_TEMP>
  Vector<VECTOR_PARAMS>::
    Vector()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  Vector<VECTOR_PARAMS>::
    Vector(value_type a_value)
    : base_type(a_value)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  template <typename T_ArrayType>
  Vector<VECTOR_PARAMS>::
    Vector(const T_ArrayType (&aArray)[T_Size])
    : base_type(aArray)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  Vector<VECTOR_PARAMS>::
    Vector(const core::data_structs::Variadic<T, T_Size>& a_vars)
    : base_type(a_vars)
  { }

  //------------------------------------------------------------------------
  // Modifiers

  template <VECTOR_TEMP>
  void
    Vector<VECTOR_PARAMS>::
    Zero()
  {
    Set(0);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  void
    Vector<VECTOR_PARAMS>::
    Negate()
  {
    ITERATE_VECTOR
    {
      m_values[i] = -m_values[i];
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  void
    Vector<VECTOR_PARAMS>::
    Negate(const this_type& a_vector)
  {
    base_type::operator=(a_vector);
    Negate();
  }

  //------------------------------------------------------------------------
  // Math Operations

  template <VECTOR_TEMP>
  VECTOR_TYPE::this_type
    Vector<VECTOR_PARAMS>::
    Add(const this_type& a_vector) const
  {
    this_type temp(*this);

    ITERATE_VECTOR
    {
      temp.m_values[i] += a_vector[i];
    }

    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  void
    Vector<VECTOR_PARAMS>::
    Add(const this_type& a_vector1, const this_type& a_vector2)
  {
    *this = a_vector1.Add(a_vector2);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::this_type
    Vector<VECTOR_PARAMS>::
    Sub(const this_type& a_vector) const
  {
    this_type temp(*this);

    ITERATE_VECTOR
    {
      temp.m_values[i] -= a_vector[i];
    }

    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  void
    Vector<VECTOR_PARAMS>::
    Sub(const this_type& a_vector1, const this_type& a_vector2)
  {
    *this = a_vector1.Sub(a_vector2);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::this_type
    Vector<VECTOR_PARAMS>::
    Mul(const this_type& a_vector) const
  {
    this_type temp(*this);

    ITERATE_VECTOR
    {
      temp.m_values[i] *= a_vector[i];
    }

    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  void Vector<VECTOR_PARAMS>::
    Mul(const this_type& a_vector1, const this_type& a_vector2)
  {
    *this = a_vector1.Mul(a_vector2);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::this_type
    Vector<VECTOR_PARAMS>::
    Mul(const value_type a_real) const
  {
    this_type temp(*this);

    ITERATE_VECTOR
    {
      temp.m_values[i] *= a_real;
    }

    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  void
    Vector<VECTOR_PARAMS>::
    Mul(const this_type& a_vector, const value_type a_real)
  {
    ITERATE_VECTOR
    {
      m_values[i] = a_vector.m_values[i] * a_real;
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::this_type
    Vector<VECTOR_PARAMS>::
    Div(const this_type& a_vector) const
  {
    this_type temp(*this);

    ITERATE_VECTOR
    {
      temp.m_values[i] /= a_vector[i];
    }

    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  void
    Vector<VECTOR_PARAMS>::
    Div(const this_type& a_vector1, const this_type& a_vector2)
  {
    *this = a_vector1.Div(a_vector2);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::this_type
    Vector<VECTOR_PARAMS>::
    Div(const value_type a_real) const
  {
    this_type temp(*this);

    ITERATE_VECTOR
    {
      temp.m_values[i] /= a_real;
    }

    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  void
    Vector<VECTOR_PARAMS>::
    Div(const this_type& a_vector, const value_type a_real)
  {
    *this = a_vector.Div(a_real);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::value_type
    Vector<VECTOR_PARAMS>::
    LengthSquared() const
  {
    T lengthSq = 0;

    ITERATE_VECTOR
    {
      lengthSq += (m_values[i] * m_values[i]);
    }

    return lengthSq;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::value_type
    Vector<VECTOR_PARAMS>::
    Length() const
  {
    return DoLength<p_vector::accurate>(*this);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  template <typename T_Accuracy>
  VECTOR_TYPE::value_type
    Vector<VECTOR_PARAMS>::
    DoLength(const this_type& a_vector) const
  {
    value_type length = a_vector.LengthSquared();
    return GetSqrt(length, T_Accuracy());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::value_type
    Vector<VECTOR_PARAMS>::
    Normalize()
  {
    return Normalize<p_vector::accurate>(*this);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::value_type
    Vector<VECTOR_PARAMS>::
    Normalize(const this_type& a_vector)
  {
    return Normalize<p_vector::accurate>(a_vector);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  template <typename T_Accuracy>
  VECTOR_TYPE::value_type
    Vector<VECTOR_PARAMS>::
    DoNorm(const this_type& a_vector)
  {
    value_type dblLength = a_vector.LengthSquared();

    TLOC_ASSERT_VEC(Math<value_type>::IsEqual(dblLength, 0) == false,
      "Divide by zero!");

    value_type invLength = GetInvSqrt(dblLength, T_Accuracy() );
    ITERATE_VECTOR
    {
      m_values[i] = a_vector[i] * invLength;
    }

    return (T)1 / invLength;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::value_type
    Vector<VECTOR_PARAMS>::
    Distance(const this_type& a_vector) const
  {
    return DoDistance<p_vector::accurate>(a_vector);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  template <typename T_Accuracy>
  VECTOR_TYPE::value_type
    Vector<VECTOR_PARAMS>::
    DoDistance(const this_type& a_vector) const
  {
    this_type lTemp = *this;
    lTemp.Sub(a_vector);

    value_type length = lTemp.DoLength<T_Accuracy>(lTemp);
    return length;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::value_type
    Vector<VECTOR_PARAMS>::
    DistanceSquared(const this_type& a_vector) const
  {
    this_type lTemp = Sub(a_vector);

    value_type lengthSq = lTemp.LengthSquared();
    return lengthSq;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::value_type
    Vector<VECTOR_PARAMS>::
    Dot(const this_type& a_vector) const
  {
    value_type dotProd = 0;

    ITERATE_VECTOR
    {
      dotProd += m_values[i] * a_vector[i];
    }

    return dotProd;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::value_type
    Vector<VECTOR_PARAMS>::
    DotAbs(const this_type& a_vector) const
  {
    value_type dotProd = Dot(a_vector);
    return Math<value_type>::Abs(dotProd);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::this_type
    Vector<VECTOR_PARAMS>::
    Midpoint(const this_type& a_vector) const
  {
    this_type temp(*this);

    ITERATE_VECTOR
    {
      temp.m_values[i] = (temp.m_values[i] + a_vector[i]) * (value_type)0.5;
    }

    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  void
    Vector<VECTOR_PARAMS>::
    Midpoint(const this_type& a_vector1, const this_type& a_vector2)
  {
    *this = a_vector1.Midpoint(a_vector2);
  }

  //------------------------------------------------------------------------
  // Operators

  template <VECTOR_TEMP>
  VECTOR_TYPE::this_type
    Vector<VECTOR_PARAMS>::
    operator+ (const this_type& a_vector) const
  {
    return Add(a_vector);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::this_type
    Vector<VECTOR_PARAMS>::
    operator- (const this_type& a_vector) const
  {
    return Sub(a_vector);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::this_type
    Vector<VECTOR_PARAMS>::
    operator* (const_reference a_value) const
  {
    return Mul(a_value);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::this_type
    Vector<VECTOR_PARAMS>::
    operator* (const this_type& a_vector) const
  {
    return Mul(a_vector);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::this_type
    Vector<VECTOR_PARAMS>::
    operator/ (const_reference a_value) const
  {
    return Div(a_value);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::this_type
    Vector<VECTOR_PARAMS>::
    operator/ (const this_type& a_vector) const
  {
    return Div(a_vector);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::this_type&
    Vector<VECTOR_PARAMS>::
    operator+= (const this_type& a_vector)
  {
    Add(*this, a_vector);
    return (*this);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::this_type&
    Vector<VECTOR_PARAMS>::
    operator-= (const this_type& a_vector)
  {
    Sub(*this, a_vector);
    return (*this);;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::this_type&
    Vector<VECTOR_PARAMS>::
    operator*= (const_reference a_value)
  {
    Mul(*this, a_value);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::this_type&
    Vector<VECTOR_PARAMS>::
    operator*= (const this_type& a_vector)
  {
    Mul(*this, a_vector);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::this_type&
    Vector<VECTOR_PARAMS>::
    operator/= (const_reference a_value)
  {
    Div(*this, a_value);
    return (*this);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  VECTOR_TYPE::this_type&
    Vector<VECTOR_PARAMS>::
    operator/=(const this_type& a_vector)
  {
    Div(*this, a_vector);
    return (*this);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  bool
    Vector<VECTOR_PARAMS>::
    operator==(const this_type& a_vector) const
  {
    ITERATE_VECTOR
    {
      if (!Math<value_type>::Approx(m_values[i], a_vector[i])) return false;
    }

    return true;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  bool
    Vector<VECTOR_PARAMS>::
    operator!=(const this_type& a_vector) const
  {
    return !operator==(a_vector);
  }

  //------------------------------------------------------------------------
  // Checks

  template <VECTOR_TEMP>
  bool
    Vector<VECTOR_PARAMS>::
    IsValid()
  {
    ITERATE_VECTOR
    {
      if (Math<value_type>::IsNaN(m_values[i])) { return false; }
    }

    return true;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <VECTOR_TEMP>
  bool
    Vector<VECTOR_PARAMS>::
    IsZero()
  {
    ITERATE_VECTOR
    {
      if (!Math<value_type>::Approx(m_values[i], 0)) { return false; }
    }

    return true;
  }

};};};

#endif
#ifndef TLOC_VECTOR_N_INL
#define TLOC_VECTOR_N_INL

#ifndef TLOC_VECTOR_N_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocMath/tlocMath.inl>

namespace tloc { namespace math {

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
  // Assertion Macros

  // If TLOC_VECTOR_ALLOW_EASY_OPERATIONS is defined, easy math operations such
  // as +,-,/,* will be available, otherwise, explicit functions must be
  // called. This can be selectively turned on/off for different files
  // depending on performance requirements. 
#ifdef TLOC_VECTOR_ALLOW_EASY_OPERATIONS
#define TLOC_VECTOR_STATIC_ASSERT_EASY_OPERATIONS
#else
#define TLOC_VECTOR_STATIC_ASSERT_EASY_OPERATIONS \
  TLOC_STATIC_ASSERT(false, Operator_operations_unavailable_Use_explicit_functions)
#endif 

  //////////////////////////////////////////////////////////////////////////
  // Misc Macros

  // Note that we have tl_int and not tl_size for the iteration. This is because
  // the [] operator only accepts integers, so we have no choice (either that
  // or we cast the tl_size to tl_int, which defeats the purpose anyway)
#define ITERATE_VECTOR for (tl_int i = 0; i < T_Size; ++i)

  //------------------------------------------------------------------------
  // Constructors

  template <VECTOR_TEMP>
  TL_FI Vector<VECTOR_PARAMS>::Vector()
  { }

  template <VECTOR_TEMP>
  TL_FI Vector<VECTOR_PARAMS>::Vector(const this_type& a_vector)
  {
    *this = a_vector;
  }

  template <VECTOR_TEMP>
  TL_FI Vector<VECTOR_PARAMS>::Vector(const_reference a_value) 
    : base_type(a_value)
  { }

  template <VECTOR_TEMP>
  template <typename T_ArrayType>
  TL_FI Vector<VECTOR_PARAMS>::Vector(const T_ArrayType (&aArray)[T_Size])
    : base_type(aArray)
  { }

  template <VECTOR_TEMP>
  TL_FI Vector<VECTOR_PARAMS>::Vector(const core::Variadic<T, T_Size>& a_vars)
    : base_type(a_vars)
  { }

  //------------------------------------------------------------------------
  // Modifiers

  template <VECTOR_TEMP>
  TL_FI void Vector<VECTOR_PARAMS>::Zero()
  {
    Set(0);
  }

  template <VECTOR_TEMP>
  TL_FI void Vector<VECTOR_PARAMS>::Neg()
  {
    ITERATE_VECTOR
    {
      m_values[i] = -m_values[i];
    }
  }

  template <VECTOR_TEMP>
  TL_FI void Vector<VECTOR_PARAMS>::Neg(const this_type& a_vector)
  {
    operator=(a_vector);
    Neg();
  }

  //------------------------------------------------------------------------
  // Math Operations

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::this_type& 
    Vector<VECTOR_PARAMS>::Add(const this_type& a_vector)
  {
    ITERATE_VECTOR
    {
      m_values[i] += a_vector[i];
    }

    return *this;
  }

  template <VECTOR_TEMP>
  TL_FI void Vector<VECTOR_PARAMS>::Add(const this_type& a_vector1,
                                        const this_type& a_vector2)
  {
    ITERATE_VECTOR
    {
      m_values[i] = a_vector1[i] + a_vector2[i];
    }
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::this_type& 
    Vector<VECTOR_PARAMS>::Sub(const this_type& a_vector)
  {
    ITERATE_VECTOR
    {
      m_values[i] -= a_vector[i];
    }

    return *this;
  }

  template <VECTOR_TEMP>
  TL_FI void Vector<VECTOR_PARAMS>::Sub(const this_type& a_vector1,
                                        const this_type& a_vector2)
  {
    *this = a_vector1;
    Sub(a_vector2);
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::this_type& 
    Vector<VECTOR_PARAMS>::Mul(const this_type& a_vector)
  {
    ITERATE_VECTOR
    {
      m_values[i] *= a_vector[i];
    }

    return *this;
  }

  template <VECTOR_TEMP>
  TL_FI void Vector<VECTOR_PARAMS>::Mul(const this_type& a_vector1,
                                        const this_type& a_vector2)
  {
    *this = a_vector1;
    Mul(a_vector2);
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::this_type& 
    Vector<VECTOR_PARAMS>::Mul(const value_type a_real)
  {
    ITERATE_VECTOR
    {
      m_values[i] *= a_real;
    }

    return *this;
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::this_type& 
    Vector<VECTOR_PARAMS>::Div(const this_type& a_vector)
  {
    ITERATE_VECTOR
    {
      m_values[i] /= a_vector[i];
    }

    return *this;
  }

  template <VECTOR_TEMP>
  TL_FI void Vector<VECTOR_PARAMS>::Div(const this_type& a_vector1,
                                        const this_type& a_vector2)
  {
    operator=(a_vector1);
    Div(a_vector2);
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::this_type& 
    Vector<VECTOR_PARAMS>::Div(const value_type a_real)
  {
    ITERATE_VECTOR
    {
      m_values[i] /= a_real;
    }

    return *this;
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::value_type 
    Vector<VECTOR_PARAMS>::LengthSquared() const
  {
    T lengthSq = 0;

    ITERATE_VECTOR
    {
      lengthSq += (m_values[i] * m_values[i]);
    }

    return lengthSq;
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::value_type 
    Vector<VECTOR_PARAMS>::Length() const
  {
    return DoLength<p_vector::accurate>(*this);
  }

  template <VECTOR_TEMP>
  template <typename T_Accuracy>
  TL_FI VECTOR_TYPE::value_type
    Vector<VECTOR_PARAMS>::DoLength(const this_type& a_vector) const
  {
    value_type length = a_vector.LengthSquared();
    return GetSqrt(length, T_Accuracy());
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::value_type
    Vector<VECTOR_PARAMS>::Norm()
  {
    return Norm<p_vector::accurate>(*this);
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::value_type
    Vector<VECTOR_PARAMS>::Norm(const this_type& a_vector)
  {
    return Norm<p_vector::accurate>(a_vector);
  }

  template <VECTOR_TEMP> 
  template <typename T_Accuracy>
  TL_FI VECTOR_TYPE::value_type 
    Vector<VECTOR_PARAMS>::DoNorm(const this_type& a_vector)
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

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::value_type 
    Vector<VECTOR_PARAMS>::Distance(const this_type& a_vector) const
  {
    return DoDistance<p_vector::accurate>(a_vector);
  }

  template <VECTOR_TEMP> 
  template <typename T_Accuracy>
  TL_FI VECTOR_TYPE::value_type 
    Vector<VECTOR_PARAMS>::DoDistance(const this_type& a_vector) const
  {
    this_type lTemp = *this;
    lTemp.Sub(a_vector);

    value_type length = lTemp.DoLength<T_Accuracy>(lTemp);
    return length;
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::value_type 
    Vector<VECTOR_PARAMS>::DistanceSquared(const this_type& a_vector) const
  {
    this_type lTemp = *this;
    lTemp.Sub(a_vector);

    value_type lengthSq = lTemp.LengthSquared();
    return lengthSq;
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::value_type 
    Vector<VECTOR_PARAMS>::Dot(const this_type& a_vector) const
  {
    value_type dotProd = 0;

    ITERATE_VECTOR
    {
      dotProd += m_values[i] * a_vector[i];
    }

    return dotProd;
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::value_type 
    Vector<VECTOR_PARAMS>::DotAbs(const this_type& a_vector) const
  {
    value_type dotProd = Dot(a_vector);
    return Math<value_type>::Abs(dotProd);
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::this_type& 
    Vector<VECTOR_PARAMS>::Midpoint(const this_type& a_vector)
  {
    ITERATE_VECTOR
    {
      m_values[i] = (m_values[i] + a_vector[i]) * (value_type)0.5;
    }

    return *this;
  }

  template <VECTOR_TEMP>
  TL_FI void Vector<VECTOR_PARAMS>::Midpoint(const this_type& a_vector1,
                                             const this_type& a_vector2)
  {
    *this = a_vector1;
    Midpoint(a_vector2);
  }

  //------------------------------------------------------------------------
  // Operators

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::this_type 
    Vector<VECTOR_PARAMS>::operator+ (const this_type& a_vector) const
  {
    TLOC_VECTOR_STATIC_ASSERT_EASY_OPERATIONS;
    this_type returnVec;
    returnVec = (*this);

    returnVec.Add(a_vector);

    return returnVec;
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::this_type 
    Vector<VECTOR_PARAMS>::operator- (const this_type& a_vector) const
  {
    TLOC_VECTOR_STATIC_ASSERT_EASY_OPERATIONS;
    this_type returnVec;
    returnVec = (*this);

    returnVec.Sub(a_vector);

    return returnVec;
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::this_type 
    Vector<VECTOR_PARAMS>::operator* (const_reference a_value) const
  {
    TLOC_VECTOR_STATIC_ASSERT_EASY_OPERATIONS;
    this_type returnVec;
    returnVec = (*this);

    returnVec.Mul(a_value);

    return returnVec;
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::this_type 
    Vector<VECTOR_PARAMS>::operator* (const this_type& a_vector) const
  {
    TLOC_VECTOR_STATIC_ASSERT_EASY_OPERATIONS;
    this_type returnVec;
    returnVec = (*this);

    returnVec.Mul(a_vector);

    return returnVec;
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::this_type 
    Vector<VECTOR_PARAMS>::operator/ (const_reference a_value) const
  {
    TLOC_VECTOR_STATIC_ASSERT_EASY_OPERATIONS;
    this_type returnVec;
    returnVec = (*this);

    returnVec.Div(a_value);

    return returnVec;
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::this_type 
    Vector<VECTOR_PARAMS>::operator/ (const this_type& a_vector) const
  {
    TLOC_VECTOR_STATIC_ASSERT_EASY_OPERATIONS;
    this_type returnVec;
    returnVec = (*this);

    returnVec.Div(a_vector);

    return returnVec;
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::this_type& 
    Vector<VECTOR_PARAMS>::operator+= (const this_type& a_vector)
  {
    Add(a_vector);

    return (*this);
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::this_type& 
    Vector<VECTOR_PARAMS>::operator-= (const this_type& a_vector)
  {
    Sub(a_vector);

    return (*this);;
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::this_type& 
    Vector<VECTOR_PARAMS>::operator*= (const_reference a_value)
  {
    Mul(a_value);

    return (*this);
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::this_type& 
    Vector<VECTOR_PARAMS>::operator*= (const this_type& a_vector)
  {
    Mul(a_vector);

    return (*this);
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::this_type&
    Vector<VECTOR_PARAMS>::operator/= (const_reference a_value)
  {
    Div(a_value);

    return (*this);
  }

  template <VECTOR_TEMP>
  TL_FI VECTOR_TYPE::this_type&
    Vector<VECTOR_PARAMS>::operator/= (const this_type& a_vector)
  {
    Div(a_vector);

    return (*this);
  }

  template <VECTOR_TEMP>
  TL_FI bool Vector<VECTOR_PARAMS>::operator == (const this_type& a_vector) const
  {
    ITERATE_VECTOR
    {
      if (!Math<value_type>::Approx(m_values[i], a_vector[i])) return false;
    }

    return true;
  }

  template <VECTOR_TEMP>
  TL_FI bool Vector<VECTOR_PARAMS>::operator != (const this_type& a_vector) const
  {
    return !operator==(a_vector);
  }

  //------------------------------------------------------------------------
  // Checks

  template <VECTOR_TEMP>
  TL_FI bool Vector<VECTOR_PARAMS>::IsValid()
  {
    ITERATE_VECTOR
    {
      if (Math<value_type>::IsNaN(m_values[i])) { return false; }
    }

    return true;
  }

  template <VECTOR_TEMP>
  TL_FI bool Vector<VECTOR_PARAMS>::IsZero()
  {
    ITERATE_VECTOR
    {
      if (!Math<value_type>::Approx(m_values[i], 0)) { return false; }
    }

    return true;
  }

};};

#endif
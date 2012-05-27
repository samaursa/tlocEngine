#ifndef TLOC_VECTOR_N_INL
#define TLOC_VECTOR_N_INL

#ifndef TLOC_VECTOR_N_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/tlocAlgorithms.h>
#include "tlocMath.inl"

namespace tloc { namespace math {

  //////////////////////////////////////////////////////////////////////////
  // Vector<N>

  //////////////////////////////////////////////////////////////////////////
  // Template Macros

#define VECTOR_TYPE typename T, tl_size T_Size
#define VECTOR_PARAMS T, T_Size

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

  template <VECTOR_TYPE>
  TL_FI Vector<VECTOR_PARAMS>::Vector()
  {
  }

  template <VECTOR_TYPE>
  TL_FI Vector<VECTOR_PARAMS>::Vector(const this_type& a_vector)
  {
    *this = a_vector;
  }

  template <VECTOR_TYPE>
  TL_FI Vector<VECTOR_PARAMS>::Vector(const_reference a_value) : Tuple(a_value)
  {
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <VECTOR_TYPE>
  TL_FI void Vector<VECTOR_PARAMS>::Zero()
  {
    Set(0);
  }

  template <VECTOR_TYPE>
  TL_FI void Vector<VECTOR_PARAMS>::Neg()
  {
    ITERATE_VECTOR
    {
      m_values[i] = -m_values[i];
    }
  }

  template <VECTOR_TYPE>
  TL_FI void Vector<VECTOR_PARAMS>::Neg(const this_type& a_vector)
  {
    operator=(a_vector);
    Neg();
  }

  //------------------------------------------------------------------------
  // Math Operations

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type& 
    Vector<VECTOR_PARAMS>::Add(const this_type& a_vector)
  {
    ITERATE_VECTOR
    {
      m_values[i] += a_vector[i];
    }

    return *this;
  }

  template <VECTOR_TYPE>
  TL_FI void Vector<VECTOR_PARAMS>::Add(const this_type& a_vector1,
                                        const this_type& a_vector2)
  {
    ITERATE_VECTOR
    {
      m_values[i] = a_vector1[i] + a_vector2[i];
    }
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type& 
    Vector<VECTOR_PARAMS>::Sub(const this_type& a_vector)
  {
    ITERATE_VECTOR
    {
      m_values[i] -= a_vector[i];
    }

    return *this;
  }

  template <VECTOR_TYPE>
  TL_FI void Vector<VECTOR_PARAMS>::Sub(const this_type& a_vector1,
                                        const this_type& a_vector2)
  {
    operator=(a_vector1);
    Sub(a_vector2);
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type& 
    Vector<VECTOR_PARAMS>::Mul(const this_type& a_vector)
  {
    ITERATE_VECTOR
    {
      m_values[i] *= a_vector[i];
    }

    return *this;
  }

  template <VECTOR_TYPE>
  TL_FI void Vector<VECTOR_PARAMS>::Mul(const this_type& a_vector1,
                                        const this_type& a_vector2)
  {
    operator=(a_vector1);
    Mul(a_vector2);
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type& 
    Vector<VECTOR_PARAMS>::Mul(const value_type a_real)
  {
    ITERATE_VECTOR
    {
      m_values[i] *= a_real;
    }

    return *this;
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type& 
    Vector<VECTOR_PARAMS>::Div(const this_type& a_vector)
  {
    ITERATE_VECTOR
    {
      m_values[i] /= a_vector[i];
    }

    return *this;
  }

  template <VECTOR_TYPE>
  TL_FI void Vector<VECTOR_PARAMS>::Div(const this_type& a_vector1,
                                        const this_type& a_vector2)
  {
    operator=(a_vector1);
    Div(a_vector2);
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type& 
    Vector<VECTOR_PARAMS>::Div(const value_type a_real)
  {
    ITERATE_VECTOR
    {
      m_values[i] /= a_real;
    }

    return *this;
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::value_type 
    Vector<VECTOR_PARAMS>::LengthSquared() const
  {
    T lengthSq = 0;

    ITERATE_VECTOR
    {
      lengthSq += (m_values[i] * m_values[i]);
    }

    return lengthSq;
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::value_type 
    Vector<VECTOR_PARAMS>::Length() const
  {
    value_type length = LengthSquared();
    return Math<value_type>::Sqrt(length);
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type& 
    Vector<VECTOR_PARAMS>::Norm()
  {
    value_type lLength = Length();

    if (lLength > 1e-08)
    {
      value_type lInvLength = (value_type)1.0 / lLength;

      ITERATE_VECTOR
      {
        m_values[i] *= lInvLength;
      }
    }

    return *this;
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type& 
    Vector<VECTOR_PARAMS>::Norm(const this_type& a_vector)
  {
    value_type lLength = a_vector.Length();

    if (lLength > 1e-08)
    {
      value_type lInvLength = (value_type)1.0 / lLength;

      ITERATE_VECTOR
      {
        m_values[i] = a_vector[i] * lInvLength;
      }
    }

    return *this;
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::value_type 
    Vector<VECTOR_PARAMS>::NormLength()
  {
    value_type lLength = Length();

    if (lLength > 1e-08)
    {
      value_type lInvLength = (value_type)1.0 / lLength;

      ITERATE_VECTOR
      {
        m_values[i] *= lInvLength;
      }
    }

    return lLength;
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::value_type 
    Vector<VECTOR_PARAMS>::NormLength(const this_type& a_vector)
  {
    value_type lLength = a_vector.Length();

    if (lLength > 1e-08)
    {
      value_type lInvLength = (value_type)1.0 / lLength;

      ITERATE_VECTOR
      {
        m_values[i] = a_vector[i] * lInvLength;
      }
    }

    return lLength;
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::value_type 
    Vector<VECTOR_PARAMS>::Distance(const this_type& a_vector) const
  {
    this_type lTemp = *this;
    lTemp.Sub(a_vector);

    value_type length = lTemp.Length();
    return length;
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::value_type 
    Vector<VECTOR_PARAMS>::DistanceSquared(const this_type& a_vector) const
  {
    this_type lTemp = *this;
    lTemp.Sub(a_vector);

    value_type lengthSq = lTemp.LengthSquared();
    return lengthSq;
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::value_type 
    Vector<VECTOR_PARAMS>::Dot(const this_type& a_vector) const
  {
    value_type dotProd = 0;

    ITERATE_VECTOR
    {
      dotProd += m_values[i] * a_vector[i];
    }

    return dotProd;
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::value_type 
    Vector<VECTOR_PARAMS>::DotAbs(const this_type& a_vector) const
  {
    value_type dotProd = Dot(a_vector);
    return Math<value_type>::Abs(dotProd);
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type& 
    Vector<VECTOR_PARAMS>::Midpoint(const this_type& a_vector)
  {
    ITERATE_VECTOR
    {
      m_values[i] = (m_values[i] + a_vector[i]) * (value_type)0.5;
    }

    return *this;
  }

  template <VECTOR_TYPE>
  TL_FI void Vector<VECTOR_PARAMS>::Midpoint(const this_type& a_vector1,
                                             const this_type& a_vector2)
  {
    operator=(a_vector1);
    Midpoint(a_vector2);
  }

  //------------------------------------------------------------------------
  // Operators

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type 
    Vector<VECTOR_PARAMS>::operator+ (const this_type& a_vector)
  {
    TLOC_VECTOR_STATIC_ASSERT_EASY_OPERATIONS;
    this_type returnVec;
    returnVec = (*this);

    returnVec.Add(a_vector);

    return returnVec;
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type 
    Vector<VECTOR_PARAMS>::operator- (const this_type& a_vector)
  {
    TLOC_VECTOR_STATIC_ASSERT_EASY_OPERATIONS;
    this_type returnVec;
    returnVec = (*this);

    returnVec.Sub(a_vector);

    return returnVec;
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type 
    Vector<VECTOR_PARAMS>::operator* (const value_type& a_value)
  {
    TLOC_VECTOR_STATIC_ASSERT_EASY_OPERATIONS;
    this_type returnVec;
    returnVec = (*this);

    returnVec.Mul(a_value);

    return returnVec;
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type 
    Vector<VECTOR_PARAMS>::operator* (const this_type& a_vector)
  {
    TLOC_VECTOR_STATIC_ASSERT_EASY_OPERATIONS;
    this_type returnVec;
    returnVec = (*this);

    returnVec.Mul(a_vector);

    return returnVec;
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type 
    Vector<VECTOR_PARAMS>::operator/ (const value_type& a_value)
  {
    TLOC_VECTOR_STATIC_ASSERT_EASY_OPERATIONS;
    this_type returnVec;
    returnVec = (*this);

    returnVec.Div(a_value);

    return returnVec;
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type 
    Vector<VECTOR_PARAMS>::operator/ (const this_type& a_vector)
  {
    TLOC_VECTOR_STATIC_ASSERT_EASY_OPERATIONS;
    this_type returnVec;
    returnVec = (*this);

    returnVec.Div(a_vector);

    return returnVec;
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type& 
    Vector<VECTOR_PARAMS>::operator+= (const this_type& a_vector)
  {
    this->Add(a_vector);

    return (*this);
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type& 
    Vector<VECTOR_PARAMS>::operator-= (const this_type& a_vector)
  {
    this->Sub(a_vector);

    return (*this);;
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type& 
    Vector<VECTOR_PARAMS>::operator*= (const value_type& a_value)
  {
    this->Mul(a_value);

    return (*this);
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type& 
    Vector<VECTOR_PARAMS>::operator*= (const this_type& a_vector)
  {
    this->Mul(a_vector);

    return (*this);
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type&
    Vector<VECTOR_PARAMS>::operator/= (const value_type& a_value)
  {
    this->Div(a_value);

    return (*this);
  }

  template <VECTOR_TYPE>
  TL_FI typename Vector<VECTOR_PARAMS>::this_type&
    Vector<VECTOR_PARAMS>::operator/= (const this_type& a_vector)
  {
    this->Div(a_vector);

    return (*this);
  }

  template <VECTOR_TYPE>
  TL_FI bool Vector<VECTOR_PARAMS>::operator == (const this_type& a_vector)
  {
    ITERATE_VECTOR
    {
      if (!Math<value_type>::Approx(m_values[i], a_vector[i])) return false;
    }

    return true;
  }

  template <VECTOR_TYPE>
  TL_FI bool Vector<VECTOR_PARAMS>::operator != (const this_type& a_vector)
  {
    return !operator==(a_vector);
  }

  //------------------------------------------------------------------------
  // Checks

  template <VECTOR_TYPE>
  TL_FI bool Vector<VECTOR_PARAMS>::IsValid()
  {
    ITERATE_VECTOR
    {
      if (Math<value_type>::IsNaN(m_values[i])) { return false; }
    }

    return true;
  }

  template <VECTOR_TYPE>
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
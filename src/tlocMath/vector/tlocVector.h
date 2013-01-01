#pragma once
#ifndef TLOC_VECTOR_N_H
#define TLOC_VECTOR_N_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/data_structures/tlocVariadic.h>

#include "tlocMath/tlocMath.h"



// If defined, simple assertions will be enabled in this class. Enabled by
// default in debug
#ifdef TLOC_DEBUG
#define TLOC_VECTOR_ENABLE_ASSERTS
#endif

// If assertions are not enabled, we do not want TLOC_ASSERT to work anymore
#ifdef TLOC_VECTOR_ENABLE_ASSERTS
#define TLOC_ASSERT_VEC(_Expression, _Msg) TLOC_ASSERT(_Expression, _Msg)
#else
#define TLOC_ASSERT_VEC(_Expression, _Msg)
#endif

namespace tloc { namespace math {

  //////////////////////////////////////////////////////////////////////////
  // Vector<N>

  namespace p_vector
  {
    struct    accurate{};
    struct    fast{};
  };

  template <typename T, tl_size T_Size>
  class Vector : public core::Tuple<T, T_Size>
  {
  public:
    enum { k_size = T_Size };

  public:
    //------------------------------------------------------------------------
    // typedefs (similar to std containers)
    typedef Vector<T, T_Size>                     this_type;
    typedef core::Tuple<T, T_Size>                base_type;

    typedef typename base_type::value_type        value_type;
    typedef typename base_type::size_type         size_type;
    typedef value_type&                           reference;
    typedef value_type const&                     const_reference;

    //------------------------------------------------------------------------
    // using declarations for access to base class
    using base_type::Set;
    using base_type::m_values;

    //------------------------------------------------------------------------
    // Constructors

    // Empty default constructor
    TL_FI Vector();
    TL_FI Vector(const this_type& a_vector);

    template <typename T_ArrayType>
    TL_FI Vector(const T_ArrayType (&aArray)[T_Size]);

    TL_FI Vector(const core::Variadic<T, T_Size>& a_vars);

    TL_FI explicit Vector(const_reference a_value);

    //------------------------------------------------------------------------
    // Modifiers

    // Modifies this vector so that all values are zero. The vector must
    // be of numerical types
    TL_FI void        Zero();

    // Negate this vector
    TL_FI void        Neg();

    // Modifies this vector by storing the negation of the incoming vector
    TL_FI void        Neg(const this_type& a_vector);

    //// All values of this vector will equal the incoming vector
    //TL_FI Vector<T, aSize>& operator=(const Vector<T, aSize>& aVector);

    //------------------------------------------------------------------------
    // Math Operations

    // Modifies this vector by adding the incoming vector
    TL_FI this_type&  Add(const this_type& a_vector);

    // Modifies this vector by adding the incoming vectors and storing the
    // result in this vector
    TL_FI void        Add(const this_type& a_vector1,
                          const this_type& a_vector2);

    // Modifies this vector by subtracting the incoming vector
    TL_FI this_type&  Sub(const this_type& a_vector);

    // Modifies this vector by subtracting the incoming vectors and storing
    // the result in this vector
    TL_FI void        Sub(const this_type& a_vector1,
                          const this_type& a_vector2);

    // Multiply each element of this vector by the elements of the incoming
    // Vector
    TL_FI this_type&  Mul(const this_type& a_vector);

    // Modifies this vector by multiplying the incoming vectors and storing
    // the result in this vector
    TL_FI void        Mul(const this_type& a_vector1,
                          const this_type& a_vector2);

    // Multiplies each element of this vector by the constant and stores the
    // the result in this vector
    TL_FI this_type&  Mul(const value_type a_real);

    // Divides each element of this vector by the elements of the incoming
    // Vector
    TL_FI this_type&  Div(const this_type& a_vector);

    // Modifies this vector by dividing the incoming vectors and storing
    // the result in this vector
    TL_FI void        Div(const this_type& a_vector1,
                          const this_type& a_vector2);

    // Divides each element of this vector by the constant and stores the
    // the result in this vector
    TL_FI this_type&  Div(const value_type a_real);

    // Faster then Length()
    TL_FI value_type  LengthSquared() const;

    // Same as Length() but returns the value instead
    TL_FI value_type  Length() const;
    template <typename T_Accuracy>
    TL_FI value_type  Length() const
    {
      type_traits::AssertTypeIsSupported
        <T_Accuracy, p_vector::fast, p_vector::accurate>();
      return DoLength<T_Accuracy>(*this);
    }

    // Normalizes this vector
    TL_FI value_type Norm();
    template <typename T_Accuracy>
    TL_FI value_type Norm()
    {
      type_traits::AssertTypeIsSupported
        <T_Accuracy, p_vector::fast, p_vector::accurate>();
      return DoNorm<T_Accuracy>(*this);
    }

    // Modifies this vector to store the normalized version of the incoming
    // vector.
    TL_FI value_type Norm(const this_type& a_vector);
    template <typename T_Accuracy>
    TL_FI value_type Norm(const this_type& a_vector)
    {
      type_traits::AssertTypeIsSupported
        <T_Accuracy, p_vector::fast, p_vector::accurate>();
      return DoNorm<T_Accuracy>(a_vector);
    }

    TL_FI value_type  Distance(const this_type& a_vector) const;
    template <typename T_Accuracy>
    TL_FI value_type  Distance(const this_type& a_vector) const
    {
      type_traits::AssertTypeIsSupported
        <T_Accuracy, p_vector::fast, p_vector::accurate>();
      return DoDistance<T_Accuracy>(a_vector);
    }

    // Returns the distance squared between two vectors (faster than
    // Distance())
    TL_FI value_type  DistanceSquared(const this_type& a_vector) const;

    // Returns the dot product between this and the incoming vector
    TL_FI value_type  Dot(const this_type& a_vector) const;

    // Returns the absolute dot product between this and the incoming vector
    TL_FI value_type  DotAbs(const this_type& a_vector) const;

    // Modifies this vector by storing the midpoint between this vector
    // and the incoming vector
    TL_FI this_type&  Midpoint(const this_type& a_vector);

    // Modifies this vector by storing the midpoint between the two
    // incoming vectors
    TL_FI void        Midpoint(const this_type& a_vector1,
                               const this_type& a_vector2);

    //------------------------------------------------------------------------
    // Operators

    TL_FI this_type   operator+ (const this_type& a_vector) const;
    TL_FI this_type   operator- (const this_type& a_vector) const;
    TL_FI this_type   operator* (const_reference a_value) const;
    TL_FI this_type   operator* (const this_type& a_vector) const;
    TL_FI this_type   operator/ (const value_type& a_value) const;
    TL_FI this_type   operator/ (const this_type& a_vector) const;

    TL_FI this_type&  operator+= (const this_type& a_vector);
    TL_FI this_type&  operator-= (const this_type& a_vector);
    TL_FI this_type&  operator*= (const_reference a_value);
    TL_FI this_type&  operator*= (const this_type& a_vector);
    TL_FI this_type&  operator/= (const_reference a_value);
    TL_FI this_type&  operator/= (const this_type& a_vector);

    TL_FI bool        operator == (const this_type& a_vector) const;
    TL_FI bool        operator != (const this_type& a_vector) const;

    //------------------------------------------------------------------------
    // Checks

    // Returns false if the vector's values are invalid (NaN)
    TL_FI bool        IsValid();
    TL_FI bool        IsZero();

    //------------------------------------------------------------------------
    // Special vectors

    static const this_type ZERO;
    static const this_type ONE;

  private:

    template <typename T_Accuracy>
    value_type DoLength(const this_type& a_vector) const;

    template <typename T_Accuracy>
    value_type DoNorm(const this_type& a_vector);

    template <typename T_Accuracy>
    value_type DoDistance(const this_type& a_vector) const;

  };

  //------------------------------------------------------------------------
  // Static const definitions
  template<typename T, tl_size T_Size>
  const typename Vector<T, T_Size>::this_type Vector<T, T_Size>::ZERO =
    typename Vector<T, T_Size>::this_type(0);

  template<typename T, tl_size T_Size>
  const typename Vector<T, T_Size>::this_type Vector<T, T_Size>::ONE =
    typename Vector<T, T_Size>::this_type(1);

  //------------------------------------------------------------------------
  // Global operators

  template <typename T, tl_size T_Size>
  Vector<T, T_Size> operator* (T a_lhs, const Vector<T, T_Size>& a_rhs)
  {
    return a_rhs.operator*(a_lhs);
  }

  template <typename T, tl_size T_Size>
  Vector<T, T_Size> operator/ (T a_lhs, const Vector<T, T_Size>& a_rhs)
  {
    return a_rhs.operator/(a_lhs);
  }

};};

#endif
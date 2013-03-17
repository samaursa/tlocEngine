#pragma once
#ifndef TLOC_VECTOR_N_H
#define TLOC_VECTOR_N_H

#include <tlocMath/tlocMathBase.h>

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

namespace tloc { namespace math { namespace types {

  //////////////////////////////////////////////////////////////////////////
  // Vector<N>

  namespace p_vector
  {
    struct    accurate{};
    struct    fast{};
  };

  template <typename T, tl_size T_Size>
  class Vector : public core::data_structs::Tuple<T, T_Size>
  {
  public:
    TLOC_STATIC_ASSERT_IS_ARITH(T);

  public:
    enum { k_size = T_Size };

  public:
    //------------------------------------------------------------------------
    // typedefs (similar to std containers)
    typedef Vector<T, T_Size>                     this_type;
    typedef core::data_structs::Tuple<T, T_Size>  base_type;

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
    Vector();
    Vector(const base_type& a_vector);

    template <typename T_ArrayType>
    Vector(const T_ArrayType (&aArray)[T_Size]);

    Vector(const core::data_structs::Variadic<T, T_Size>& a_vars);

    explicit Vector(const_reference a_value);

    //------------------------------------------------------------------------
    // Modifiers

    // Modifies this vector so that all values are zero. The vector must
    // be of numerical types
    void        Zero();

    // Negate this vector
    void        Neg();

    // Modifies this vector by storing the negation of the incoming vector
    void        Neg(const this_type& a_vector);

    //// All values of this vector will equal the incoming vector
    //Vector<T, aSize>& operator=(const Vector<T, aSize>& aVector);

    //------------------------------------------------------------------------
    // Math Operations

    // Modifies this vector by adding the incoming vector
    this_type&  Add(const this_type& a_vector);

    // Modifies this vector by adding the incoming vectors and storing the
    // result in this vector
    void        Add(const this_type& a_vector1,
                          const this_type& a_vector2);

    // Modifies this vector by subtracting the incoming vector
    this_type&  Sub(const this_type& a_vector);

    // Modifies this vector by subtracting the incoming vectors and storing
    // the result in this vector
    void        Sub(const this_type& a_vector1,
                          const this_type& a_vector2);

    // Multiply each element of this vector by the elements of the incoming
    // Vector
    this_type&  Mul(const this_type& a_vector);

    // Modifies this vector by multiplying the incoming vectors and storing
    // the result in this vector
    void        Mul(const this_type& a_vector1,
                          const this_type& a_vector2);

    // Multiplies each element of this vector by the constant and stores the
    // the result in this vector
    this_type&  Mul(const value_type a_real);

    // Divides each element of this vector by the elements of the incoming
    // Vector
    this_type&  Div(const this_type& a_vector);

    // Modifies this vector by dividing the incoming vectors and storing
    // the result in this vector
    void        Div(const this_type& a_vector1,
                          const this_type& a_vector2);

    // Divides each element of this vector by the constant and stores the
    // the result in this vector
    this_type&  Div(const value_type a_real);

    // Faster then Length()
    value_type  LengthSquared() const;

    // Same as Length() but returns the value instead
    value_type  Length() const;
    template <typename T_Accuracy>
    value_type  Length() const;

    // Normalizes this vector
    value_type  Norm();
    template <typename T_Accuracy>
    value_type  Norm();

    // Modifies this vector to store the normalized version of the incoming
    // vector.
    value_type  Norm(const this_type& a_vector);
    template <typename T_Accuracy>
    value_type  Norm(const this_type& a_vector);

    value_type  Distance(const this_type& a_vector) const;
    template <typename T_Accuracy>
    value_type  Distance(const this_type& a_vector) const;

    // Returns the distance squared between two vectors (faster than
    // Distance())
    value_type  DistanceSquared(const this_type& a_vector) const;

    // Returns the dot product between this and the incoming vector
    value_type  Dot(const this_type& a_vector) const;

    // Returns the absolute dot product between this and the incoming vector
    value_type  DotAbs(const this_type& a_vector) const;

    // Modifies this vector by storing the midpoint between this vector
    // and the incoming vector
    this_type&  Midpoint(const this_type& a_vector);

    // Modifies this vector by storing the midpoint between the two
    // incoming vectors
    void        Midpoint(const this_type& a_vector1,
                               const this_type& a_vector2);

    //------------------------------------------------------------------------
    // Operators

    this_type   operator+ (const this_type& a_vector) const;
    this_type   operator- (const this_type& a_vector) const;
    this_type   operator* (const_reference a_value) const;
    this_type   operator* (const this_type& a_vector) const;
    this_type   operator/ (const value_type& a_value) const;
    this_type   operator/ (const this_type& a_vector) const;

    this_type&  operator+= (const this_type& a_vector);
    this_type&  operator-= (const this_type& a_vector);
    this_type&  operator*= (const_reference a_value);
    this_type&  operator*= (const this_type& a_vector);
    this_type&  operator/= (const_reference a_value);
    this_type&  operator/= (const this_type& a_vector);

    bool        operator == (const this_type& a_vector) const;
    bool        operator != (const this_type& a_vector) const;

    //------------------------------------------------------------------------
    // Checks

    // Returns false if the vector's values are invalid (NaN)
    bool        IsValid();
    bool        IsZero();

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
  // Template definitions

  template <typename T, tl_size T_Size>
  template <typename T_Accuracy>
  typename Vector<T, T_Size>::value_type
    Vector<T, T_Size>::
    Length() const
  {
    type_traits::AssertTypeIsSupported
      <T_Accuracy, p_vector::fast, p_vector::accurate>();
    return DoLength<T_Accuracy>(*this);
  }

  template <typename T, tl_size T_Size>
  template <typename T_Accuracy>
  typename Vector<T, T_Size>::value_type
    Vector<T, T_Size>::
    Norm()
  {
    type_traits::AssertTypeIsSupported
      <T_Accuracy, p_vector::fast, p_vector::accurate>();
    return DoNorm<T_Accuracy>(*this);
  }

  template <typename T, tl_size T_Size>
  template <typename T_Accuracy>
  typename Vector<T, T_Size>::value_type
    Vector<T, T_Size>::
    Norm(const this_type& a_vector)
  {
    type_traits::AssertTypeIsSupported
      <T_Accuracy, p_vector::fast, p_vector::accurate>();
    return DoNorm<T_Accuracy>(a_vector);
  }

  template <typename T, tl_size T_Size>
  template <typename T_Accuracy>
  typename Vector<T, T_Size>::value_type
    Vector<T, T_Size>::
    Distance(const this_type& a_vector) const
  {
    type_traits::AssertTypeIsSupported
      <T_Accuracy, p_vector::fast, p_vector::accurate>();
    return DoDistance<T_Accuracy>(a_vector);
  }

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

};};};

#endif
#pragma once
#ifndef TLOC_VECTOR_N_H
#define TLOC_VECTOR_N_H

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/tlocStaticAssert.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/data_structures/tlocVariadic.h>

#include "tlocMath/tlocMath.h"

namespace tloc { namespace math { namespace types {

  //////////////////////////////////////////////////////////////////////////
  // Vector_T<N>

  namespace p_vector
  {
    struct    accurate{};
    struct    fast{};
  };

  template <typename T, tl_size T_Size>
  class Vector_TI
    : public core::data_structs::Tuple<T, T_Size>
  {
  public:
    TLOC_STATIC_ASSERT_IS_ARITH(T);

  public:
    enum { k_size = T_Size };

  public:
    //------------------------------------------------------------------------
    // typedefs (similar to std containers)
    typedef Vector_TI<T, T_Size>                  this_type;
    typedef core::data_structs::Tuple<T, T_Size>  base_type;

    typedef typename base_type::value_type        value_type;
    typedef typename base_type::size_type         size_type;
    typedef value_type&                           reference;
    typedef value_type const&                     const_reference;

    //------------------------------------------------------------------------
    // Constructors

    // Empty default constructor
    Vector_TI();
    explicit Vector_TI(value_type a_value);
    Vector_TI(const core::data_structs::Variadic<T, T_Size>& a_vars);

    template <typename T_Real>
    Vector_TI(const core_ds::Tuple<T_Real, T_Size>& a_vector);

    template <typename T_ArrayType>
    Vector_TI(const T_ArrayType (&aArray)[T_Size]);

    //------------------------------------------------------------------------
    // Modifiers

    void        MakeZero();
    this_type   Inverse() const;
    void        Inverse(const this_type& a_vector);

    //------------------------------------------------------------------------
    // Math Operations

    this_type   Add(const this_type& a_vector) const;
    void        Add(const this_type& a_vector1, const this_type& a_vector2);

    this_type   Sub(const this_type& a_vector) const;
    void        Sub(const this_type& a_vector1, const this_type& a_vector2);

    this_type   Mul(const this_type& a_vector) const;
    void        Mul(const this_type& a_vector1, const this_type& a_vector2);
    this_type   Mul(const value_type a_real) const;
    void        Mul(const this_type& a_vector, const value_type a_real);

    this_type   Div(const this_type& a_vector) const;
    void        Div(const this_type& a_vector1, const this_type& a_vector2);
    this_type   Div(const value_type a_real) const;
    void        Div(const this_type& a_vector, const value_type a_real);

    value_type  LengthSquared() const;

    value_type  Length() const;
    template <typename T_Accuracy>
    value_type  Length() const;

    value_type  Normalize();
    value_type  Normalize(const this_type& a_vector);
    template <typename T_Accuracy>
    value_type  Normalize();
    template <typename T_Accuracy>
    value_type  Normalize(const this_type& a_vector);

    value_type  Distance(const this_type& a_vector) const;
    template <typename T_Accuracy>
    value_type  Distance(const this_type& a_vector) const;

    value_type  DistanceSquared(const this_type& a_vector) const;

    value_type  Dot(const this_type& a_vector) const;
    value_type  DotAbs(const this_type& a_vector) const;

    this_type   Midpoint(const this_type& a_vector) const;
    void        Midpoint(const this_type& a_vector1,
                         const this_type& a_vector2);

    //------------------------------------------------------------------------
    // Operators

    this_type   operator+ (const this_type& a_vector) const;
    this_type   operator- (const this_type& a_vector) const;
    this_type   operator* (      value_type a_value) const;
    this_type   operator* (const this_type& a_vector) const;
    this_type   operator/ (      value_type a_value) const;
    this_type   operator/ (const this_type& a_vector) const;

    this_type&  operator+= (const this_type& a_vector);
    this_type&  operator-= (const this_type& a_vector);
    this_type&  operator*= (      value_type a_value);
    this_type&  operator*= (const this_type& a_vector);
    this_type&  operator/= (      value_type a_value);
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

    // -----------------------------------------------------------------------
    // base functions

    using base_type::Get;
    using base_type::data;
    using base_type::Set;
    using base_type::ConvertFrom;
    using base_type::ConvertTo;
    using base_type::Cast;
    using base_type::operator[];

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
  const typename Vector_TI<T, T_Size>::this_type 
    Vector_TI<T, T_Size>::ZERO = typename Vector_TI<T, T_Size>::this_type(0);

  template<typename T, tl_size T_Size>
  const typename Vector_TI<T, T_Size>::this_type 
    Vector_TI<T, T_Size>::ONE = typename Vector_TI<T, T_Size>::this_type(1);

  //------------------------------------------------------------------------
  // Template definitions

  template <typename T, tl_size T_Size>
  template <typename T_Real>
  Vector_TI<T, T_Size>::
    Vector_TI(const core_ds::Tuple<T_Real, T_Size>& a_vector)
      : base_type(a_vector)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, tl_size T_Size>
  template <typename T_Accuracy>
  typename Vector_TI<T, T_Size>::value_type
    Vector_TI<T, T_Size>::
    Length() const
  {
    type_traits::AssertTypeIsSupported
      <T_Accuracy, p_vector::fast, p_vector::accurate>();
    return DoLength<T_Accuracy>(*this);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, tl_size T_Size>
  template <typename T_Accuracy>
  typename Vector_TI<T, T_Size>::value_type
    Vector_TI<T, T_Size>::
    Normalize()
  {
    type_traits::AssertTypeIsSupported
      <T_Accuracy, p_vector::fast, p_vector::accurate>();
    return DoNorm<T_Accuracy>(*this);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, tl_size T_Size>
  template <typename T_Accuracy>
  typename Vector_TI<T, T_Size>::value_type
    Vector_TI<T, T_Size>::
    Normalize(const this_type& a_vector)
  {
    type_traits::AssertTypeIsSupported
      <T_Accuracy, p_vector::fast, p_vector::accurate>();
    return DoNorm<T_Accuracy>(a_vector);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, tl_size T_Size>
  template <typename T_Accuracy>
  typename Vector_TI<T, T_Size>::value_type
    Vector_TI<T, T_Size>::
    Distance(const this_type& a_vector) const
  {
    type_traits::AssertTypeIsSupported
      <T_Accuracy, p_vector::fast, p_vector::accurate>();
    return DoDistance<T_Accuracy>(a_vector);
  }

  //------------------------------------------------------------------------
  // Global operators

  template <typename T, tl_size T_Size>
  Vector_TI<T, T_Size> 
    operator* (T a_lhs, const Vector_TI<T, T_Size>& a_rhs)
  {
    return a_rhs.operator*(a_lhs);
  }

  template <typename T, tl_size T_Size>
  Vector_TI<T, T_Size> 
    operator/ (T a_lhs, const Vector_TI<T, T_Size>& a_rhs)
  {
    return a_rhs.operator/(a_lhs);
  }

  // ///////////////////////////////////////////////////////////////////////
  // VectorT<>

  template <typename T, tl_size T_Size>
  class Vector_T;

};};};

#endif
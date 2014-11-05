#pragma once
#ifndef _TLOC_VECTOR_N_H_
#define _TLOC_VECTOR_N_H_

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

  template <typename T, tl_size T_Size, typename T_Derived = DummyStruct>
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
    typedef Vector_TI<T, T_Size, T_Derived>               this_type;
    typedef core::data_structs::Tuple<T, T_Size>          base_type;

    // select this_type as the derived_type if no derived type was passed
    typedef typename Loki::Select
      <Loki::IsSameType<T_Derived, DummyStruct>::value, 
       this_type, T_Derived>::Result                      derived_type;

    typedef typename base_type::value_type                value_type;
    typedef typename base_type::size_type                 size_type;
    typedef value_type&                                   reference;
    typedef value_type const&                             const_reference;

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

    void          MakeZero();
    derived_type  Inverse() const;
    void          Inverse(const this_type& a_vector);

    //------------------------------------------------------------------------
    // Math Operations

    derived_type  Add(const this_type& a_vector) const;
    void          Add(const this_type& a_vector1, const this_type& a_vector2);

    derived_type  Sub(const this_type& a_vector) const;
    void          Sub(const this_type& a_vector1, const this_type& a_vector2);

    derived_type  Mul(const this_type& a_vector) const;
    void          Mul(const this_type& a_vector1, const this_type& a_vector2);
    derived_type  Mul(const value_type a_real) const;
    void          Mul(const this_type& a_vector, const value_type a_real);

    derived_type  Div(const this_type& a_vector) const;
    void          Div(const this_type& a_vector1, const this_type& a_vector2);
    derived_type  Div(const value_type a_real) const;
    void          Div(const this_type& a_vector, const value_type a_real);

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

    bool        IsParallel(const this_type& a_vector) const;

    derived_type  Midpoint(const this_type& a_vector) const;
    void          Midpoint(const this_type& a_vector1,
                           const this_type& a_vector2);

    //------------------------------------------------------------------------
    // Operators

    derived_type   operator+ (const this_type& a_vector) const;
    derived_type   operator- (const this_type& a_vector) const;
    derived_type   operator* (      value_type a_value) const;
    derived_type   operator* (const this_type& a_vector) const;
    derived_type   operator/ (      value_type a_value) const;
    derived_type   operator/ (const this_type& a_vector) const;

    derived_type&  operator+= (const this_type& a_vector);
    derived_type&  operator-= (const this_type& a_vector);
    derived_type&  operator*= (      value_type a_value);
    derived_type&  operator*= (const this_type& a_vector);
    derived_type&  operator/= (      value_type a_value);
    derived_type&  operator/= (const this_type& a_vector);

    bool        operator == (const this_type& a_vector) const;
    bool        operator != (const this_type& a_vector) const;

    //------------------------------------------------------------------------
    // Checks

    // Returns false if the vector's values are invalid (NaN)
    bool        IsValid();
    bool        IsZero();

    //------------------------------------------------------------------------
    // Special vectors

    static const derived_type ZERO;
    static const derived_type ONE;

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
    
  protected:
    using base_type::m_values;

  };

  //------------------------------------------------------------------------
  // Static const definitions
  template<typename T, tl_size T_Size, typename T_DT>
  const typename Vector_TI<T, T_Size, T_DT>::derived_type 
    Vector_TI<T, T_Size, T_DT>::ZERO = 
    typename Vector_TI<T, T_Size, T_DT>::derived_type(0);

  template<typename T, tl_size T_Size, typename T_DT>
  const typename Vector_TI<T, T_Size, T_DT>::derived_type 
    Vector_TI<T, T_Size, T_DT>::ONE = 
    typename Vector_TI<T, T_Size, T_DT>::derived_type(1);

  //------------------------------------------------------------------------
  // Template definitions

  template <typename T, tl_size T_Size, typename T_DerivedType>
  template <typename T_Real>
  Vector_TI<T, T_Size, T_DerivedType>::
    Vector_TI(const core_ds::Tuple<T_Real, T_Size>& a_vector)
      : base_type(a_vector)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, tl_size T_Size, typename T_DerivedType>
  template <typename T_Accuracy>
  typename Vector_TI<T, T_Size, T_DerivedType>::value_type
    Vector_TI<T, T_Size, T_DerivedType>::
    Length() const
  {
    type_traits::AssertTypeIsSupported
      <T_Accuracy, p_vector::fast, p_vector::accurate>();
    return DoLength<T_Accuracy>(*this);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, tl_size T_Size, typename T_DerivedType>
  template <typename T_Accuracy>
  typename Vector_TI<T, T_Size, T_DerivedType>::value_type
    Vector_TI<T, T_Size, T_DerivedType>::
    Normalize()
  {
    type_traits::AssertTypeIsSupported
      <T_Accuracy, p_vector::fast, p_vector::accurate>();
    return DoNorm<T_Accuracy>(*this);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, tl_size T_Size, typename T_DerivedType>
  template <typename T_Accuracy>
  typename Vector_TI<T, T_Size, T_DerivedType>::value_type
    Vector_TI<T, T_Size, T_DerivedType>::
    Normalize(const this_type& a_vector)
  {
    type_traits::AssertTypeIsSupported
      <T_Accuracy, p_vector::fast, p_vector::accurate>();
    return DoNorm<T_Accuracy>(a_vector);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, tl_size T_Size, typename T_DerivedType>
  template <typename T_Accuracy>
  typename Vector_TI<T, T_Size, T_DerivedType>::value_type
    Vector_TI<T, T_Size, T_DerivedType>::
    Distance(const this_type& a_vector) const
  {
    type_traits::AssertTypeIsSupported
      <T_Accuracy, p_vector::fast, p_vector::accurate>();
    return DoDistance<T_Accuracy>(a_vector);
  }

  //------------------------------------------------------------------------
  // Global operators

  template <typename T, tl_size T_Size, typename T_DT>
  typename Vector_TI<T, T_Size, T_DT>::derived_type
    operator* (T a_lhs, const Vector_TI<T, T_Size, T_DT>& a_rhs)
  {
    return a_rhs.operator*(a_lhs);
  }

  template <typename T, tl_size T_Size, typename T_DT>
  typename Vector_TI<T, T_Size, T_DT>::derived_type
    operator/ (T a_lhs, const Vector_TI<T, T_Size, T_DT>& a_rhs)
  {
    return a_rhs.operator/(a_lhs);
  }

  // ///////////////////////////////////////////////////////////////////////
  // VectorT<>

  template <typename T, tl_size T_Size>
  class Vector_T;

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(Vector_TI<f32 TLOC_COMMA 2>);
  TLOC_EXTERN_TEMPLATE_CLASS(Vector_TI<f32 TLOC_COMMA 3>);
  TLOC_EXTERN_TEMPLATE_CLASS(Vector_TI<f32 TLOC_COMMA 4>);

  TLOC_EXTERN_TEMPLATE_CLASS(Vector_TI<f64 TLOC_COMMA 2>);
  TLOC_EXTERN_TEMPLATE_CLASS(Vector_TI<f64 TLOC_COMMA 3>);
  TLOC_EXTERN_TEMPLATE_CLASS(Vector_TI<f64 TLOC_COMMA 4>);

};};};

#endif
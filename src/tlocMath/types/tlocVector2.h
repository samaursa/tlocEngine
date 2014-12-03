#pragma once
#ifndef TLOC_VECTOR_2_H
#define TLOC_VECTOR_2_H

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/tlocAlgorithms.h>

#include <tlocMath/tlocMath.h>
#include <tlocMath/types/tlocVector.h>

namespace tloc { namespace math { namespace types {

  //////////////////////////////////////////////////////////////////////////
  // Vector_T<T, 2>

  template<typename T>
  class Vector_T<T, 2> 
    : public Vector_TI<T, 2, Vector_T<T, 2> >
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T);

  public:
    //------------------------------------------------------------------------
    // typedefs (similar to std containers)
    typedef Vector_T<T, 2>                         this_type;
    typedef Vector_TI<T, 2, this_type>             base_type;

    typedef typename base_type::value_type        value_type;
    typedef typename base_type::reference         reference;
    typedef typename base_type::const_reference   const_reference;

  public:
    //------------------------------------------------------------------------
    // Constructors
    Vector_T();
    Vector_T(value_type aX, value_type aY);
    Vector_T(const this_type& aVector);
    Vector_T(const base_type& aVector);
    Vector_T(const core::data_structs::Variadic<value_type, 2>& a_vars);

    explicit Vector_T(const_reference aValue);

    // -----------------------------------------------------------------------
    // base functions

    using base_type::Get;
    using base_type::data;
    using base_type::Set;
    using base_type::ConvertFrom;
    using base_type::ConvertTo;
    using base_type::Cast;
    using base_type::operator[];
    using base_type::Length;
    using base_type::LengthSquared;
    using base_type::IsParallel;

  public:
    static const Vector_T ZERO;
    static const Vector_T UNIT_X;
    static const Vector_T UNIT_Y;
    static const Vector_T NEG_UNIT_X;
    static const Vector_T NEG_UNIT_Y;

  private:
    using base_type::m_values;
  };

  //------------------------------------------------------------------------
  // Typedefs
  typedef Vector_T<f32, 2>    Vec2f32;
  typedef Vector_T<f64, 2>    Vec2f64;
  typedef Vector_T<f128, 2>   Vec2f128;

  typedef Vector_T<tl_float, 2> Vec2f;

  //------------------------------------------------------------------------
  // Static const definitions
  template<typename T>
  const Vector_T<T, 2> Vector_T<T, 2>::ZERO       (0, 0);
  template<typename T>
  const Vector_T<T, 2> Vector_T<T, 2>::UNIT_X     (1, 0);
  template<typename T>
  const Vector_T<T, 2> Vector_T<T, 2>::UNIT_Y     (0, 1);
  template<typename T>
  const Vector_T<T, 2> Vector_T<T, 2>::NEG_UNIT_X (T(-1), 0);
  template<typename T>
  const Vector_T<T, 2> Vector_T<T, 2>::NEG_UNIT_Y (0, T(-1));

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(Vector_T<f32 TLOC_COMMA 2>);
  TLOC_EXTERN_TEMPLATE_CLASS(Vector_T<f64 TLOC_COMMA 2>);
  TLOC_EXTERN_TEMPLATE_CLASS(Vector_T<f128 TLOC_COMMA 2>);

  TLOC_EXTERN_TEMPLATE_CLASS(Vector_TI<f32 TLOC_COMMA 2 TLOC_COMMA  Vec2f32>);
  TLOC_EXTERN_TEMPLATE_CLASS(Vector_TI<f64 TLOC_COMMA 2 TLOC_COMMA  Vec2f64>);
  TLOC_EXTERN_TEMPLATE_CLASS(Vector_TI<f128 TLOC_COMMA 2 TLOC_COMMA  Vec2f128>);

};};};

#endif
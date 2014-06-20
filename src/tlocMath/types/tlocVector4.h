#pragma once
#ifndef TLOC_MATH_VECTOR_4_H
#define TLOC_MATH_VECTOR_4_H

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/tlocAlgorithms.h>

#include <tlocMath/types/tlocVector.h>

namespace tloc { namespace math { namespace types {

  template <typename T>
  class Vector_T<T, 4> 
    : public Vector_TI<T, 4>
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T);

  public:
    typedef Vector_T<T, 4>                        this_type;
    typedef Vector_TI<T, 4>                       base_type;

    typedef typename base_type::value_type        value_type;
    typedef typename base_type::reference         reference;
    typedef typename base_type::const_reference   const_reference;

  public:
    Vector_T();
    Vector_T(const base_type& aVector);
    Vector_T(const this_type& a_other);
    Vector_T(value_type a_x, value_type a_y, value_type a_z, value_type a_w);

    Vector_T(const core::data_structs::Variadic<T, 4>& a_vars);
    explicit Vector_T(const_reference a_value);

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

  public:
    static const this_type ZERO;
    static const this_type ONE;
    static const this_type UNIT_X;
    static const this_type UNIT_Y;
    static const this_type UNIT_Z;
    static const this_type UNIT_W;
    static const this_type NEG_UNIT_X;
    static const this_type NEG_UNIT_Y;
    static const this_type NEG_UNIT_Z;
    static const this_type NEG_UNIT_W;
    
  private:
    using base_type::m_values;
  };

  //------------------------------------------------------------------------
  // Typedefs
  typedef Vector_T<f32, 4>  Vec4f32;
  typedef Vector_T<f64, 4>  Vec4f64;
  typedef Vector_T<f128, 4> Vec4f128;

  typedef Vector_T<s32, 4>  Vec4s32;
  typedef Vector_T<s64, 4>  Vec4s64;

  typedef Vector_T<u32, 4>  Vec4u32;
  typedef Vector_T<u64, 4>  Vec4u64;

  typedef Vector_T<tl_float, 4> Vec4f;

  //------------------------------------------------------------------------
  // Static const definitions

  template <typename T>
  const Vector_T<T, 4> Vector_T<T, 4>::ZERO       (0, 0, 0, 0);
  template <typename T>
  const Vector_T<T, 4> Vector_T<T, 4>::ONE        (1, 1, 1, 1);
  template <typename T>
  const Vector_T<T, 4> Vector_T<T, 4>::UNIT_X     (1, 0, 0, 0);
  template <typename T>
  const Vector_T<T, 4> Vector_T<T, 4>::UNIT_Y     (0, 1, 0, 0);
  template <typename T>
  const Vector_T<T, 4> Vector_T<T, 4>::UNIT_Z     (0, 0, 1, 0);
  template <typename T>
  const Vector_T<T, 4> Vector_T<T, 4>::UNIT_W     (0, 0, 0, 1);
  template <typename T>
  const Vector_T<T, 4> Vector_T<T, 4>::NEG_UNIT_X (T(-1), 0, 0, 0);
  template <typename T>
  const Vector_T<T, 4> Vector_T<T, 4>::NEG_UNIT_Y (0, T(-1), 0, 0);
  template <typename T>
  const Vector_T<T, 4> Vector_T<T, 4>::NEG_UNIT_Z (0, 0, T(-1), 0);
  template <typename T>
  const Vector_T<T, 4> Vector_T<T, 4>::NEG_UNIT_W (0, 0, 0, T(-1));

};};};

#endif
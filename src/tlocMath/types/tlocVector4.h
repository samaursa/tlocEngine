#pragma once
#ifndef TLOC_MATH_VECTOR_4_H
#define TLOC_MATH_VECTOR_4_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/tlocAlgorithms.h>

#include <tlocMath/types/tlocVector.h>

namespace tloc { namespace math { namespace types {

  template <typename T>
  class Vector4 : public Vector<T, 4>
  {
  public:
    typedef Vector4<T>            this_type;
    typedef Vector<T, 4>          base_type;

    typedef typename base_type::value_type        value_type;
    typedef typename base_type::reference         reference;
    typedef typename base_type::const_reference   const_reference;

  public:
    Vector4();
    Vector4(const base_type& aVector);
    Vector4(const this_type& a_other);
    Vector4(value_type a_x, value_type a_y, value_type a_z, value_type a_w);

    Vector4(const core::data_structs::Variadic<T, 4>& a_vars);
    explicit Vector4(const_reference a_value);

    static const Vector4  ZERO;
    static const Vector4  ONE;
    static const Vector4  UNIT_X;
    static const Vector4  UNIT_Y;
    static const Vector4  UNIT_Z;
    static const Vector4  UNIT_W;
    static const Vector4  NEG_UNIT_X;
    static const Vector4  NEG_UNIT_Y;
    static const Vector4  NEG_UNIT_Z;
    static const Vector4  NEG_UNIT_W;
  };

  //------------------------------------------------------------------------
  // Typedefs
  typedef Vector4<f32>  Vec4f32;
  typedef Vector4<f64>  Vec4f64;
  typedef Vector4<f128> Vec4f128;

  typedef Vector4<s32>  Vec4s32;
  typedef Vector4<s64>  Vec4s64;

  typedef Vector4<u32>  Vec4u32;
  typedef Vector4<u64>  Vec4u64;

  typedef Vector4<tl_float> Vec4f;

  //------------------------------------------------------------------------
  // Static const definitions

  template <typename T>
  const Vector4<T> Vector4<T>::ZERO       (0, 0, 0, 0);
  template <typename T>
  const Vector4<T> Vector4<T>::ONE        (1, 1, 1, 1);
  template <typename T>
  const Vector4<T> Vector4<T>::UNIT_X     (1, 0, 0, 0);
  template <typename T>
  const Vector4<T> Vector4<T>::UNIT_Y     (0, 1, 0, 0);
  template <typename T>
  const Vector4<T> Vector4<T>::UNIT_Z     (0, 0, 1, 0);
  template <typename T>
  const Vector4<T> Vector4<T>::UNIT_W     (0, 0, 0, 1);
  template <typename T>
  const Vector4<T> Vector4<T>::NEG_UNIT_X (T(-1), 0, 0, 0);
  template <typename T>
  const Vector4<T> Vector4<T>::NEG_UNIT_Y (0, T(-1), 0, 0);
  template <typename T>
  const Vector4<T> Vector4<T>::NEG_UNIT_Z (0, 0, T(-1), 0);
  template <typename T>
  const Vector4<T> Vector4<T>::NEG_UNIT_W (0, 0, 0, T(-1));

};};};

#endif
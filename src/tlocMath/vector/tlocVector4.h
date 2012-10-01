#pragma once
#ifndef TLOC_MATH_VECTOR_4_H
#define TLOC_MATH_VECTOR_4_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/tlocAlgorithms.h>

#include <tlocMath/vector/tlocVector.h>

namespace tloc { namespace math {

  template <typename T>
  class Vector4 : public Vector<T, 4>
  {
  public:
    typedef Vector4<T>            this_type;
    typedef Vector<T, 4>          base_type;
    using base_type::value_type;
    using base_type::reference;
    using base_type::const_reference;

  public:
    Vector4();
    Vector4(const this_type& a_other);
    Vector4(value_type a_x, value_type a_y, value_type a_z, value_type a_w);

    Vector4(const core::Variadic<T, 4>& a_vars);
    explicit Vector4(const_reference a_value);

    static const Vector4  ZERO;
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
  // Static const definitions

  template <typename T>
  const Vector4<T> Vector4<T>::ZERO       (0.0, 0.0, 0.0, 0.0);
  template <typename T>
  const Vector4<T> Vector4<T>::UNIT_X     (1.0, 0.0, 0.0, 0.0);
  template <typename T>
  const Vector4<T> Vector4<T>::UNIT_Y     (0.0, 1.0, 0.0, 0.0);
  template <typename T>
  const Vector4<T> Vector4<T>::UNIT_Z     (0.0, 0.0, 1.0, 0.0);
  template <typename T>
  const Vector4<T> Vector4<T>::UNIT_W     (0.0, 0.0, 0.0, 1.0);
  template <typename T>
  const Vector4<T> Vector4<T>::NEG_UNIT_X (-1.0, 0.0, 0.0, 0.0);
  template <typename T>
  const Vector4<T> Vector4<T>::NEG_UNIT_Y (0.0, -1.0, 0.0, 0.0);
  template <typename T>
  const Vector4<T> Vector4<T>::NEG_UNIT_Z (0.0, 0.0, -1.0, 0.0);
  template <typename T>
  const Vector4<T> Vector4<T>::NEG_UNIT_W (0.0, 0.0, 0.0, -1.0);

};};

#endif
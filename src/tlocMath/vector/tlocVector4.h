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

    static const Vector4  ZERO;
    static const Vector4  UNIT_X;
    static const Vector4  UNIT_Y;
    static const Vector4  UNIT_Z;
    static const Vector4  NEG_UNIT_X;
    static const Vector4  NEG_UNIT_Y;
    static const Vector4  NEG_UNIT_Z;
  };

};};
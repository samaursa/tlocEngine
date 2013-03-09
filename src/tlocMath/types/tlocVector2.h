#pragma once
#ifndef TLOC_VECTOR_2_H
#define TLOC_VECTOR_2_H

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/tlocAlgorithms.h>

#include <tlocMath/tlocMath.h>
#include <tlocMath/types/tlocVector.h>

namespace tloc { namespace math { namespace types {

  //////////////////////////////////////////////////////////////////////////
  // Vector2

  template<typename T>
  class Vector2 : public Vector<T, 2>
  {
  public:
    //------------------------------------------------------------------------
    // typedefs (similar to std containers)
    typedef Vector2<T>                            this_type;
    typedef Vector<T, 2>                          base_type;

    typedef typename base_type::value_type        value_type;
    typedef typename base_type::reference         reference;
    typedef typename base_type::const_reference   const_reference;

    //------------------------------------------------------------------------
    // using declarations for access to base class
    using base_type::m_values;

    //------------------------------------------------------------------------
    // Constructors
    TL_FI Vector2();
    TL_FI Vector2(const_reference aX, const_reference aY);
    TL_FI Vector2(const this_type& aVector);
    TL_FI Vector2(const base_type& aVector);
    TL_FI Vector2(const core::data_structs::Variadic<value_type, 2>& a_vars);

    TL_FI explicit Vector2(const_reference aValue);

    static const Vector2 ZERO;
    static const Vector2 UNIT_X;
    static const Vector2 UNIT_Y;
    static const Vector2 NEG_UNIT_X;
    static const Vector2 NEG_UNIT_Y;

  };

  //------------------------------------------------------------------------
  // Typedefs
  typedef Vector2<f32>    Vec2f32;
  typedef Vector2<f64>    Vec2f64;
  typedef Vector2<f128>   Vec2f128;

  typedef Vector2<s32>    Vec2s32;
  typedef Vector2<s64>    Vec2s64;

  typedef Vector2<u32>    Vec2u32;
  typedef Vector2<u64>    Vec2u64;

  typedef Vector2<tl_float> Vec2f;

  //------------------------------------------------------------------------
  // Static const definitions
  template<typename T>
  const Vector2<T> Vector2<T>::ZERO       (0, 0);
  template<typename T>
  const Vector2<T> Vector2<T>::UNIT_X     (1, 0);
  template<typename T>
  const Vector2<T> Vector2<T>::UNIT_Y     (0, 1);
  template<typename T>
  const Vector2<T> Vector2<T>::NEG_UNIT_X (T(-1), 0);
  template<typename T>
  const Vector2<T> Vector2<T>::NEG_UNIT_Y (0, T(-1));

};};};

#endif
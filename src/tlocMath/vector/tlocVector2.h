#pragma once
#ifndef TLOC_VECTOR_2_H
#define TLOC_VECTOR_2_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/tlocAlgorithms.h>

#include <tlocMath/tlocMath.h>
#include <tlocMath/vector/tlocVector.h>

namespace tloc { namespace math {

  //////////////////////////////////////////////////////////////////////////
  // Vector2

  template<typename T>
  class Vector2 : public Vector<T, 2>
  {
  public:
    //------------------------------------------------------------------------
    // typedefs (similar to std containers)
    typedef Vector2<T>                      this_type;
    typedef Vector<T, 2>                    base_type;
    
    typedef typename base_type::value_type  value_type;
    
    //------------------------------------------------------------------------
    // using declarations for access to base class
    using base_type::m_values;
    
    //------------------------------------------------------------------------
    // Constructors
    TL_FI Vector2();
    TL_FI Vector2(const T& aX, const T& aY);
    TL_FI Vector2(const Vector2<T>& aVector);
    TL_FI Vector2(const Vector<T, 2>& aVector);

    TL_FI explicit Vector2(const T& aValue);

    static const Vector2 UNIT_X;
    static const Vector2 UNIT_Y;
    static const Vector2 NEG_UNIT_X;
    static const Vector2 NEG_UNIT_Y;

  };

  //------------------------------------------------------------------------
  // Typedefs
  typedef Vector2<f32>    Vec2f;
  typedef Vector2<f64>    Vec2d;
  typedef Vector2<f128>   Vec2l;

  //------------------------------------------------------------------------
  // Static const definitions
  template<typename T>
  const Vector2<T> Vector2<T>::UNIT_X     (1.0, 0.0);
  template<typename T>
  const Vector2<T> Vector2<T>::UNIT_Y     (0.0, 1.0);
  template<typename T>
  const Vector2<T> Vector2<T>::NEG_UNIT_X (-1.0, 0.0);
  template<typename T>
  const Vector2<T> Vector2<T>::NEG_UNIT_Y (0.0, -1.0);

};};

#endif
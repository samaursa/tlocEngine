#pragma once
#ifndef TLOC_VECTOR_2_H
#define TLOC_VECTOR_2_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocStandardFuncs.h"

#include "tlocMath/tlocMath.h"
#include "tlocMath/tlocVector.h"

namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Vector2

  template<typename T>
  class Vector2 : public Vector<T, 2>
  {
  public:
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
};

#ifdef TLOC_FULL_SOURCE
#include "tlocVector2.inl"
#endif

#endif
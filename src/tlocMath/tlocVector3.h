#pragma once
#ifndef TLOC_VECTOR_3_H
#define TLOC_VECTOR_3_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocStandardFuncs.h"

#include "tlocMath/tlocMath.h"
#include "tlocMath/tlocVector.h"

namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Vector3

  template<typename T>
  class Vector3 : public Vector<T, 3>
  {
  public:
    TL_FI Vector3();
    TL_FI Vector3(const T& aX, const T& aY, const T& aZ);
    TL_FI Vector3(const Vector3<T>& aVector);
    TL_FI Vector3(const Vector<T, 3>& aVector);
    
    TL_FI explicit Vector3(const T& aValue);    

    // Modifies this vector by storing the cross product between this vector
    // and the incoming vector
    TL_FI void Cross(const Vector3<T>& aVector);

    // Modifies this vector by storing the cross product between the two
    // incoming vectors
    TL_FI void Cross(const Vector3<T>& aVector1, 
                     const Vector3<T>& aVector2);

    // Modifies this vector to store the normalized version of the incoming
    // vector with an approx 3% error. Inverse square root code taken from
    // http://www.codemaestro.com/reviews/9 (originally from Quake)
    // 
    // NOTE: Only works on floats
    TL_FI void FastNorm(const Vector3<f32>& aVector);

    // Same as FastNorm() but modifies this vector directly
    //
    // NOTE: Only works on floats
    TL_FI void FastNorm();

    static const Vector3 UNIT_X;
    static const Vector3 UNIT_Y;
    static const Vector3 UNIT_Z;
    static const Vector3 NEG_UNIT_X;
    static const Vector3 NEG_UNIT_Y;
    static const Vector3 NEG_UNIT_Z;

  };

  typedef Vector3<f32>  Vec3f;
  typedef Vector3<f64>  Vec3d;

#include "tlocVector3.inl"

};

#endif
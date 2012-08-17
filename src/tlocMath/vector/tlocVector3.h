#pragma once
#ifndef TLOC_VECTOR_3_H
#define TLOC_VECTOR_3_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/tlocAlgorithms.h>

#include <tlocMath/tlocMath.h>
#include <tlocMath/vector/tlocVector.h>

namespace tloc { namespace math {

  //////////////////////////////////////////////////////////////////////////
  // Vector3

  template<typename T>
  class Vector3 : public Vector<T, 3>
  {
  public:
    //------------------------------------------------------------------------
    // typedefs (similar to std containers)
    typedef Vector3<T>                            this_type;
    typedef Vector<T, 3>                          base_type;
    
    typedef typename base_type::value_type        value_type;
    typedef typename base_type::reference         reference;
    typedef typename base_type::const_reference   const_reference;
    
    //------------------------------------------------------------------------
    // using declarations for access to base class
    using base_type::LengthSquared;
    using base_type::m_values;
    
    //------------------------------------------------------------------------
    // Constructors
    TL_FI Vector3();
    TL_FI Vector3(const_reference aX, const_reference aY, const_reference aZ);
    TL_FI Vector3(const this_type& aVector);
    TL_FI Vector3(const base_type& aVector);

    TL_FI explicit Vector3(const_reference aValue);

    // Modifies this vector by storing the cross product between this vector
    // and the incoming vector
    TL_FI this_type& Cross(const this_type& aVector);

    // Modifies this vector by storing the cross product between the two
    // incoming vectors
    TL_FI void Cross(const this_type& aVector1,
                     const this_type& aVector2);

    // Modifies this vector to store the normalized version of the incoming
    // vector with an approx 3% error. Inverse square root code taken from
    // http://www.codemaestro.com/reviews/9 (originally from Quake)
    //
    // NOTE: Only works on floats!
    TL_FI void FastNorm(const this_type& aVector);

    // Same as FastNorm() but modifies this vector directly
    //
    // NOTE: Only works on floats!
    TL_FI void FastNorm();

    static const Vector3 UNIT_X;
    static const Vector3 UNIT_Y;
    static const Vector3 UNIT_Z;
    static const Vector3 NEG_UNIT_X;
    static const Vector3 NEG_UNIT_Y;
    static const Vector3 NEG_UNIT_Z;

  };

  //------------------------------------------------------------------------
  // Typedefs
  typedef Vector3<f32>  Vec3f;
  typedef Vector3<f64>  Vec3d;
  typedef Vector3<f128> Vec3l;

  //------------------------------------------------------------------------
  // Static const definitions
  template <typename T>
  const Vector3<T> Vector3<T>::UNIT_X     (1.0, 0.0, 0.0);
  template <typename T>
  const Vector3<T> Vector3<T>::UNIT_Y     (0.0, 1.0, 0.0);
  template <typename T>
  const Vector3<T> Vector3<T>::UNIT_Z     (0.0, 0.0, 1.0);
  template <typename T>
  const Vector3<T> Vector3<T>::NEG_UNIT_X (-1.0, 0.0, 0.0);
  template <typename T>
  const Vector3<T> Vector3<T>::NEG_UNIT_Y (0.0, -1.0, 0.0);
  template <typename T>
  const Vector3<T> Vector3<T>::NEG_UNIT_Z (0.0, 0.0, -1.0);

};};

#ifdef TLOC_FULL_SOURCE
#include "tlocVector3.inl"
#endif

#endif
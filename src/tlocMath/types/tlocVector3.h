#pragma once
#ifndef TLOC_VECTOR_3_H
#define TLOC_VECTOR_3_H

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/tlocAlgorithms.h>

#include <tlocMath/tlocMath.h>
#include <tlocMath/types/tlocVector.h>

namespace tloc { namespace math { namespace types {

  //////////////////////////////////////////////////////////////////////////
  // Vector3

  template<typename T>
  class Vector_T<T, 3>
    : public Vector_TI<T, 3>
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T);

  public:
    //------------------------------------------------------------------------
    // typedefs (similar to std containers)
    typedef Vector_T<T, 3>                        this_type;
    typedef Vector_TI<T, 3>                       base_type;

    typedef typename base_type::value_type        value_type;
    typedef typename base_type::reference         reference;
    typedef typename base_type::const_reference   const_reference;

  public:
    //------------------------------------------------------------------------
    // Constructors
    Vector_T();
    Vector_T(const_reference aX, const_reference aY, const_reference aZ);
    Vector_T(const this_type& aVector);
    Vector_T(const base_type& aVector);
    Vector_T(const core::data_structs::Variadic<value_type, 3>& a_vars);

    explicit Vector_T(value_type aValue);

    // Modifies this vector by storing the cross product between this vector
    // and the incoming vector
    this_type Cross(const this_type& aVector) const;

    // Modifies this vector by storing the cross product between the two
    // incoming vectors
    void Cross(const this_type& aVector1, const this_type& aVector2);


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
    static const this_type ZERO;
    static const this_type UNIT_X;
    static const this_type UNIT_Y;
    static const this_type UNIT_Z;
    static const this_type NEG_UNIT_X;
    static const this_type NEG_UNIT_Y;
    static const this_type NEG_UNIT_Z;

  private:
    using base_type::m_values;
  };

  //------------------------------------------------------------------------
  // Typedefs
  typedef Vector_T<f32, 3>  Vec3f32;
  typedef Vector_T<f64, 3>  Vec3f64;
  typedef Vector_T<f128, 3> Vec3f128;

  typedef Vector_T<s32, 3>  Vec3s32;
  typedef Vector_T<s64, 3>  Vec3s64;

  typedef Vector_T<u32, 3>  Vec3u32;
  typedef Vector_T<u64, 3>  Vec3u64;

  typedef Vector_T<tl_float, 3> Vec3f;

  //------------------------------------------------------------------------
  // Static const definitions
  template <typename T>
  const Vector_T<T, 3> Vector_T<T, 3>::ZERO       (0, 0, 0);
  template <typename T>
  const Vector_T<T, 3> Vector_T<T, 3>::UNIT_X     (1, 0, 0);
  template <typename T>
  const Vector_T<T, 3> Vector_T<T, 3>::UNIT_Y     (0, 1, 0);
  template <typename T>
  const Vector_T<T, 3> Vector_T<T, 3>::UNIT_Z     (0, 0, 1);
  template <typename T>
  const Vector_T<T, 3> Vector_T<T, 3>::NEG_UNIT_X (T(-1), 0, 0);
  template <typename T>
  const Vector_T<T, 3> Vector_T<T, 3>::NEG_UNIT_Y (0, T(-1), 0);
  template <typename T>
  const Vector_T<T, 3> Vector_T<T, 3>::NEG_UNIT_Z (0, 0, T(-1));

};};};

#ifdef TLOC_FULL_SOURCE
#include "tlocVector3.inl.h"
#endif

#endif
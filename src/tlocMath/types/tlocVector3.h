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
    : public Vector_TI<T, 3, Vector_T<T, 3> >
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T);

  public:
    //------------------------------------------------------------------------
    // typedefs (similar to std containers)
    typedef Vector_T<T, 3>                        this_type;
    typedef Vector_TI<T, 3, this_type>            base_type;
    typedef Vector_TI<T, 2, Vector_T<T, 2> >      vec2_type;

    typedef typename base_type::value_type        value_type;
    typedef typename base_type::reference         reference;
    typedef typename base_type::const_reference   const_reference;

  public:
    //------------------------------------------------------------------------
    // Constructors
    Vector_T();
    Vector_T(value_type a_X, value_type a_Y, value_type a_Z);
    Vector_T(vec2_type a_xy, value_type a_z);
    Vector_T(value_type a_X, vec2_type a_yz);
    Vector_T(const this_type& a_Vector);
    Vector_T(const base_type& a_Vector);
    Vector_T(const core::data_structs::Variadic<value_type, 3>& a_vars);

    explicit Vector_T(value_type a_Value);

    // Modifies this vector by storing the cross product between this vector
    // and the incoming vector
    this_type Cross(const this_type& a_Vector) const;

    // Modifies this vector by storing the cross product between the two
    // incoming vectors
    void Cross(const this_type& a_Vector1, const this_type& a_Vector2);


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

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(Vector_T<f32 TLOC_COMMA 3>);
  TLOC_EXTERN_TEMPLATE_CLASS(Vector_T<f64 TLOC_COMMA 3>);
  TLOC_EXTERN_TEMPLATE_CLASS(Vector_T<f128 TLOC_COMMA 3>);

  TLOC_EXTERN_TEMPLATE_CLASS(Vector_TI<f32 TLOC_COMMA 3 TLOC_COMMA  Vec3f32>);
  TLOC_EXTERN_TEMPLATE_CLASS(Vector_TI<f64 TLOC_COMMA 3 TLOC_COMMA  Vec3f64>);
  TLOC_EXTERN_TEMPLATE_CLASS(Vector_TI<f128 TLOC_COMMA 3 TLOC_COMMA  Vec3f128>);

};};};

#endif
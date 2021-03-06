#pragma once
#ifndef TLOC_MATH_VECTOR_4_H
#define TLOC_MATH_VECTOR_4_H

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocMath/types/tlocVector.h>
#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>

namespace tloc { namespace math { namespace types {

  template <typename T>
  class Vector_T<T, 4> 
    : public Vector_TI<T, 4, Vector_T<T, 4> >
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T);

  public:
    typedef Vector_T<T, 4>                        this_type;
    typedef Vector_TI<T, 4, this_type>            base_type;
    typedef Vector_T<T, 3>                        vec3_type;
    typedef Vector_T<T, 2>                        vec2_type;

    typedef typename base_type::value_type        value_type;
    typedef typename base_type::reference         reference;
    typedef typename base_type::const_reference   const_reference;

  public:
    Vector_T();
    Vector_T(const base_type& aVector);
    Vector_T(const this_type& a_other);
    Vector_T(value_type a_x, value_type a_y, value_type a_z, value_type a_w);
    Vector_T(value_type a_x, vec3_type a_yzw);
    Vector_T(vec3_type a_xyz, value_type a_w);
    Vector_T(vec2_type a_xy, vec2_type a_zw);
    Vector_T(vec2_type a_xy, value_type a_z, value_type a_w);
    Vector_T(value_type a_x, value_type a_y, vec2_type a_zw);
    Vector_T(value_type a_x, vec2_type a_yz, value_type a_z);

    Vector_T(const core::data_structs::Variadic<T, 4>& a_vars);
    explicit Vector_T(const_reference a_value);

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
    static const this_type ONE;
    static const this_type UNIT_X;
    static const this_type UNIT_Y;
    static const this_type UNIT_Z;
    static const this_type UNIT_W;
    static const this_type NEG_UNIT_X;
    static const this_type NEG_UNIT_Y;
    static const this_type NEG_UNIT_Z;
    static const this_type NEG_UNIT_W;
    
  private:
    using base_type::m_values;
  };

  //------------------------------------------------------------------------
  // Typedefs
  typedef Vector_T<f32, 4>  Vec4f32;
  typedef Vector_T<f64, 4>  Vec4f64;

  typedef Vector_T<tl_float, 4> Vec4f;

  TLOC_TYPEDEF_ALL_SMART_PTRS(Vec4f32, vec4_f32);
  TLOC_TYPEDEF_ALL_SMART_PTRS(Vec4f64, vec4_f64);
  TLOC_TYPEDEF_ALL_SMART_PTRS(Vec4f, vec4_f);

  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Vec4f32, vec4_f32);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Vec4f64, vec4_f64);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Vec4f, vec4_f);

  //------------------------------------------------------------------------
  // Static const definitions

  template <typename T>
  const Vector_T<T, 4> Vector_T<T, 4>::ZERO       (0, 0, 0, 0);
  template <typename T>
  const Vector_T<T, 4> Vector_T<T, 4>::ONE        (1, 1, 1, 1);
  template <typename T>
  const Vector_T<T, 4> Vector_T<T, 4>::UNIT_X     (1, 0, 0, 0);
  template <typename T>
  const Vector_T<T, 4> Vector_T<T, 4>::UNIT_Y     (0, 1, 0, 0);
  template <typename T>
  const Vector_T<T, 4> Vector_T<T, 4>::UNIT_Z     (0, 0, 1, 0);
  template <typename T>
  const Vector_T<T, 4> Vector_T<T, 4>::UNIT_W     (0, 0, 0, 1);
  template <typename T>
  const Vector_T<T, 4> Vector_T<T, 4>::NEG_UNIT_X (T(-1), 0, 0, 0);
  template <typename T>
  const Vector_T<T, 4> Vector_T<T, 4>::NEG_UNIT_Y (0, T(-1), 0, 0);
  template <typename T>
  const Vector_T<T, 4> Vector_T<T, 4>::NEG_UNIT_Z (0, 0, T(-1), 0);
  template <typename T>
  const Vector_T<T, 4> Vector_T<T, 4>::NEG_UNIT_W (0, 0, 0, T(-1));

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(Vector_T<f32 TLOC_COMMA 4>);
  TLOC_EXTERN_TEMPLATE_CLASS(Vector_T<f64 TLOC_COMMA 4>);

  TLOC_EXTERN_TEMPLATE_CLASS(Vector_TI<f32 TLOC_COMMA 4 TLOC_COMMA  Vec4f32>);
  TLOC_EXTERN_TEMPLATE_CLASS(Vector_TI<f64 TLOC_COMMA 4 TLOC_COMMA  Vec4f64>);

};};};

#include <tlocCore/logging/tlocLog.h>

namespace tloc { namespace core { 

  namespace logging {

    template <typename T_Logger, typename T_BuildConfig, typename T>
    const Log_T<T_Logger, T_BuildConfig>&
      operator << (const Log_T<T_Logger, T_BuildConfig>& a_log,
                   const math_t::Vector_T<T, 4>& a_vec)
    {
      a_log << a_vec[0] << ", " << a_vec[1] << ", " << a_vec[2] << ", " << a_vec[3];
      return a_log;
    }

  };

};};

#endif
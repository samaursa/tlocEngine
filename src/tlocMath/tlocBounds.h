#pragma once

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/containers/tlocArray.h>
#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>

namespace tloc { namespace math {

  // -----------------------------------------------------------------------
  // Bounds_T

  template <typename T_VecType>
  class Bounds_T
  {
    TLOC_STATIC_ASSERT(
    (Loki::IsSameType<T_VecType, math_t::Vec2f32>::value ||
     Loki::IsSameType<T_VecType, math_t::Vec2f64>::value ||
     Loki::IsSameType<T_VecType, math_t::Vec3f32>::value ||
     Loki::IsSameType<T_VecType, math_t::Vec3f64>::value),
     Only_Vec3_and_Vec2_types_allowed);

  public:
    typedef T_VecType                             vec_type;
    typedef Bounds_T<vec_type>                    this_type;
    typedef core_conts::Array<vec_type>           vec_cont;

  public:
    Bounds_T(const vec_cont& a_allPoints);

    TLOC_DECL_AND_DEF_GETTER(vec_type, GetMax, m_max);
    TLOC_DECL_AND_DEF_GETTER(vec_type, GetMin, m_min);
    
  private:
    vec_type m_max;
    vec_type m_min;
  };

  // -----------------------------------------------------------------------
  // typedefs

  typedef Bounds_T<math_t::Vec2f>               Bounds2D;
  typedef Bounds_T<math_t::Vec3f>               Bounds3D;

  typedef Bounds_T<math_t::Vec2f32>             bounds_2d_f32;
  typedef Bounds_T<math_t::Vec2f64>             bounds_2d_f64;
  typedef Bounds_T<math_t::Vec3f32>             bounds_3d_f32;
  typedef Bounds_T<math_t::Vec3f64>             bounds_3d_f64;

};};
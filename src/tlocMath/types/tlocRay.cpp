#include "tlocRay.h"

#include <tlocCore/types/tlocStrongType.inl>
#include <tlocCore/types/tlocStrongTypeExplicitMacros.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>

namespace tloc { namespace math { namespace types {

#define RAY_TEMPS   typename T, tl_size T_Size
#define RAY_PARAMS  T, T_Size
#define RAY_TYPE    typename Ray_T<RAY_PARAMS>

  template <RAY_TEMPS>
  Ray_T<RAY_PARAMS>::
    Ray_T()
    : m_origin(0)
    , m_direction(0)
  { }

  template <RAY_TEMPS>
  Ray_T<RAY_PARAMS>::
    Ray_T(origin a_origin, direction a_direction)
    : m_origin(a_origin)
    , m_direction(a_direction)
  { }

  //------------------------------------------------------------------------
  // Explicit instantiations

  template class Ray_T<f32, 2>;
  template class Ray_T<f32, 3>;

  template class Ray_T<f64, 2>;
  template class Ray_T<f64, 3>;

};};};

TLOC_INSTANTIATE_STRONG_TYPE(tloc::math_t::Vec2f32);
TLOC_INSTANTIATE_STRONG_TYPE(tloc::math_t::Vec2f64);
TLOC_INSTANTIATE_STRONG_TYPE(tloc::math_t::Vec3f32);
TLOC_INSTANTIATE_STRONG_TYPE(tloc::math_t::Vec3f64);

typedef tloc::math_t::Vector<tloc::f32, 2> Vector2f32;
typedef tloc::math_t::Vector<tloc::f64, 2> Vector2f64;
typedef tloc::math_t::Vector<tloc::f32, 3> Vector3f32;
typedef tloc::math_t::Vector<tloc::f64, 3> Vector3f64;

TLOC_INSTANTIATE_STRONG_TYPE(Vector2f32);
TLOC_INSTANTIATE_STRONG_TYPE(Vector2f64);
TLOC_INSTANTIATE_STRONG_TYPE(Vector3f32);
TLOC_INSTANTIATE_STRONG_TYPE(Vector3f64);
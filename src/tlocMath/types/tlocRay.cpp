#include "tlocRay.h"

#include <tlocCore/types/tlocStrongType.inl.h>
#include <tlocCore/types/tlocStrongTypeExplicitMacros.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocMatrix3.h>

namespace tloc { namespace math { namespace types {

  // ///////////////////////////////////////////////////////////////////////
  // Ray_T<T, T_Size>

#define RAY_TEMPS   typename T
#define RAY_PARAMS  T, 3
#define RAY_TYPE    typename Ray_T<RAY_PARAMS>

  template <RAY_TEMPS>
  Ray_T<RAY_PARAMS>::
    Ray_T()
    : m_origin(0)
    , m_direction(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY_TEMPS>
  Ray_T<RAY_PARAMS>::
    Ray_T(origin a_origin, direction a_direction)
    : m_origin(a_origin)
    , m_direction(a_direction)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY_TEMPS>
  RAY_TYPE::this_type
  Ray_T<RAY_PARAMS>::
    operator+(const this_type& a_other) const
  {
    vec_type pos = GetOrigin() + a_other.GetOrigin();
    vec_type dir = GetDirection() + a_other.GetDirection();
    dir.Normalize();

    return this_type(origin(pos), direction(dir) );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY_TEMPS>
  RAY_TYPE::this_type
  Ray_T<RAY_PARAMS>::
    operator-(const this_type& a_other) const
  {
    vec_type pos = GetOrigin() - a_other.GetOrigin();
    vec_type dir = GetDirection() - a_other.GetDirection();
    dir.Normalize();

    return this_type(origin(pos), direction(dir) );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY_TEMPS>
  RAY_TYPE::this_type
  Ray_T<RAY_PARAMS>::
    operator*(const transform_type& a_trans) const
  {
    typedef Vector4<T>    vec4_type;

    vec4_type newPos = a_trans * m_origin.template ConvertTo<vec4_type>();

    Matrix3<T> mRot(a_trans[0], a_trans[4], a_trans[8],
                    a_trans[1], a_trans[5], a_trans[9],
                    a_trans[2], a_trans[6], a_trans[10]);

    vec_type newDir = mRot * m_direction;

    return this_type(origin(newPos.template ConvertTo<vec_type>()), direction(newDir) );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY_TEMPS>
  RAY_TYPE::this_type
  Ray_T<RAY_PARAMS>::
    operator*(const orientation_type& a_rotMat) const
  {
    vec_type      newPos = a_rotMat * m_origin;
    dir_vec_type  newDir = a_rotMat * m_direction;

    return this_type(origin(newPos), direction(newDir) );
  }

  // ///////////////////////////////////////////////////////////////////////
  // Ray_T<T, 2>

#define RAY2_TEMPS   typename T
#define RAY2_PARAMS  T, 2
#define RAY2_TYPE    typename Ray_T<RAY2_PARAMS>

  template <RAY2_TEMPS>
  Ray_T<RAY2_PARAMS>::
    Ray_T()
    : m_origin(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY2_TEMPS>
  Ray_T<RAY2_PARAMS>::
    Ray_T(origin a_origin, direction )
    : m_origin(a_origin)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY2_TEMPS>
  RAY2_TYPE::this_type
  Ray_T<RAY2_PARAMS>::
    operator+(const this_type& a_other) const
  {
    vec_type pos = GetOrigin() + a_other.GetOrigin();

    return this_type(origin(pos));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RAY2_TEMPS>
  RAY2_TYPE::this_type
  Ray_T<RAY2_PARAMS>::
    operator-(const this_type& a_other) const
  {
    vec_type pos = GetOrigin() - a_other.GetOrigin();

    return this_type(origin(pos));
  }

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
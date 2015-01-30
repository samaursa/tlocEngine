#include "tlocPlane.h"

#include <tlocCore/types/tlocStrongType.inl.h>
#include <tlocCore/types/tlocStrongTypeExplicitMacros.h>
#include <tlocCore/logging/tlocLogger.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc { namespace math { namespace types {

  // ///////////////////////////////////////////////////////////////////////
  // Plane_T<T>

#define PLANE_TEMPS   typename T
#define PLANE_PARAMS  T

  template <PLANE_TEMPS>
  Plane_T<PLANE_PARAMS>::
    Plane_T(origin a_origin, direction a_direction)
    : m_origin(a_origin)
    , m_direction(a_direction)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <PLANE_TEMPS>
  auto
    Plane_T<PLANE_PARAMS>::
    GetIntersect(const ray_type& a_ray) const -> vec_type
  {
    // d = (p0 - l0) . n / l . n
    // where p0 = point on a plane
    //       l0 = point on a line (ray for us)
    //       n  = plane normal or direction
    //       l  = line direction vector (ray for us)

    if (GetIsParallel(a_ray))
    {
      TLOC_LOG_MATH_ERR_FILENAME_ONLY() <<
        "Ray " << a_ray << " and Plane " << *this << " are parallel";
      return vec_type::ZERO;
    }

    auto numerator = (m_origin - a_ray.GetOrigin()).Dot(m_direction);
    auto denominator = a_ray.GetDirection().Dot(m_direction);
    real_type scalar = numerator / denominator;

    return scalar * a_ray.GetDirection() + a_ray.GetOrigin();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <PLANE_TEMPS>
  bool
    Plane_T<PLANE_PARAMS>::
    GetIsParallel(const ray_type& a_ray) const
  {
    return math::IsEqualToZero(a_ray.GetDirection().Dot(m_direction));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <PLANE_TEMPS>
  auto
    Plane_T<PLANE_PARAMS>::
    operator+(const this_type& a_other) const -> this_type
  {
    this_type temp(*this);
    temp += a_other;

    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <PLANE_TEMPS>
  auto
    Plane_T<PLANE_PARAMS>::
    operator+=(const this_type& a_other) -> this_type&
  {
    m_origin += a_other.m_origin;
    m_direction += a_other.m_direction;
    m_direction.Normalize();

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <PLANE_TEMPS>
  auto
    Plane_T<PLANE_PARAMS>::
    operator-(const this_type& a_other) const -> this_type
  {
    this_type temp(*this);
    temp -= a_other;

    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <PLANE_TEMPS>
  auto
    Plane_T<PLANE_PARAMS>::
    operator-=(const this_type& a_other) -> this_type&
  {
    m_origin -= a_other.m_origin;
    m_direction -= a_other.m_direction;
    m_direction.Normalize();

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <PLANE_TEMPS>
  auto
    Plane_T<PLANE_PARAMS>::
    operator*(const transform_type& a_trans) const -> this_type
  {
    this_type temp(*this);
    temp *= a_trans;

    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <PLANE_TEMPS>
  auto
    Plane_T<PLANE_PARAMS>::
    operator*(const orientation_type& a_rotMat) const -> this_type
  {
    this_type temp(*this);
    temp *= a_rotMat;

    return temp;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <PLANE_TEMPS>
  auto
    Plane_T<PLANE_PARAMS>::
    operator*=(const transform_type& a_trans) -> this_type&
  {
    typedef Vector_T<value_type, 4>             vec4_type;

    auto newOrigin = a_trans * m_origin.template ConvertTo<vec4_type>();

    orientation_type mRot(a_trans[0], a_trans[4], a_trans[8],
                          a_trans[1], a_trans[5], a_trans[9],
                          a_trans[2], a_trans[6], a_trans[10]);

    m_origin = newOrigin.ConvertTo<vec_type>();
    m_direction = mRot * m_direction;

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <PLANE_TEMPS>
  auto
    Plane_T<PLANE_PARAMS>::
    operator*=(const orientation_type& a_rotMat) -> this_type&
  {
    m_direction = a_rotMat * m_direction;
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <PLANE_TEMPS>
  bool
    Plane_T<PLANE_PARAMS>::
    operator==(const this_type& a_other) const
  {
    return m_origin == a_other.m_origin && m_direction == a_other.m_direction;
  }

  //------------------------------------------------------------------------
  // Explicit instantiations

  template class Plane_T<f32>;
  template class Plane_T<f64>;

};};};

TLOC_INSTANTIATE_STRONG_TYPE(tloc::math_t::Vec2f32);
TLOC_INSTANTIATE_STRONG_TYPE(tloc::math_t::Vec2f64);
TLOC_INSTANTIATE_STRONG_TYPE(tloc::math_t::Vec3f32);
TLOC_INSTANTIATE_STRONG_TYPE(tloc::math_t::Vec3f64);
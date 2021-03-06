#include "tlocCircle.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/data_structures/tlocTuple.inl.h>

#include <tlocMath/types/tlocPlane.h>

namespace tloc { namespace math { namespace types {

  //////////////////////////////////////////////////////////////////////////
  // Assertion Macros

#define TLOC_ASSERT_CIRCLE_VALID() \
  TLOC_ASSERT_LOW_LEVEL(m_radius >= 0, "Circle radius must be >= 0!")

  //////////////////////////////////////////////////////////////////////////
  // Template macros

#define TLOC_CIRCLE_TEMP typename T
#define TLOC_CIRCLE_PARAMS T
#define TLOC_CIRCLE_TYPE typename Circle_T<TLOC_CIRCLE_PARAMS>

  //////////////////////////////////////////////////////////////////////////
  // Circle<T>

  template <TLOC_CIRCLE_TEMP>
  Circle_T<TLOC_CIRCLE_PARAMS>::
    Circle_T(radius a_r, position a_p)
    : m_radius(a_r)
    , m_position(a_p)
  { }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  Circle_T<TLOC_CIRCLE_PARAMS>::
    Circle_T(diameter a_d, position a_p)
    : m_radius(a_d * 0.5f)
    , m_position(a_p)
  { }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  TLOC_CIRCLE_TYPE::this_type&
    Circle_T<TLOC_CIRCLE_PARAMS>::
    operator=(const this_type& a_other)
  {
    m_radius = a_other.m_radius;
    m_position = a_other.m_position;
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  void
    Circle_T<TLOC_CIRCLE_PARAMS>::
    swap(this_type& a_circ)
  {
    using core::swap;

    swap(m_radius, a_circ.m_radius);
    swap(m_position, a_circ.m_position);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  bool Circle_T<TLOC_CIRCLE_PARAMS>::
    operator ==(const this_type& a_other) const
  {
    TLOC_ASSERT_CIRCLE_VALID();
    return (m_radius == a_other.m_radius) && (m_position == a_other.m_position);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  TLOC_CIRCLE_TYPE::value_type
    Circle_T<TLOC_CIRCLE_PARAMS>::
    GetRadius() const
  {
    TLOC_ASSERT_CIRCLE_VALID();
    return m_radius;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  void Circle_T<TLOC_CIRCLE_PARAMS>::
    SetRadius(value_type a_radius)
  {
    m_radius = a_radius;
    TLOC_ASSERT_CIRCLE_VALID();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  bool Circle_T<TLOC_CIRCLE_PARAMS>::
    IsValid() const
  {
    return m_radius > (value_type)0;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  bool Circle_T<TLOC_CIRCLE_PARAMS>::
    Contains(const point_type& a_xyPoint) const
  {
    TLOC_ASSERT_CIRCLE_VALID();
    Vector_T<value_type, 2> displacement(m_position);
    displacement = displacement.Sub(a_xyPoint);

    value_type distance = displacement.Length();

    return distance <= m_radius;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  bool Circle_T<TLOC_CIRCLE_PARAMS>::
    Contains(const this_type& a_other) const
  {
    TLOC_ASSERT_CIRCLE_VALID();
    Vector_T<value_type, 2> displacement(m_position);
    displacement = displacement.Sub(a_other.m_position);

    value_type outerDistance = displacement.Length() + a_other.m_radius;

    return outerDistance <= m_radius;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  bool Circle_T<TLOC_CIRCLE_PARAMS>::
    Intersects(const this_type& a_other) const
  {
    TLOC_ASSERT(IsValid(), "Intersects() may not work with invalid dimensions!");

    TLOC_ASSERT_CIRCLE_VALID();
    Vector_T<value_type, 2> displacement(m_position);
    displacement = displacement.Sub(a_other.m_position);

    value_type distance = displacement.Length();

    return distance < m_radius + a_other.m_radius;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  bool Circle_T<TLOC_CIRCLE_PARAMS>::
    Intersects(const ray_type& a_ray) const
  {
    this_type rayCircle(radius(0), position(a_ray.GetOrigin()) );
    return Intersects(rayCircle);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  bool Circle_T<TLOC_CIRCLE_PARAMS>::
    Intersects(const ray3d_type& a_ray) const
  {
    typedef Plane_T<value_type>             plane_type;
    typedef typename plane_type::vec_type   vec3_type;

    plane_type p(typename plane_type::origin(vec3_type(m_position, 0)));
    auto point = p.GetIntersect(a_ray);

    return point.Length() <= m_radius;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  TLOC_CIRCLE_TYPE::point_type  Circle_T<TLOC_CIRCLE_PARAMS>::
    GetCoord(Radian_T<value_type> a_angle) const
  {
    // Get the point on a unit circle
    value_type r = a_angle.Get();
    value_type rCos = math::Cos(math_t::MakeRadian(r));
    value_type rSin = math::Sin(math_t::MakeRadian(r));

    return point_type(m_radius * rCos, m_radius * rSin) + m_position;
  }

  //////////////////////////////////////////////////////////////////////////
  // Explicit instantiation for Circle<>

  template class Circle_T<f32>;
  template class Circle_T<f64>;

};};};

//////////////////////////////////////////////////////////////////////////
// Explicit instantiation for StrongType<>

#include <tlocCore/types/tlocStrongType.inl.h>
#include <tlocCore/types/tlocStrongTypeExplicitMacros.h>
TLOC_INSTANTIATE_STRONG_TYPE(tloc::math::types::Circlef32::point_type);
TLOC_INSTANTIATE_STRONG_TYPE(tloc::math::types::Circlef64::point_type);
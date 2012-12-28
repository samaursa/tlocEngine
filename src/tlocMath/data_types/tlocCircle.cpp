#include "tlocCircle.h"

#include <tlocCore/data_structures/tlocTuple.inl>

#include <tlocMath/vector/tlocVector2.inl>

namespace tloc { namespace math { namespace types {

  //////////////////////////////////////////////////////////////////////////
  // Assertion Macros

#define TLOC_ASSERT_CIRCLE_VALID() \
  TLOC_ASSERT_LOW_LEVEL(m_radius >= 0, "Circle radius must be >= 0!")

  //////////////////////////////////////////////////////////////////////////
  // Template macros

#define TLOC_CIRCLE_TEMP typename T
#define TLOC_CIRCLE_PARAMS T
#define TLOC_CIRCLE_TYPE typename Circle<TLOC_CIRCLE_PARAMS>

  //////////////////////////////////////////////////////////////////////////
  // Circle<T>

  template <TLOC_CIRCLE_TEMP>
  Circle<TLOC_CIRCLE_PARAMS>::
    Circle(radius a_r, position a_p)
    : m_radius((radius::const_sel_return_type)a_r)
    , m_position((position::const_sel_return_type)a_p)
  {
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  Circle<TLOC_CIRCLE_PARAMS>::
    Circle(diameter a_d, position a_p)
    : m_radius( ((diameter::const_sel_return_type)a_d) * (value_type)0.5 )
    , m_position((position::const_sel_return_type)a_p)
  {
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  bool Circle<TLOC_CIRCLE_PARAMS>::
    operator ==(const this_type& a_other) const
  {
    TLOC_ASSERT_CIRCLE_VALID();
    return (m_radius == a_other.m_radius) && (m_position == a_other.m_position);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  TLOC_CIRCLE_TYPE::value_type
    Circle<TLOC_CIRCLE_PARAMS>::
    GetRadius() const
  {
    TLOC_ASSERT_CIRCLE_VALID();
    return m_radius;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  void Circle<TLOC_CIRCLE_PARAMS>::
    SetRadius(value_type a_radius)
  {
    m_radius = a_radius;
    TLOC_ASSERT_CIRCLE_VALID();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  bool Circle<TLOC_CIRCLE_PARAMS>::
    IsValid() const
  {
    return m_radius > (value_type)0;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  bool Circle<TLOC_CIRCLE_PARAMS>::
    Contains(const point_type& a_xyPoint) const
  {
    TLOC_ASSERT_CIRCLE_VALID();
    Vector2<value_type> displacement(m_position);
    displacement.Sub(a_xyPoint);
    
    value_type distance = displacement.Length();

    return distance <= m_radius;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  bool Circle<TLOC_CIRCLE_PARAMS>::
    Contains(const this_type& a_other) const
  {
    TLOC_ASSERT_CIRCLE_VALID();
    Vector2<value_type> displacement(m_position);
    displacement.Sub(a_other.m_position);
    
    value_type outerDistance = displacement.Length() + a_other.m_radius;

    return outerDistance <= m_radius;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_CIRCLE_TEMP>
  bool Circle<TLOC_CIRCLE_PARAMS>::
    Intersects(const this_type& a_other) const
  {
    TLOC_ASSERT_CIRCLE_VALID();
    Vector2<value_type> displacement(m_position);
    displacement.Sub(a_other.m_position);
    
    value_type distance = displacement.Length();

    return distance < m_radius + a_other.m_radius;
  }

  //////////////////////////////////////////////////////////////////////////
  // Explicit instantiation for Circle<>
  
  template class Circle<f32>;
  template class Circle<f64>;
  template class Circle<f128>;

};};};

//////////////////////////////////////////////////////////////////////////
// Explicit instantiation for StrongType<>

#include <tlocCore/types/tlocStrongType.inl>
#include <tlocCore/types/tlocStrongTypeExplicitMacros.h>
TLOC_INSTANTIATE_STRONG_TYPE(tloc::math::types::Circlef32::point_type);
TLOC_INSTANTIATE_STRONG_TYPE(tloc::math::types::Circlef64::point_type);
TLOC_INSTANTIATE_STRONG_TYPE(tloc::math::types::Circlef128::point_type);
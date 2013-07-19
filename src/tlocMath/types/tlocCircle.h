#pragma once
#ifndef _TLOC_MATH_TYPES_CIRCLE_H_
#define _TLOC_MATH_TYPES_CIRCLE_H_

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/types/tlocTypeTraits.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocAngle.h>
#include <tlocMath/types/tlocRay.h>

namespace tloc { namespace math { namespace types {

  template <typename T>
  class Circle_T
  {
  public:
    TLOC_STATIC_ASSERT_IS_ARITH(T);

  public:
    typedef T                                         value_type;
    typedef Circle_T<value_type>                      this_type;
    typedef Vector2<value_type>                       point_type;
    typedef Ray_T<value_type, 2>                      ray_type;
    typedef tl_size                                   size_type;

    typedef core::types::StrongType_T<value_type, 0>  radius;
    typedef core::types::StrongType_T<value_type, 2>  diameter;
    typedef core::types::StrongType_T<point_type, 3>  position;

  public:
    Circle_T(radius a_r = radius(0), position a_p = position(point_type(0)));
    Circle_T(diameter a_d, position a_p = position(point_type(0)));

    template <typename T_Real>
    Circle_T(const Circle_T<T_Real>& a_other);

    this_type&  operator=(const this_type& a_other);
    void        swap(this_type& a_rect);

    bool operator ==(const this_type& a_other) const;
    TLOC_DECLARE_OPERATOR_NOT_EQUAL(this_type);

    value_type  GetRadius() const;
    void        SetRadius(value_type a_radius);

    bool        IsValid() const;

    bool        Contains(const point_type& a_xyPoint) const;
    bool        Contains(const this_type& a_other) const;

    bool        Intersects(const this_type& a_other) const;
    bool        Intersects(const ray_type& a_ray) const;

    // The angle follows the ASTC rules when it comes to start/end points
    point_type  GetCoord(Radian_T<value_type> a_angle) const;

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(point_type, GetPosition, m_position);
    TLOC_DECL_AND_DEF_SETTER(point_type, SetPosition, m_position);

  private:
    value_type m_radius;
    point_type m_position;
  };

  //------------------------------------------------------------------------
  // swap

  template <typename T>
  void swap(Circle_T<T>& a, Circle_T<T>& b)
  { a.swap(b); }

  //------------------------------------------------------------------------
  // Template definitions

  template <typename T>
  template <typename T_Real>
  Circle_T<T>::
    Circle_T(const Circle_T<T_Real>& a_other)
    : m_radius(a_other.GetRadius())
    , m_position(a_other.GetPosition())
  { }

  //////////////////////////////////////////////////////////////////////////
  // Typedefs

  typedef Circle_T<tl_float>  Circlef;
  typedef Circle_T<f32>       Circlef32;
  typedef Circle_T<f64>       Circlef64;
  typedef Circle_T<f128>      Circlef128;

};};};

#endif
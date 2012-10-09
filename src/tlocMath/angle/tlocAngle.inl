#ifndef _TLOC_MATH_ANGLE_INL_
#define _TLOC_MATH_ANGLE_INL_

#ifndef _TLOC_MATH_ANGLE_H_
#error "Must include header before including the inline file"
#endif

#include "tlocAngle.h"
#include <tlocMath/tlocMath.h>

namespace tloc { namespace math { 

#define ANGLE_TEMP    typename T, class T_Derived 
#define ANGLE_PARAMS  T, T_Derived
#define ANGLE_TYPE    typename Angle_T<ANGLE_PARAMS>

  template <ANGLE_TEMP>
  Angle_T<ANGLE_PARAMS>::Angle_T(value_type a_angle)
    : m_angle(a_angle) { }

  template <ANGLE_TEMP>
  template <typename T_AngleType>
  Angle_T<ANGLE_PARAMS>::Angle_T(T_AngleType a_angle);

  template <ANGLE_TEMP>
  ANGLE_TYPE::this_type& 
    Angle_T<ANGLE_PARAMS>::operator= (value_type a_angle)
  {
    m_angle = a_angle;
    return *this;
  }

  template <ANGLE_TEMP>
  ANGLE_TYPE::this_type& 
    Angle_T<ANGLE_PARAMS>::operator= (const this_type& a_other)
  {
    m_angle = a_other.m_angle;
    return *this;
  }

  template <ANGLE_TEMP>
  template <typename T_AngleType>
  ANGLE_TYPE::this_type&
    Angle_T<ANGLE_PARAMS>::operator= (const T_AngleType& a_angle)
  {
    static_cast<derived_type*>(this)->DoSetAngle(a_angle);
    return *this;
  }

  template <ANGLE_TEMP>
  template <typename T_AngleType>
  ANGLE_TYPE::value_type 
    Angle_T<ANGLE_PARAMS>::GetAs() const
  {
    return static_cast<const derived_type*>(this)->DoGetAs(T_AngleType(0.0f));
  }

  template <ANGLE_TEMP>
  ANGLE_TYPE::this_type 
    Angle_T<ANGLE_PARAMS>::operator+ (this_type a_other) const
  {
    return m_angle + a_other.m_angle;
  }

  template <ANGLE_TEMP>
  ANGLE_TYPE::this_type&
    Angle_T<ANGLE_PARAMS>::operator+= (this_type a_other)
  {
    m_angle += a_other.m_angle;
    return *this;
  }

  template <ANGLE_TEMP>
  ANGLE_TYPE::this_type 
    Angle_T<ANGLE_PARAMS>::operator- (this_type a_other) const
  {
    return m_angle - a_other.m_angle;
  }

  template <ANGLE_TEMP>
  ANGLE_TYPE::this_type&
    Angle_T<ANGLE_PARAMS>::operator-= (this_type a_other)
  {
    m_angle -= a_other.m_angle;
    return *this;
  }

  template <ANGLE_TEMP>
  ANGLE_TYPE::this_type 
    Angle_T<ANGLE_PARAMS>::operator* (this_type a_other) const
  {
    return m_angle * a_other.m_angle;
  }

  template <ANGLE_TEMP>
  ANGLE_TYPE::this_type&
    Angle_T<ANGLE_PARAMS>::operator*= (this_type a_other)
  {
    m_angle *= a_other.m_angle;
    return *this;
  }
  
  template <ANGLE_TEMP>
  ANGLE_TYPE::this_type 
    Angle_T<ANGLE_PARAMS>::operator/ (this_type a_other) const
  {
    TLOC_ASSERT(Math<value_type>::IsEqual(a_other.m_angle, 0), "Divide by zero!");
    return m_angle / a_other.m_angle;
  }

  template <ANGLE_TEMP>
  ANGLE_TYPE::this_type&
    Angle_T<ANGLE_PARAMS>::operator/= (this_type a_other)
  {
    TLOC_ASSERT(Math<value_type>::IsEqual(a_other.m_angle, 0), "Divide by zero!");
    m_angle /= a_other.m_angle;
    return *this;
  }

  template <ANGLE_TEMP>
  bool Angle_T<ANGLE_PARAMS>::operator< (this_type a_other) const
  {
    if (!operator== (a_other))
    { return m_angle < derived_type(a_other.m_angle).m_angle; }
    else
    { return false; }
  }

  template <ANGLE_TEMP>
  bool Angle_T<ANGLE_PARAMS>::operator== (this_type a_other) const
  {
    return Math<value_type>::IsEqual(m_angle, a_other.m_angle);
  }

  template <ANGLE_TEMP>
  void Angle_T<ANGLE_PARAMS>::DoSetAngleCtor(value_type a_angle, fundamental_type)
  {
    m_angle = a_angle;
  }

  template <ANGLE_TEMP>
  template <typename T_AngleType>
  void Angle_T<ANGLE_PARAMS>::DoSetAngleCtor(T_AngleType a_angle, angle_type)
  {
    static_cast<derived_type*>(this)->DoSetAngle(a_angle);
  }

  //////////////////////////////////////////////////////////////////////////
  // Radian

#define RADIAN_TEMP   typename T
#define RADIAN_PARAMS T
#define RADIAN_TYPE   typename Radian_T<RADIAN_PARAMS>

  template <RADIAN_TEMP>
  Radian_T<RADIAN_PARAMS>::Radian_T(value_type a_angle)
    : base_type(a_angle)
  { }

  template <RADIAN_TEMP>
  template <typename T_AngleType>
  RADIAN_TYPE::this_type&
    Radian_T<RADIAN_PARAMS>::operator= (const T_AngleType& a_angle)
  {
    base_type::operator=(a_angle);
    return *this;
  }

  template <RADIAN_TEMP>
  RADIAN_TYPE::value_type
    Radian_T<RADIAN_PARAMS>::GetAsDegree() const
  {
    return base_type::template GetAs<Degree_T<value_type> >();
  }

  template <RADIAN_TEMP>
  template <typename T_AngleType>
  void Radian_T<RADIAN_PARAMS>::DoSetAngle(T_AngleType a_angle)
  {
    m_angle = a_angle.template GetAs<Radian_T<value_type> >();
  }

  template <RADIAN_TEMP>
  void Radian_T<RADIAN_PARAMS>::DoSetAngle(this_type a_angle)
  {
    m_angle = a_angle.m_angle;
  }

  template <RADIAN_TEMP>
  template <typename T_AngleType>
  RADIAN_TYPE::value_type
    Radian_T<RADIAN_PARAMS>::DoGetAs(T_AngleType) const
  {
    return m_angle * Math<value_type>::RAD_TO_DEG;
  }

  template <RADIAN_TEMP>
  RADIAN_TYPE::value_type
    Radian_T<RADIAN_PARAMS>::DoGetAs(this_type) const
  {
    return m_angle;
  }

  //////////////////////////////////////////////////////////////////////////
  // Degree 

#define DEGREE_TEMP   typename T
#define DEGREE_PARAMS T
#define DEGREE_TYPE   typename Degree_T<DEGREE_PARAMS>

  template <DEGREE_TEMP>
  Degree_T<DEGREE_PARAMS>::Degree_T(value_type a_angle)
    : base_type(a_angle)
  { }

  template <DEGREE_TEMP>
  template <typename T_AngleType>
  DEGREE_TYPE::this_type&
    Degree_T<DEGREE_PARAMS>::operator= (const T_AngleType& a_angle)
  {
    base_type::operator=(a_angle);
    return *this;
  }

  template <DEGREE_TEMP>
  DEGREE_TYPE::value_type
    Degree_T<DEGREE_PARAMS>::GetAsRadian() const
  {
    return base_type::template GetAs<Radian_T<value_type> >();
  }

  template <DEGREE_TEMP>
  template <typename T_AngleType>
  void Degree_T<DEGREE_PARAMS>::DoSetAngle(T_AngleType a_angle)
  {
    m_angle = a_angle.template GetAs<Degree_T<value_type> >();
  }

  template <DEGREE_TEMP>
  void Degree_T<DEGREE_PARAMS>::DoSetAngle(this_type a_angle)
  {
    m_angle = a_angle.m_angle;
  }

  template <DEGREE_TEMP>
  template <typename T_AngleType>
  DEGREE_TYPE::value_type
    Degree_T<DEGREE_PARAMS>::DoGetAs(T_AngleType) const
  {
    return m_angle * Math<value_type>::DEG_TO_RAD;
  }

  template <DEGREE_TEMP>
  DEGREE_TYPE::value_type
    Degree_T<DEGREE_PARAMS>::DoGetAs(this_type) const
  {
    return m_angle;
  }

};};

#endif
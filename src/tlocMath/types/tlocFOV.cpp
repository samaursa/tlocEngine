#include "tlocFOV.h"

#include <tlocMath/tlocMath.h>
#include <tlocMath/tlocMath.inl.h>

namespace tloc { namespace math { namespace types {

#define FOV_TEMPS  typename T_Real
#define FOV_PARAMS T_Real
#define FOV_TYPE   typename FOV_T<FOV_PARAMS>

  template <FOV_TEMPS>
  template <typename T_AngleOrientation>
  FOV_T<FOV_PARAMS>::
    FOV_T(angle_type a_angle, ar_type a_ratio, T_AngleOrientation)
    : m_aspectRatio(a_ratio)
  {
    DoSetAngle(a_angle, T_AngleOrientation() );
  }

  template <FOV_TEMPS>
  template <typename T_AngleOrientation>
  FOV_T<FOV_PARAMS>::
    FOV_T(const right_tri_type& a_rightTriangle, ar_type a_ratio,
           T_AngleOrientation)
           : m_aspectRatio(a_ratio)
  {
    DoSetAngle(a_rightTriangle, T_AngleOrientation());
  }

  template <FOV_TEMPS>
  template <typename T_AngleOrientation>
  FOV_TYPE::angle_type
    FOV_T<FOV_PARAMS>::
    Get() const
  {
    return DoGetFOV(T_AngleOrientation());
  }

  //------------------------------------------------------------------------
  // Helper functions

  // FOVh = 2 * atan ( tan (FOVv / 2) * width/height);
  // FOVv = 2 * atan ( tan (FOVh / 2) * height/width);

  template <FOV_TEMPS>
  void FOV_T<FOV_PARAMS>::
    DoSetAngle(angle_type a_angle, p_FOV::horizontal)
  {
    m_FOVx = a_angle;
    m_FOVy = math::ATan( math::Tan( m_FOVx / 2.0f) * m_aspectRatio.GetInv()) * 2.0f;
  }

  template <FOV_TEMPS>
  void FOV_T<FOV_PARAMS>::
    DoSetAngle(angle_type a_angle, p_FOV::vertical)
  {
    m_FOVy = a_angle;
    m_FOVx = math::ATan( math::Tan( m_FOVy / 2.0f) * m_aspectRatio.Get()) * 2.0f;
  }

  template <FOV_TEMPS>
  void FOV_T<FOV_PARAMS>::
    DoSetAngle(const right_tri_type& a_rightAngledTriangle, p_FOV::horizontal)
  {
    DoSetAngle(a_rightAngledTriangle.GetAngle(), p_FOV::horizontal());
  }

  template <FOV_TEMPS>
  void FOV_T<FOV_PARAMS>::
    DoSetAngle(const right_tri_type& a_rightAngledTriangle, p_FOV::vertical)
  {
    DoSetAngle(a_rightAngledTriangle.GetAngle(), p_FOV::vertical());
  }

  template <FOV_TEMPS>
  FOV_TYPE::angle_type
    FOV_T<FOV_PARAMS>::
    DoGetFOV(p_FOV::horizontal) const
  {
    return m_FOVx;
  }

  template <FOV_TEMPS>
  FOV_TYPE::angle_type
    FOV_T<FOV_PARAMS>::
    DoGetFOV(p_FOV::vertical) const
  {
    return m_FOVy;
  }

  //------------------------------------------------------------------------
  // Explicit Instantiations

#define TLOC_EXPLICITLY_INSTANTIATE_FOV(_type_)\
  template class FOV_T<_type_>;\
  \
  template FOV_T<_type_>::FOV_T(FOV_T<_type_>::angle_type, FOV_T<_type_>::ar_type, p_FOV::horizontal);\
  template FOV_T<_type_>::FOV_T(FOV_T<_type_>::angle_type, FOV_T<_type_>::ar_type, p_FOV::vertical);\
  \
  template FOV_T<_type_>::FOV_T(FOV_T<_type_>::right_tri_type const &, FOV_T<_type_>::ar_type, p_FOV::horizontal);\
  template FOV_T<_type_>::FOV_T(FOV_T<_type_>::right_tri_type const &, FOV_T<_type_>::ar_type, p_FOV::vertical);\
  \
  template FOV_T<_type_>::angle_type FOV_T<_type_>::Get<p_FOV::horizontal>() const;\
  template FOV_T<_type_>::angle_type FOV_T<_type_>::Get<p_FOV::vertical>() const

  TLOC_EXPLICITLY_INSTANTIATE_FOV(f32);
  TLOC_EXPLICITLY_INSTANTIATE_FOV(f64);

};};};
#include "tlocFOV.h"

#include <tlocMath/tlocMath.h>

namespace tloc { namespace graphics { namespace types {

  template <typename T_AngleOrientation>
  FOV::FOV(angle_type a_angle, ar_type a_ratio, T_AngleOrientation)
    : m_aspectRatio(a_ratio)
  {
    DoSetAngle(a_angle, T_AngleOrientation() );
  }

  template <typename T_AngleOrientation>
  FOV::FOV(const right_tri_type& a_rightAngledTriangle, ar_type a_ratio,
           T_AngleOrientation)
           : m_aspectRatio(a_ratio)
  {
    DoSetAngle(a_rightAngledTriangle, T_AngleOrientation());
  }

  template <typename T_AngleOrientation>
  FOV::angle_type
    FOV::GetFOV(T_AngleOrientation) const
  {
    DoGetFOV(T_AngleOrientation());
  }

  //------------------------------------------------------------------------
  // Helper functions

  // FOVh = 2 * atan ( tan (FOVv / 2) * width/height);
  // FOVv = 2 * atan ( tan (FOVh / 2) * height/width);

  void FOV::DoSetAngle(angle_type a_angle, p_FOV::horizontal)
  {
    typedef Math<value_type>  math;
    m_FOVx = a_angle;
    m_FOVy = 2 * math::ATan( math::Tan( m_FOVx.GetAngle() / 2) * m_aspectRatio.GetInv());
  }

  void FOV::DoSetAngle(angle_type a_angle, p_FOV::vertical)
  {
    typedef Math<value_type>  math;
    m_FOVy = a_angle;
    m_FOVx = 2 * math::ATan( math::Tan( m_FOVx.GetAngle() / 2) * m_aspectRatio.Get());
  }

  void FOV::DoSetAngle(const right_tri_type& a_rightAngledTriangle,
                       p_FOV::horizontal)
  {
    DoSetAngle(a_rightAngledTriangle.GetAngle(), p_FOV::horizontal());
  }

  void FOV::DoSetAngle(const right_tri_type& a_rightAngledTriangle,
                       p_FOV::vertical)
  {
    DoSetAngle(a_rightAngledTriangle.GetAngle(), p_FOV::vertical());
  }

  FOV::angle_type
    FOV::DoGetFOV(p_FOV::horizontal) const
  {
    return m_FOVx;
  }

  FOV::angle_type
    FOV::DoGetFOV(p_FOV::vertical) const
  {
    return m_FOVy;
  }

};};};
#ifndef _TLOC_GRAPHICS_TYPES_FOV_H_
#define _TLOC_GRAPHICS_TYPES_FOV_H_

#include <tlocMath/types/tlocAngle.h>
#include <tlocMath/utilities/tlocPythagoras.h>
#include <tlocGraphics/types/tlocAspectRatio.h>

namespace tloc { namespace graphics { namespace types {

  namespace p_FOV
  {
    struct horizontal{};
    struct vertical{};
  };

  class FOV
  {
  public:
    typedef tl_float                                      value_type;
    typedef math::Radian                                  angle_type;
    typedef math::utils::Pythagoras                       right_tri_type;
    typedef types::AspectRatio                            ar_type;

  public:
    template <typename T_AngleOrientation>
    FOV(angle_type a_angle, ar_type a_ratio, T_AngleOrientation);

    template <typename T_AngleOrientation>
    FOV(const right_tri_type& a_rightTriangle, ar_type a_ratio,
        T_AngleOrientation);

    template <typename T_AngleOrientation>
    angle_type  Get() const;

    TLOC_DECL_AND_DEF_GETTER(ar_type, GetAspectRatio, m_aspectRatio);

  private:
    void DoSetAngle(angle_type a_angle, p_FOV::horizontal);
    void DoSetAngle(angle_type a_angle, p_FOV::vertical);
    void DoSetAngle(const right_tri_type& a_rightAngledTriangle, p_FOV::horizontal);
    void DoSetAngle(const right_tri_type& a_rightAngledTriangle, p_FOV::vertical);

    angle_type DoGetFOV(p_FOV::horizontal) const;
    angle_type DoGetFOV(p_FOV::vertical) const;

    ar_type     m_aspectRatio;
    angle_type  m_FOVx;
    angle_type  m_FOVy;

  };

};};};

#endif
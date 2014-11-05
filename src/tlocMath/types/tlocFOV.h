#ifndef _TLOC_MATH_TYPES_FOV_H_
#define _TLOC_MATH_TYPES_FOV_H_

#include <tlocMath/tlocMathBase.h>

#include <tlocMath/types/tlocAngle.h>
#include <tlocMath/utilities/tlocPythagoras.h>
#include <tlocMath/types/tlocAspectRatio.h>

namespace tloc { namespace math { namespace types {

  namespace p_FOV
  {
    struct horizontal{};
    struct vertical{};
  };

  template <typename T_Real>
  class FOV_T
  {
    TLOC_STATIC_ASSERT_IS_FLOAT(T_Real);

  public:
    typedef T_Real                                        value_type;
    typedef math::types::Radian_T<value_type>             angle_type;
    typedef math::utils::Pythagoras_T<value_type>         right_tri_type;
    typedef types::AspectRatio_T<value_type>              ar_type;

  public:
    template <typename T_AngleOrientation>
    FOV_T(angle_type a_angle, ar_type a_ratio, T_AngleOrientation);

    template <typename T_AngleOrientation>
    FOV_T(const right_tri_type& a_rightTriangle, ar_type a_ratio,
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

  //------------------------------------------------------------------------
  // typedefs

  typedef FOV_T<tl_float> FOV;
  typedef FOV_T<f32>      fov_f32;
  typedef FOV_T<f32>      fov_f64;

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(FOV_T<tl_float>);
  TLOC_EXTERN_TEMPLATE_CLASS(FOV_T<f32>);
  TLOC_EXTERN_TEMPLATE_CLASS(FOV_T<f64>);

};};};

#endif
#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_ARC_BALL_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_ARC_BALL_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/utilities/tlocCheckpoints.h>

#include <tlocGraphics/component_system/tlocComponentType.h>

#include <tlocMath/types/tlocAngle.h>
#include <tlocMath/types/tlocVector3.h>

namespace tloc { namespace graphics { namespace component_system {

  class ArcBall
    : public core_cs::Component_T<ArcBall, components::arcball>
  {
  public:
    typedef ArcBall                                       this_type;
    typedef Component_T<this_type, components::arcball>   base_type;
    typedef f32                                           real_type;
    typedef math_t::Vector3<real_type>                    vec_type;
    typedef math_t::radian_f32                            angle_type;

  public:
    ArcBall();
    explicit ArcBall(const vec_type& a_focusPoint);

    void Reset();

    void FlipVertical();
    void FlipHorizontal();

    TLOC_DECL_AND_DEF_GETTER(vec_type, GetFocus, m_focusPoint);
    TLOC_DECL_AND_DEF_SETTER(vec_type, SetFocus, m_focusPoint);

    TLOC_DECL_SETTER(angle_type, MoveVertical);
    TLOC_DECL_SETTER(angle_type, MoveHorizontal);

    TLOC_DECL_AND_DEF_GETTER(angle_type, GetVerticalAngle, m_verticalAngle);
    TLOC_DECL_AND_DEF_GETTER(angle_type, GetHorizontalAngle, m_horizontalAngle);

  private:
    vec_type                  m_focusPoint;
    angle_type                m_verticalAngle;
    angle_type                m_horizontalAngle;
    core_utils::Checkpoints   m_flags;

  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(ArcBall, arcball);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(ArcBall, arcball);
  TLOC_TYPEDEF_COMPONENT_POOL(ArcBall, arcball);

};};};

#endif
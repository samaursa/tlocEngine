#ifndef _TLOC_INPUT_COMPONENT_SYSTEM_ARC_BALL_CONTROL_H_
#define _TLOC_INPUT_COMPONENT_SYSTEM_ARC_BALL_CONTROL_H_

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/utilities/tlocUtils.h>

#include <tlocMath/types/tlocVector2.h>

#include <tlocInput/component_system/tlocComponentType.h>

namespace tloc { namespace input { namespace component_system {

  class ArcBallControl
    : public core_cs::Component_T<ArcBallControl, components::k_arcball_control>
  {
  public:
    typedef ArcBallControl                                        this_type;
    typedef Component_T<this_type, components::k_arcball_control> base_type;
    typedef math_t::Vec2f                                         vec_type;
    typedef vec_type::value_type                                  real_type;

  public:
    ArcBallControl();

    TLOC_DECL_AND_DEF_GETTER(vec_type, GetGlobalMultiplier, m_globalMulti);
    TLOC_DECL_AND_DEF_GETTER(vec_type, GetRotationMultiplier, m_rotMulti);
    TLOC_DECL_AND_DEF_GETTER(vec_type, GetPanMultiplier, m_panMulti);
    TLOC_DECL_AND_DEF_GETTER(real_type, GetDollyMultiplier, m_dollyMulti);

    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(vec_type, SetGlobalMultiplier, m_globalMulti);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(vec_type, SetRotationMultiplier, m_rotMulti);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(vec_type, SetPanMultiplier, m_panMulti);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(real_type, SetDollyMultiplier, m_dollyMulti);

  private:
    vec_type     m_globalMulti, m_rotMulti, m_panMulti;
    real_type    m_dollyMulti;
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(ArcBallControl, arc_ball_control);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(ArcBallControl, arc_ball_control);
  TLOC_TYPEDEF_COMPONENT_POOL(ArcBallControl, arc_ball_control);

};};};

#endif
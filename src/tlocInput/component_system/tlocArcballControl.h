#ifndef _TLOC_INPUT_COMPONENT_SYSTEM_ARC_BALL_CONTROL_H_
#define _TLOC_INPUT_COMPONENT_SYSTEM_ARC_BALL_CONTROL_H_

#include <tlocInput/tlocInputBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/utilities/tlocUtils.h>

#include <tlocInput/component_system/tlocComponentType.h>
#include <tlocInput/hid/tlocKeyboard.h>
#include <tlocInput/hid/tlocMouse.h>

namespace tloc { namespace input { namespace component_system {

  class ArcBallControl
    : public core_cs::Component_T<ArcBallControl, components::k_arcball_control>
  {
  public:
    typedef ArcBallControl                                        this_type;
    typedef Component_T<this_type, components::k_arcball_control> base_type;
    typedef hid::keyboard_b_sptr                                  keyboard_ptr;
    typedef hid::mouse_b_sptr                                     mouse_ptr;

  public:
    ArcBallControl();
    ArcBallControl(keyboard_ptr a_keyboard);
    ArcBallControl(mouse_ptr a_mouse);
    ArcBallControl(keyboard_ptr a_keyboard, mouse_ptr a_mouse);

    TLOC_DECL_AND_DEF_SETTER(keyboard_ptr, SetKeyboard, m_keyboard);
    TLOC_DECL_AND_DEF_SETTER(mouse_ptr, SetMouse, m_mouse);

    TLOC_DECL_AND_DEF_GETTER(keyboard_ptr, GetKeyboard, m_keyboard);
    TLOC_DECL_AND_DEF_GETTER(mouse_ptr, GetMouse, m_mouse);

  private:
    keyboard_ptr    m_keyboard;
    mouse_ptr       m_mouse;
  };

};};};

#endif
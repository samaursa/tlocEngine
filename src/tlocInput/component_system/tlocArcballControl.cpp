#include "tlocArcBallControl.h"


namespace tloc { namespace input { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // ArcBallControl

  ArcBallControl::
    ArcBallControl()
    : base_type(k_component_type, "ArcBallControl")
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ArcBallControl::
    ArcBallControl(keyboard_ptr a_keyboard)
    : base_type(k_component_type, "ArcBallControl")
    , m_keyboard(a_keyboard)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ArcBallControl::
    ArcBallControl(mouse_ptr a_mouse)
    : base_type(k_component_type, "ArcBallControl")
    , m_mouse(a_mouse)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ArcBallControl::
    ArcBallControl(keyboard_ptr a_keyboard, mouse_ptr a_mouse)
    : base_type(k_component_type, "ArcBallControl")
    , m_keyboard(a_keyboard)
    , m_mouse(a_mouse)
  { }

};};};
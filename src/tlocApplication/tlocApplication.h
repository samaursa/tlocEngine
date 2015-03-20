#pragma once

#ifndef _TLOC_APPLICATION_H_
#define _TLOC_APPLICATION_H_

#include <tlocApplication/tlocApplicationBase.h>

#include <tlocCore/containers/tlocArrayFixed.h>
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocECS.h>
#include <tlocGraphics/window/tlocWindow.h>
#include <tlocGraphics/renderer/tlocRenderer.h>
#include <tlocInput/tlocInputManager.h>
#include <tlocInput/hid/tlocKeyboard.h>
#include <tlocInput/hid/tlocMouse.h>
#include <tlocInput/hid/tlocJoystick.h>
#include <tlocInput/hid/tlocTouchSurface.h>

namespace tloc {

  class Application
    : public input_hid::KeyboardListener
    , public input_hid::MouseListener
    , public input_hid::JoystickListener
  {
  public:
    typedef gfx_win::window_sptr                  window_ptr;
    typedef gfx_rend::renderer_sptr               renderer_ptr;
    typedef input::input_mgr_b_ptr                input_mgr_ptr;
    typedef input_hid::keyboard_b_vptr            keyboard_ptr;
    typedef input_hid::mouse_b_vptr               mouse_ptr;
    typedef input_hid::joystick_b_vptr            joystick_ptr;
    typedef input_hid::touch_surface_b_vptr       touch_surface_ptr;

    typedef core_conts::ArrayFixed<joystick_ptr, 4>       joystick_cont;

    typedef core_dispatch::Event                  event_type;
    typedef core_err::Error                       error_type;
    typedef core_cs::entity_vptr                  entity_ptr;
    typedef core_cs::ecs_sptr                     ecs_ptr;

  public:
    Application(BufferArg a_appName,
                const window_ptr&    a_window = nullptr,
                const renderer_ptr&  a_renderer = nullptr,
                const input_mgr_ptr& a_inputMgr = nullptr);

    error_type  Initialize(gfx_t::Dimension2 a_winDim,
                           const ecs_ptr& a_scene = nullptr,
                           const entity_ptr& a_camera = nullptr);

    event_type  OnWindowEvent(const gfx_win::WindowEvent&);

  private:
    bool              m_quit;

    core_str::String  m_appName;

    window_ptr        m_window;
    renderer_ptr      m_renderer;
    ecs_ptr           m_scene;
    entity_ptr        m_camera;

    input_mgr_ptr     m_inputMgr;
    keyboard_ptr      m_keyboard;
    mouse_ptr         m_mouse;
    touch_surface_ptr m_touchSurface;
    joystick_cont     m_joysticks;

  public:
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT_AUTO(GetWindow, m_window);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT_AUTO(GetRenderer, m_renderer);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT_AUTO(GetScene, m_scene);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT_AUTO(GetCamera, m_camera);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT_AUTO(GetInputMgr, m_inputMgr);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT_AUTO(GetKeyboard, m_keyboard);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT_AUTO(GetMouse, m_mouse);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT_AUTO(GetTouchSurface, m_touchSurface);

    TLOC_DECL_AND_DEF_CONTAINER_ALL_METHODS(_joysticks, m_joysticks);
  };
  TLOC_DEF_TYPE(Application);

};

#endif
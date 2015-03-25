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

    typedef core_time::Timer                      timer_type;
    typedef timer_type::sec_type                  sec_type;
    typedef f32                                   real_type;

  public:
    Application(BufferArg a_appName,
                const window_ptr&    a_window = nullptr,
                const renderer_ptr&  a_renderer = nullptr,
                const input_mgr_ptr& a_inputMgr = nullptr);

    error_type  Initialize(gfx_t::Dimension2 a_winDim,
                           const ecs_ptr& a_scene = nullptr);

    // infinite loop that will return only if Quit() is called (externally or
    // internally)
    void        Run();
    void        Update();
    void        Render();

    // all destruction code goes here - this is called after the main loop
    // has ended
    void        Finalize();

    // will trigger the end of the main loop
    void        Quit();
    void        SetAppendFPSToTitle(bool a_append = true);

    event_type  OnWindowEvent(const gfx_win::WindowEvent&);

  protected:

    virtual error_type  Pre_Initialize(gfx_t::Dimension2 a_winDim,
                                       const ecs_ptr& a_scene);
    virtual error_type  Post_Initialize();

    virtual void        Pre_Update(sec_type a_deltaT);
    virtual void        DoUpdate(sec_type a_deltaT);
    virtual void        Post_Update(sec_type a_deltaT);

    virtual void        Pre_Render(sec_type a_deltaT);
    virtual void        DoRender(sec_type a_deltaT);
    virtual void        Post_Render(sec_type a_deltaT);

    virtual void        Pre_Finalize();
    virtual void        Post_Finalize();

  private:
    error_type          DoCreateWindow(gfx_t::Dimension2 a_winDim);
    error_type          DoInitializePlatform();
    error_type          DoInitializeRenderer();
    error_type          DoInitializeInput();
    error_type          DoCreateScene(const ecs_ptr& a_scene);
    void                DoAppendTitleWithFPS(bool a_append);

  private:
    core_utils::Checkpoints m_flags;
    core_str::String        m_appName;

    sec_type            m_updateDeltaT;
    sec_type            m_renderDeltaT;

    sec_type            m_updateFrameTimeAccum;
    sec_type            m_renderFrameTimeAccum;

    sec_type            m_updateFrameTime;
    sec_type            m_renderFrameTime;

    timer_type          m_updateTimer;
    timer_type          m_renderTimer;

    window_ptr          m_window;
    renderer_ptr        m_renderer;
    ecs_ptr             m_scene;

    input_mgr_ptr       m_inputMgr;
    keyboard_ptr        m_keyboard;
    mouse_ptr           m_mouse;
    touch_surface_ptr   m_touchSurface;
    joystick_cont       m_joysticks;

    sec_type            m_fpsOutput;

  public:
    TLOC_DECL_AND_DEF_GETTER_AUTO(GetUpdateDeltaT, m_updateDeltaT);
    TLOC_DECL_AND_DEF_GETTER_AUTO(GetRenderDeltaT, m_renderDeltaT);

    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_AUTO(SetUpdateDeltaT, m_updateDeltaT);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_AUTO(SetRenderDeltaT, m_renderDeltaT);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT_AUTO(GetWindow, m_window);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT_AUTO(GetRenderer, m_renderer);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT_AUTO(GetScene, m_scene);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT_AUTO(GetInputMgr, m_inputMgr);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT_AUTO(GetKeyboard, m_keyboard);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT_AUTO(GetMouse, m_mouse);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT_AUTO(GetTouchSurface, m_touchSurface);

    TLOC_DECL_AND_DEF_GETTER_AUTO(GetFPSOutput, m_fpsOutput);

    TLOC_DECL_AND_DEF_CONTAINER_ALL_METHODS(_joysticks, m_joysticks);
  };
};

TLOC_DEF_TYPE(tloc::Application);

#endif
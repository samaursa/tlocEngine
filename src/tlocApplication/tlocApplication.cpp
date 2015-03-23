#include "tlocApplication.h"
#include <tlocCore/types/tlocTemplateParams.h>
#include <tlocCore/logging/tlocLogger.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc {

  namespace {

    const Application::sec_type       g_updateDeltaT = 0.1f;
    const Application::sec_type       g_renderDeltaT = 1.0f/60.0f;

    enum {

      k_app_quit = 0,
      k_app_initialized,

      k_app_count
    };

  };

  // ///////////////////////////////////////////////////////////////////////
  // Application

  Application::
    Application(BufferArg a_appName,
                const window_ptr& a_window, 
                const renderer_ptr&  a_renderer,
                const input_mgr_ptr& a_inputMgr)
                : m_flags(k_app_count)
                , m_appName(a_appName)
                , m_updateDeltaT(g_updateDeltaT)
                , m_renderDeltaT(g_renderDeltaT)
                , m_currentUpdateFrameTime(0.0f)
                , m_updateFrameTimeAccum(0.0f)
                , m_currentRenderFrameTime(0.0f)
                , m_renderFrameTimeAccum(0.0f)
                , m_updateFrameTime(0.0f)
                , m_renderFrameTime(0.0f)
                , m_window(a_window)
                , m_renderer(a_renderer)
                , m_inputMgr(a_inputMgr)
  {
    if (m_window == nullptr)
    {
      m_window = core_sptr::MakeShared<gfx_win::Window>();
      m_window->Register(this);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Application::
    Pre_Initialize(gfx_t::Dimension2, const ecs_ptr&) -> error_type
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Application::
    Initialize(gfx_t::Dimension2 a_winDim,
               const ecs_ptr& a_scene) -> error_type
  {
    TLOC_ASSERT(m_flags.IsUnMarked(k_app_initialized), 
                "Application already initialized");
    m_flags.Mark(k_app_initialized);

    TLOC_ERROR_RETURN_IF_FAILED(Pre_Initialize(a_winDim, a_scene));

    TLOC_ERROR_RETURN_IF_FAILED(DoCreateWindow(a_winDim));
    TLOC_ERROR_RETURN_IF_FAILED(DoInitializePlatform());
    TLOC_ERROR_RETURN_IF_FAILED(DoInitializeRenderer());
    TLOC_ERROR_RETURN_IF_FAILED(DoCreateScene(a_scene));

    return Post_Initialize();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Application::
    Run()
  {
    auto_cref win = GetWindow();
    while (win->IsValid() && m_flags[k_app_quit] == false)
    {
      gfx_win::WindowEvent evt;
      while(win->GetEvent(evt))
      { }

      timer_type  t;
      {
        Update();
      }
      m_updateFrameTime = t.ElapsedSeconds();

      t.Reset();
      {
        Render();
      }
      m_renderFrameTime = t.ElapsedSeconds();
    }

    Finalize();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Application::
    Pre_Update(sec_type )
  { m_scene->Update(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Application::
    DoUpdate(sec_type )
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Application::
    Update()
  {
    auto newTime = m_updateTimer.ElapsedSeconds();
    auto frameTime = newTime - m_currentUpdateFrameTime;

    if (m_currentUpdateFrameTime > 0.25f)
    { frameTime = 0.25f; }

    m_currentUpdateFrameTime = newTime;

    m_updateFrameTimeAccum += frameTime;

    while (m_updateFrameTimeAccum >= m_updateDeltaT)
    {
      Pre_Update(m_updateDeltaT);
      DoUpdate(m_updateDeltaT);
      Post_Update(m_updateDeltaT);
      m_updateFrameTimeAccum -= m_updateDeltaT;
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Application::
    Post_Update(sec_type a_deltaT)
  { m_scene->Process(a_deltaT); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Application::
    Pre_Render(sec_type )
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Application::
    DoRender(sec_type )
  { 
    GetRenderer()->ApplyRenderSettings();
    GetRenderer()->Render();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Application::
    Render()
  {
    auto newTime = m_renderTimer.ElapsedSeconds();
    auto frameTime = newTime - m_currentUpdateFrameTime;

    m_currentRenderFrameTime = newTime;

    m_renderFrameTimeAccum += frameTime;

    if (m_renderFrameTimeAccum >= m_renderDeltaT)
    {
      const auto prevFrameTimeAccum = m_renderFrameTimeAccum;

      while (m_renderFrameTimeAccum >= m_renderDeltaT)
      {
        m_renderFrameTimeAccum -= m_renderDeltaT;
      }

      m_renderTimer.Reset();
      Pre_Render(prevFrameTimeAccum);
      DoRender(prevFrameTimeAccum);
      Post_Render(prevFrameTimeAccum);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Application::
    Post_Render(sec_type )
  { 
    GetWindow()->SwapBuffers();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Application::
    Pre_Finalize()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Application::
    Finalize()
  {
    Pre_Finalize();
    {
      GetWindow()->Close();
    }
    Post_Finalize();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Application::
    Post_Finalize()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Application::
    Quit()
  { m_flags.Mark(k_app_quit); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Application::
    OnWindowEvent(const gfx_win::WindowEvent& a_event) -> event_type
  {
    if (a_event.m_type == gfx_win::WindowEvent::close)
    { Quit(); }

    return core_dispatch::f_event::Continue();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Application::
    Post_Initialize() -> error_type
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Application::
    DoCreateWindow(gfx_t::Dimension2 a_winDim) -> error_type
  {
    using namespace gfx_win;
    m_window->Create(Window::graphics_mode::Properties(a_winDim[0], a_winDim[1]),
                     WindowSettings(m_appName));

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Application::
    DoInitializePlatform() -> error_type
  {
    auto err = gfx_gl::InitializePlatform();
    if (err != ErrorSuccess)
    { 
      TLOC_LOG_APP_ERR_FILENAME_ONLY() 
        << "Graphics platform failed to initialize"; 
      return err; 
    }

    return err;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Application::
    DoInitializeRenderer() -> error_type
  {
    if (GetRenderer() == nullptr)
    {
      m_renderer = GetWindow()->GetRenderer();

      using namespace gfx_rend::p_renderer;
      gfx_rend::Renderer::Params  p(m_renderer->GetParams());
      p.SetClearColor(gfx_t::Color(0.0f, 0.0f, 0.0f, 1.0f))
       .Enable<enable_disable::CullFace>()
       .Cull<cull_face::Back>()
       .Enable<enable_disable::DepthTest>()
       .AddClearBit<clear::ColorBufferBit>()
       .AddClearBit<clear::DepthBufferBit>();

      m_renderer->SetParams(p);
    }

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Application::
    DoInitializeInput() -> error_type
  {
    if (GetInputMgr() == nullptr)
    {
      ParamList<core_t::Any>  inputParams;
      inputParams.m_param1 = m_window->GetWindowHandle();
      m_inputMgr = core_sptr::MakeShared<input::InputManagerB>(inputParams);

      m_keyboard      = m_inputMgr->CreateHID<input_hid::KeyboardB>();
      m_mouse         = m_inputMgr->CreateHID<input_hid::MouseB>();
      m_touchSurface  = m_inputMgr->CreateHID<input_hid::TouchSurfaceB>();

      for (tl_size i = 0; i < m_joysticks.size(); ++i)
      {
        auto_cref joy = m_inputMgr->CreateHID<input_hid::JoystickB>();
        if (joy)
        { m_joysticks.push_back(joy); }
        else
        { break; }
      }
    }
    else
    {
      if (m_inputMgr->GetTotalHID<input_hid::KeyboardB>() > 0)
      { m_keyboard = m_inputMgr->GetHID<input_hid::KeyboardB>(); }

      if (m_inputMgr->GetTotalHID<input_hid::MouseB>() > 0)
      { m_mouse = m_inputMgr->GetHID<input_hid::MouseB>(); }
      if (m_inputMgr->GetTotalHID<input_hid::TouchSurfaceB>() > 0) 
      { m_touchSurface = m_inputMgr->GetHID<input_hid::TouchSurfaceB>(); }

      const auto totalJoysticks = m_inputMgr->GetTotalHID<input_hid::JoystickB>();
      for (tl_size i = 0; i < totalJoysticks; ++i)
      { m_joysticks.push_back(m_inputMgr->GetHID<input_hid::JoystickB>(i)); }
    }

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Application::
    DoCreateScene(const ecs_ptr& a_scene) -> error_type
  {
    m_scene = a_scene;

    if (m_scene == nullptr)
    { m_scene = core_sptr::MakeShared<core_cs::ECS>(); }

    return ErrorSuccess;
  }

};

#include <tlocCore/containers/tlocArrayFixed.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_ARRAY_FIXED(tloc::Application::joystick_ptr, 4);
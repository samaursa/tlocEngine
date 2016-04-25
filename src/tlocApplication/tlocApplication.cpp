#include "tlocApplication.h"
#include <tlocCore/types/tlocTemplateParams.h>
#include <tlocCore/logging/tlocLogger.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc {

  namespace {

    const Application::sec_type       g_updateDeltaT = 1.0f/100.0f;
    const Application::sec_type       g_renderDeltaT = 1.0f/60.0f;

    enum {

      k_app_quit = 0,
      k_app_initialized,
      k_app_fps_in_title,

      k_app_count
    };

  };

  // ///////////////////////////////////////////////////////////////////////
  // Application

  BufferArg Application::s_updateGroupName = "Update";
  BufferArg Application::s_renderGroupName = "Render";

  Application::
    Application(BufferArg a_appName,
                const window_ptr& a_window, 
                const renderer_ptr&  a_renderer,
                const input_mgr_ptr& a_inputMgr)
                : m_flags(k_app_count)
                , m_appName(a_appName)
                , m_updateDeltaT(g_updateDeltaT)
                , m_renderDeltaT(g_renderDeltaT)
                , m_updateFrameTimeAccum(0.0f)
                , m_renderFrameTimeAccum(0.0f)
                , m_updateFrameTime(0.0f)
                , m_renderFrameTime(0.0f)
                , m_window(a_window)
                , m_renderer(a_renderer)
                , m_inputMgr(a_inputMgr)
                , m_fpsOutput(0.0f)
                , m_fpsOutputCap(1000.0f)
  {
    if (m_window == nullptr)
    {
      m_window = core_sptr::MakeShared<gfx_win::Window>();
      m_window->Register(this);
    }

    SetAppendFPSToTitle();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Application::
    Pre_Initialize(const graphics_mode& , const window_settings& , 
                   const ecs_ptr&) -> error_type
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Application::
    Initialize(gfx_t::Dimension2 a_winDim,
               const ecs_ptr& a_scene) -> error_type
  {
    return Initialize(graphics_mode::Properties(a_winDim), 
                      window_settings(m_appName), a_scene);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Application::
    Initialize(const graphics_mode& a_mode,
               const window_settings& a_settings,
               const ecs_ptr& a_scene) -> error_type
  {
    TLOC_ASSERT(m_flags.IsUnMarked(k_app_initialized), 
                "Application already initialized");
    m_flags.Mark(k_app_initialized);

    TLOC_ERROR_RETURN_IF_FAILED(Pre_Initialize(a_mode, a_settings, a_scene));

    TLOC_ERROR_RETURN_IF_FAILED(DoCreateWindow(a_mode, a_settings));
    TLOC_ERROR_RETURN_IF_FAILED(DoInitializePlatform());
    TLOC_ERROR_RETURN_IF_FAILED(DoInitializeRenderer());
    TLOC_ERROR_RETURN_IF_FAILED(DoInitializeInput());
    TLOC_ERROR_RETURN_IF_FAILED(DoCreateScene(a_scene));

    return Post_Initialize();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Application::
    Post_Initialize() -> error_type
  { 
    TLOC_LOG_APP_DEBUG_FILENAME_ONLY() << "Scene initialization time (s): " 
      << GetScene()->Initialize();

    return ErrorSuccess;
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

      Update();
      Render();
      
      // weighted FPS calculation
      const auto totalFrameTime = m_updateFrameTime + m_renderFrameTime;
      const auto frameFPS = 1.0f/totalFrameTime;
      const auto alpha = 0.9f;
      m_fpsOutput = alpha * m_fpsOutput + (1 - alpha) * frameFPS;
      m_fpsOutput = core::Clamp(m_fpsOutput, 0.0, m_fpsOutputCap);

      DoAppendTitleWithFPS(m_flags.IsMarked(k_app_fps_in_title));
    }

    Finalize();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Application::
    Pre_Update(sec_type )
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Application::
    DoUpdate(sec_type a_deltaT)
  { 
    m_inputMgr->Update();
    m_updateGroup->GetSystemsProcessor()->Process(a_deltaT);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Application::
    Update()
  {
    auto frameTime    = m_updateTimer.ElapsedSeconds();

    if (frameTime > 0.30f)
    { frameTime = 0.30f; }

    m_updateFrameTimeAccum += frameTime;

    while (m_updateFrameTimeAccum >= m_updateDeltaT)
    {

      m_updateTimer.Reset();

      Pre_Update(m_updateDeltaT);
      DoUpdate(m_updateDeltaT);
      Post_Update(m_updateDeltaT);

      m_updateFrameTimeAccum -= m_updateDeltaT;
      m_updateFrameTime = m_updateTimer.ElapsedSeconds();
    }

    m_updateTimer.Reset();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Application::
    Post_Update(sec_type a_deltaT)
  { 
    m_scene->Update(a_deltaT);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Application::
    Pre_Render(sec_type )
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Application::
    DoRender(sec_type a_deltaT)
  { 
    m_renderGroup->GetSystemsProcessor()->Process(a_deltaT);

    GetRenderer()->ApplyRenderSettings();
    GetRenderer()->Render();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Application::
    Render()
  {
    auto frameTime = m_renderTimer.ElapsedSeconds();

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
      m_renderFrameTime = m_renderTimer.ElapsedSeconds();
    }

    m_renderTimer.Reset();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    Application::
    Post_Render(sec_type a_deltaT)
  { 
    m_scene->Update(a_deltaT);
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
      m_renderer.reset();

      m_touchSurface.reset();
      m_mouse.reset();
      m_keyboard.reset();
      m_inputMgr.reset();

      m_scene.reset();
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

  void
    Application::
    SetAppendFPSToTitle(bool a_append)
  { m_flags[k_app_fps_in_title] = a_append; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Application::
    OnWindowEvent(const gfx_win::WindowEvent& a_event) -> event_type
  {
    if (a_event.m_type == gfx_win::WindowEvent::close)
    { Quit(); }

    return core_dispatch::f_event::Continue();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Application::
    DoCreateWindow(const graphics_mode& a_mode, 
                   const window_settings& a_settings) -> error_type
  {
    using namespace gfx_win;
    m_window->Create(a_mode, a_settings);

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
      p.SetClearColor(gfx_t::Color(0.1f, 0.1f, 0.1f, 1.0f))
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

    m_updateGroup = GetScene()->GetOrCreateSystemsGroup(s_updateGroupName);
    m_renderGroup = GetScene()->GetOrCreateSystemsGroup(s_renderGroupName);

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Application::
    DoAppendTitleWithFPS(bool a_append)
  {
    if (a_append == false) { return; }

    auto_cref newTitle = 
      core_str::Format("%.2f FPS (Update: %.5f sec, Render: %.5f sec)", 
      GetFPSOutput(), m_updateFrameTime, m_renderFrameTime);
    GetWindow()->SetTitle(newTitle);
  }

};

#include <tlocCore/containers/tlocArrayFixed.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_ARRAY_FIXED(tloc::Application::joystick_ptr, 4);
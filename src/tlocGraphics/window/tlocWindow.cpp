#include "tlocWindow.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/containers/tlocQueue.inl.h>

//------------------------------------------------------------------------
// Platform dependant includes

#if defined(TLOC_WIN32) || defined(TLOC_WIN64)
# include <tlocGraphics/window/tlocWindowImplWin.h>
#elif defined(TLOC_OS_IPHONE)
# include <tlocGraphics/window/tlocWindowImplIphone.h>
#else
# error "WIP"
#endif

#include "tlocCore/tlocFunctional.h"

namespace tloc { namespace graphics { namespace win {

  //////////////////////////////////////////////////////////////////////////
  //  Window.

#define WINDOW_TEMP   typename T_Platform
#define WINDOW_PARAMS T_Platform
#define WINDOW_TYPE   typename Window_T<WINDOW_PARAMS>

#define VALIDATE_WINDOW() TLOC_ASSERT(IsValid(), \
"Window has not been created OR has been closed (destroyed)")
#define VALIDATE_NOT_WINDOW() TLOC_ASSERT(!IsValid(), \
"Window already exists. Call Close() before calling Create()");



  template <WINDOW_TEMP>
  Window_T<WINDOW_PARAMS>::
    Window_T()
    : m_impl(nullptr)
    , m_mouseVisible(true)
  {
  }

  template <WINDOW_TEMP>
  Window_T<WINDOW_PARAMS>::
    ~Window_T()
  {
    Close();
    delete m_impl;
  }

  template <WINDOW_TEMP>
  void Window_T<WINDOW_PARAMS>::
    Create()
  {
    DoCreateImpl();
    m_impl->Create();
    DoSetupRenderer();
  }

  template <WINDOW_TEMP>
  void Window_T<WINDOW_PARAMS>::
    DoCreate(window_handle_type a_ptr, const WindowSettings& a_settings,
             IsWindowHandle)
  {
    DoCreateImpl();
    m_impl->Create(a_ptr, a_settings);
  }

  template <WINDOW_TEMP>
  void Window_T<WINDOW_PARAMS>::
  DoCreate(const graphics_mode& a_mode, const WindowSettings& a_settings,
          IsNotWindowHandle)
  {
    Create(a_mode, a_settings);
  }

  template <WINDOW_TEMP>
  void
    Window_T<WINDOW_PARAMS>::
    DoSetupRenderer()
  {
    using gfx_gl::framebuffer_object_sptr;

    framebuffer_object_sptr fbo = m_impl->DoGetFramebuffer();

    renderer_params_type params;
    params.SetFBO(fbo);
    m_renderer = core_sptr::MakeShared<renderer_type>(params);
  }

  template <WINDOW_TEMP>
  void Window_T<WINDOW_PARAMS>::
    Create(const graphics_mode& a_mode,
           const WindowSettings& a_settings)


  {
    DoCreateImpl();
    m_impl->Create(a_mode, a_settings);
    DoSetupRenderer();
  }

  template <WINDOW_TEMP>
  void Window_T<WINDOW_PARAMS>::
    Close()
  {
    VALIDATE_WINDOW();

    delete m_impl;
    m_impl = nullptr;
  }

  template <WINDOW_TEMP>
  bool Window_T<WINDOW_PARAMS>::
    IsValid() const
  {
    return m_impl != nullptr;
  }

  template <WINDOW_TEMP>
  bool Window_T<WINDOW_PARAMS>::
    IsCreated() const
  {
    if (IsValid())
    { return m_impl->IsCreated(); }
    else
    { return false; }
  }

  template <WINDOW_TEMP>
  WINDOW_TYPE::size_type Window_T<WINDOW_PARAMS>::
    GetWidth() const
  {
    VALIDATE_WINDOW();
    return m_impl->GetWidth();
  }

  template <WINDOW_TEMP>
  WINDOW_TYPE::size_type Window_T<WINDOW_PARAMS>::
    GetHeight() const
  {
    VALIDATE_WINDOW();
    return m_impl->GetHeight();
  }

  template <WINDOW_TEMP>
  WINDOW_TYPE::dim_type Window_T<WINDOW_PARAMS>::
    GetDimensions() const
  {
    VALIDATE_WINDOW();
    return core_ds::MakeTuple(GetWidth(), GetHeight());
  }

  template <WINDOW_TEMP>
  WINDOW_TYPE::dim_type Window_T<WINDOW_PARAMS>::
    GetDPI() const
  {
    VALIDATE_WINDOW();
    return m_impl->GetDPI();
  }

  template <WINDOW_TEMP>
  WINDOW_TYPE::size_type Window_T<WINDOW_PARAMS>::
    GetMaxWidth() const
  {
    VALIDATE_WINDOW();
    return m_impl->GetMaxWidth();
  }

  template <WINDOW_TEMP>
  WINDOW_TYPE::size_type Window_T<WINDOW_PARAMS>::
    GetMaxHeight() const
  {
    VALIDATE_WINDOW();
    return m_impl->GetMaxHeight();
  }

  template <WINDOW_TEMP>
  WINDOW_TYPE::aspect_ratio
    Window_T<WINDOW_PARAMS>::
    GetAspectRatio() const
  {
    typedef aspect_ratio::value_type f_type;
    f_type width  = (f_type)GetWidth();
    f_type height = (f_type)GetHeight();
    return aspect_ratio(aspect_ratio::width(width),
                        aspect_ratio::height(height) );
  }

  template <WINDOW_TEMP>
  bool Window_T<WINDOW_PARAMS>::GetEvent(WindowEvent& a_eventOut)
  {
    // If the stack is empty, then see if the window has more events for us
    if (m_impl && m_events.empty())
    {
      m_impl->ProcessEvents();
    }

    if (!m_events.empty())
    {
      a_eventOut = m_events.front();
      m_events.pop();

      return true;
    }

    return false;
  }

  template <WINDOW_TEMP>
  WINDOW_TYPE::window_handle_type Window_T<WINDOW_PARAMS>::
    GetWindowHandle() const
  {
    VALIDATE_WINDOW();
    return m_impl->GetWindowHandle();
  }

  template <WINDOW_TEMP>
  void Window_T<WINDOW_PARAMS>::
    SetVerticalSync(bool a_enable)
  {
    VALIDATE_WINDOW();
    m_impl->SetVerticalSync(a_enable);
  }

  template <WINDOW_TEMP>
  void Window_T<WINDOW_PARAMS>::
    SetActive(bool a_active) const
  {
    VALIDATE_WINDOW();
    m_impl->SetActive(a_active);
  }

  template <WINDOW_TEMP>
  bool Window_T<WINDOW_PARAMS>::
    IsActive() const
  {
    return GetCurrentActiveWindow() == this;
  }

  template <WINDOW_TEMP>
  bool Window_T<WINDOW_PARAMS>::
    HasValidContext() const
  {
    if (IsValid())
    { return m_impl->HasValidContext(); }

    return false;
  }

  template <WINDOW_TEMP>
  void Window_T<WINDOW_PARAMS>::
    SetMouseVisibility(bool a_visible)
  {
    VALIDATE_WINDOW();
    m_mouseVisible = a_visible;
    m_impl->SetMouseVisibility(a_visible);
  }

  template <WINDOW_TEMP>
  void Window_T<WINDOW_PARAMS>::
    SetPosition(s32 a_x, s32 a_y)
  {
    VALIDATE_WINDOW();
    m_impl->SetPosition(a_x, a_y);
  }

  template <WINDOW_TEMP>
  void Window_T<WINDOW_PARAMS>::
    SetSize(size_type a_width, size_type a_height)
  {
    VALIDATE_WINDOW();
    m_impl->SetSize(a_width, a_height);
  }

  template <WINDOW_TEMP>
  void Window_T<WINDOW_PARAMS>::
    SetVisibility(bool a_visible)
  {
    VALIDATE_WINDOW();
    m_impl->SetVisibility(a_visible);
  }

  template <WINDOW_TEMP>
  void Window_T<WINDOW_PARAMS>::
    SetTitle(const char* a_title)
  {
    VALIDATE_WINDOW();
    m_impl->SetTitle(a_title);
  }

  template <WINDOW_TEMP>
  void Window_T<WINDOW_PARAMS>::
    SwapBuffers() const
  {
    VALIDATE_WINDOW();
    m_impl->SwapBuffers();
  }

  template <WINDOW_TEMP>
  void Window_T<WINDOW_PARAMS>::
    SendEvent(const WindowEvent& a_event)
  {
    for (u32 i = 0; i < m_allObservers.size(); ++i)
    {
      m_allObservers[i]->OnWindowEvent(a_event);
    }
    m_events.push(a_event);
  }

  template <WINDOW_TEMP>
  WINDOW_TYPE::renderer_sptr
    Window_T<WINDOW_PARAMS>::
    GetRenderer() const
  {
    VALIDATE_WINDOW();
    return m_renderer;
  }

  //````````````````````````````````````````````````````````````````````````
  // Private methods

  template <WINDOW_TEMP>
  void Window_T<WINDOW_PARAMS>::
    DoCreateImpl()
  {
    VALIDATE_NOT_WINDOW();
    m_impl = new impl_type(this);
  }

  //------------------------------------------------------------------------
  // Explicit Instantiation

  template class Window_T<>;

  //////////////////////////////////////////////////////////////////////////
  // Globals

  namespace {
    Window_T<>*                   g_currentActiveWindow = nullptr;
  }

  Window_T<>* GetCurrentActiveWindow()
  {
    return g_currentActiveWindow;
  }

  namespace priv {

    void SetCurrentActiveWindow(Window_T<>* a_window)
    {
      g_currentActiveWindow = a_window;
    }

    void SetNonActiveWindow(Window_T<>* a_window)
    {
      if (a_window == g_currentActiveWindow)
      {
        g_currentActiveWindow = nullptr;
      }
    }
  };

};};};
#include "tlocWindow.h"

#include "tlocCore/tlocQueue.inl"

//------------------------------------------------------------------------
// Platform dependant includes

#if defined(TLOC_WIN32) || defined(TLOC_WIN64)
# include "tlocWindowImplWin.h"
#else
# error "WIP"
#endif

#include "tlocCore/tlocFunctional.h"

namespace tloc { namespace graphics {

  //////////////////////////////////////////////////////////////////////////
  //  Window.

#define WINDOW_TEMP   typename T_Platform
#define WINDOW_PARAMS T_Platform
#define WINDOW_TYPE   typename Window<WINDOW_PARAMS>

#define VALIDATE_WINDOW() TLOC_ASSERT(IsValid(), \
  "Window has not been created OR has been closed (destroyed)")
#define VALIDATE_NOT_WINDOW() TLOC_ASSERT(!IsValid(), \
  "Window already exists. Call Close() before calling Create()");

  // ------------------------------------------------------------------------
  //  Instantiate the template to avoid linking errors. This will only
  //  instantiate for the platform it is being compiled on.

  template Window<>;

  template <WINDOW_TEMP>
  Window<WINDOW_PARAMS>::Window() : m_impl(NULL)
  {
  }

  template <WINDOW_TEMP>
  Window<WINDOW_PARAMS>::~Window()
  {
    delete m_impl;
  }

  template <WINDOW_TEMP>
  void Window<WINDOW_PARAMS>::Create()
  {
    DoCreateImpl();
    m_impl->Create();
  }

  template <WINDOW_TEMP>
  void Window<WINDOW_PARAMS>::Create(window_handle_type a_ptr,
                                     const WindowSettings& a_settings)
  {
    DoCreateImpl();
    m_impl->Create(a_ptr, a_settings);
  }

  template <WINDOW_TEMP>
  void Window<WINDOW_PARAMS>::Create(const graphics_mode& a_mode,
                                     const WindowSettings& a_settings,
                                     window_style_type a_style)

  {
    DoCreateImpl();
    m_impl->Create(a_mode, a_settings, a_style);
  }

  template <WINDOW_TEMP>
  void Window<WINDOW_PARAMS>::Close()
  {
    VALIDATE_WINDOW();

    delete m_impl;
    m_impl = NULL;
  }

  template <WINDOW_TEMP>
  bool Window<WINDOW_PARAMS>::IsValid() const
  {
    return m_impl != NULL;
  }

  template <WINDOW_TEMP>
  bool Window<WINDOW_PARAMS>::IsCreated() const
  {
    if (IsValid())
    { return m_impl->IsCreated(); }
    else
    { return false; }
  }

  template <WINDOW_TEMP>
  WINDOW_TYPE::size_type Window<WINDOW_PARAMS>::GetWidth() const
  {
    VALIDATE_WINDOW();
    return m_impl->GetWidth();
  }

  template <WINDOW_TEMP>
  WINDOW_TYPE::size_type Window<WINDOW_PARAMS>::GetHeight() const
  {
    VALIDATE_WINDOW();
    return m_impl->GetHeight();
  }

  template <WINDOW_TEMP>
  bool Window<WINDOW_PARAMS>::GetEvent(WindowEvent& a_eventOut)
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
  void Window<WINDOW_PARAMS>::SetVerticalSync(bool a_enable)
  {
    VALIDATE_WINDOW();
    m_impl->SetVerticalSync(a_enable);
  }

  template <WINDOW_TEMP>
  void Window<WINDOW_PARAMS>::SetActive(bool a_active) const
  {
    VALIDATE_WINDOW();
    m_impl->SetActive(a_active);
  }

  template <WINDOW_TEMP>
  void Window<WINDOW_PARAMS>::SetMouseVisibility(bool a_visible)
  {
    VALIDATE_WINDOW();
    m_impl->SetMouseVisibility(a_visible);
  }

  template <WINDOW_TEMP>
  void Window<WINDOW_PARAMS>::SetPosition(s32 a_x, s32 a_y)
  {
    VALIDATE_WINDOW();
    m_impl->SetPosition(a_x, a_y);
  }

  template <WINDOW_TEMP>
  void Window<WINDOW_PARAMS>::SetSize(size_type a_width, size_type a_height)
  {
    VALIDATE_WINDOW();
    m_impl->SetSize(a_width, a_height);
  }

  template <WINDOW_TEMP>
  void Window<WINDOW_PARAMS>::SetVisibility(bool a_visible)
  {
    VALIDATE_WINDOW();
    m_impl->SetVisibility(a_visible);
  }

  template <WINDOW_TEMP>
  void Window<WINDOW_PARAMS>::SwapBuffers()
  {
    VALIDATE_WINDOW();
    m_impl->SwapBuffers();
  }

  template <WINDOW_TEMP>
  void Window<WINDOW_PARAMS>::SendEvent(const WindowEvent& a_event)
  {
    for (u32 i = 0; i < m_allObservers.size(); ++i)
    {
      m_allObservers[i]->OnWindowEvent(a_event);
    }
  }

  //````````````````````````````````````````````````````````````````````````
  // Private methods

  template <WINDOW_TEMP>
  void Window<WINDOW_PARAMS>::DoCreateImpl()
  {
    VALIDATE_NOT_WINDOW();
    m_impl = new impl_type(this);
  }

};};
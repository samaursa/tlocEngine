#include "tlocWindow.h"

#include "tlocCore/tlocArray.h"
#include "tlocCore/tlocArray.inl"

//------------------------------------------------------------------------
// Platform dependant includes

#if defined(TLOC_WIN32) || defined(TLOC_WIN64)
# include "tlocWindowWin32.h"
#else
# error "WIP"
#endif

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
  Window<WINDOW_PARAMS>::Window()
  {
  }

  template <WINDOW_TEMP>
  Window<WINDOW_PARAMS>::~Window()
  {
    delete m_impl;
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
                                     const core::String& a_title,
                                     window_style_type a_style,
                                     const WindowSettings& a_settings)
  {
    DoCreateImpl();
    m_impl->Create(a_mode, a_title, a_style, a_settings);
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
  void Window<WINDOW_PARAMS>::SetVerticalSync(bool a_enable)
  {
    VALIDATE_WINDOW();
    m_impl->SetVerticalSync(a_enable);
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

  //````````````````````````````````````````````````````````````````````````
  // Private methods

  template <WINDOW_TEMP>
  void Window<WINDOW_PARAMS>::DoCreateImpl()
  {
    VALIDATE_NOT_WINDOW();
    m_impl = new impl_type();
  }

};};
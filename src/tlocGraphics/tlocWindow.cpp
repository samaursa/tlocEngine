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
#define WINDOW_TYPE   typename template<WINDOW_PARAMS>

  // ------------------------------------------------------------------------
  //  Instantiate the template to avoid linking errors. This will only
  //  instantiate for the platform it is being compiled on.

  //template Window<>;

  template <WINDOW_TEMP>
  Window<WINDOW_PARAMS>::Window()
  {
    m_impl = new priv::WindowImpl<platform_type>();
  }

  template <WINDOW_TEMP>
  Window<WINDOW_PARAMS>::~Window()
  {
    delete m_impl;
  }

  template <WINDOW_TEMP>
  void Window<WINDOW_PARAMS>::Create()
  {
    m_impl->Create();
  }

  template <WINDOW_TEMP>
  void Window<WINDOW_PARAMS>::Create(window_handle_type a_ptr,
                                     const WindowSettings& a_settings)
  {
    TLOC_UNUSED(a_ptr); TLOC_UNUSED(a_settings);
    TLOC_ASSERT_WIP();
  }

  template <WINDOW_TEMP>
  void Window<WINDOW_PARAMS>::Create(const graphics_mode& a_mode,
                                     const core::String& a_title,
                                     window_style_type a_style,
                                     const WindowSettings& a_settings)
  {
    m_impl->Create(a_mode, a_title, a_style, a_settings);
  }

};};
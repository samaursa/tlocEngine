#include "tlocWindowImplWin.h"

namespace tloc { namespace graphics { namespace priv {

#define WINDOW_IMPL_WIN_PARAMS core::PlatformInfo<>::platform_type
#define WINDOW_IMPL_WIN_TYPE WindowImpl<WINDOW_IMPL_WIN_PARAMS>

  const char32* g_className = L"TLOC Window";

  WindowImpl<WINDOW_IMPL_WIN_PARAMS>::WindowImpl()
    : WindowImplBase()
    , m_handle(NULL)
    , m_callbackPtr(0)
    , m_cursor(NULL)
    , m_icon(NULL)
    , m_isCursorIn(false)
    , m_deviceContext(NULL)
    , m_OpenGLContext(NULL)
  {
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::Create()
  {
    m_graphicsMode = graphics_mode(graphics_mode::Properties(1, 1));
    graphics_mode::Properties props = m_graphicsMode.GetProperties();

    // Create a dummy window
    m_handle = CreateWindowW(g_className, L"", WS_POPUP | WS_DISABLED, 0, 0,
      props.m_width, props.m_height, NULL, NULL, GetModuleHandle(NULL), NULL);

    ShowWindow(m_handle, SW_HIDE);

    if (m_handle)
    {
      m_windowSettings.m_depthBits = 0;
      m_windowSettings.m_stencilBits = 0;
      m_windowSettings.m_antiAlias = 0;
    }
    else
    {
      TLOC_ASSERT(m_handle, "Could not create Win32 window!");
    }
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::
    Create(window_handle_type a_ptr, const WindowSettings& a_settings)
  {
    TLOC_UNUSED_2(a_ptr, a_settings);
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::
    Create(const graphics_mode& a_mode, const core::String& a_title,
           const window_style_type& a_style, const WindowSettings& a_settings)
  {
    TLOC_UNUSED_4(a_mode, a_title, a_style, a_settings);
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::
    DoCreateContext(const graphics_mode& a_gMode, const WindowSettings& a_params)
  {
    TLOC_UNUSED_2(a_gMode, a_params);
  }

};};};
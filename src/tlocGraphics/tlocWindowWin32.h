#ifndef TLOC_WINDOW_H
#define TLOC_WINDOW_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocUtils.h"
#include "tlocCore/tlocTypes.h"
#include "tlocCore/tlocString.h"
#include "tlocCore/tlocPlatform.h"
#include "tlocCore/tlocNonCopyable.h"

#include "tlocGraphicsModes.h"
#include "tlocWindowSettings.h"

#define WIN32_LEAN_AND_MEAN
#include "Windows.h"
#include <gl/GL.h>

namespace tloc { namespace graphics { namespace priv {

  template <typename T_Platform>
  class WindowImpl
  {
  public:

    typedef GraphicsMode<T_Platform>                     graphics_mode;
    typedef void*                                        window_handle_type;
    typedef typename WindowSettings::style_type          window_style_type;

  public:

    ///-------------------------------------------------------------------------
    /// Default constructor. Only initialzes values.
    ///-------------------------------------------------------------------------
    WindowImpl() { }
    ~WindowImpl() {}

    ///-------------------------------------------------------------------------
    /// Create a window for a valid OpenGL context. This is needed when querying
    /// for OpenGL support without creating an actual window.
    ///-------------------------------------------------------------------------
    void Create();

    ///-------------------------------------------------------------------------
    /// Creates this actual window with the specified properties
    ///
    /// @param  a_ptr    An existing window handle
    /// @param  a_params Window settings
    ///-------------------------------------------------------------------------
    void Create(window_handle_type a_ptr, const WindowSettings& a_settings);

    ///-------------------------------------------------------------------------
    /// Creates the actual window with the specified properties
    ///
    /// @param  a_mode The graphics mode
    /// @param  a_prop The window properties.
    ///-------------------------------------------------------------------------
    void Create(const graphics_mode& a_mode, const core::String& a_title,
      window_style_type a_style, const WindowSettings& a_settings);

  private:

    HWND      m_handle;
    tl_size   m_callbackPtr;
    HCURSOR   m_cursor;
    HICON     m_icon;
    bool      m_isCursorIn;
    HDC       m_deviceContext;
    HGLRC     m_OpenGLContext;

  };

};};};

#endif
#ifndef TLOC_WINDOW_WIN32_H
#define TLOC_WINDOW_WIN32_H

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

  template <typename T_Platform> class WindowImpl;

  // TODO: Abstract out the win32/win64 and remove the #ifdef
  template <>
#ifdef TLOC_WIN64
  class WindowImpl<core::Platform_win64> : public core::NonCopyable
#else
  class WindowImpl<core::Platform_win32> : public core::NonCopyable
#endif
  {
  public:

#ifdef TLOC_WIN64
    typedef GraphicsMode<core::Platform_win64>           graphics_mode;
#else
    typedef GraphicsMode<core::Platform_win32>           graphics_mode;
#endif

    typedef void*                                        window_handle_type;
    typedef WindowSettings::style_type                   window_style_type;
    typedef tl_size                                      size_type;

  public:

    ///-------------------------------------------------------------------------
    /// Default constructor. Only initialzes values.
    ///-------------------------------------------------------------------------
    WindowImpl();
    ~WindowImpl() {}

    ///-------------------------------------------------------------------------
    /// Create a window for a valid OpenGL context. This is needed when querying
    /// for OpenGL support without creating an actual window.
    ///-------------------------------------------------------------------------
    void Create() {}

    ///-------------------------------------------------------------------------
    /// Creates this actual window with the specified properties
    ///
    /// @param  a_ptr    An existing window handle
    /// @param  a_params Window settings
    ///-------------------------------------------------------------------------
    void Create(window_handle_type a_ptr, const WindowSettings& a_settings)
    {
      TLOC_UNUSED_2(a_ptr, a_settings);
    }

    ///-------------------------------------------------------------------------
    /// Creates the actual window with the specified properties
    ///
    /// @param  a_mode The graphics mode
    /// @param  a_prop The window properties.
    ///-------------------------------------------------------------------------
    void Create(const graphics_mode& a_mode, const core::String& a_title,
      window_style_type a_style, const WindowSettings& a_settings)
    {
      TLOC_UNUSED_4(a_mode, a_title, a_style, a_settings);
    }

    ///-------------------------------------------------------------------------
    /// Gets the width.
    ///
    /// @return The width.
    ///-------------------------------------------------------------------------
    size_type GetWidth() const { return 0; }

    ///-------------------------------------------------------------------------
    /// Gets the height.
    ///
    /// @return The height.
    ///-------------------------------------------------------------------------
    size_type GetHeight() const { return 0; }

    ///-------------------------------------------------------------------------
    /// Gets the window settings.
    ///
    /// @return The window settings.
    ///-------------------------------------------------------------------------
    //const WindowSettings& GetSettings() const;

    ///-------------------------------------------------------------------------
    /// Enable/disable vertical sync
    ///
    /// @param  a_enable (optional)
    ///-------------------------------------------------------------------------
    void SetVerticalSync(bool a_enable = true) { TLOC_UNUSED(a_enable); }

    ///-------------------------------------------------------------------------
    /// Sets the visibility of the mouse cursor.
    ///
    /// @param  a_visible True shows the mouse cursor
    ///-------------------------------------------------------------------------
    void SetMouseVisibility(bool a_visible) { TLOC_UNUSED(a_visible); }

    ///-------------------------------------------------------------------------
    /// Sets the window position
    ///
    /// @param  a_X The.
    /// @param  a_Y The.
    ///-------------------------------------------------------------------------
    void SetPosition(s32 a_x, s32 a_y) { TLOC_UNUSED_2(a_x, a_y); }

    ///-------------------------------------------------------------------------
    /// Sets a new window size. This will call the appropriate callbacks.
    ///
    /// @param  a_width  The width.
    /// @param  a_height The height.
    ///-------------------------------------------------------------------------
    void SetSize(size_type a_width, size_type a_height) { TLOC_UNUSED_2(a_width, a_height); }

    ///-------------------------------------------------------------------------
    /// Sets a visibility of the window.
    ///
    /// @param  a_visible true to show, false to hide.
    ///-------------------------------------------------------------------------
    void SetVisibility(bool a_visible) { TLOC_UNUSED(a_visible); }

    ///-------------------------------------------------------------------------
    /// Calls the OS specific display update.
    ///-------------------------------------------------------------------------
    void SwapBuffers() {}

  private:

    HWND      m_handle;
    size_type m_callbackPtr;
    HCURSOR   m_cursor;
    HICON     m_icon;
    bool      m_isCursorIn;
    HDC       m_deviceContext;
    HGLRC     m_OpenGLContext;

  };

};};};

#endif
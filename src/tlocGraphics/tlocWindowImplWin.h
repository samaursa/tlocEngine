#ifndef TLOC_WINDOW_IMPL_WIN_H
#define TLOC_WINDOW_IMPL_WIN_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocUtils.h"
#include "tlocCore/tlocTypes.h"

#include "tlocCore/tlocString.h"
#include "tlocCore/tlocString.inl"

#include "tlocCore/tlocPlatform.h"
#include "tlocCore/tlocNonCopyable.h"

#include "tlocGraphicsModes.h"
#include "tlocWindowSettings.h"

#include "tlocWindowImpl.h"

#define WIN32_LEAN_AND_MEAN
#include "Windows.h"
#include <gl/GL.h>

namespace tloc { namespace graphics { namespace priv {

  template<>
  class WindowImpl<core::PlatformInfo<>::platform_type> :
    public WindowImplBase<core::PlatformInfo<>::platform_type>
  {
  public:

    // TODO: Static assert to prevent other platforms from using this class

    typedef core::PlatformInfo<>::platform_type          platform_type;
    typedef WindowImpl<platform_type>                    this_type;
    typedef GraphicsMode<platform_type>                  graphics_mode;

    typedef void*                                        window_handle_type;
    typedef WindowSettings::style_type                   window_style_type;
    typedef tl_size                                      size_type;

  public:

    ///-------------------------------------------------------------------------
    /// Default constructor. Only initialzes values.
    ///-------------------------------------------------------------------------
    WindowImpl();
    ~WindowImpl();

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
      const window_style_type& a_style, const WindowSettings& a_settings);

    ///-------------------------------------------------------------------------
    /// Gets the width.
    ///
    /// @return The width.
    ///-------------------------------------------------------------------------
    size_type GetWidth() const;

    ///-------------------------------------------------------------------------
    /// Gets the height.
    ///
    /// @return The height.
    ///-------------------------------------------------------------------------
    size_type GetHeight() const;

    ///-------------------------------------------------------------------------
    /// Sets this window as active.
    ///
    /// @param  a_active true to set this window as active.
    ///-------------------------------------------------------------------------
    void SetActive(bool a_active);

    ///-------------------------------------------------------------------------
    /// Enable/disable vertical sync
    ///
    /// @param  a_enable (optional)
    ///-------------------------------------------------------------------------
    void SetVerticalSync(bool a_enable = true);

    ///-------------------------------------------------------------------------
    /// Sets the visibility of the mouse cursor.
    ///
    /// @param  a_visible True shows the mouse cursor
    ///-------------------------------------------------------------------------
    void SetMouseVisibility(bool a_visible);

    ///-------------------------------------------------------------------------
    /// Sets the window position
    ///
    /// @param  a_X The.
    /// @param  a_Y The.
    ///-------------------------------------------------------------------------
    void SetPosition(s32 a_x, s32 a_y);

    ///-------------------------------------------------------------------------
    /// Sets a new window size. This will call the appropriate callbacks.
    ///
    /// @param  a_width  The width.
    /// @param  a_height The height.
    ///-------------------------------------------------------------------------
    void SetSize(size_type a_width, size_type a_height);

    ///-------------------------------------------------------------------------
    /// Sets a visibility of the window.
    ///
    /// @param  a_visible true to show, false to hide.
    ///-------------------------------------------------------------------------
    void SetVisibility(bool a_visible);

    ///-------------------------------------------------------------------------
    /// Calls the OS specific display update.
    ///-------------------------------------------------------------------------
    void SwapBuffers();

  private:

    static LRESULT CALLBACK DoWindowProcedure(HWND a_handle, UINT a_message,
                                              WPARAM a_wparam, LPARAM a_lParam);
    void DoProcessEvent(UINT a_message, WPARAM a_wparam, LPARAM a_lparam);

    void DoRegisterWindowClass();
    void DoCreateContext(const graphics_mode& a_gMode,
                         WindowSettings& a_settings);
    void DoSwitchToFullscreen(const graphics_mode& a_gMode);
    void DoCleanup();

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
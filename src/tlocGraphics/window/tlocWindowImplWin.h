#ifndef TLOC_WINDOW_IMPL_WIN_H
#define TLOC_WINDOW_IMPL_WIN_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/types/tlocTypes.h>

#include <tlocCore/string/tlocString.h>
#include <tlocCore/string/tlocString.inl.h>

#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>

#include <tlocGraphics/window/tlocGraphicsModes.h>
#include <tlocGraphics/window/tlocWindowSettings.h>

#include <tlocGraphics/opengl/tlocFramebufferObject.h>

#include "tlocWindow.h"
#include "tlocWindowImpl.h"

#define WIN32_LEAN_AND_MEAN
#include "Windows.h"
#include <gl/GL.h>

namespace tloc { namespace graphics { namespace win { namespace priv {

  template <>
  class WindowImpl<Window_T<> >
    : public WindowImplBase<Window_T<> >

  {
  public:

    // TODO: Static assert to prevent other platforms from using this class

    typedef core_plat::PlatformInfo::platform_type       platform_type;
    typedef WindowImpl<Window_T<> >                      this_type;
    typedef WindowImplBase<Window_T<> >                  base_type;
    typedef GraphicsMode<platform_type>                  graphics_mode;
    typedef base_type::parent_window_type                parent_window_type;

    typedef HWND                                         window_handle_type;
    typedef WindowSettings::style_type                   window_style_type;
    typedef tl_size                                      size_type;

    typedef gl::FramebufferObject                        fbo_type;
    typedef gl::framebuffer_object_sptr                  fbo_sptr;

  public:

    ///-------------------------------------------------------------------------
    /// Default constructor. Only initialzes values.
    ///-------------------------------------------------------------------------
    WindowImpl(parent_window_type* a_parent);
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
    void Create(const graphics_mode& a_mode, const WindowSettings& a_settings);

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
    /// @brief
    /// Gets the maximum width of the window that the system is capable
    /// of supporting.
    ///
    /// @return The maximum width.
    ///-------------------------------------------------------------------------
    size_type GetMaxWidth() const;

    ///-------------------------------------------------------------------------
    /// @brief
    /// Gets the maximum height of the window that the system is capable
    /// of supporting.
    ///
    /// @return The maximum height.
    ///-------------------------------------------------------------------------
    size_type GetMaxHeight() const;

    void ProcessEvents();

    ///-------------------------------------------------------------------------
    /// Gets the window handle.
    ///
    /// @return The window handle.
    ///-------------------------------------------------------------------------
    window_handle_type GetWindowHandle() const;

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
    /// @brief Sets the window title.
    ///
    /// @param  a_title The title of the window.
    ///-------------------------------------------------------------------------
    void SetTitle(const char* a_title);

    ///-------------------------------------------------------------------------
    /// @brief Calls IsWindow() on the handle and returns the result
    ///
    /// @return true if window has bee created, false if not.
    ///-------------------------------------------------------------------------
    bool IsCreated() const;

    ///-------------------------------------------------------------------------
    /// Calls the OS specific display update.
    ///-------------------------------------------------------------------------
    void SwapBuffers();

    ///-------------------------------------------------------------------------
    /// Called by Window_T<> when setting up the renderer
    ///-------------------------------------------------------------------------
    fbo_sptr DoGetFramebuffer();

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

    window_handle_type  m_handle;
    size_type           m_callbackPtr;
    HCURSOR             m_cursor;
    HICON               m_icon;
    bool                m_isCursorIn;
    HDC                 m_deviceContext;
    HGLRC               m_OpenGLContext;

  };

};};};};

#endif
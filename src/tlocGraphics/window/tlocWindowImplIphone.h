#ifndef TLOC_WINDOW_IMPL_IPHONE_H
#define TLOC_WINDOW_IMPL_IPHONE_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocAny.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/types/tlocTypes.h>

#include <tlocCore/platform/tlocPlatform.h>

#include <tlocGraphics/window/tlocGraphicsModes.h>
#include <tlocGraphics/window/tlocWindowSettings.h>

#include <tlocGraphics/opengl/tlocFramebufferObject.h>

#include "tlocWindow.h"
#include "tlocWindowImpl.h"

#include <OpenGLES/ES2/gl.h>

namespace tloc { namespace graphics { namespace win { namespace priv {

  template <>
  class WindowImpl<Window_T<> >
    : public WindowImplBase<Window_T<> >

  {
  public:

    // TODO: Static assert to prevent other platforms from using this class

    typedef core_plat::PlatformInfo::platform_type  platform_type;
    typedef WindowImpl<Window_T<> >                 this_type;
    typedef WindowImplBase<Window_T<> >             base_type;
    typedef GraphicsMode<platform_type>             graphics_mode;
    typedef base_type::parent_window_type           parent_window_type;

    // Note: We are using tlocAny to replace Objective-C types in this case
    // since any source file (cpp) that included this header would have to be
    // treated as an Objective-C++ file.
    typedef core_t::Any /*(UIWindow*) */            window_handle_type;
    typedef WindowSettings::style_type              window_style_type;
    typedef tl_size                                 size_type;
    typedef core_t::Any /*(OpenGLView*) */          view_handle_type;
    typedef core_t::Any /*(OpenGLViewController*) */view_controller_handle_type;

    typedef gl::FramebufferObject                   fbo_type;
    typedef gl::framebuffer_object_sptr             fbo_sptr;

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
    /// @param  a_mode     The graphics mode
    /// @param  a_settings The window settings.
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
    
    bool HasValidContext() const;

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

    //------------------------------------------------------------------------
    // Implementation specific functions

    ///-------------------------------------------------------------------------
    /// Gets the parent window to this implementation
    ///
    /// @return The parent window handle
    ///-------------------------------------------------------------------------
    parent_window_type* GetParentWindowHandle();

    ///-------------------------------------------------------------------------
    /// Gets the window handle
    ///
    /// @return The window handle
    ///-------------------------------------------------------------------------
    window_handle_type GetWindowHandle();

    ///-------------------------------------------------------------------------
    /// Gets the OpenGLView handle
    ///
    /// @return The OpenGLView handle
    ///-------------------------------------------------------------------------
    view_handle_type GetOpenGLViewHandle();

    ///-------------------------------------------------------------------------
    /// Called by Window_T<> when setting up the window
    ///-------------------------------------------------------------------------
    fbo_sptr DoGetFramebuffer();

  private:

    window_handle_type m_handle;
    view_controller_handle_type m_viewController;
    view_handle_type m_view;

  };

};};};};

#endif
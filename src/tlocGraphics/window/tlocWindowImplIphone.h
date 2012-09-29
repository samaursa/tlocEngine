#ifndef TLOC_WINDOW_IMPL_WIN_H
#define TLOC_WINDOW_IMPL_WIN_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/types/tlocTypes.h>

#include <tlocCore/platform/tlocPlatform.h>

#include <tlocGraphics/window/tlocGraphicsModes.h>
#include <tlocGraphics/window/tlocWindowSettings.h>

#include "tlocWindow.h"
#include "tlocWindowImpl.h"

#include <OpenGLES/ES2/gl.h>

#import <UIKit/UIKit.h>
#import <tlocGraphics/window/tlocOpenGLViewIphone.h>
#import <tlocGraphics/window/tlocOpenGLViewControllerIphone.h>

namespace tloc { namespace graphics { namespace priv {
  
  template <>
  class WindowImpl<Window<> >
    : public WindowImplBase<Window<> >

  {
  public:

    // TODO: Static assert to prevent other platforms from using this class

    typedef core::PlatformInfo<>::platform_type     platform_type;
    typedef WindowImpl<Window<> >                   this_type;
    typedef WindowImplBase<Window<> >               base_type;
    typedef GraphicsMode<platform_type>             graphics_mode;
    typedef base_type::parent_window_type           parent_window_type;

    typedef UIWindow*                               window_handle_type;
    typedef WindowSettings::style_type              window_style_type;
    typedef tl_size                                 size_type;
    typedef OpenGLView*                             view_handle_type;
    typedef OpenGLViewController*                   view_controller_handle_type;

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
    void Create(const graphics_mode& a_mode, const WindowSettings& a_settings,
                const window_style_type& a_style);

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

  private:
    
    window_handle_type m_handle;
    view_controller_handle_type m_viewController;
    view_handle_type m_view;

  };

};};};

#endif
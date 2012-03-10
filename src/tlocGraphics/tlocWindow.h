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
#include "tlocWindowHandle.h"

namespace tloc { namespace graphics {


    ///-------------------------------------------------------------------------
    /// Platform independent window code
    ///-------------------------------------------------------------------------

    namespace priv
    {
      template <typename T_Platform> class    WindowImpl;
    }

  ///-------------------------------------------------------------------------
  /// A window to render to.
  ///
  /// Notes: The initial implementation was influenced by SFML
  ///
  /// @sa tloc::core::NonCopyable
  ///-------------------------------------------------------------------------
  template <typename T_Platform = typename core::PlatformInfo<>::platform_type>
  class Window : public core::NonCopyable
  {
  public:

    typedef T_Platform                                   platform_type;
    typedef GraphicsMode<T_Platform>                     graphics_mode;
    //typedef typename WindowHandle<T_Platform>::type      window_handle_type;
    typedef void*                                        window_handle_type;
    typedef typename WindowSettings::style_type          window_style_type;
    typedef tl_size                                      size_type;

  public:

    Window();
    ~Window();

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

    ///-------------------------------------------------------------------------
    /// Closes the window and destroys internal implementations. Does NOT
    /// destroy this object itself.
    ///-------------------------------------------------------------------------
    void Close() {}

    ///-------------------------------------------------------------------------
    /// Query whether the window has been created or not
    ///
    /// @return true if valid, false if not.
    ///-------------------------------------------------------------------------
    bool IsValid() const { return false; }

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
    void SetPosition(s32 a_x, s32 a_y) { TLOC_UNUSED(a_x); TLOC_UNUSED(a_y); }

    ///-------------------------------------------------------------------------
    /// Sets a new window size. This will call the appropriate callbacks.
    ///
    /// @param  a_width  The width.
    /// @param  a_height The height.
    ///-------------------------------------------------------------------------
    void SetSize(size_type a_width, size_type a_height)
    { TLOC_UNUSED(a_width); TLOC_UNUSED(a_height); }

    ///-------------------------------------------------------------------------
    /// Sets a visibility of the window.
    ///
    /// @param  a_visible true to show, false to hide.
    ///-------------------------------------------------------------------------
    void SetVisibility(bool a_visible) { TLOC_UNUSED(a_visible); }

  protected:

    typedef priv::WindowImpl<T_Platform>    impl_type;
    impl_type*                              m_impl;

  };

};};

#endif
#ifndef TLOC_WINDOW_H
#define TLOC_WINDOW_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/containers/tlocQueue.h>
#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>
#include <tlocCore/base_classes/tlocTemplateDispatchDefaults.h>

#include <tlocGraphics/window/tlocGraphicsModes.h>
#include <tlocGraphics/window/tlocWindowSettings.h>
#include <tlocGraphics/window/tlocWindowHandle.h>

// Platform independant window implementation (forward declaration)
#include "tlocWindowImpl.h"

namespace tloc { namespace graphics {

  struct WindowEvent
  {
    enum EventType
    {
      none = -1,
      close = 0,
      resized,
      lost_focus,
      gained_focus,
      destroy,

      events_count
    };

    WindowEvent(const EventType& a_event = none) : m_type(a_event) {}

    EventType m_type;
  };

  struct WindowCallbacks
  {
    virtual void OnWindowEvent(const WindowEvent& a_event) = 0;
  };

  template <typename T>
  struct WindowCallbackGroupT :
    public core::CallbackGroupTArray<T, WindowCallbacks>::type
  {
    typedef typename core::CallbackGroupTArray<T, WindowCallbacks>::type 
      base_type;
    using base_type::m_observers;
    
    virtual void OnWindowEvent(const WindowEvent& a_event)
    {
      for (u32 i = 0; i < m_observers.size(); ++i)
      {
        m_observers[i]->OnWindowEvent(a_event);
      }
    }
  };

  ///-------------------------------------------------------------------------
  /// A window to render to.
  ///
  /// Notes: The initial implementation was influenced by SFML
  ///
  /// @sa tloc::core::NonCopyable
  ///-------------------------------------------------------------------------
  template <typename T_Platform = typename core::PlatformInfo<>::platform_type>
  class Window :
    public core::DispatcherBaseArray <WindowCallbacks, WindowCallbackGroupT>::type,
    public core::NonCopyable
  {
  public:

    typedef T_Platform                                   platform_type;
    typedef Window<platform_type>                        this_type;
    typedef GraphicsMode<T_Platform>                     graphics_mode;
    typedef typename WindowHandle<T_Platform>::type      window_handle_type;
    typedef typename WindowSettings::style_type          window_style_type;
    typedef tl_size                                      size_type;

  public:

    Window();
    ~Window();

    ///-------------------------------------------------------------------------
    /// Creates an invisible window (lookup False Context)
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
                window_style_type a_style = WindowSettings::style_resize |
                                            WindowSettings::style_close);

    ///-------------------------------------------------------------------------
    /// Closes the window and destroys internal implementations. Does NOT
    /// destroy this object itself.
    ///-------------------------------------------------------------------------
    void Close();

    ///-------------------------------------------------------------------------
    /// Query whether the window has been created or not
    ///
    /// @return true if valid, false if not.
    ///-------------------------------------------------------------------------
    bool IsValid() const;

    ///-------------------------------------------------------------------------
    /// @brief Query if the window has been created successfully
    ///
    /// @return true if window was created, false if not.
    ///-------------------------------------------------------------------------
    bool IsCreated() const;

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
    /// Gets an event on the stack, if stack is empty, then asks the window
    /// to get more events (if any)
    ///
    /// @param [in,out] a_eventOut The last event on the stack
    ///
    /// @return true if an event exists, false otherwise
    ///-------------------------------------------------------------------------
    bool GetEvent(WindowEvent& a_eventOut);

    ///-------------------------------------------------------------------------
    /// Gets the window settings.
    ///
    /// @return The window settings.
    ///-------------------------------------------------------------------------
    //const WindowSettings& GetSettings() const;
    
    ///-------------------------------------------------------------------------
    /// Gets the window handle.
    ///
    /// @return The window handle.
    ///-------------------------------------------------------------------------
    window_handle_type GetWindowHandle() const;

    ///-------------------------------------------------------------------------
    /// Enable/disable vertical sync
    ///
    /// @param  a_enable (optional)
    ///-------------------------------------------------------------------------
    void SetVerticalSync(bool a_enable = true);

    ///-------------------------------------------------------------------------
    /// @brief Set this window as active
    ///
    /// @param  a_active (optional)
    ///-------------------------------------------------------------------------
    void SetActive(bool a_active = true) const;

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

    ///-------------------------------------------------------------------------
    /// Sends a WindowEvent to all registered objects
    ///
    /// @param  a_event The WindowEvent
    ///-------------------------------------------------------------------------
    void SendEvent(const WindowEvent& a_event);

  protected:

    void DoCreateImpl();

    typedef priv::WindowImpl<this_type>     impl_type;
    impl_type*                              m_impl;
    core::Queue<WindowEvent>                m_events;
  };
  
  //////////////////////////////////////////////////////////////////////////
  // Global Functions
  
  ///-------------------------------------------------------------------------
  /// Gets the current active window. This is the window that has focus.
  ///
  /// @return  The current active Window
  ///-------------------------------------------------------------------------
  Window<>* GetCurrentActiveWindow();
  
  namespace priv {
  
    ///-------------------------------------------------------------------------
    /// Sets the current active window. This is primarily when a window gains 
    /// focus.
    ///
    /// @param  a_window The Window
    ///-------------------------------------------------------------------------
    void SetCurrentActiveWindow(Window<>* a_window);
    
    ///-------------------------------------------------------------------------
    /// Sets the window as non active. This is primarily when a window loses
    /// focus. If it is the current active window, the current active window is
    /// set to null.
    ///
    /// @param  a_window The Window
    ///-------------------------------------------------------------------------
    void SetNonActiveWindow(Window<>* a_window);
  
  };

};};

#endif
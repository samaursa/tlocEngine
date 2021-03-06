#ifndef TLOC_WINDOW_H
#define TLOC_WINDOW_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/data_structures/tlocVariadic.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/containers/tlocQueue.h>
#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>
#include <tlocCore/dispatch/tlocTemplateDispatchDefaults.h>
#include <tlocCore/dispatch/tlocEvent.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocGraphics/window/tlocGraphicsModes.h>
#include <tlocGraphics/window/tlocWindowSettings.h>
#include <tlocGraphics/window/tlocWindowHandle.h>
#include <tlocGraphics/renderer/tlocRenderer.h>

#include <tlocMath/types/tlocAspectRatio.h>

// Platform independant window implementation (forward declaration)
#include "tlocWindowImpl.h"

namespace tloc { namespace graphics { namespace win {

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
      open_url,

      events_count
    };

    typedef tl_size                           size_type;
    typedef core_ds::Tuple<size_type, 2>      dim_type;
    typedef core_ds::Variadic<size_type, 2>   variadic_type;
    typedef core_str::String                  string_type;

    WindowEvent()
      : m_type(none)
      , m_dim(variadic_type(0, 0))
    { }

    WindowEvent(const EventType& a_event,
                tl_size a_sizeX, tl_size a_sizeY,
                const string_type& a_url = string_type(),
                const string_type& a_urlSourceApplication = string_type())
      : m_type(a_event)
      , m_dim(variadic_type(a_sizeX, a_sizeY))
      , m_url(a_url)
      , m_urlSourceApplication(a_urlSourceApplication)
    { }

    size_type GetWidth() const
    { return m_dim[0]; }

    size_type GetHeight() const
    { return m_dim[1]; }

    EventType m_type;
    dim_type  m_dim;

    string_type m_url;
    string_type m_urlSourceApplication;
  };

  struct WindowCallbacks
  {
  public:
    typedef core_dispatch::Event                    event_type;

  public:
    virtual event_type OnWindowEvent(const WindowEvent& a_event) = 0;
  };

  template <typename T>
  struct WindowCallbackGroupT
    : public core::dispatch::CallbackGroupTArray<T, WindowCallbacks>::type
  {
  public:
    typedef typename core::dispatch::
      CallbackGroupTArray<T, WindowCallbacks>::type         base_type;

    typedef typename base_type::event_type                  event_type;

    using base_type::m_observers;

  public:
    virtual event_type OnWindowEvent(const WindowEvent& a_event)
    {
      for (u32 i = 0; i < m_observers.size(); ++i)
      {
        if (m_observers[i]->OnWindowEvent(a_event).IsVeto())
        { return core_dispatch::f_event::Veto(); }
      }

      return core_dispatch::f_event::Continue();
    }
  };

  ///-------------------------------------------------------------------------
  /// A window to render to.
  ///
  /// Notes: The initial implementation was influenced by SFML
  ///
  /// @sa tloc::core::NonCopyable
  ///-------------------------------------------------------------------------
  template <typename T_Platform = typename core_plat::PlatformInfo::platform_type>
  class Window_T
    : public core::dispatch::DispatcherBaseArray
             <WindowCallbacks, WindowCallbackGroupT>::type
    , public core_bclass::NonCopyable_I
  {
  public:

    typedef T_Platform                                   platform_type;
    typedef Window_T<platform_type>                      this_type;
    typedef GraphicsMode<T_Platform>                     graphics_mode;
    typedef typename WindowHandle<T_Platform>::type      window_handle_type;
    typedef typename WindowSettings::style_type          window_style_type;
    typedef tl_size                                      size_type;
    typedef math_t::AspectRatio                          aspect_ratio;
    typedef gfx_rend::Renderer                           renderer_type;
    typedef renderer_type::Params                        renderer_params_type;
    typedef gfx_rend::renderer_sptr                      renderer_sptr;
    typedef priv::WindowImpl<this_type>                  impl_type;
    typedef WindowEvent::dim_type                        dim_type;

  public:

    Window_T();
    ~Window_T();

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
    template <typename T_WindowHandleType>
    void Create(T_WindowHandleType a_ptr, const WindowSettings& a_settings)
    {
      typedef Loki::IsSameType<T_WindowHandleType, window_handle_type>
        win_handle_type;
      DoCreate(a_ptr, a_settings, Loki::Int2Type<win_handle_type::value>() );
      DoSetupRenderer();
    }

    ///-------------------------------------------------------------------------
    /// Creates the actual window with the specified properties
    ///
    /// @param  a_mode The graphics mode
    /// @param  a_prop The window properties.
    ///-------------------------------------------------------------------------
    void Create(const graphics_mode& a_mode, const WindowSettings& a_settings);

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
    /// Gets the width and height.
    ///
    /// @return The window dimensions
    ///-------------------------------------------------------------------------
    dim_type GetDimensions() const;

    ///-------------------------------------------------------------------------
    /// Returns the horizontal and vertical DPI for the device.
    ///
    /// @return The device DPI
    ///-------------------------------------------------------------------------
    dim_type GetDPI() const;

    ///-------------------------------------------------------------------------
    /// @brief
    /// Gets the maximum width of the window that the system is capable
    /// of producing.
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

    ///-------------------------------------------------------------------------
    /// @brief Gets the aspect ratio of this window.
    ///
    /// @return The aspect ratio.
    ///-------------------------------------------------------------------------
    aspect_ratio GetAspectRatio() const;

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

    bool IsActive() const;

    bool HasValidContext() const;

    ///-------------------------------------------------------------------------
    /// Sets the visibility of the mouse cursor.
    ///
    /// @param  a_visible True shows the mouse cursor
    ///-------------------------------------------------------------------------
    void SetMouseVisibility(bool a_visible);

    void ConfineMouseToWindow(bool a_confine = true);

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
    /// @brief Sets the window title. May not work on all platforms.
    ///
    /// @param  a_title The title of the window.
    ///-------------------------------------------------------------------------
    void SetTitle(BufferArg a_title);

    ///-------------------------------------------------------------------------
    /// Calls the OS specific display update.
    ///-------------------------------------------------------------------------
    void SwapBuffers() const;

    ///-------------------------------------------------------------------------
    /// Sends a WindowEvent to all registered objects
    ///
    /// @param  a_event The WindowEvent
    ///-------------------------------------------------------------------------
    void SendEvent(const WindowEvent& a_event);

    ///-------------------------------------------------------------------------
    /// Get the window renderer
    ///-------------------------------------------------------------------------
    renderer_sptr GetRenderer() const;

    TLOC_DECL_AND_DEF_GETTER(bool, IsMouseVisible, m_mouseVisible);
    TLOC_DECL_AND_DEF_GETTER(bool, IsMouseConfined, m_mouseConfined);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(WindowSettings, GetSettings, m_windowSettings);

  private:
    typedef tloc::type_true   IsWindowHandle;
    typedef tloc::type_false  IsNotWindowHandle;

    void DoCreate(window_handle_type a_ptr, const WindowSettings& a_settings,
                  IsWindowHandle);
    void DoCreate(const graphics_mode& a_mode, const WindowSettings& a_settings,
                  IsNotWindowHandle);
    void DoSetupRenderer();
  protected:

    void DoCreateImpl();

    WindowSettings                          m_windowSettings;
    impl_type*                              m_impl;
    core::containers::Queue<WindowEvent>    m_events;
    bool                                    m_mouseVisible;
    bool                                    m_mouseConfined;
    renderer_sptr                           m_renderer;
  };

  //////////////////////////////////////////////////////////////////////////
  // Global Functions

  ///-------------------------------------------------------------------------
  /// Gets the current active window. This is the window that has focus.
  ///
  /// @return  The current active Window
  ///-------------------------------------------------------------------------
  Window_T<>* GetCurrentActiveWindow();

  namespace priv {

    ///-------------------------------------------------------------------------
    /// Sets the current active window. This is primarily when a window gains
    /// focus.
    ///
    /// @param  a_window The Window
    ///-------------------------------------------------------------------------
    void SetCurrentActiveWindow(Window_T<>* a_window);

    ///-------------------------------------------------------------------------
    /// Sets the window as non active. This is primarily when a window loses
    /// focus. If it is the current active window, the current active window is
    /// set to null.
    ///
    /// @param  a_window The Window
    ///-------------------------------------------------------------------------
    void SetNonActiveWindow(Window_T<>* a_window);
  };

  //////////////////////////////////////////////////////////////////////////
  // Typedefs

  typedef Window_T<>    Window;

  TLOC_TYPEDEF_ALL_SMART_PTRS(Window, window);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(Window, window);

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(Window_T<>);

};};};

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_win::Window);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(tloc::gfx_win::Window);

#endif
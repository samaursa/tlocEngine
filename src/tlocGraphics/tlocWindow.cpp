#include "tlocWindow.h"

#include "tlocCore/tlocArray.h"
#include "tlocCore/tlocArray.inl"

//------------------------------------------------------------------------
// Platform dependant includes

#if defined(TLOC_WIN32) || defined(TLOC_WIN64)
# define WIN32_LEAN_AND_MEAN
# include <Windows.h>
# include <GL/GL.h>
#else
# error "WIP"
#endif

namespace tloc { namespace graphics {

  //////////////////////////////////////////////////////////////////////////
  // Platform independant window members

  template <typename T_Platform>
  struct WindowMembers
  {
    WindowMembers()
    {
      TLOC_STATIC_ASSERT(false, Patform_not_supported);
    }
  };

  //------------------------------------------------------------------------
  // Platform = Windows

  template<>
  struct WindowMembers<core::Platform_win>
  {
    WindowMembers()
      : m_handle(NULL)
      , m_callbackPtr(0)
      , m_cursor(NULL)
      , m_icon(NULL)
      , m_isCursorIn(false)
      , m_deviceContext(NULL)
      , m_OpenGLContext(NULL)
    {
    }

    HWND    m_handle;
    tl_size m_callbackPtr;
    HCURSOR m_cursor;
    HICON   m_icon;
    bool    m_isCursorIn;
    HDC     m_deviceContext;
    HGLRC   m_OpenGLContext;
  };

  template<>
  struct WindowMembers<core::Platform_win32> :
    public WindowMembers<core::Platform_win>
  {
    WindowMembers() : WindowMembers<core::Platform_win>() {}
  };

  template<>
  struct WindowMembers<core::Platform_win64> :
    public WindowMembers<core::Platform_win>
  {
    WindowMembers() : WindowMembers<core::Platform_win>() {}
  };

  //////////////////////////////////////////////////////////////////////////
  //  Window.

#define WINDOW_TEMP   typename T_Platform
#define WINDOW_PARAMS T_Platform
#define WINDOW_TYPE   typename template<WINDOW_PARAMS>

  // ------------------------------------------------------------------------
  //  Instantiate the template to avoid linking errors. This will only
  //  instantiate for the platform it is being compiled on.

  template Window<>;

  template <WINDOW_TEMP>
  Window<WINDOW_PARAMS>::Window()
    : m_members(NULL)
    , m_properties("Dummy")
    , m_graphicsMode(graphics_mode::Properties(0, 0))
  {
    m_members = new WindowMembers<platform_type>();
  }

  template <WINDOW_TEMP>
  Window<WINDOW_PARAMS>::~Window()
  {
    delete m_members;
  }

  template <WINDOW_TEMP>
  void Window<WINDOW_PARAMS>::Create()
  {
    DoCreate<platform_type>(platform_type());
  }

  template <WINDOW_TEMP>
  void Window<WINDOW_PARAMS>::Create(const graphics_mode& a_mode,
                                     const Properties& a_prop)
  {
    m_properties    = a_prop;
    m_graphicsMode  = a_mode;

  }

  template <WINDOW_TEMP>
  template <typename T>
  void Window<WINDOW_PARAMS>::DoCreate(core::Platform_win)
  {
  }

  template <WINDOW_TEMP>
  template <typename T>
  void Window<WINDOW_PARAMS>::DoCreate(core::Platform_osx)
  {
    TLOC_STATIC_ASSERT_WIP();
  }

  //template <WINDOW_TEMP>
  //void Window<WINDOW_PARAMS>::DoCreate(core::Platform_osx)
  //{
  //}

  //template <WINDOW_TEMP>
  //void Window<WINDOW_PARAMS>::DoCreate(core::Platform_linux)
  //{
  //}

};};
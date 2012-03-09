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
    , m_graphicsMode(graphics_mode::Properties(1, 1))
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

    DoCreate<platform_type>(platform_type());
  }

  LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
  {
    switch(msg)
    {
    case WM_CLOSE:
      DestroyWindow(hwnd);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    default:
      return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
  }

  template <WINDOW_TEMP>
  template <typename T>
  void Window<WINDOW_PARAMS>::DoCreate(core::Platform_win)
  {
    WNDCLASSW WindowClass;
    WindowClass.style = 0;
    WindowClass.lpfnWndProc = WndProc;
    WindowClass.cbClsExtra = 0;
    WindowClass.cbWndExtra = 0;
    WindowClass.hInstance = GetModuleHandle(NULL);
    WindowClass.hIcon = NULL;
    WindowClass.hCursor = 0;
    WindowClass.hbrBackground = 0;
    WindowClass.lpszMenuName = NULL;
    WindowClass.lpszClassName = L"OpenGL";
    if (!RegisterClassW(&WindowClass))
    {
      TLOC_ASSERT(false, "Failed!");
    }

    DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    DWORD dwStyle = WS_OVERLAPPEDWINDOW;

    //m_members->m_handle = CreateWindowW(L"TLOC Window", L"Test", WS_CAPTION | WS_MINIMIZEBOX, 0, 0, 100, 100, NULL, NULL, GetModuleHandle(NULL), NULL);
    m_members->m_handle = CreateWindowEx(dwExStyle, "OpenGL", "Test",
      WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle, 0, 0, 400, 400, NULL, NULL, WindowClass.hInstance, NULL);
    ShowWindow(m_members->m_handle, SW_SHOW);
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
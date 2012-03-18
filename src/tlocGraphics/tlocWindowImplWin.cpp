#include "tlocWindowImplWin.h"

#include "glext.h"
#include "wglext.h"

namespace tloc { namespace graphics { namespace priv {

#define WINDOW_IMPL_WIN_PARAMS core::PlatformInfo<>::platform_type
#define WINDOW_IMPL_WIN_TYPE WindowImpl<WINDOW_IMPL_WIN_PARAMS>

  const wchar_t g_className[] = L"TLOC_Window";

  WindowImpl<WINDOW_IMPL_WIN_PARAMS>::WindowImpl()
    : WindowImplBase()
    , m_handle(NULL)
    , m_callbackPtr(0)
    , m_cursor(NULL)
    , m_icon(NULL)
    , m_isCursorIn(false)
    , m_deviceContext(NULL)
    , m_OpenGLContext(NULL)
  {
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::Create()
  {
    DoRegisterWindowClass();

    m_graphicsMode = graphics_mode(graphics_mode::Properties(1, 1));
    graphics_mode::Properties props = m_graphicsMode.GetProperties();

    DWORD error = GetLastError();

    // Create a dummy window
    m_handle = CreateWindowW(g_className, L"", WS_POPUP | WS_DISABLED, 0, 0,
      (INT)props.m_width, (INT)props.m_height, NULL, NULL,
      GetModuleHandle(NULL), NULL);

    error = GetLastError();

    ShowWindow(m_handle, SW_HIDE);

    if (m_handle)
    {
      m_windowSettings.m_depthBits = 0;
      m_windowSettings.m_stencilBits = 0;
      m_windowSettings.m_antiAlias = 0;

      DoCreateContext(graphics_mode(props), m_windowSettings);
    }
    else
    {
      // LOG: Could not create Win32 Window
      TLOC_ASSERT(m_handle, "Could not create Win32 window!");
    }
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::
    Create(window_handle_type a_ptr, const WindowSettings& a_settings)
  {
    TLOC_UNUSED_2(a_ptr, a_settings);
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::
    Create(const graphics_mode& a_mode, const core::String& a_title,
           const window_style_type& a_style, const WindowSettings& a_settings)
  {
    m_graphicsMode    = a_mode;
    m_windowSettings  = a_settings;

    DoRegisterWindowClass();

    const graphics_mode::Properties modeProps = a_mode.GetProperties();

    // Center the window to the screen regardless of the given size
    HDC screenDC     = GetDC(NULL);
    size_type left   = (GetDeviceCaps(screenDC, HORZRES) - modeProps.m_width)  / 2;
    size_type top    = (GetDeviceCaps(screenDC, VERTRES) - modeProps.m_height) / 2;
    size_type width  = modeProps.m_width;
    size_type height = modeProps.m_height;
    // LOG: Window resolution greater than screen's resolution
    ReleaseDC(NULL, screenDC);

    DWORD win32Style = WS_VISIBLE;
    if (win32Style == WindowSettings::style_none)
    {
      win32Style |= WS_POPUP;
    }
    else
    {
      if (a_style& WindowSettings::style_titlebar)
      { win32Style |= WS_CAPTION | WS_MINIMIZEBOX; }
      if (a_style& WindowSettings::style_resize)
      { win32Style |= WS_THICKFRAME | WS_MAXIMIZEBOX; }
      if (a_style& WindowSettings::style_close)
      { win32Style |= WS_SYSMENU; }
    }

    // Adjust the window's width and height given the requested resolution
    const bool fullScreen = (a_style & WindowSettings::style_fullscreen) == 1;
    if (fullScreen == false)
    {
      RECT rect = {0, 0, (LONG)width, (LONG)height};
      AdjustWindowRect(&rect, win32Style, false);
      width = rect.right - rect.left;
      height = rect.bottom - rect.top;
    }

    // Create the actual window
    const size_type wTitleSize = 256; char32 wTitle[wTitleSize];
    s32 retIndex = core::CharAsciiToWide(a_title.c_str(), -1, wTitle, wTitleSize);
    wTitle[retIndex] = L'\0';
    m_handle = CreateWindowW(g_className, wTitle, win32Style, (int)left,
      (int)top, (int)width, (int)height, NULL, NULL, GetModuleHandle(NULL),
      this);

    // LOG: Grab log from GetLastError
    TLOC_ASSERT(m_handle, "CreateWindowW failed.");
    DoCreateContext(a_mode, m_windowSettings);

    // (From SFML): Actual size of window may be different after the
    // AdjustWindowRect() call.
    RECT actualRect;
    GetClientRect(m_handle, &actualRect);
    graphics_mode::Properties& gProps = m_graphicsMode.GetProperties();

    gProps.m_width  = actualRect.right - actualRect.left;
    gProps.m_height = actualRect.bottom - actualRect.top;
  }

  LRESULT CALLBACK WindowImpl<WINDOW_IMPL_WIN_PARAMS>::
    DoProcessEvents(HWND a_handle, UINT a_message, WPARAM a_wparam,
                    LPARAM a_lParam)
  {
    return DefWindowProcW(a_handle, a_message, a_wparam, a_lParam);
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::DoRegisterWindowClass()
  {
    // TODO: Register class for non-unicode OS (older windows)

    WNDCLASSW WindowClass;
    WindowClass.style         = 0;
    WindowClass.lpfnWndProc   = &this_type::DoProcessEvents;
    WindowClass.cbClsExtra    = 0;
    WindowClass.cbWndExtra    = 0;
    WindowClass.hInstance     = GetModuleHandle(NULL);
    WindowClass.hIcon         = NULL;
    WindowClass.hCursor       = 0;
    WindowClass.hbrBackground = 0;
    WindowClass.lpszMenuName  = NULL;
    WindowClass.lpszClassName = g_className;

    ATOM result = RegisterClassW(&WindowClass);
    TLOC_UNUSED(result);
    TLOC_ASSERT(result, "Failed to register the window class");
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::
    DoCreateContext(const graphics_mode& a_gMode, WindowSettings& a_settings)
  {
    TLOC_UNUSED(a_gMode);

    m_deviceContext = GetDC(m_handle);
    TLOC_ASSERT(m_deviceContext, "Failed to get window's device context");

    s32 bestFormat = 0;
    if (a_settings.m_antiAlias > 0)
    {
      // Since we don't have GLEW yet, we will have to manually get the function
      // which will in turn give us the pixel format
      PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB =
        reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>
        (wglGetProcAddress("wglChoosePixelFormatARB"));

      if (wglChoosePixelFormatARB)
      {
        s32 pixAttribs[] =
        {
          WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
          WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
          WGL_ACCELERATION_ARB, GL_TRUE,
          WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
          WGL_SAMPLE_BUFFERS_ARB, (a_settings.m_antiAlias ? GL_TRUE : GL_FALSE),
          WGL_SAMPLES_ARB, (a_settings.m_antiAlias),
          0, 0
        };

        // Grab all the formats
        const s32 maxFormatsToReturn = 256;
        s32 formats[maxFormatsToReturn];
        UINT numFormats;
        FLOAT attributeList[] = {0, 0};

        bool isValid = wglChoosePixelFormatARB(m_deviceContext, pixAttribs,
          attributeList, maxFormatsToReturn, formats, &numFormats) != 0;

        if (isValid == false || numFormats == 0)
        {
          if (a_settings.m_antiAlias > 2)
          {
            // LOG: Failed to find a format that supports the required AA,
            // trying lower levels.
            a_settings.m_antiAlias = pixAttribs[11] = 2;
            isValid = wglChoosePixelFormatARB(m_deviceContext, pixAttribs,
              attributeList, maxFormatsToReturn, formats, &numFormats) != 0;
          }

          if (isValid == false || numFormats == 0)
          {
            // LOG: Cannot find pixel format supporting any AA, disabling AA
            a_settings.m_antiAlias = 0;
          }
        }

        if (isValid == false && numFormats > 0)
        {
          // TODO: Select the best format available
          TLOC_ASSERT_WIP();
        }

      }
      else
      {
        // LOG: AA not supported and will be disabled
        a_settings.m_antiAlias = 0;
      }
    }

    if (bestFormat == 0)
    {
      PIXELFORMATDESCRIPTOR pixelDesc;
      const size_type pixelDescSize = sizeof(pixelDesc);
      ZeroMemory(&pixelDesc, pixelDescSize);

      pixelDesc.nSize = pixelDescSize;
      pixelDesc.nVersion = 1;
      pixelDesc.iLayerType = PFD_MAIN_PLANE;
      pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
      pixelDesc.iPixelType = PFD_TYPE_RGBA;
      pixelDesc.cColorBits = static_cast<BYTE>(a_gMode.GetProperties().m_bitsPerPixel);
      pixelDesc.cDepthBits = static_cast<BYTE>(a_settings.m_depthBits);
      pixelDesc.cStencilBits = static_cast<BYTE>(a_settings.m_stencilBits);
      pixelDesc.cAlphaBits = a_gMode.GetProperties().m_bitsPerPixel == 32 ? 8 : 0;

      bestFormat = ChoosePixelFormat(m_deviceContext, &pixelDesc);
      TLOC_ASSERT(bestFormat, "Failed to find a suitable pixel format for the "
        L"device context -- cannot create OpenGL context");
    }

    PIXELFORMATDESCRIPTOR pixFormat;
    const size_type pixFormatSize = sizeof(pixFormat);
    pixFormat.nSize    = pixFormatSize;
    pixFormat.nVersion = 1;

    DescribePixelFormat(m_deviceContext, bestFormat, pixFormatSize, &pixFormat);

    a_settings.m_depthBits   = pixFormat.cDepthBits;
    a_settings.m_stencilBits = pixFormat.cStencilBits;

    bool setPixelFormatResult =
      SetPixelFormat(m_deviceContext, bestFormat, &pixFormat) != 0;
    TLOC_UNUSED(setPixelFormatResult);
    TLOC_ASSERT(setPixelFormatResult,
      "SetPixelFormat() failed -- cannot create OpenGL context");

    m_OpenGLContext = wglCreateContext(m_deviceContext);
    TLOC_ASSERT(m_OpenGLContext, "Failed to create OpenGL context");

    SetActive(true);

    if (a_settings.m_antiAlias > 0)
    {
      glEnable(GL_MULTISAMPLE_ARB);
    }
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::SetActive(bool a_active)
  {
    if (a_active)
    {
      if (m_deviceContext && m_OpenGLContext && (wglGetCurrentContext() != m_OpenGLContext))
      {
        wglMakeCurrent(m_deviceContext, m_OpenGLContext);
      }
      else
      {
        // LOG: Window already active
      }
    }
    else
    {
      if (wglGetCurrentContext() == m_OpenGLContext)
      {
        wglMakeCurrent(NULL, NULL);
      }
      else
      {
        // LOG: Window is already inactive
      }
    }
  }

};};};
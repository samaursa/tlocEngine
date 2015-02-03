#include "tlocWindowImplWin.h"

#include <3rdParty/Graphics/glext/glext.h>
#include <3rdParty/Graphics/glext/wglext.h>

#include <tlocCore/tlocAssert.h>
#include <tlocCore/utilities/tlocType.h>
#include <tlocCore/logging/tlocLogger.h>

namespace tloc { namespace graphics { namespace win { namespace priv {

  using namespace core::string;

#define WINDOW_IMPL_WIN_PARAMS Window_T<>
#define WINDOW_IMPL_WIN_TYPE WindowImpl<WINDOW_IMPL_WIN_PARAMS>

#define VERIFY_DEVICE_CONTEXT() \
    TLOC_ASSERT(m_deviceContext, "No device context available -- did you call "\
       "Create()?");
#define VERIFY_OPENGL_CONTEXT() \
    TLOC_ASSERT(m_OpenGLContext, "No OpenGL context available -- did you call "\
       "Create()? -- If yes, it may not have succeeded");

  //////////////////////////////////////////////////////////////////////////
  // Global variables

  const wchar_t g_className[]                                = L"TLOC_Window";
  WindowImpl<WINDOW_IMPL_WIN_PARAMS>* g_currFullScreenWindow = nullptr;
  WINDOW_IMPL_WIN_TYPE::size_type g_currWindowCount          = 0;

  // ///////////////////////////////////////////////////////////////////////
  // Windows has a default framebuffer with the id of 0. We will therefore
  // manually set that ID on FramebufferObject so that we have a FBO with
  // an ID of 0. To do that we need to inherit from FBO because its constructor
  // to construct an FBO with an ID is protected for this very purpose

  class WindowsFramebufferObject
    : public gl::FramebufferObject
  {
  public:
    typedef gl::FramebufferObject           base_type;
  public:
    WindowsFramebufferObject()
      : base_type(gl::p_fbo::Default())
    { }
  };

  //////////////////////////////////////////////////////////////////////////
  // WindowImpl<>

  WindowImpl<WINDOW_IMPL_WIN_PARAMS>::WindowImpl(parent_window_type* a_parent)
    : WindowImplBase(a_parent)
    , m_handle(nullptr)
    , m_callbackPtr(0)
    , m_cursor(nullptr)
    , m_icon(nullptr)
    , m_isCursorIn(false)
    , m_deviceContext(nullptr)
    , m_OpenGLContext(nullptr)
  {
    TLOC_ASSERT_NOT_NULL(a_parent);
  }

  WindowImpl<WINDOW_IMPL_WIN_PARAMS>::~WindowImpl()
  {
    if (m_icon) { DestroyIcon(m_icon); }
    if (m_callbackPtr == TLOC_NULL)
    {
      if (m_handle) { DestroyWindow(m_handle); }

      --g_currWindowCount;

      // If this is the last window...
      if (g_currWindowCount == 0)
      {
        UnregisterClassW(g_className, GetModuleHandle(TLOC_NULL));
      }
    }
    else
    {
      // Window is external, which we are not handling yet
      TLOC_ASSERT_FALSE("External windows are not supported yet");
    }
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::Create()
  {
    if (g_currWindowCount == 0) { DoRegisterWindowClass(); }

    m_graphicsMode = graphics_mode(graphics_mode::Properties(1, 1));
    graphics_mode::Properties props = m_graphicsMode.GetProperties();

    DWORD error;

    // Create a dummy window
    m_handle = CreateWindowW(g_className, L"", WS_POPUP | WS_DISABLED, 0, 0,
      (INT)props.m_width, (INT)props.m_height, TLOC_NULL, TLOC_NULL,
      GetModuleHandle(TLOC_NULL), TLOC_NULL);

    error = GetLastError();
    // Possible reasons:
    // - Too high a resolution
    // - Incorrect window properties
    TLOC_ASSERT(error == 0, "Error creating Window");

    ShowWindow(m_handle, SW_HIDE);

    if (m_handle)
    {
      m_windowSettings.SetDepthBits(0);
      m_windowSettings.SetStencilBits(0);
      m_windowSettings.SetAntiAlias(0);

      DoCreateContext(graphics_mode(props), m_windowSettings);

      ++g_currWindowCount;
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
    TLOC_ASSERT_WIP();
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::
    Create(const graphics_mode& a_mode, const WindowSettings& a_settings)
  {
    m_graphicsMode    = a_mode;
    m_windowSettings  = a_settings;

    if (g_currWindowCount == 0) { DoRegisterWindowClass(); }

    const graphics_mode::Properties modeProps = a_mode.GetProperties();

    // Center the window to the screen regardless of the given size

    HDC       screenDC = GetDC(TLOC_NULL);

    const tl_size horDeviceCap = core_utils::CastNumber<tl_size>
      (GetDeviceCaps(screenDC, HORZRES));
    const tl_size verDeviceCap = core_utils::CastNumber<tl_size>
      (GetDeviceCaps(screenDC, VERTRES));

    tl_size   left		 = (horDeviceCap - modeProps.m_width)  / 2;
    tl_size   top			 = (verDeviceCap - modeProps.m_height) / 2;
    size_type width		 = modeProps.m_width;
    size_type height	 = modeProps.m_height;
    ReleaseDC(TLOC_NULL, screenDC);

    TLOC_LOG_GFX_WARN_IF(width > GetMaxWidth() || height > GetMaxHeight())
      << "Screen width/height not supported: "
      << width << ", " << height;

    using namespace p_window_settings;
    DWORD win32Style = WS_VISIBLE;
    if (a_settings.GetStyleBits() == style::None::s_glParamName)
    {
      win32Style |= WS_POPUP;
    }
    else
    {
      if (a_settings.GetStyleBits() & style::TitleBar::s_glParamName)
      { win32Style |= WS_CAPTION | WS_MINIMIZEBOX; }
      if (a_settings.GetStyleBits() & style::Resize::s_glParamName)
      { win32Style |= WS_THICKFRAME | WS_MAXIMIZEBOX; }
      if (a_settings.GetStyleBits() & style::Close::s_glParamName)
      { win32Style |= WS_SYSMENU; }
    }

    // Adjust the window's width and height given the requested resolution
    const bool fullScreen = (a_settings.GetStyleBits() &
                             style::FullScreen::s_glParamName) != 0;
    if (fullScreen == false)
    {
      RECT rect = {0, 0,
                   core_utils::CastNumber<LONG, tl_size>(width),
                   core_utils::CastNumber<LONG, tl_size>(height)};
      AdjustWindowRect(&rect, win32Style, false);
      width = rect.right - rect.left;
      height = rect.bottom - rect.top;
    }

    // Create the actual window
    const size_type wTitleSize = 256; char32 wTitle[wTitleSize];
    tl_size retIndex =
      CharAsciiToWide(wTitle, a_settings.GetTitle().c_str(), wTitleSize );
    wTitle[retIndex] = L'\0';
    m_handle = CreateWindowW(g_className, wTitle, win32Style, (s32)left,
      (s32)top, (s32)width, (s32)height, TLOC_NULL, TLOC_NULL,
      GetModuleHandle(TLOC_NULL), this);

    if (fullScreen)
    { DoSwitchToFullscreen(a_mode); }

    if (m_handle == TLOC_NULL)
    {
      DWORD hresult = GetLastError();
      LPTSTR errorText = NULL;

      // Convoluted error string retrieval: http://stackoverflow.com/a/455533/368599
      FormatMessage(
        // use system message tables to retrieve error text
        FORMAT_MESSAGE_FROM_SYSTEM
        // allocate buffer on local heap for error text
        |FORMAT_MESSAGE_ALLOCATE_BUFFER
        // Important! will fail otherwise, since we're not
        // (and CANNOT) pass insertion parameters
        |FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,    // unused with FORMAT_MESSAGE_FROM_SYSTEM
        hresult,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&errorText,  // output
        0, // minimum size for output buffer
        NULL);   // arguments - see note

      TLOC_LOG_GFX_ERR() << "CreateWindowW failed: " << errorText;
      LocalFree(errorText);
    }

    DoCreateContext(a_mode, m_windowSettings);

    ++g_currWindowCount;

    // (From SFML): Actual size of window may be different after the
    // AdjustWindowRect() call.
    RECT actualRect;
    GetClientRect(m_handle, &actualRect);
    graphics_mode::Properties& gProps = m_graphicsMode.GetProperties();

    gProps.m_width  = actualRect.right - actualRect.left;
    gProps.m_height = actualRect.bottom - actualRect.top;

    GetClipCursor(&m_defaultMouseClip);
  }

  WINDOW_IMPL_WIN_TYPE::size_type
    WindowImpl<WINDOW_IMPL_WIN_PARAMS>::GetWidth() const
  {
    return GetGraphicsMode().GetProperties().m_width;
  }

  WINDOW_IMPL_WIN_TYPE::size_type
    WindowImpl<WINDOW_IMPL_WIN_PARAMS>::GetHeight() const
  {
    return GetGraphicsMode().GetProperties().m_height;
  }

  WINDOW_IMPL_WIN_TYPE::dim_type
    WindowImpl<WINDOW_IMPL_WIN_PARAMS>::
    GetDPI() const
  {
    HDC screen = GetDC(TLOC_NULL);
    tl_size dpiX = core_utils::CastNumber<tl_size>( GetDeviceCaps(screen, LOGPIXELSX) );
    tl_size dpiY = core_utils::CastNumber<tl_size>( GetDeviceCaps(screen, LOGPIXELSY) );

    return core_ds::MakeTuple(dpiX, dpiY);
  }

  WINDOW_IMPL_WIN_TYPE::size_type
    WindowImpl<WINDOW_IMPL_WIN_PARAMS>::GetMaxWidth() const
  {
    size_type maxWidth  = GetSystemMetrics(SM_CXSCREEN);
    return maxWidth;
  }

  WINDOW_IMPL_WIN_TYPE::size_type
    WindowImpl<WINDOW_IMPL_WIN_PARAMS>::GetMaxHeight() const
  {
    size_type maxHeight = GetSystemMetrics(SM_CYSCREEN);
    return maxHeight;
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::SetActive(bool a_active)
  {
    if (a_active)
    {
      if (m_deviceContext && m_OpenGLContext && (wglGetCurrentContext() != m_OpenGLContext))
      {
        priv::SetCurrentActiveWindow(m_parentWindow);
        wglMakeCurrent(m_deviceContext, m_OpenGLContext);
      }
      else
      { TLOC_LOG_GFX_WARN() << "Window already active"; }
    }
    else
    {
      if (wglGetCurrentContext() == m_OpenGLContext)
      {
        priv::SetNonActiveWindow(m_parentWindow);
        wglMakeCurrent(TLOC_NULL, TLOC_NULL);
      }
      else
      { TLOC_LOG_GFX_WARN() << "Window already inactive"; }
    }
  }

  bool WindowImpl<WINDOW_IMPL_WIN_PARAMS>::HasValidContext() const
  {
    return m_OpenGLContext != TLOC_NULL;
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::ProcessEvents() const
  {
    // SFML: Update the window only if we own it
    if (!m_callbackPtr)
    {
      MSG msg;
      while (PeekMessage(&msg, TLOC_NULL, 0, 0, PM_REMOVE))
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }
  }

  WINDOW_IMPL_WIN_TYPE::window_handle_type
    WindowImpl<WINDOW_IMPL_WIN_PARAMS>::GetWindowHandle() const
  {
    return m_handle;
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::SetVerticalSync(bool a_enable)
  {
    // Not using GLFW because it may not be initialized yet
    PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT =
      reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>
      (wglGetProcAddress("wglSwapIntervalEXT"));

    if (wglSwapIntervalEXT) { wglSwapIntervalEXT(a_enable ? 1 : 0); }
    else
    {
      TLOC_LOG_GFX_WARN()
        << "Could not enable vertical sync (unsupported procedure)";
    }
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::SetMouseVisibility(bool a_enable)
  {
    if (a_enable) { m_cursor = LoadCursor(TLOC_NULL, IDC_ARROW); }
    else
    {
      m_cursor = TLOC_NULL;
    }

    SetCursor(m_cursor);
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::ConfineMouseToWindow(bool a_confine)
  {
    if (a_confine) 
    { 
      POINT point;
      point.x = 0; point.y = 0;
      ClientToScreen(GetWindowHandle(), &point);

      RECT rcClip;
      GetClientRect(GetWindowHandle(), &rcClip);

      rcClip.top += point.y;
      rcClip.bottom += point.y;

      rcClip.left += point.x;
      rcClip.right += point.x;

      ClipCursor(&rcClip);
    }
    else
    {
      ClipCursor(&m_defaultMouseClip);
    }
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::SetPosition(s32 a_x, s32 a_y)
  {
    SetWindowPos(m_handle, TLOC_NULL, a_x, a_y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::SetSize
    (size_type a_width, size_type a_height)
  {
    const LONG width  = (LONG)a_width;
    const LONG height = (LONG)a_height;

    // SFML: We have to adjust according to the total size of the window which
    // includes the title bar, borders etc.
    RECT rect = {0, 0, width, height};
    AdjustWindowRect(&rect, GetWindowLong(m_handle, GWL_STYLE), false);

    a_width  = rect.right - rect.left;
    a_height = rect.bottom - rect.top;

    // the events are fired as soon as SetWindowPos is TRUE. So we set the
    // width and height of m_graphicsMode and if FALSE, we reset it.
    graphics_mode::size_type oldWidth = m_graphicsMode.GetProperties().m_width;
    graphics_mode::size_type oldHeight = m_graphicsMode.GetProperties().m_height;

    m_graphicsMode.GetProperties().m_width = width;
    m_graphicsMode.GetProperties().m_height = height;

    if (SetWindowPos(m_handle, TLOC_NULL, 0, 0,
                     width, height, SWP_NOMOVE | SWP_NOZORDER) == FALSE)
    {
      m_graphicsMode.GetProperties().m_width = oldWidth;
      m_graphicsMode.GetProperties().m_height = oldHeight;
    }
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::SetVisibility(bool a_visible)
  {
    ShowWindow(m_handle, a_visible ? SW_SHOW : SW_HIDE);
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::SetTitle(BufferArg a_title)
  {
    SetWindowText(m_handle, a_title);
  }

  bool WindowImpl<WINDOW_IMPL_WIN_PARAMS>::IsCreated() const
  {
    return IsWindow(m_handle) == 1;
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::SwapBuffers()
  {
    VERIFY_DEVICE_CONTEXT();
    VERIFY_OPENGL_CONTEXT();

    // We have a name clash, make sure we are looking in the global scope
    ::SwapBuffers(m_deviceContext);
  }

  WINDOW_IMPL_WIN_TYPE::fbo_sptr
    WindowImpl<WINDOW_IMPL_WIN_PARAMS>::
    DoGetFramebuffer()
  {
    return fbo_sptr(new WindowsFramebufferObject());
  }

  //------------------------------------------------------------------------
  // Private helper functions

  LRESULT CALLBACK WindowImpl<WINDOW_IMPL_WIN_PARAMS>::
    DoWindowProcedure(HWND a_handle, UINT a_message, WPARAM a_wparam,
                      LPARAM a_lParam)
  {
    // I am not entirely sure why SFML chooses this technique to store the
    // user pointer (that is, wait for the create event and then use a 'trick'
    // to get this class's instance. Should test it later.
    // TODO: Register the user variable in Create()
    if (a_message == WM_CREATE)
    {
      // Convert LPARAM to a meanigul structure i.e. CREATESTRUCT and then
      // cast the lpCreateParams member to a long which a pointer to
      // WindowImpl<> (this is set by CreateWindowEx function)
      long thisPtr = reinterpret_cast<long>(reinterpret_cast<CREATESTRUCT*>
        (a_lParam)->lpCreateParams);

      // We set HWND's (a_handle) user data attribute to thisPtr, which is
      // WindowImpl pointer (this is then queried later by GetWindowLongPtr)
      SetWindowLongPtr(a_handle, GWLP_USERDATA, thisPtr);
    }

    this_type* win = reinterpret_cast<this_type*>(GetWindowLongPtr(a_handle,
                                                  GWLP_USERDATA));
    if (win)
    {
      win->DoProcessEvent(a_message, a_wparam, a_lParam);
      if (win->m_callbackPtr)
      {
        return CallWindowProc(reinterpret_cast<WNDPROC>(win->m_callbackPtr),
          a_handle, a_message, a_wparam, a_lParam);
      }
    }

    if (a_message == WM_CLOSE) { return 0; }

    return DefWindowProcW(a_handle, a_message, a_wparam, a_lParam);
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::
    DoProcessEvent(UINT a_message, WPARAM a_wparam, LPARAM a_lparam)
  {
    if (m_handle == TLOC_NULL) { return; }

    auto activeWindowHandle = GetActiveWindow();

    // To ensure the mouse doesn't disappear or remains confined, the following 
    // is necessary to check whether this is the active window because 
    // DoProcessEvent is sometimes called when another window is active. 
    if (activeWindowHandle != m_handle)
    {
      SetMouseVisibility(true);
      ConfineMouseToWindow(false);
    }
    else
    {
      SetMouseVisibility(m_parentWindow->IsMouseVisible());
      ConfineMouseToWindow(m_parentWindow->IsMouseConfined());
    }

    switch (a_message)
    {
    case WM_DESTROY:
      {
        SetMouseVisibility(true);
        ConfineMouseToWindow(false);
        m_parentWindow->SendEvent(WindowEvent
          (WindowEvent::destroy, GetWidth(), GetHeight()));
        DoCleanup();
        break;
      }
    case WM_CLOSE:
      {
        SetMouseVisibility(true);
        ConfineMouseToWindow(false);
        m_parentWindow->SendEvent(WindowEvent
          (WindowEvent::close, GetWidth(), GetHeight()));
        break;
      }
    case WM_SIZE:
      {
        m_parentWindow->SendEvent(WindowEvent
          (WindowEvent::resized, GetWidth(), GetHeight()));
        break;
      }
    case WM_SETFOCUS:
      {
        m_parentWindow->SendEvent(WindowEvent
          (WindowEvent::gained_focus, GetWidth(), GetHeight()));
        break;
      }
    case WM_KILLFOCUS:
      {
        SetMouseVisibility(true);
        ConfineMouseToWindow(false);
        m_parentWindow->SendEvent(WindowEvent
          (WindowEvent::lost_focus, GetWidth(), GetHeight()));
        break;
      }
    case WM_MOUSEMOVE:
      { break; }
    }

    TLOC_UNUSED_2(a_wparam, a_lparam);
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::DoRegisterWindowClass()
  {
    // TODO: Register class for non-unicode OS (older windows)

    WNDCLASSW WindowClass;
    WindowClass.style         = 0;
    WindowClass.lpfnWndProc   = &this_type::DoWindowProcedure;
    WindowClass.cbClsExtra    = 0;
    WindowClass.cbWndExtra    = 0;
    WindowClass.hInstance     = GetModuleHandle(TLOC_NULL);
    WindowClass.hIcon         = TLOC_NULL;
    WindowClass.hCursor       = 0;
    WindowClass.hbrBackground = 0;
    WindowClass.lpszMenuName  = TLOC_NULL;
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
    if (a_settings.GetAntiAlias() > 0)
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
          WGL_SAMPLE_BUFFERS_ARB, (a_settings.GetAntiAlias() ? GL_TRUE : GL_FALSE),
          WGL_SAMPLES_ARB, (a_settings.GetAntiAlias()),
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
          if (a_settings.GetAntiAlias() > 2)
          {
            TLOC_LOG_GFX_WARN() << "Failed to find a format that supports the "
              << "required AA, trying lower levels";

            a_settings.SetAntiAlias(2);
            pixAttribs[11] = a_settings.GetAntiAlias();
            isValid = wglChoosePixelFormatARB(m_deviceContext, pixAttribs,
              attributeList, maxFormatsToReturn, formats, &numFormats) != 0;
          }

          if (isValid == false || numFormats == 0)
          {
            TLOC_LOG_GFX_WARN() << "Cannot find pixel format supporting any AA"
              << ", disabling AA";
            a_settings.SetAntiAlias(0);
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
        TLOC_LOG_GFX_WARN() << "AA not supported and will be disabled";
        a_settings.SetAntiAlias(0);
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
      pixelDesc.cDepthBits = static_cast<BYTE>(a_settings.GetDepthBits());
      pixelDesc.cStencilBits = static_cast<BYTE>(a_settings.GetStencilBits());
      pixelDesc.cAlphaBits = a_gMode.GetProperties().m_bitsPerPixel == 32 ? 8 : 0;

      bestFormat = ChoosePixelFormat(m_deviceContext, &pixelDesc);
      TLOC_ASSERT(bestFormat, "Failed to find a suitable pixel format for the "
        "device context -- cannot create OpenGL context");
    }

    PIXELFORMATDESCRIPTOR pixFormat;
    const size_type pixFormatSize = sizeof(pixFormat);
    pixFormat.nSize    = pixFormatSize;
    pixFormat.nVersion = 1;

    DescribePixelFormat(m_deviceContext, bestFormat, pixFormatSize, &pixFormat);

    a_settings.SetDepthBits(pixFormat.cDepthBits);
    a_settings.SetStencilBits(pixFormat.cStencilBits);

    bool setPixelFormatResult =
      SetPixelFormat(m_deviceContext, bestFormat, &pixFormat) != 0;
    TLOC_UNUSED(setPixelFormatResult);
    TLOC_ASSERT(setPixelFormatResult,
      "SetPixelFormat() failed -- cannot create OpenGL context");

    m_OpenGLContext = wglCreateContext(m_deviceContext);
    TLOC_ASSERT(m_OpenGLContext, "Failed to create OpenGL context");

    m_parentWindow->SetActive(true);

    if (a_settings.GetAntiAlias() > 0)
    {
      glEnable(GL_MULTISAMPLE_ARB);
    }
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::
    DoSwitchToFullscreen(const graphics_mode& a_gMode)
  {
    const graphics_mode::Properties& props = a_gMode.GetProperties();

    DEVMODE devMode;
    devMode.dmSize       = sizeof(devMode);
    devMode.dmPelsWidth  = core_utils::CastNumber<DWORD>(props.m_width);
    devMode.dmPelsHeight = core_utils::CastNumber<DWORD>(props.m_height);
    devMode.dmBitsPerPel = core_utils::CastNumber<DWORD>(props.m_bitsPerPixel);
    devMode.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

    s32 result = ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
    if (result != DISP_CHANGE_SUCCESSFUL)
    {
      TLOC_LOG_GFX_WARN() << "Could not change display to full-screen";
      return;
    }

    // SFML: Make the window flags compatible with fullscreen mode
    SetWindowLong(m_handle, GWL_STYLE, WS_POPUP | WS_CLIPCHILDREN |
                            WS_CLIPSIBLINGS);
    SetWindowLong(m_handle, GWL_EXSTYLE, WS_EX_APPWINDOW);

    // SFML: Resize the window so that it fits the entire screen
    SetWindowPos( m_handle, HWND_TOP, 0, 0,
                  (int)props.m_width, (int)props.m_height,
                  SWP_FRAMECHANGED );
    ShowWindow(m_handle, SW_SHOW);

    g_currFullScreenWindow = this;
  }

  void WindowImpl<WINDOW_IMPL_WIN_PARAMS>::DoCleanup()
  {
    // SFML: Restore the previous video mode (in case we are fullscreen)
    if (g_currFullScreenWindow == this)
    {
      ChangeDisplaySettings(TLOC_NULL, 0);
      g_currFullScreenWindow = TLOC_NULL;
    }

    ConfineMouseToWindow(false);
    SetMouseVisibility(true);

    // SFML: Destroy the OpenGL context
    if (m_OpenGLContext)
    {
      if (m_parentWindow->IsActive() == false)
      { m_parentWindow->SetActive(true); }

      wglDeleteContext(m_OpenGLContext);
      m_OpenGLContext = TLOC_NULL;

      m_parentWindow->SetActive(false);
    }

    if (m_deviceContext)
    {
      ReleaseDC(m_handle, m_deviceContext);
      m_deviceContext = TLOC_NULL;
    }
  }

};};};};
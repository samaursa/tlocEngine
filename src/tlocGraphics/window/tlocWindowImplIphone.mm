#include "tlocWindowImplIphone.h"

#import <UIKit/UIKit.h>

namespace tloc { namespace graphics { namespace win { namespace priv {

#define WINDOW_IMPL_IPHONE_PARAMS Window_T<>
#define WINDOW_IMPL_IPHONE_TYPE WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>

  //////////////////////////////////////////////////////////////////////////
  // Global variables
  
  WINDOW_IMPL_IPHONE_TYPE::size_type g_currWindowCount = 0;

  //////////////////////////////////////////////////////////////////////////
  // WindowImpl<>

  WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::WindowImpl(parent_window_type* a_parent)
    : WindowImplBase(a_parent)
    , m_handle(nil)
    , m_viewController(nil)
    , m_view(nil)
  {
    TLOC_ASSERT_NOT_NULL(a_parent);
  }

  WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::~WindowImpl()
  {
    --g_currWindowCount;
    priv::SetNonActiveWindow(m_parentWindow);
    
    [m_view release];
    [m_viewController release];
    [m_handle release];
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::Create()
  {
    // This function was meant to create a dummy context, in order to create
    // a true context. This is not needed on iOS.
    TLOC_STATIC_ASSERT(false, "Function not implemented and needed on iOS");
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::
    Create(window_handle_type a_ptr, const WindowSettings& a_settings)
  {
    TLOC_UNUSED_2(a_ptr, a_settings);
    TLOC_ASSERT_WIP();
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::
    Create(const graphics_mode& a_mode, const WindowSettings& a_settings,
           const window_style_type& a_style)
  {
    // TODO: Since we save the settings, make it able to switch between
    // full screen and the user requested size
    m_graphicsMode = a_mode;
    m_windowSettings = a_settings;
    
    TLOC_ASSERT(g_currWindowCount < 1, 
                "TLOC currently only supports 1 window on an iOS device");
    
    // TODO: Change this to the actual screen that we want our window to be on
    // for now only supports main device
    UIScreen* currentScreen = [UIScreen mainScreen];
    
    if (a_style& WindowSettings::style_titlebar) 
    {
      [UIApplication sharedApplication].statusBarHidden = NO;
      m_handle = [[UIWindow alloc] initWithFrame:[currentScreen applicationFrame]];
    }
    else 
    {
      [UIApplication sharedApplication].statusBarHidden = YES;
      m_handle = [[UIWindow alloc] initWithFrame:[currentScreen bounds]];
    }
    
    graphics_mode::Properties modeProps = m_graphicsMode.GetProperties();
    
    CGRect viewFrame;
    if (a_style& WindowSettings::style_fullscreen) 
    {
      viewFrame = m_handle.bounds;
    }
    else 
    {
      size_type width = modeProps.m_width;
      size_type height = modeProps.m_height;
      size_type left = (m_handle.bounds.size.width - width) / 2;
      size_type top = (m_handle.bounds.size.height - height) / 2;
      
      viewFrame = CGRectMake(left, top, width, height);
    }
    
    m_view = [[OpenGLView alloc] initWithFrame:viewFrame retainBacking:NO 
                                  bitsPerPixel:modeProps.m_bitsPerPixel 
                                  bitsPerDepth:a_settings.m_depthBits 
                                bitsPerStencil:a_settings.m_stencilBits];
    
    m_viewController = [[OpenGLViewController alloc] initWithWindow:this];
    
    TLOC_ASSERT(m_view && m_viewController && m_handle, "CreateWindow failed.");
    
    [m_viewController setView:m_view];

    [m_handle setRootViewController:m_viewController];
    [m_handle addSubview:m_view];
    [m_handle makeKeyAndVisible];
    
    ++g_currWindowCount;
    
    priv::SetCurrentActiveWindow(m_parentWindow);
  }

  WINDOW_IMPL_IPHONE_TYPE::size_type
    WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::GetWidth() const
  {
    return (size_type)m_view.bounds.size.width;
  }

  WINDOW_IMPL_IPHONE_TYPE::size_type
    WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::GetHeight() const
  {
    return (size_type)m_view.bounds.size.height;
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::SetActive(bool a_active)
  {
    if (a_active) 
    {
      if ([m_view context] && [EAGLContext currentContext] != [m_view context]) 
      {
        [m_view SetAsCurrentContext];
      }
      else 
      {
        // LOG: Window already active
      }
    }
    else 
    {
      if ([EAGLContext currentContext] == [m_view context]) 
      {
        [EAGLContext setCurrentContext:nil];
      }
      else 
      {
        // LOG: Window is already inactive
      }
    }
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::ProcessEvents()
  {
    while (CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0, TRUE) == 
           kCFRunLoopRunHandledSource);
  }
  
  WINDOW_IMPL_IPHONE_TYPE::window_handle_type 
    WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::GetWindowHandle() const
  {
    return m_handle;
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::SetVerticalSync(bool a_enable)
  {
    // There does not appear to be a way to change vertical sync on the iOS
    TLOC_STATIC_ASSERT(false, "Cannot currently change vertical sync on iOS");
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::SetMouseVisibility(bool a_enable)
  {
    // There is no concept of a mouse on the iOS
    TLOC_STATIC_ASSERT(false, "Function not implemented and needed on iOS");
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::SetPosition(s32 a_x, s32 a_y)
  {
    m_view.frame = CGRectOffset(m_view.frame, (CGFloat)a_x, (CGFloat)a_y);
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::SetSize
    (size_type a_width, size_type a_height)
  {
    m_view.frame = CGRectMake(m_view.frame.origin.x, m_view.frame.origin.y, 
                              (CGFloat)a_width, (CGFloat)a_height);
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::SetVisibility(bool a_visible)
  {
    [m_view setHidden:!a_visible];
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::SetTitle(const char* a_title)
  {
    NSString *title = [[NSString alloc] initWithUTF8String:a_title];
    [m_view setTitle:title];
  }

  bool WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::IsCreated() const
  {
    return m_handle && m_view && m_viewController;
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::SwapBuffers()
  {
    [m_view SwapBuffers];
  }
  
  //------------------------------------------------------------------------
  // Implementation specific functions
  
  WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::parent_window_type*
    WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::GetParentWindowHandle()
  {
    return m_parentWindow;
  }
  
  WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::window_handle_type 
    WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::GetWindowHandle()
  {
    return m_handle;
  }
  
  WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::view_handle_type
    WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::GetOpenGLViewHandle()
  {
    return m_view;
  }

};};};};
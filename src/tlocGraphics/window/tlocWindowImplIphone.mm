#include "tlocWindowImplIphone.h"

#include <tlocCore/types/tlocAny.inl.h>

#import <UIKit/UIKit.h>
#import <tlocGraphics/window/tlocOpenGLViewIphone.h>
#import <tlocGraphics/window/tlocOpenGLViewControllerIphone.h>

namespace tloc { namespace graphics { namespace win { namespace priv {

#define WINDOW_IMPL_IPHONE_PARAMS Window_T<>
#define WINDOW_IMPL_IPHONE_TYPE WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>

  //////////////////////////////////////////////////////////////////////////
  // Helper functions

  namespace {

    OpenGLView* GetOpenGLView(const core_t::Any& a_any)
    {
      return a_any.Cast<OpenGLView*>();
    }
    
    UIWindow* GetUIWindow(const core_t::Any& a_any)
    {
      return a_any.Cast<UIWindow*>();
    }
    
    OpenGLViewController* GetViewController(const core_t::Any& a_any)
    {
      return a_any.Cast<OpenGLViewController*>();
    }

  }

  //////////////////////////////////////////////////////////////////////////
  // Global variables
  
  WINDOW_IMPL_IPHONE_TYPE::size_type g_currWindowCount = 0;

  //////////////////////////////////////////////////////////////////////////
  // WindowImpl<>

  WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::WindowImpl(parent_window_type* a_parent)
    : WindowImplBase(a_parent)
    , m_viewController(nil)
    , m_view(nil)
  {
    m_handle.Assign(nil);
    TLOC_ASSERT_NOT_NULL(a_parent);
  }

  WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::~WindowImpl()
  {
    --g_currWindowCount;
    priv::SetNonActiveWindow(m_parentWindow);
    
    [GetOpenGLView(m_view) release];
    [GetViewController(m_viewController) release];
    [GetUIWindow(m_handle) release];
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::Create()
  {
    // This function was meant to create a dummy context, in order to create
    // a true context. This is not needed on iOS.
    TLOC_ASSERT(false, "Function not implemented and needed on iOS" );
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::
    Create(window_handle_type a_ptr, const WindowSettings& a_settings)
  {
    TLOC_UNUSED_2(a_ptr, a_settings);
    TLOC_ASSERT_WIP();
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::
    Create(const graphics_mode& a_mode, const WindowSettings& a_settings)
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

    [UIApplication sharedApplication].statusBarHidden =
      (a_settings.GetStyleBits() &
       p_window_settings::style::TitleBar::s_glParamName) == false;

    // The window must take the screens bounds. This is since our view
    // automatically adjusts its size even when there is a title bar present.
    m_handle.Assign<UIWindow*>([[UIWindow alloc]
                            initWithFrame:[currentScreen bounds]]);

    CGFloat screenScale = [currentScreen scale];

    graphics_mode::Properties modeProps = m_graphicsMode.GetProperties();
    
    CGRect viewFrame = m_handle.Cast<UIWindow*>().bounds;

    m_view = [[OpenGLView alloc] initWithFrame:viewFrame
                                   screenScale:screenScale
                                 retainBacking:NO
                                  bitsPerPixel:modeProps.m_bitsPerPixel 
                                  bitsPerDepth:a_settings.GetDepthBits() 
                                bitsPerStencil:a_settings.GetStencilBits()];
    
    m_viewController = [[OpenGLViewController alloc] initWithWindow:this];
    
    TLOC_ASSERT(GetOpenGLView(m_view) &&
                GetViewController(m_viewController) &&
                GetUIWindow(m_handle), "CreateWindow failed.");
    
    [GetViewController(m_viewController) setView:GetOpenGLView(m_view)];

    [GetUIWindow(m_handle)
     setRootViewController:GetViewController(m_viewController)];
    [GetUIWindow(m_handle) makeKeyAndVisible];
    
    ++g_currWindowCount;
    
    priv::SetCurrentActiveWindow(m_parentWindow);
  }

  WINDOW_IMPL_IPHONE_TYPE::size_type
    WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::GetWidth() const
  {
    return (size_type)m_view.Cast<OpenGLView*>().bounds.size.width;
  }

  WINDOW_IMPL_IPHONE_TYPE::size_type
    WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::GetHeight() const
  {
    return (size_type)m_view.Cast<OpenGLView*>().bounds.size.height;
  }
  
  WINDOW_IMPL_IPHONE_TYPE::size_type
    WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::GetMaxWidth() const
  {
    CGFloat width = [UIScreen mainScreen].bounds.size.width;
    return static_cast<size_type>(width);
  }

  WINDOW_IMPL_IPHONE_TYPE::size_type
    WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::GetMaxHeight() const
  {
    CGFloat height = [UIScreen mainScreen].bounds.size.height;
    return static_cast<size_type>(height);
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::SetActive(bool a_active)
  {
    OpenGLView* view = GetOpenGLView(m_view);

    if (a_active) 
    {
      if ([view context] && [EAGLContext currentContext] != [view context]) 
      {
        [view SetAsCurrentContext];
      }
      else 
      {
        // LOG: Window already active
      }
    }
    else 
    {
      if ([EAGLContext currentContext] == [GetOpenGLView(m_view) context]) 
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

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::SetVerticalSync(bool)
  {
    // LOG: iOS does not have vertical sync
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::SetMouseVisibility(bool)
  {
    // LOG: SetMouseVisibility() does nothing on iOS
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::SetPosition(s32 a_x, s32 a_y)
  {
    OpenGLView* view = GetOpenGLView(m_view);
    view.frame = CGRectOffset(view.frame, (CGFloat)a_x, (CGFloat)a_y);
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::SetSize
    (size_type a_width, size_type a_height)
  {
    OpenGLView* view = GetOpenGLView(m_view);
    view.frame = CGRectMake(view.frame.origin.x, view.frame.origin.y, 
                              (CGFloat)a_width, (CGFloat)a_height);
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::SetVisibility(bool a_visible)
  {
    [GetOpenGLView(m_view) setHidden:!a_visible];
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::SetTitle(const char*)
  {
    // LOG: iOS platform has no title
  }

  bool WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::IsCreated() const
  {
    UIWindow* uiWin = GetUIWindow(m_handle);
    OpenGLView* view = GetOpenGLView(m_view);
    OpenGLViewController* viewController = GetViewController(m_viewController);

    return uiWin && view && viewController;
  }

  void WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::SwapBuffers()
  {
    [GetOpenGLView(m_view) SwapBuffers];
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

  WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::fbo_sptr
    WindowImpl<WINDOW_IMPL_IPHONE_PARAMS>::DoGetFramebuffer()
  {
    return [GetOpenGLView(m_view) GetFramebuffer];
  }

};};};};

#ifndef TLOC_WINDOW_HANDLE_H
#define TLOC_WINDOW_HANDLE_H

#include <tlocCore/platform/tlocPlatform.h>

#if defined(TLOC_OS_WIN)
# define WIN32_LEAN_AND_MEAN
# include <Windows.h>
#elif defined(TLOC_OS_IPHONE)
# import <UIKit/UIKit.h>
#endif

namespace tloc { namespace graphics {

  template <typename T_Platform> struct WindowHandle;
  
#if defined (TLOC_OS_WIN)
  
  template<>
  struct WindowHandle<core::Platform_win>
  {
    typedef HWND         type;
  };
  
  template<>
  struct WindowHandle<core::Platform_win32>
    : public WindowHandle<core::Platform_win>
  {
    typedef WindowHandle<core::Platform_win>::type type;
  };
  
  template<>
  struct WindowHandle<core::Platform_win64>
    : public WindowHandle<core::Platform_win>
  {
    typedef WindowHandle<core::Platform_win>::type type;
  };
  
#elif defined (TLOC_OS_MAC)

  template<>
  struct WindowHandle<core::Platform_mac>
  {
    typedef void*         type;
  };
 
#elif defined (TLOC_OS_IPHONE)
  
  template<>
  struct WindowHandle<core::Platform_iphone>
  {
    typedef UIWindow*     type;
  };
  
#elif defined (TLOC_OS_LINUX)

  template<>
  struct WindowHandle<core::Platform_linux>
  {
    typedef tl_size       type;
  };
  
#endif

};};

#endif

#ifndef TLOC_WINDOW_HANDLE_H
#define TLOC_WINDOW_HANDLE_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/platform/tlocPlatform.h>

#if defined(TLOC_OS_WIN)
# define WIN32_LEAN_AND_MEAN
# include <Windows.h>
#elif defined(TLOC_OS_IPHONE)
# import <UIKit/UIKit.h>
#endif

namespace tloc { namespace graphics { namespace win {

  template <typename T_Platform> struct WindowHandle;

#if defined (TLOC_OS_WIN)

  template<>
  struct WindowHandle<core::Platform_win>
  {
    typedef HWND         type;
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

};};};

#endif

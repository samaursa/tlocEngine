#ifndef TLOC_WINDOW_HANDLE_H
#define TLOC_WINDOW_HANDLE_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/platform/tlocPlatform.h>

#include <tlocCore/types/tlocAny.h>

#if defined(TLOC_OS_WIN)
# define WIN32_LEAN_AND_MEAN
# include <Windows.h>
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

  // Note: We are using tlocAny to replace Objective-C types in this case
  // since any source file (cpp) that included this header would have to be
  // treated as an Objective-C++ file.
  template<>
  struct WindowHandle<core::Platform_iphone>
  {
    typedef core_t::Any /* (UIWindow*) */   type;
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

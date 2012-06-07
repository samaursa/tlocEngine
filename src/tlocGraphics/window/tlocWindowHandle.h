#ifndef TLOC_WINDOW_HANDLE_H
#define TLOC_WINDOW_HANDLE_H

#include <tlocCore/platform/tlocPlatform.h>

namespace tloc { namespace graphics {

  template <typename T_Platform> struct WindowHandle;

  template<>
  struct WindowHandle<core::Platform_win>
  {
    typedef void*         type;
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

  template<>
  struct WindowHandle<core::Platform_osx>
  {
    typedef void*         type;
  };

  template<>
  struct WindowHandle<core::Platform_linux>
  {
    typedef tl_size       type;
  };

};};

#endif

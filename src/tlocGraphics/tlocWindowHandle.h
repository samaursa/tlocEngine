#ifndef TLOC_WINDOW_H
#define TLOC_WINDOW_H

#include "tlocCore/tlocPlatform.h"

namespace tloc { namespace graphics {

  template <typename T_Platform> struct WindowHandle;

  template<>
  struct WindowHandle<core::Platform_win>
  {
    DECL_TYPEDEF_HELPER(WindowHandle);

    typedef void*         type;
  };

  template<>
  struct WindowHandle<core::Platform_win32>
    : public WindowHandle<core::Platform_win>
  {
    DECL_TYPEDEF_HELPER(WindowHandle);

    typedef typename WindowHandle<core::Platform_win>::type type;
  };

  template<>
  struct WindowHandle<core::Platform_win64>
    : public WindowHandle<core::Platform_win>
  {
    DECL_TYPEDEF_HELPER(WindowHandle);

    typedef typename WindowHandle<core::Platform_win>::type type;
  };

  template<>
  struct WindowHandle<core::Platform_osx>
  {
    DECL_TYPEDEF_HELPER(WindowHandle);

    typedef void*         type;
  };

  template<>
  struct WindowHandle<core::Platform_linux>
  {
    DECL_TYPEDEF_HELPER(WindowHandle);

    typedef tl_size       type;
  };

};};

#endif

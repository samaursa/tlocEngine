#ifndef TLOC_PLATFORM_H
#define TLOC_PLATFORM_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/platform/tlocPlatformDefines.h>
#include <tlocCore/types/tlocTypes.h>


namespace tloc { namespace core {

  struct Platform_win {};
  struct Platform_win32 : public Platform_win {};
  struct Platform_win64 : public Platform_win {};
  struct Platform_xbox : public Platform_win32 {};

  struct Platform_mac {};
  struct Platform_iphone : public Platform_mac {};

  struct Platform_linux {};

  struct Platform_ps3 {};

#if defined(TLOC_WIN32) || defined(TLOC_WIN64)
  template <typename T_Platform = Platform_win>
#elif defined(TLOC_OS_MAC)
  template <typename T_Platform = Platform_mac>
#elif defined(TLOC_OS_IPHONE)
  template <typename T_Platform = Platform_iphone>
#elif defined(TLOC_OS_LINUX)
  template <typename T_Platform = Platform_linux>
#endif
  class PlatformInfo
  {
  public:
    typedef T_Platform platform_type;

    typedef tl_size platform_index;
    enum {windows = 0, win32, win64, xbox, osx, osx_iphone, linux,
          ps3, total_platforms};

    // Returns the platform name (descriptive)
    static const char*   GetPlatformName();

    // Returns the descriptive platform name given the platform index
    static const char*   GetPlatformName(platform_index aIndex);

    // Returns the current platform type
    static platform_type GetPlatformType();

  private:
    static const char*  DoGetPlatformName(Platform_win);
    static const char*  DoGetPlatformName(Platform_win32);
    static const char*  DoGetPlatformName(Platform_win64);
    static const char*  DoGetPlatformName(Platform_xbox);
    static const char*  DoGetPlatformName(Platform_mac);
    static const char*  DoGetPlatformName(Platform_iphone);
    static const char*  DoGetPlatformName(Platform_linux);
    static const char*  DoGetPlatformName(Platform_ps3);

    static const char* platforms[total_platforms];
  };

};};

#endif

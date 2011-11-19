#ifndef TLOC_PLATFORM_H
#define TLOC_PLATFORM_H

#include "tlocBase.h"
#include "tlocTypes.h"

//////////////////////////////////////////////////////////////////////////
// Macros

#if defined(WIN32) || defined(_WIN32)
#define TLOC_WIN32
#elif defined(_WIN64)
#define TLOC_WIN64
#elif defined(TARGET_OS_MAC)
#define TLOC_OS_MAC
#elif defined(__linux__)
#define TLOC_LINUX
#endif

namespace tloc { namespace core {

  struct platform_win32 {};
  struct platform_win64 {};
  struct platform_xbox : public platform_win32 {};
  struct platform_osx {};
  struct platform_osx_iphone : public platform_osx {};
  struct platform_linux {};
  struct platform_ps3 {};

#if defined(TLOC_WIN32)
  template <typename T_Platform = platform_win32>
#elif defined(TLOC_WIN64)
  template <typename T_Platform = platform_win64>
#elif defined(TLOC_OS_MAC)
  template <typename T_Platform = platform_osx>
#elif defined(TLOC_LINUX)
  template <typename T_Platform = platform_linux>
#endif
  class PlatformInfo
  {
  public:
    typedef T_Platform platform_type;

    typedef u32 platform_index;
    enum {win32 = 0, win64, xbox, osx, osx_iphone, linux, ps3, total_platforms};

    // Returns the platform name (descriptive)
    static const char*   GetPlatformName();

    // Returns the descriptive platform name given the platform index
    static const char*   GetPlatformName(platform_index aIndex);

    // Returns the current platform type
    static platform_type GetPlatformType();

  private:
    static const char*  DoGetPlatformName(platform_win32);
    static const char*  DoGetPlatformName(platform_win64);
    static const char*  DoGetPlatformName(platform_xbox);
    static const char*  DoGetPlatformName(platform_osx);
    static const char*  DoGetPlatformName(platform_osx_iphone);
    static const char*  DoGetPlatformName(platform_linux);
    static const char*  DoGetPlatformName(platform_ps3);

    static const char* platforms[total_platforms];
  };

};};

#endif
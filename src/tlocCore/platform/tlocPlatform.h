#ifndef TLOC_PLATFORM_H
#define TLOC_PLATFORM_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/platform/tlocPlatformDefines.h>
#include <tlocCore/types/tlocTypes.h>


namespace tloc { namespace core { namespace platform {

  // ///////////////////////////////////////////////////////////////////////
  // All platform types

  namespace p_platform_info {

    struct win {};
    struct win32  : public win {};
    struct win64  : public win {};
    struct xbox   : public win32 {};

    struct mac {};
    struct iphone : public mac {};

    struct linux {};

    struct ps3 {};

  };

  // ///////////////////////////////////////////////////////////////////////
  // PlatformInfo

#if defined(TLOC_WIN32) || defined(TLOC_WIN64)
  template <typename T_Platform = p_platform_info::win>
#elif defined(TLOC_OS_MAC)
  template <typename T_Platform = p_platform_info::mac>
#elif defined(TLOC_OS_IPHONE)
  template <typename T_Platform = p_platform_info::iphone>
#elif defined(TLOC_OS_LINUX)
  template <typename T_Platform = p_platform_info::linux>
#endif
  class PlatformInfo_T
  {
  public:
    enum {windows = 0, win32, win64, xbox, osx, osx_iphone, linux,
          ps3, total_platforms};

  public:
    typedef T_Platform                        platform_type;
    typedef PlatformInfo_T<platform_type>     this_type;
    typedef tl_size                           platform_index;

  public:
    // Returns the platform name (descriptive)
    static const char*   GetPlatformName();

    // Returns the descriptive platform name given the platform index
    static const char*   GetPlatformName(platform_index aIndex);

    // Returns the current platform type
    static platform_type GetPlatformType();

  private:
    static const char*  DoGetPlatformName(p_platform_info::win);
    static const char*  DoGetPlatformName(p_platform_info::win32);
    static const char*  DoGetPlatformName(p_platform_info::win64);
    static const char*  DoGetPlatformName(p_platform_info::xbox);
    static const char*  DoGetPlatformName(p_platform_info::mac);
    static const char*  DoGetPlatformName(p_platform_info::iphone);
    static const char*  DoGetPlatformName(p_platform_info::linux);
    static const char*  DoGetPlatformName(p_platform_info::ps3);

    static const char*  platforms[total_platforms];
  };

  // -----------------------------------------------------------------------
  // typedefs

  typedef PlatformInfo_T<>                    PlatformInfo;

};};};

#endif

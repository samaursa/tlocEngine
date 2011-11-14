#include "tlocPlatform.h"

namespace tloc { namespace core {

  PlatformInfo<> g_platformInfo;

  //////////////////////////////////////////////////////////////////////////
  // PlatformInfo

  template <typename T_Platform>
  const char* PlatformInfo<T_Platform>::
    platforms[PlatformInfo<T_Platform>::total_platforms] =
  {
    "Windows 32-bit",
    "Windows 64-bit",
    "XBOX",
    "Apple OSX",
    "Apple OSX iPhone",
    "Linux",
    "Playstation 3",
  };

  template <typename T_Platform>
  const char* PlatformInfo<T_Platform>::GetPlatformName()
  {
    return GetPlatformName(platform_type());
  }

  template <typename T_Platform>
  const char* PlatformInfo<T_Platform>::GetPlatformName(platform_index aIndex)
  {
    TLOC_ASSERT(aIndex < total_platforms,
      "Invalid platform index! Check tlocPlatform.h for supported platforms.");

    return platforms[aIndex];
  }

  template <typename T_Platform>
  typename PlatformInfo<T_Platform>::platform_type
    PlatformInfo<T_Platform>::GetPlatformType()
  {
    return platform_type;
  }

  //------------------------------------------------------------------------
  // Helper functions

  template <typename T_Platform>
  const char* PlatformInfo<T_Platform>::DoGetPlatformName(platform_win32)
  {
    return platforms[win32];
  }

  template <typename T_Platform>
  const char* PlatformInfo<T_Platform>::DoGetPlatformName(platform_win64)
  {
    return platforms[win64];
  }

  template <typename T_Platform>
  const char* PlatformInfo<T_Platform>::DoGetPlatformName(platform_xbox)
  {
    return platforms[xbox];
  }

  template <typename T_Platform>
  const char* PlatformInfo<T_Platform>::DoGetPlatformName(platform_osx)
  {
    return platforms[osx];
  }

  template <typename T_Platform>
  const char* PlatformInfo<T_Platform>::DoGetPlatformName(platform_osx_iphone)
  {
    return platforms[osx_iphone];
  }

  template <typename T_Platform>
  const char* PlatformInfo<T_Platform>::DoGetPlatformName(platform_linux)
  {
    return platforms[linux];
  }

  template <typename T_Platform>
  const char* PlatformInfo<T_Platform>::DoGetPlatformName(platform_ps3)
  {
    return platforms[ps3];
  }

};};
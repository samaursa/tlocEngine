#include "tlocPlatform.h"

#include <tlocCore/tlocAssert.h>

namespace tloc { namespace core { namespace platform {

  //////////////////////////////////////////////////////////////////////////
  // PlatformInfo

#define TLOC_PLATFORM_INFO_TEMPS  typename T_Platform
#define TLOC_PLATFORM_INFO_PARAMS T_Platform
#define TLOC_PLATFORM_INFO_TYPE   typename PlatformInfo_T<TLOC_PLATFORM_INFO_PARAMS>

  template <TLOC_PLATFORM_INFO_TEMPS>
  const char*
    PlatformInfo_T<TLOC_PLATFORM_INFO_PARAMS>::
    platforms[PlatformInfo_T<TLOC_PLATFORM_INFO_PARAMS>::total_platforms] =
  {
    "Windows"
    "Windows 32-bit",
    "Windows 64-bit",
    "XBOX",

    "Apple OSX",
    "Apple OSX iPhone",

    "Linux",

    "Playstation 3",
  };

  template <TLOC_PLATFORM_INFO_TEMPS>
  const char*
    PlatformInfo_T<TLOC_PLATFORM_INFO_PARAMS>::
    GetPlatformName()
  {
    return DoGetPlatformName(platform_type());
  }

  template <TLOC_PLATFORM_INFO_TEMPS>
  const char*
    PlatformInfo_T<TLOC_PLATFORM_INFO_PARAMS>::
    GetPlatformName(platform_index aIndex)
  {
    TLOC_ASSERT(aIndex < total_platforms,
      "Invalid platform index! Check tlocPlatform.h for supported platforms.");

    return platforms[aIndex];
  }

  template <TLOC_PLATFORM_INFO_TEMPS>
  TLOC_PLATFORM_INFO_TYPE::platform_type
    PlatformInfo_T<TLOC_PLATFORM_INFO_PARAMS>::
    GetPlatformType()
  {
    return platform_type();
  }

  //------------------------------------------------------------------------
  // Helper functions

  template <TLOC_PLATFORM_INFO_TEMPS>
  const char*
    PlatformInfo_T<TLOC_PLATFORM_INFO_PARAMS>::
    DoGetPlatformName(p_platform_info::win)
  {
    return platforms[windows];
  }

  template <TLOC_PLATFORM_INFO_TEMPS>
  const char*
    PlatformInfo_T<TLOC_PLATFORM_INFO_PARAMS>::
    DoGetPlatformName(p_platform_info::win32)
  {
    return platforms[win32];
  }

  template <TLOC_PLATFORM_INFO_TEMPS>
  const char*
    PlatformInfo_T<TLOC_PLATFORM_INFO_PARAMS>::
    DoGetPlatformName(p_platform_info::win64)
  {
    return platforms[win64];
  }

  template <TLOC_PLATFORM_INFO_TEMPS>
  const char*
    PlatformInfo_T<TLOC_PLATFORM_INFO_PARAMS>::
    DoGetPlatformName(p_platform_info::xbox)
  {
    return platforms[xbox];
  }

  template <TLOC_PLATFORM_INFO_TEMPS>
  const char*
    PlatformInfo_T<TLOC_PLATFORM_INFO_PARAMS>::
    DoGetPlatformName(p_platform_info::mac)
  {
    return platforms[osx];
  }

  template <TLOC_PLATFORM_INFO_TEMPS>
  const char*
    PlatformInfo_T<TLOC_PLATFORM_INFO_PARAMS>::
    DoGetPlatformName(p_platform_info::iphone)
  {
    return platforms[osx_iphone];
  }

  template <TLOC_PLATFORM_INFO_TEMPS>
  const char*
    PlatformInfo_T<TLOC_PLATFORM_INFO_PARAMS>::
    DoGetPlatformName(p_platform_info::linux)
  {
    return platforms[linux];
  }

  template <TLOC_PLATFORM_INFO_TEMPS>
  const char*
    PlatformInfo_T<TLOC_PLATFORM_INFO_PARAMS>::
    DoGetPlatformName(p_platform_info::ps3)
  {
    return platforms[ps3];
  }

  // -----------------------------------------------------------------------
  // explicit instantiation

  template class PlatformInfo_T<>;

};};};
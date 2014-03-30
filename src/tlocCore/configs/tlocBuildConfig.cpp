#include "tlocBuildConfig.h"

#include <tlocCore/tlocAssert.h>

namespace tloc { namespace core { namespace configs {

  //////////////////////////////////////////////////////////////////////////
  // PlatformInfo

#define BUILD_CONFIG_TEMP typename T_BuildConfigType
#define BUILD_CONFIG_PARAMS T_BuildConfigType
#define BUILD_CONFIG_TYPE typename BuildConfig_T<BUILD_CONFIG_PARAMS>

  template <BUILD_CONFIG_TEMP>
  const char* BuildConfig_T<BUILD_CONFIG_PARAMS>::
    m_buildTypes[BuildConfig_T<BUILD_CONFIG_PARAMS>::total_build_configs] =
  {
    "Debug",
    "Release",
    "Release_DebugInfo",
  };

  template <BUILD_CONFIG_TEMP>
  const char* BuildConfig_T<BUILD_CONFIG_PARAMS>::GetBuildConfigName()
  {
    return DoGetBuildConfigName(build_config_type());
  }

  template <BUILD_CONFIG_TEMP>
  const char* BuildConfig_T<BUILD_CONFIG_PARAMS>::
    GetBuildConfigName(build_config_index a_index)
  {
    TLOC_ASSERT(a_index < total_build_configs,
      "Invalid index! Check tlocBuildConfig.h for supported configurations.");

    return m_buildTypes[a_index];
  }

  template <BUILD_CONFIG_TEMP>
  typename BuildConfig_T<BUILD_CONFIG_PARAMS>::build_config_type
    BuildConfig_T<BUILD_CONFIG_PARAMS>::GetBuildConfigType()
  {
    return build_config_type();
  }

  //------------------------------------------------------------------------
  // Helper functions

  template <BUILD_CONFIG_TEMP>
  const char* BuildConfig_T<BUILD_CONFIG_PARAMS>::
    DoGetBuildConfigName(p_build_config::Debug)
  {
    return m_buildTypes[debug];
  }

  template <BUILD_CONFIG_TEMP>
  const char* BuildConfig_T<BUILD_CONFIG_PARAMS>::
    DoGetBuildConfigName(p_build_config::Release)
  {
    return m_buildTypes[release];
  }

  template <BUILD_CONFIG_TEMP>
  const char* BuildConfig_T<BUILD_CONFIG_PARAMS>::
    DoGetBuildConfigName(p_build_config::Release_DebugInfo)
  {
    return m_buildTypes[release_debug_info];
  }

  //------------------------------------------------------------------------
  // Explicit instantiations

  template class BuildConfig_T<>;

};};};
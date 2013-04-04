#ifndef TLOC_BUILD_CONFIG_H
#define TLOC_BUILD_CONFIG_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocBasicTypes.h>

namespace tloc { namespace core { namespace configs {

  namespace p_build_config
  {
    struct Debug {};
    struct Release {};
    struct Release_DebugInfo {};
  };

#if defined(TLOC_DEBUG)
  template <typename T_BuildConfigType = p_build_config::Debug>
#elif defined (TLOC_RELEASE)
  template <typename T_BuildConfigType = p_build_config::Release>
#elif defined (TLOC_RELEASE_DEBUGINFO)
  template <typename T_BuildConfigType = p_build_config::Release_DebugInfo>
#endif
  class BuildConfig
  {
  public:
    typedef T_BuildConfigType   build_config_type;

    typedef tl_size   build_config_index;
    enum { debug = 0, release, release_debug_info, total_build_configs};

    static const char*        GetBuildConfigName();
    static const char*        GetBuildConfigName(build_config_index a_index);
    static build_config_type  GetBuildConfigType();

  private:

    static const char*  DoGetBuildConfigName(p_build_config::Debug);
    static const char*  DoGetBuildConfigName(p_build_config::Release);
    static const char*  DoGetBuildConfigName(p_build_config::Release_DebugInfo);

    static const char* m_buildTypes[total_build_configs];
  };

};};};

#endif

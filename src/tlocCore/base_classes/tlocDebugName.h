#ifndef _TLOC_CORE_BASE_CLASSES_DEBUG_NAME_H_
#define _TLOC_CORE_BASE_CLASSES_DEBUG_NAME_H_

#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/configs/tlocBuildConfig.h>

namespace tloc{ namespace core { namespace base_classes {

  // ///////////////////////////////////////////////////////////////////////
  // DebugName<>

  template <typename T_BuildConfig = core_cfg::BuildConfig::build_config_type>
  class debug_name_ti
  {
  public:
    typedef std::string                     string_type;

  protected:
    debug_name_ti(buffer_arg a_name);
    ~debug_name_ti();
    
    void          set_debug_name(buffer_arg a_name);
    const char*   get_debug_name() const;

  private:
    string_type m_name;
  };

  // ///////////////////////////////////////////////////////////////////////
  // DebugName<Release>

  template <>
  class debug_name_ti<core_cfg::p_build_config::Release>
  {
  public:
    typedef std::string                     string_type;

  protected:
    debug_name_ti(buffer_arg );
    ~debug_name_ti();
    
    void          set_debug_name(buffer_arg );
    const char*   get_debug_name() const;
  };

  // -----------------------------------------------------------------------
  // typedef

  typedef debug_name_ti<>                              DebugName;

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(debug_name_ti<core_cfg::p_build_config::Debug>);
  TLOC_EXTERN_TEMPLATE_CLASS(debug_name_ti<core_cfg::p_build_config::Release_DebugInfo>);
  TLOC_EXTERN_TEMPLATE_CLASS(debug_name_ti<core_cfg::p_build_config::Release>);

};};};

#endif
#include "tlocDebugName.h"

namespace tloc{ namespace core { namespace base_classes {

  // ///////////////////////////////////////////////////////////////////////
  // DebugName_TI<>

#define TLOC_DEBUG_NAME_TEMPS   typename T_BuildConfig
#define TLOC_DEBUG_NAME_PARAMS  T_BuildConfig
#define TLOC_DEBUG_NAME_TYPE    typename DebugName_TI<T_BuildConfig>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_DEBUG_NAME_TEMPS>
  debug_name_ti<TLOC_DEBUG_NAME_PARAMS>::
    debug_name_ti(buffer_arg  a_name)
    : m_name(a_name)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_DEBUG_NAME_TEMPS>
  debug_name_ti<TLOC_DEBUG_NAME_PARAMS>::
    ~debug_name_ti()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_DEBUG_NAME_TEMPS>
  void
  debug_name_ti<TLOC_DEBUG_NAME_PARAMS>::
    set_debug_name(buffer_arg a_name)
  { m_name = a_name; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_DEBUG_NAME_TEMPS>
  const char*
    debug_name_ti<TLOC_DEBUG_NAME_PARAMS>::
    get_debug_name() const
  { return m_name.c_str(); }

  // ///////////////////////////////////////////////////////////////////////
  // DebugName_TI<Release>

#define TLOC_DEBUG_NAME_RELEASE_PARAMS    core_cfg::p_build_config::Release

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  debug_name_ti<TLOC_DEBUG_NAME_RELEASE_PARAMS>::
    debug_name_ti(buffer_arg )
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  debug_name_ti<TLOC_DEBUG_NAME_RELEASE_PARAMS>::
    ~debug_name_ti()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    debug_name_ti<TLOC_DEBUG_NAME_RELEASE_PARAMS>::
    set_debug_name(buffer_arg)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const char*
    debug_name_ti<TLOC_DEBUG_NAME_RELEASE_PARAMS>::
    get_debug_name() const
  { return "No name assigned - RELEASE CONFIG"; }


  // -----------------------------------------------------------------------
  // explicit instantiations

  template class debug_name_ti<core_cfg::p_build_config::Debug>;
  template class debug_name_ti<core_cfg::p_build_config::Release_DebugInfo>;

};};};
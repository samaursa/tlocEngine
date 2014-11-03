#include "tlocDebugName.h"

namespace tloc{ namespace core { namespace base_classes {

  // ///////////////////////////////////////////////////////////////////////
  // DebugName_TI<>

#define TLOC_DEBUG_NAME_TEMPS   typename T_BuildConfig
#define TLOC_DEBUG_NAME_PARAMS  T_BuildConfig
#define TLOC_DEBUG_NAME_TYPE    typename DebugName_TI<T_BuildConfig>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_DEBUG_NAME_TEMPS>
  DebugName_TI<TLOC_DEBUG_NAME_PARAMS>::
    DebugName_TI(BufferArg  a_name)
    : m_name(a_name)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_DEBUG_NAME_TEMPS>
  DebugName_TI<TLOC_DEBUG_NAME_PARAMS>::
    ~DebugName_TI()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_DEBUG_NAME_TEMPS>
  void
  DebugName_TI<TLOC_DEBUG_NAME_PARAMS>::
    SetDebugName(BufferArg a_name)
  { m_name = a_name; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_DEBUG_NAME_TEMPS>
  const char*
    DebugName_TI<TLOC_DEBUG_NAME_PARAMS>::
    GetDebugName() const
  { return m_name.c_str(); }

  // ///////////////////////////////////////////////////////////////////////
  // DebugName_TI<Release>

#define TLOC_DEBUG_NAME_RELEASE_PARAMS    core_cfg::p_build_config::Release

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  DebugName_TI<TLOC_DEBUG_NAME_RELEASE_PARAMS>::
    DebugName_TI(BufferArg )
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  DebugName_TI<TLOC_DEBUG_NAME_RELEASE_PARAMS>::
    ~DebugName_TI()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DebugName_TI<TLOC_DEBUG_NAME_RELEASE_PARAMS>::
    SetDebugName(BufferArg)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const char*
    DebugName_TI<TLOC_DEBUG_NAME_RELEASE_PARAMS>::
    GetDebugName() const
  { return "No name assigned - RELEASE CONFIG"; }


  // -----------------------------------------------------------------------
  // explicit instantiations

  template class DebugName_TI<core_cfg::p_build_config::Debug>;
  template class DebugName_TI<core_cfg::p_build_config::Release_DebugInfo>;
  template class DebugName_TI<core_cfg::p_build_config::Release>;

};};};
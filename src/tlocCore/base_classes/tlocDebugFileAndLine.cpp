#include "tlocDebugFileAndLine.h"

namespace tloc { namespace core { namespace base_classes {

#define TLOC_DEBUG_FILE_AND_LINE_TEMPS  typename T_BuildConfig
#define TLOC_DEBUG_FILE_AND_LINE_PARAMS T_BuildConfig
#define TLOC_DEBUG_FILE_AND_LINE_TYPE   typename DebugFileAndLine_T<TLOC_DEBUG_FILE_AND_LINE_PARAMS>

  // ///////////////////////////////////////////////////////////////////////
  // DebugFileAndLine_T<>

  template <TLOC_DEBUG_FILE_AND_LINE_TEMPS>
  DebugFileAndLine_T<TLOC_DEBUG_FILE_AND_LINE_PARAMS>::
    DebugFileAndLine_T(TLOC_FILE_AND_LINE_ARGS)
    : m_fileName(a_fileName)
    , m_lineNumber(a_lineNumber)
  { }

  // ///////////////////////////////////////////////////////////////////////
  // DebugFileAndLine_T<Release>

  DebugFileAndLine_T<core_cfg::p_build_config::Release>::
    DebugFileAndLine_T(TLOC_FILE_AND_LINE_ARGS_NO_VARS)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const char*
    DebugFileAndLine_T<core_cfg::p_build_config::Release>::
    GetFileName() const
  { return "No filename - Release"; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

   tl_int
    DebugFileAndLine_T<core_cfg::p_build_config::Release>::
    GetLineNumber() const
  { return -1; }

   // -----------------------------------------------------------------------
   // explicit instantiation

   template class DebugFileAndLine_T<core_cfg::p_build_config::Debug>;
   template class DebugFileAndLine_T<core_cfg::p_build_config::Release_DebugInfo>;

};};};
#ifndef _TLOC_CORE_BASE_CLASSES_DEBUG_FILE_AND_LINE_H_
#define _TLOC_CORE_BASE_CLASSES_DEBUG_FILE_AND_LINE_H_

#include <tlocCore/tlocBase.h>

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/configs/tlocBuildConfig.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace core { namespace base_classes {

  // -----------------------------------------------------------------------
  // macros used for function/method arguments (declaring and calling)

#define TLOC_FILE_AND_LINE_ARGS_NO_VARS BufferArg , const tl_int
#define TLOC_FILE_AND_LINE_ARGS         BufferArg a_fileName, const tl_int a_lineNumber
#define TLOC_FILE_AND_LINE              __FILE__, __LINE__

  // ///////////////////////////////////////////////////////////////////////
  // DebugFileAndLine_T<>
   
  template <typename T_BuildConfig = core_cfg::BuildConfig::build_config_type>
  class DebugFileAndLine_T
  {
  public:
    DebugFileAndLine_T(TLOC_FILE_AND_LINE_ARGS);

    TLOC_DECL_AND_DEF_GETTER(BufferArg, GetFileName, m_fileName);
    TLOC_DECL_AND_DEF_GETTER(tl_int, GetLineNumber, m_lineNumber);

  private:
    BufferArg   m_fileName;
    tl_int      m_lineNumber;
  };

  // ///////////////////////////////////////////////////////////////////////
  // DebugFileAndLine<Release>

  template <>
  class DebugFileAndLine_T<core_cfg::p_build_config::Release>
  {
  public:
    DebugFileAndLine_T(TLOC_FILE_AND_LINE_ARGS_NO_VARS);

    TLOC_DECL_GETTER(const char*, GetFileName);
    TLOC_DECL_GETTER(tl_int, GetLineNumber);
  };

  // -----------------------------------------------------------------------
  // typedefs

  typedef DebugFileAndLine_T<>                            DebugFileAndLine;

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(DebugFileAndLine_T<core_cfg::p_build_config::Debug>);
  TLOC_EXTERN_TEMPLATE_CLASS(DebugFileAndLine_T<core_cfg::p_build_config::Release_DebugInfo>);
  TLOC_EXTERN_TEMPLATE_CLASS(DebugFileAndLine_T<core_cfg::p_build_config::Release>);

};};};

#endif
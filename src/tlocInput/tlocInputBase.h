#ifndef _TLOC_INPUT_COMMON_H_
#define _TLOC_INPUT_COMMON_H_

#include <tlocCore/tlocBase.h>

// All major namespaces that input uses should go here

namespace tloc {

  //////////////////////////////////////////////////////////////////////////
  // Complete namespace here

  namespace input { namespace hid { }};

  //////////////////////////////////////////////////////////////////////////
  // Namespace aliases here

  namespace input_hid = input::hid;

};

#include <tlocCore/logging/tlocLoggerHelper.h>

TLOC_FORWARD_DECLARE_LOGGER_CONSOLE_IMMEDIATE_DEFAULT();

// -----------------------------------------------------------------------
// inputs's default logger
namespace tloc { namespace input {

  TLOC_LOGGER_DECLARE_LOGGER_FUNC_CONSOLE_IMMEDIATE_DEFAULT(GetLogger);

};};

#define TLOC_LOG_INPUT_INFO()    TLOC_LOG_INFO(&tloc::input::GetLogger())
#define TLOC_LOG_INPUT_DEBUG()   TLOC_LOG_DEBUG(&tloc::input::GetLogger())
#define TLOC_LOG_INPUT_WARN()    TLOC_LOG_WARN(&tloc::input::GetLogger())
#define TLOC_LOG_INPUT_ERR()     TLOC_LOG_ERR(&tloc::input::GetLogger())

#define TLOC_LOG_INPUT_INFO_IF(_expr_)    TLOC_LOG_INFO_IF(_expr_, &tloc::input::GetLogger())
#define TLOC_LOG_INPUT_DEBUG_IF(_expr_)   TLOC_LOG_DEBUG_IF(_expr_, &tloc::input::GetLogger())
#define TLOC_LOG_INPUT_WARN_IF(_expr_)    TLOC_LOG_WARN_IF(_expr_, &tloc::input::GetLogger())
#define TLOC_LOG_INPUT_ERR_IF(_expr_)     TLOC_LOG_ERR_IF(_expr_, &tloc::input::GetLogger())

#define TLOC_LOG_INPUT_INFO_FILENAME_ONLY()    TLOC_LOG_INFO_FILENAME_ONLY(&tloc::input::GetLogger())
#define TLOC_LOG_INPUT_DEBUG_FILENAME_ONLY()   TLOC_LOG_DEBUG_FILENAME_ONLY(&tloc::input::GetLogger())
#define TLOC_LOG_INPUT_WARN_FILENAME_ONLY()    TLOC_LOG_WARN_FILENAME_ONLY(&tloc::input::GetLogger())
#define TLOC_LOG_INPUT_ERR_FILENAME_ONLY()     TLOC_LOG_ERR_FILENAME_ONLY(&tloc::input::GetLogger())

#define TLOC_LOG_INPUT_INFO_FILENAME_ONLY_IF(_expr_)    TLOC_LOG_INFO_FILENAME_ONLY_IF(_expr_, &tloc::input::GetLogger())
#define TLOC_LOG_INPUT_DEBUG_FILENAME_ONLY_IF(_expr_)   TLOC_LOG_DEBUG_FILENAME_ONLY_IF(_expr_, &tloc::input::GetLogger())
#define TLOC_LOG_INPUT_WARN_FILENAME_ONLY_IF(_expr_)    TLOC_LOG_WARN_FILENAME_ONLY_IF(_expr_, &tloc::input::GetLogger())
#define TLOC_LOG_INPUT_ERR_FILENAME_ONLY_IF(_expr_)     TLOC_LOG_ERR_FILENAME_ONLY_IF(_expr_, &tloc::input::GetLogger())

#define TLOC_LOG_INPUT_INFO_NO_FILENAME()    TLOC_LOG_INFO_NO_FILENAME(&tloc::input::GetLogger())
#define TLOC_LOG_INPUT_DEBUG_NO_FILENAME()   TLOC_LOG_DEBUG_NO_FILENAME(&tloc::input::GetLogger())
#define TLOC_LOG_INPUT_WARN_NO_FILENAME()    TLOC_LOG_WARN_NO_FILENAME(&tloc::input::GetLogger())
#define TLOC_LOG_INPUT_ERR_NO_FILENAME()     TLOC_LOG_ERR_NO_FILENAME(&tloc::input::GetLogger())

#define TLOC_LOG_INPUT_INFO_NO_FILENAME_IF(_expr_)    TLOC_LOG_INFO_NO_FILENAME_IF(_expr_, &tloc::input::GetLogger())
#define TLOC_LOG_INPUT_DEBUG_NO_FILENAME_IF(_expr_)   TLOC_LOG_DEBUG_NO_FILENAME_IF(_expr_, &tloc::input::GetLogger())
#define TLOC_LOG_INPUT_WARN_NO_FILENAME_IF(_expr_)    TLOC_LOG_WARN_NO_FILENAME_IF(_expr_, &tloc::input::GetLogger())
#define TLOC_LOG_INPUT_ERR_NO_FILENAME_IF(_expr_)     TLOC_LOG_ERR_NO_FILENAME_IF(_expr_, &tloc::input::GetLogger())

#endif
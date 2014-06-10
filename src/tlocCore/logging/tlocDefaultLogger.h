#ifndef _TLOC_CORE_DEFAULT_LOGGER_H_
#define _TLOC_CORE_DEFAULT_LOGGER_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/logging/tlocLogger.h>

namespace tloc { namespace default_logger {

  TLOC_LOGGER_DECLARE_LOGGER_FUNC_CONSOLE_IMMEDIATE_DEFAULT(GetLogger);

};};

#define TLOC_LOG_DEFAULT_INFO()    TLOC_LOG_INFO(&tloc::default_logger::GetLogger())
#define TLOC_LOG_DEFAULT_DEBUG()   TLOC_LOG_DEBUG(&tloc::default_logger::GetLogger())
#define TLOC_LOG_DEFAULT_WARN()    TLOC_LOG_WARN(&tloc::default_logger::GetLogger())
#define TLOC_LOG_DEFAULT_ERR()     TLOC_LOG_ERR(&tloc::default_logger::GetLogger())

#define TLOC_LOG_DEFAULT_INFO_IF(_expr_)    TLOC_LOG_INFO_IF(_expr_, &tloc::default_logger::GetLogger())
#define TLOC_LOG_DEFAULT_DEBUG_IF(_expr_)   TLOC_LOG_DEBUG_IF(_expr_, &tloc::default_logger::GetLogger())
#define TLOC_LOG_DEFAULT_WARN_IF(_expr_)    TLOC_LOG_WARN_IF(_expr_, &tloc::default_logger::GetLogger())
#define TLOC_LOG_DEFAULT_ERR_IF(_expr_)     TLOC_LOG_ERR_IF(_expr_, &tloc::default_logger::GetLogger())

#define TLOC_LOG_DEFAULT_INFO_FILENAME_ONLY()    TLOC_LOG_INFO_FILENAME_ONLY(&tloc::default_logger::GetLogger())
#define TLOC_LOG_DEFAULT_DEBUG_FILENAME_ONLY()   TLOC_LOG_DEBUG_FILENAME_ONLY(&tloc::default_logger::GetLogger())
#define TLOC_LOG_DEFAULT_WARN_FILENAME_ONLY()    TLOC_LOG_WARN_FILENAME_ONLY(&tloc::default_logger::GetLogger())
#define TLOC_LOG_DEFAULT_ERR_FILENAME_ONLY()     TLOC_LOG_ERR_FILENAME_ONLY(&tloc::default_logger::GetLogger())

#define TLOC_LOG_DEFAULT_INFO_FILENAME_ONLY_IF(_expr_)    TLOC_LOG_INFO_FILENAME_ONLY_IF(_expr_, &tloc::default_logger::GetLogger())
#define TLOC_LOG_DEFAULT_DEBUG_FILENAME_ONLY_IF(_expr_)   TLOC_LOG_DEBUG_FILENAME_ONLY_IF(_expr_, &tloc::default_logger::GetLogger())
#define TLOC_LOG_DEFAULT_WARN_FILENAME_ONLY_IF(_expr_)    TLOC_LOG_WARN_FILENAME_ONLY_IF(_expr_, &tloc::default_logger::GetLogger())
#define TLOC_LOG_DEFAULT_ERR_FILENAME_ONLY_IF(_expr_)     TLOC_LOG_ERR_FILENAME_ONLY_IF(_expr_, &tloc::default_logger::GetLogger())

#define TLOC_LOG_DEFAULT_INFO_NO_FILENAME()    TLOC_LOG_INFO_NO_FILENAME(&tloc::default_logger::GetLogger())
#define TLOC_LOG_DEFAULT_DEBUG_NO_FILENAME()   TLOC_LOG_DEBUG_NO_FILENAME(&tloc::default_logger::GetLogger())
#define TLOC_LOG_DEFAULT_WARN_NO_FILENAME()    TLOC_LOG_WARN_NO_FILENAME(&tloc::default_logger::GetLogger())
#define TLOC_LOG_DEFAULT_ERR_NO_FILENAME()     TLOC_LOG_ERR_NO_FILENAME(&tloc::default_logger::GetLogger())

#define TLOC_LOG_DEFAULT_INFO_NO_FILENAME_IF(_expr_)    TLOC_LOG_INFO_NO_FILENAME_IF(_expr_, &tloc::default_logger::GetLogger())
#define TLOC_LOG_DEFAULT_DEBUG_NO_FILENAME_IF(_expr_)   TLOC_LOG_DEBUG_NO_FILENAME_IF(_expr_, &tloc::default_logger::GetLogger())
#define TLOC_LOG_DEFAULT_WARN_NO_FILENAME_IF(_expr_)    TLOC_LOG_WARN_NO_FILENAME_IF(_expr_, &tloc::default_logger::GetLogger())
#define TLOC_LOG_DEFAULT_ERR_NO_FILENAME_IF(_expr_)     TLOC_LOG_ERR_NO_FILENAME_IF(_expr_, &tloc::default_logger::GetLogger())

#endif
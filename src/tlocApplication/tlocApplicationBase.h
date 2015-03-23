#ifndef _TLOC_APPLICATION_BASE_H_
#define _TLOC_APPLICATION_BASE_H_

#include <tlocCore/tlocBase.h>

// All major namespaces that application uses should go here

namespace tloc {

  // ///////////////////////////////////////////////////////////////////////
  // Complete namespace here

  namespace application
  {
    namespace resources {};
  };

  // ///////////////////////////////////////////////////////////////////////
  // Namespace aliases here

  namespace app           = application;
  namespace app_res       = app::resources;

};

#include <tlocCore/logging/tlocLoggerHelper.h>

TLOC_FORWARD_DECLARE_LOGGER_CONSOLE_IMMEDIATE_DEFAULT();

// -----------------------------------------------------------------------
// application's default logger
namespace tloc { namespace application {

  TLOC_LOGGER_DECLARE_LOGGER_FUNC_CONSOLE_IMMEDIATE_DEFAULT(GetLogger);

};};

#define TLOC_LOG_APP_INFO()    TLOC_LOG_INFO(&tloc::application::GetLogger())
#define TLOC_LOG_APP_SUCCESS() TLOC_LOG_SUCCESS(&tloc::application::GetLogger())
#define TLOC_LOG_APP_DEBUG()   TLOC_LOG_DEBUG(&tloc::application::GetLogger())
#define TLOC_LOG_APP_WARN()    TLOC_LOG_WARN(&tloc::application::GetLogger())
#define TLOC_LOG_APP_ERR()     TLOC_LOG_ERR(&tloc::application::GetLogger())

#define TLOC_LOG_APP_INFO_IF(_expr_)    TLOC_LOG_INFO_IF(_expr_, &tloc::application::GetLogger())
#define TLOC_LOG_APP_SUCCESS_IF(_expr_) TLOC_LOG_SUCCESS_IF(_expr_, &tloc::application::GetLogger())
#define TLOC_LOG_APP_DEBUG_IF(_expr_)   TLOC_LOG_DEBUG_IF(_expr_, &tloc::application::GetLogger())
#define TLOC_LOG_APP_WARN_IF(_expr_)    TLOC_LOG_WARN_IF(_expr_, &tloc::application::GetLogger())
#define TLOC_LOG_APP_ERR_IF(_expr_)     TLOC_LOG_ERR_IF(_expr_, &tloc::application::GetLogger())

#define TLOC_LOG_APP_INFO_FILENAME_ONLY()    TLOC_LOG_INFO_FILENAME_ONLY(&tloc::application::GetLogger())
#define TLOC_LOG_APP_SUCCESS_FILENAME_ONLY() TLOC_LOG_SUCCESS_FILENAME_ONLY(&tloc::application::GetLogger())
#define TLOC_LOG_APP_DEBUG_FILENAME_ONLY()   TLOC_LOG_DEBUG_FILENAME_ONLY(&tloc::application::GetLogger())
#define TLOC_LOG_APP_WARN_FILENAME_ONLY()    TLOC_LOG_WARN_FILENAME_ONLY(&tloc::application::GetLogger())
#define TLOC_LOG_APP_ERR_FILENAME_ONLY()     TLOC_LOG_ERR_FILENAME_ONLY(&tloc::application::GetLogger())

#define TLOC_LOG_APP_INFO_FILENAME_ONLY_IF(_expr_)    TLOC_LOG_INFO_FILENAME_ONLY_IF(_expr_, &tloc::application::GetLogger())
#define TLOC_LOG_APP_SUCCESS_FILENAME_ONLY_IF(_expr_) TLOC_LOG_SUCCESS_FILENAME_ONLY_IF(_expr_, &tloc::application::GetLogger())
#define TLOC_LOG_APP_DEBUG_FILENAME_ONLY_IF(_expr_)   TLOC_LOG_DEBUG_FILENAME_ONLY_IF(_expr_, &tloc::application::GetLogger())
#define TLOC_LOG_APP_WARN_FILENAME_ONLY_IF(_expr_)    TLOC_LOG_WARN_FILENAME_ONLY_IF(_expr_, &tloc::application::GetLogger())
#define TLOC_LOG_APP_ERR_FILENAME_ONLY_IF(_expr_)     TLOC_LOG_ERR_FILENAME_ONLY_IF(_expr_, &tloc::application::GetLogger())

#define TLOC_LOG_APP_INFO_NO_FILENAME()    TLOC_LOG_INFO_NO_FILENAME(&tloc::application::GetLogger())
#define TLOC_LOG_APP_SUCCESS_NO_FILENAME() TLOC_LOG_SUCCESS_NO_FILENAME(&tloc::application::GetLogger())
#define TLOC_LOG_APP_DEBUG_NO_FILENAME()   TLOC_LOG_DEBUG_NO_FILENAME(&tloc::application::GetLogger())
#define TLOC_LOG_APP_WARN_NO_FILENAME()    TLOC_LOG_WARN_NO_FILENAME(&tloc::application::GetLogger())
#define TLOC_LOG_APP_ERR_NO_FILENAME()     TLOC_LOG_ERR_NO_FILENAME(&tloc::application::GetLogger())

#define TLOC_LOG_APP_INFO_NO_FILENAME_IF(_expr_)    TLOC_LOG_INFO_NO_FILENAME_IF(_expr_, &tloc::application::GetLogger())
#define TLOC_LOG_APP_SUCCESS_NO_FILENAME_IF(_expr_) TLOC_LOG_SUCCESS_NO_FILENAME_IF(_expr_, &tloc::application::GetLogger())
#define TLOC_LOG_APP_DEBUG_NO_FILENAME_IF(_expr_)   TLOC_LOG_DEBUG_NO_FILENAME_IF(_expr_, &tloc::application::GetLogger())
#define TLOC_LOG_APP_WARN_NO_FILENAME_IF(_expr_)    TLOC_LOG_WARN_NO_FILENAME_IF(_expr_, &tloc::application::GetLogger())
#define TLOC_LOG_APP_ERR_NO_FILENAME_IF(_expr_)     TLOC_LOG_ERR_NO_FILENAME_IF(_expr_, &tloc::application::GetLogger())

#endif

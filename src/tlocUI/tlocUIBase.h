#ifndef _TLOC_UI_BASE_H_
#define _TLOC_UI_BASE_H_

#include <tlocCore/tlocBase.h>

// All major namespaces that ui uses should go here

namespace tloc {

  //////////////////////////////////////////////////////////////////////////
  // Complete namespace here

  namespace ui
  {
    namespace error            {};
  };

  //////////////////////////////////////////////////////////////////////////
  // Namespace aliases here

  namespace ui_err        = ui::error;

};

#include <tlocCore/logging/tlocLoggerHelper.h>

TLOC_FORWARD_DECLARE_LOGGER_CONSOLE_IMMEDIATE_DEFAULT();

// -----------------------------------------------------------------------
// ui's default logger
namespace tloc { namespace ui {

  TLOC_LOGGER_DECLARE_LOGGER_FUNC_CONSOLE_IMMEDIATE_DEFAULT(GetLogger);

};};

#define TLOC_LOG_ANIM_INFO()    TLOC_LOG_INFO(&tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_SUCCESS() TLOC_LOG_SUCCESS(&tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_DEBUG()   TLOC_LOG_DEBUG(&tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_WARN()    TLOC_LOG_WARN(&tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_ERR()     TLOC_LOG_ERR(&tloc::ui::GetLogger())

#define TLOC_LOG_ANIM_INFO_IF(_expr_)    TLOC_LOG_INFO_IF(_expr_, &tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_SUCCESS_IF(_expr_) TLOC_LOG_SUCCESS_IF(_expr_, &tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_DEBUG_IF(_expr_)   TLOC_LOG_DEBUG_IF(_expr_, &tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_WARN_IF(_expr_)    TLOC_LOG_WARN_IF(_expr_, &tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_ERR_IF(_expr_)     TLOC_LOG_ERR_IF(_expr_, &tloc::ui::GetLogger())

#define TLOC_LOG_ANIM_INFO_FILENAME_ONLY()    TLOC_LOG_INFO_FILENAME_ONLY(&tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_SUCCESS_FILENAME_ONLY() TLOC_LOG_SUCCESS_FILENAME_ONLY(&tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_DEBUG_FILENAME_ONLY()   TLOC_LOG_DEBUG_FILENAME_ONLY(&tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_WARN_FILENAME_ONLY()    TLOC_LOG_WARN_FILENAME_ONLY(&tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_ERR_FILENAME_ONLY()     TLOC_LOG_ERR_FILENAME_ONLY(&tloc::ui::GetLogger())

#define TLOC_LOG_ANIM_INFO_FILENAME_ONLY_IF(_expr_)    TLOC_LOG_INFO_FILENAME_ONLY_IF(_expr_, &tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_SUCCESS_FILENAME_ONLY_IF(_expr_) TLOC_LOG_SUCCESS_FILENAME_ONLY_IF(_expr_, &tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_DEBUG_FILENAME_ONLY_IF(_expr_)   TLOC_LOG_DEBUG_FILENAME_ONLY_IF(_expr_, &tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_WARN_FILENAME_ONLY_IF(_expr_)    TLOC_LOG_WARN_FILENAME_ONLY_IF(_expr_, &tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_ERR_FILENAME_ONLY_IF(_expr_)     TLOC_LOG_ERR_FILENAME_ONLY_IF(_expr_, &tloc::ui::GetLogger())

#define TLOC_LOG_ANIM_INFO_NO_FILENAME()    TLOC_LOG_INFO_NO_FILENAME(&tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_SUCCESS_NO_FILENAME() TLOC_LOG_SUCCESS_NO_FILENAME(&tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_DEBUG_NO_FILENAME()   TLOC_LOG_DEBUG_NO_FILENAME(&tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_WARN_NO_FILENAME()    TLOC_LOG_WARN_NO_FILENAME(&tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_ERR_NO_FILENAME()     TLOC_LOG_ERR_NO_FILENAME(&tloc::ui::GetLogger())

#define TLOC_LOG_ANIM_INFO_NO_FILENAME_IF(_expr_)    TLOC_LOG_INFO_NO_FILENAME_IF(_expr_, &tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_SUCCESS_NO_FILENAME_IF(_expr_) TLOC_LOG_SUCCESS_NO_FILENAME_IF(_expr_, &tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_DEBUG_NO_FILENAME_IF(_expr_)   TLOC_LOG_DEBUG_NO_FILENAME_IF(_expr_, &tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_WARN_NO_FILENAME_IF(_expr_)    TLOC_LOG_WARN_NO_FILENAME_IF(_expr_, &tloc::ui::GetLogger())
#define TLOC_LOG_ANIM_ERR_NO_FILENAME_IF(_expr_)     TLOC_LOG_ERR_NO_FILENAME_IF(_expr_, &tloc::ui::GetLogger())

#endif
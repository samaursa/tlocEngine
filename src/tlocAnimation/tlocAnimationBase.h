#ifndef _TLOC_ANIMATION_BASE_H_
#define _TLOC_ANIMATION_BASE_H_

#include <tlocCore/tlocBase.h>

// All major namespaces that animation uses should go here

namespace tloc {

  //////////////////////////////////////////////////////////////////////////
  // Complete namespace here

  namespace animation
  {
    namespace component_system {};
    namespace error            {};
    namespace types            {};
    namespace resources        {};
  };

  //////////////////////////////////////////////////////////////////////////
  // Namespace aliases here

  namespace anim          = animation;
  namespace anim_cs       = animation::component_system;
  namespace anim_err      = animation::error;
  namespace anim_t        = animation::types;
  namespace anim_res      = animation::resources;

};

namespace tl_anim          = tloc::animation;
namespace tl_anim_cs       = tloc::animation::component_system;
namespace tl_anim_err      = tloc::animation::error;
namespace tl_anim_t        = tloc::animation::types;
namespace tl_anim_res      = tloc::animation::resources;

#include <tlocCore/logging/tlocLoggerHelper.h>

TLOC_FORWARD_DECLARE_LOGGER_CONSOLE_IMMEDIATE_DEFAULT();

// -----------------------------------------------------------------------
// animation's default logger
namespace tloc { namespace animation {

  TLOC_LOGGER_DECLARE_LOGGER_FUNC_CONSOLE_IMMEDIATE_DEFAULT(GetLogger);

};};

#define TLOC_LOG_ANIM_INFO()    TLOC_LOG_INFO(&tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_SUCCESS() TLOC_LOG_SUCCESS(&tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_DEBUG()   TLOC_LOG_DEBUG(&tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_WARN()    TLOC_LOG_WARN(&tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_ERR()     TLOC_LOG_ERR(&tloc::animation::GetLogger())

#define TLOC_LOG_ANIM_INFO_IF(_expr_)    TLOC_LOG_INFO_IF(_expr_, &tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_SUCCESS_IF(_expr_) TLOC_LOG_SUCCESS_IF(_expr_, &tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_DEBUG_IF(_expr_)   TLOC_LOG_DEBUG_IF(_expr_, &tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_WARN_IF(_expr_)    TLOC_LOG_WARN_IF(_expr_, &tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_ERR_IF(_expr_)     TLOC_LOG_ERR_IF(_expr_, &tloc::animation::GetLogger())

#define TLOC_LOG_ANIM_INFO_FILENAME_ONLY()    TLOC_LOG_INFO_FILENAME_ONLY(&tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_SUCCESS_FILENAME_ONLY() TLOC_LOG_SUCCESS_FILENAME_ONLY(&tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_DEBUG_FILENAME_ONLY()   TLOC_LOG_DEBUG_FILENAME_ONLY(&tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_WARN_FILENAME_ONLY()    TLOC_LOG_WARN_FILENAME_ONLY(&tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_ERR_FILENAME_ONLY()     TLOC_LOG_ERR_FILENAME_ONLY(&tloc::animation::GetLogger())

#define TLOC_LOG_ANIM_INFO_FILENAME_ONLY_IF(_expr_)    TLOC_LOG_INFO_FILENAME_ONLY_IF(_expr_, &tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_SUCCESS_FILENAME_ONLY_IF(_expr_) TLOC_LOG_SUCCESS_FILENAME_ONLY_IF(_expr_, &tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_DEBUG_FILENAME_ONLY_IF(_expr_)   TLOC_LOG_DEBUG_FILENAME_ONLY_IF(_expr_, &tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_WARN_FILENAME_ONLY_IF(_expr_)    TLOC_LOG_WARN_FILENAME_ONLY_IF(_expr_, &tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_ERR_FILENAME_ONLY_IF(_expr_)     TLOC_LOG_ERR_FILENAME_ONLY_IF(_expr_, &tloc::animation::GetLogger())

#define TLOC_LOG_ANIM_INFO_NO_FILENAME()    TLOC_LOG_INFO_NO_FILENAME(&tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_SUCCESS_NO_FILENAME() TLOC_LOG_SUCCESS_NO_FILENAME(&tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_DEBUG_NO_FILENAME()   TLOC_LOG_DEBUG_NO_FILENAME(&tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_WARN_NO_FILENAME()    TLOC_LOG_WARN_NO_FILENAME(&tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_ERR_NO_FILENAME()     TLOC_LOG_ERR_NO_FILENAME(&tloc::animation::GetLogger())

#define TLOC_LOG_ANIM_INFO_NO_FILENAME_IF(_expr_)    TLOC_LOG_INFO_NO_FILENAME_IF(_expr_, &tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_SUCCESS_NO_FILENAME_IF(_expr_) TLOC_LOG_SUCCESS_NO_FILENAME_IF(_expr_, &tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_DEBUG_NO_FILENAME_IF(_expr_)   TLOC_LOG_DEBUG_NO_FILENAME_IF(_expr_, &tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_WARN_NO_FILENAME_IF(_expr_)    TLOC_LOG_WARN_NO_FILENAME_IF(_expr_, &tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_ERR_NO_FILENAME_IF(_expr_)     TLOC_LOG_ERR_NO_FILENAME_IF(_expr_, &tloc::animation::GetLogger())

#endif
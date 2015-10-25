#ifndef _TLOC_MATH_BASE_H_
#define _TLOC_MATH_BASE_H_

#include <tlocCore/tlocBase.h>

// All major namespaces that math uses should go here

namespace tloc {

  //////////////////////////////////////////////////////////////////////////
  // Complete namespace here

  namespace math
  {
    namespace error            {};
    namespace component_system {};
    namespace statistics       {};
    namespace types            {};
    namespace utils            {};
    namespace proj             {};
    namespace optimize         {};
  };

  //////////////////////////////////////////////////////////////////////////
  // Namespace aliases here

  namespace math_err   = math::error;
  namespace math_cs    = math::component_system;
  namespace math_stat  = math::statistics;
  namespace math_t     = math::types;
  namespace math_utils = math::utils;
  namespace math_proj  = math::proj;
  namespace math_opt   = math::optimize;

};

namespace tl_math       = tloc::math;
namespace tl_math_err   = tloc::math::error;
namespace tl_math_cs    = tloc::math::component_system;
namespace tl_math_stat  = tloc::math::statistics;
namespace tl_math_t     = tloc::math::types;
namespace tl_math_utils = tloc::math::utils;
namespace tl_math_proj  = tloc::math::proj;
namespace tl_math_opt   = tloc::math::optimize;

#include <tlocCore/logging/tlocLoggerHelper.h>

TLOC_FORWARD_DECLARE_LOGGER_CONSOLE_IMMEDIATE_DEFAULT();

// -----------------------------------------------------------------------
// math's default logger
namespace tloc { namespace math {

  TLOC_LOGGER_DECLARE_LOGGER_FUNC_CONSOLE_IMMEDIATE_DEFAULT(GetLogger);

};};

#define TLOC_LOG_MATH_INFO()    TLOC_LOG_INFO(&tloc::math::GetLogger())
#define TLOC_LOG_MATH_SUCCESS() TLOC_LOG_SUCCESS(&tloc::math::GetLogger())
#define TLOC_LOG_MATH_DEBUG()   TLOC_LOG_DEBUG(&tloc::math::GetLogger())
#define TLOC_LOG_MATH_WARN()    TLOC_LOG_WARN(&tloc::math::GetLogger())
#define TLOC_LOG_MATH_ERR()     TLOC_LOG_ERR(&tloc::math::GetLogger())

#define TLOC_LOG_MATH_INFO_IF(_expr_)    TLOC_LOG_INFO_IF(_expr_, &tloc::math::GetLogger())
#define TLOC_LOG_MATH_SUCCESS_IF(_expr_) TLOC_LOG_SUCCESS_IF(_expr_, &tloc::math::GetLogger())
#define TLOC_LOG_MATH_DEBUG_IF(_expr_)   TLOC_LOG_DEBUG_IF(_expr_, &tloc::math::GetLogger())
#define TLOC_LOG_MATH_WARN_IF(_expr_)    TLOC_LOG_WARN_IF(_expr_, &tloc::math::GetLogger())
#define TLOC_LOG_MATH_ERR_IF(_expr_)     TLOC_LOG_ERR_IF(_expr_, &tloc::math::GetLogger())

#define TLOC_LOG_MATH_INFO_FILENAME_ONLY()    TLOC_LOG_INFO_FILENAME_ONLY(&tloc::math::GetLogger())
#define TLOC_LOG_MATH_SUCCESS_FILENAME_ONLY() TLOC_LOG_SUCCESS_FILENAME_ONLY(&tloc::math::GetLogger())
#define TLOC_LOG_MATH_DEBUG_FILENAME_ONLY()   TLOC_LOG_DEBUG_FILENAME_ONLY(&tloc::math::GetLogger())
#define TLOC_LOG_MATH_WARN_FILENAME_ONLY()    TLOC_LOG_WARN_FILENAME_ONLY(&tloc::math::GetLogger())
#define TLOC_LOG_MATH_ERR_FILENAME_ONLY()     TLOC_LOG_ERR_FILENAME_ONLY(&tloc::math::GetLogger())

#define TLOC_LOG_MATH_INFO_FILENAME_ONLY_IF(_expr_)    TLOC_LOG_INFO_FILENAME_ONLY_IF(_expr_, &tloc::math::GetLogger())
#define TLOC_LOG_MATH_SUCCESS_FILENAME_ONLY_IF(_expr_) TLOC_LOG_SUCCESS_FILENAME_ONLY_IF(_expr_, &tloc::math::GetLogger())
#define TLOC_LOG_MATH_DEBUG_FILENAME_ONLY_IF(_expr_)   TLOC_LOG_DEBUG_FILENAME_ONLY_IF(_expr_, &tloc::math::GetLogger())
#define TLOC_LOG_MATH_WARN_FILENAME_ONLY_IF(_expr_)    TLOC_LOG_WARN_FILENAME_ONLY_IF(_expr_, &tloc::math::GetLogger())
#define TLOC_LOG_MATH_ERR_FILENAME_ONLY_IF(_expr_)     TLOC_LOG_ERR_FILENAME_ONLY_IF(_expr_, &tloc::math::GetLogger())

#define TLOC_LOG_MATH_INFO_NO_FILENAME()    TLOC_LOG_INFO_NO_FILENAME(&tloc::math::GetLogger())
#define TLOC_LOG_MATH_SUCCESS_NO_FILENAME() TLOC_LOG_SUCCESS_NO_FILENAME(&tloc::math::GetLogger())
#define TLOC_LOG_MATH_DEBUG_NO_FILENAME()   TLOC_LOG_DEBUG_NO_FILENAME(&tloc::math::GetLogger())
#define TLOC_LOG_MATH_WARN_NO_FILENAME()    TLOC_LOG_WARN_NO_FILENAME(&tloc::math::GetLogger())
#define TLOC_LOG_MATH_ERR_NO_FILENAME()     TLOC_LOG_ERR_NO_FILENAME(&tloc::math::GetLogger())

#define TLOC_LOG_MATH_INFO_NO_FILENAME_IF(_expr_)    TLOC_LOG_INFO_NO_FILENAME_IF(_expr_, &tloc::math::GetLogger())
#define TLOC_LOG_MATH_SUCCESS_NO_FILENAME_IF(_expr_) TLOC_LOG_SUCCESS_NO_FILENAME_IF(_expr_, &tloc::math::GetLogger())
#define TLOC_LOG_MATH_DEBUG_NO_FILENAME_IF(_expr_)   TLOC_LOG_DEBUG_NO_FILENAME_IF(_expr_, &tloc::math::GetLogger())
#define TLOC_LOG_MATH_WARN_NO_FILENAME_IF(_expr_)    TLOC_LOG_WARN_NO_FILENAME_IF(_expr_, &tloc::math::GetLogger())
#define TLOC_LOG_MATH_ERR_NO_FILENAME_IF(_expr_)     TLOC_LOG_ERR_NO_FILENAME_IF(_expr_, &tloc::math::GetLogger())


#endif
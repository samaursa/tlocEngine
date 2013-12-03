#ifndef _TLOC_MATH_BASE_H_
#define _TLOC_MATH_BASE_H_

#include <tlocCore/tlocBase.h>

// All major namespaces that math uses should go here

namespace tloc {

  //////////////////////////////////////////////////////////////////////////
  // Complete namespace here

  namespace math
  {
    namespace component_system {};
    namespace types            {};
    namespace utils            {};
    namespace proj             {};
  };

  //////////////////////////////////////////////////////////////////////////
  // Namespace aliases here

  namespace math_cs    = math::component_system;
  namespace math_t     = math::types;
  namespace math_utils = math::utils;
  namespace math_proj  = math::proj;

};

#include <tlocCore/logger/tlocLoggerHelper.h>

TLOC_FORWARD_DECLARE_LOGGER_CONSOLE_IMMEDIATE_DEFAULT();

// -----------------------------------------------------------------------
// math's default logger
namespace tloc { namespace math {

  TLOC_LOGGER_DECLARE_LOGGER_FUNC_CONSOLE_IMMEDIATE_DEFAULT(GetLogger);

};};

#define TLOC_LOG_MATH_INFO()    TLOC_LOG_INFO(&tloc::math::GetLogger())
#define TLOC_LOG_MATH_DEBUG()   TLOC_LOG_DEBUG(&tloc::math::GetLogger())
#define TLOC_LOG_MATH_WARN()    TLOC_LOG_WARN(&tloc::math::GetLogger())
#define TLOC_LOG_MATH_ERR()     TLOC_LOG_ERR(&tloc::math::GetLogger())


#endif
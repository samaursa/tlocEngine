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
  };

  //////////////////////////////////////////////////////////////////////////
  // Namespace aliases here

  namespace anim          = animation;
  namespace anim_cs       = animation::component_system;
  namespace anim_err      = animation::error;
  namespace anim_t        = animation::types;

};

#include <tlocCore/logging/tlocLoggerHelper.h>

TLOC_FORWARD_DECLARE_LOGGER_CONSOLE_IMMEDIATE_DEFAULT();

// -----------------------------------------------------------------------
// animation's default logger
namespace tloc { namespace animation {

  TLOC_LOGGER_DECLARE_LOGGER_FUNC_CONSOLE_IMMEDIATE_DEFAULT(GetLogger);

};};

#define TLOC_LOG_ANIM_INFO()    TLOC_LOG_INFO(&tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_DEBUG()   TLOC_LOG_DEBUG(&tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_WARN()    TLOC_LOG_WARN(&tloc::animation::GetLogger())
#define TLOC_LOG_ANIM_ERR()     TLOC_LOG_ERR(&tloc::animation::GetLogger())

#endif
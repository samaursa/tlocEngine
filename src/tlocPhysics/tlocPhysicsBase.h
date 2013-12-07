#ifndef _TLOC_PHYSICS_BASE_H_
#define _TLOC_PHYSICS_BASE_H_

#include <tlocCore/tlocBase.h>

// All major namespaces that physics uses should go here

namespace tloc {

  //////////////////////////////////////////////////////////////////////////
  // Complete namespace here

  namespace physics
  {
    namespace box2d            {};
    namespace component_system {};
    namespace error            {};
  };

  //////////////////////////////////////////////////////////////////////////
  // Namespace aliases here

  namespace phys_box2d = physics::box2d;
  namespace phys_cs    = physics::component_system;
  namespace phys_err   = physics::error;

};

#include <tlocCore/logging/tlocLoggerHelper.h>

TLOC_FORWARD_DECLARE_LOGGER_CONSOLE_IMMEDIATE_DEFAULT();

// -----------------------------------------------------------------------
// physics's default logger
namespace tloc { namespace physics {

  TLOC_LOGGER_DECLARE_LOGGER_FUNC_CONSOLE_IMMEDIATE_DEFAULT(GetLogger);

};};

#define TLOC_LOG_PHYS_INFO()    TLOC_LOG_INFO(&tloc::physics::GetLogger())
#define TLOC_LOG_PHYS_DEBUG()   TLOC_LOG_DEBUG(&tloc::physics::GetLogger())
#define TLOC_LOG_PHYS_WARN()    TLOC_LOG_WARN(&tloc::physics::GetLogger())
#define TLOC_LOG_PHYS_ERR()     TLOC_LOG_ERR(&tloc::physics::GetLogger())

#define TLOC_LOG_PHYS_INFO_IF(_expr_)    TLOC_LOG_INFO_IF(_expr_, &tloc::physics::GetLogger())
#define TLOC_LOG_PHYS_DEBUG_IF(_expr_)   TLOC_LOG_DEBUG_IF(_expr_, &tloc::physics::GetLogger())
#define TLOC_LOG_PHYS_WARN_IF(_expr_)    TLOC_LOG_WARN_IF(_expr_, &tloc::physics::GetLogger())
#define TLOC_LOG_PHYS_ERR_IF(_expr_)     TLOC_LOG_ERR_IF(_expr_, &tloc::physics::GetLogger())

#define TLOC_LOG_PHYS_INFO_FILENAME_ONLY()    TLOC_LOG_INFO_FILENAME_ONLY(&tloc::physics::GetLogger())
#define TLOC_LOG_PHYS_DEBUG_FILENAME_ONLY()   TLOC_LOG_DEBUG_FILENAME_ONLY(&tloc::physics::GetLogger())
#define TLOC_LOG_PHYS_WARN_FILENAME_ONLY()    TLOC_LOG_WARN_FILENAME_ONLY(&tloc::physics::GetLogger())
#define TLOC_LOG_PHYS_ERR_FILENAME_ONLY()     TLOC_LOG_ERR_FILENAME_ONLY(&tloc::physics::GetLogger())

#define TLOC_LOG_PHYS_INFO_FILENAME_ONLY_IF(_expr_)    TLOC_LOG_INFO_FILENAME_ONLY_IF(_expr_, &tloc::physics::GetLogger())
#define TLOC_LOG_PHYS_DEBUG_FILENAME_ONLY_IF(_expr_)   TLOC_LOG_DEBUG_FILENAME_ONLY_IF(_expr_, &tloc::physics::GetLogger())
#define TLOC_LOG_PHYS_WARN_FILENAME_ONLY_IF(_expr_)    TLOC_LOG_WARN_FILENAME_ONLY_IF(_expr_, &tloc::physics::GetLogger())
#define TLOC_LOG_PHYS_ERR_FILENAME_ONLY_IF(_expr_)     TLOC_LOG_ERR_FILENAME_ONLY_IF(_expr_, &tloc::physics::GetLogger())

#define TLOC_LOG_PHYS_INFO_NO_FILENAME()    TLOC_LOG_INFO_NO_FILENAME(&tloc::physics::GetLogger())
#define TLOC_LOG_PHYS_DEBUG_NO_FILENAME()   TLOC_LOG_DEBUG_NO_FILENAME(&tloc::physics::GetLogger())
#define TLOC_LOG_PHYS_WARN_NO_FILENAME()    TLOC_LOG_WARN_NO_FILENAME(&tloc::physics::GetLogger())
#define TLOC_LOG_PHYS_ERR_NO_FILENAME()     TLOC_LOG_ERR_NO_FILENAME(&tloc::physics::GetLogger())

#define TLOC_LOG_PHYS_INFO_NO_FILENAME_IF(_expr_)    TLOC_LOG_INFO_NO_FILENAME_IF(_expr_, &tloc::physics::GetLogger())
#define TLOC_LOG_PHYS_DEBUG_NO_FILENAME_IF(_expr_)   TLOC_LOG_DEBUG_NO_FILENAME_IF(_expr_, &tloc::physics::GetLogger())
#define TLOC_LOG_PHYS_WARN_NO_FILENAME_IF(_expr_)    TLOC_LOG_WARN_NO_FILENAME_IF(_expr_, &tloc::physics::GetLogger())
#define TLOC_LOG_PHYS_ERR_NO_FILENAME_IF(_expr_)     TLOC_LOG_ERR_NO_FILENAME_IF(_expr_, &tloc::physics::GetLogger())


#endif
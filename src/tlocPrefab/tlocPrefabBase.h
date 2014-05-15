#ifndef _TLOC_PREFAB_BASE_H_
#define _TLOC_PREFAB_BASE_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/error/tlocError.h>

// All major namespaces that prefab uses should go here

namespace tloc {

  // ///////////////////////////////////////////////////////////////////////
  // Complete namespace here

  namespace prefab
  {
    namespace core      {};
    namespace graphics  {};
    namespace input     {};
    namespace math      {};
    namespace physics   {};
    namespace animation {};
  };

  // ///////////////////////////////////////////////////////////////////////
  // Namespace aliases here

  namespace pref_core   = prefab::core;
  namespace pref_math   = prefab::math;
  namespace pref_gfx    = prefab::graphics;
  namespace pref_input  = prefab::input;
  namespace pref_phys   = prefab::physics;
  namespace pref_anim   = prefab::animation;

  // ///////////////////////////////////////////////////////////////////////
  // Base for all prefab objects

  class Prefab_I
    : core_bclass::NonCopyable_I
  {
  public:
    typedef core_cs::entity_manager_vptr      entity_mgr_ptr;
    typedef core_cs::component_pool_mgr_vptr  comp_pool_mgr_ptr;
    typedef core_cs::Entity                   entity_type;
    typedef core_cs::entity_vptr              entity_ptr;
    typedef core_err::Error                   error_type;

  protected:
    Prefab_I(entity_mgr_ptr  a_entMgr, comp_pool_mgr_ptr a_poolMgr)
             : m_entMgr(a_entMgr)
             , m_compPoolMgr(a_poolMgr)
    { }

  protected:
    entity_mgr_ptr          m_entMgr;
    comp_pool_mgr_ptr       m_compPoolMgr;
  };

};

#include <tlocCore/logging/tlocLoggerHelper.h>

TLOC_FORWARD_DECLARE_LOGGER_CONSOLE_IMMEDIATE_DEFAULT();

// -----------------------------------------------------------------------
// prefab's default logger
namespace tloc { namespace prefab {

  TLOC_LOGGER_DECLARE_LOGGER_FUNC_CONSOLE_IMMEDIATE_DEFAULT(GetLogger);

};};

#define TLOC_LOG_PREF_INFO()    TLOC_LOG_INFO(&tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_SUCCESS() TLOC_LOG_SUCCESS(&tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_DEBUG()   TLOC_LOG_DEBUG(&tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_WARN()    TLOC_LOG_WARN(&tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_ERR()     TLOC_LOG_ERR(&tloc::prefab::GetLogger())

#define TLOC_LOG_PREF_INFO_IF(_expr_)    TLOC_LOG_INFO_IF(_expr_, &tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_SUCCESS_IF(_expr_) TLOC_LOG_SUCCESS_IF(_expr_, &tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_DEBUG_IF(_expr_)   TLOC_LOG_DEBUG_IF(_expr_, &tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_WARN_IF(_expr_)    TLOC_LOG_WARN_IF(_expr_, &tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_ERR_IF(_expr_)     TLOC_LOG_ERR_IF(_expr_, &tloc::prefab::GetLogger())

#define TLOC_LOG_PREF_INFO_FILENAME_ONLY()    TLOC_LOG_INFO_FILENAME_ONLY(&tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_SUCCESS_FILENAME_ONLY() TLOC_LOG_SUCCESS_FILENAME_ONLY(&tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_DEBUG_FILENAME_ONLY()   TLOC_LOG_DEBUG_FILENAME_ONLY(&tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_WARN_FILENAME_ONLY()    TLOC_LOG_WARN_FILENAME_ONLY(&tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_ERR_FILENAME_ONLY()     TLOC_LOG_ERR_FILENAME_ONLY(&tloc::prefab::GetLogger())

#define TLOC_LOG_PREF_INFO_FILENAME_ONLY_IF(_expr_)    TLOC_LOG_INFO_FILENAME_ONLY_IF(_expr_, &tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_SUCCESS_FILENAME_ONLY_IF(_expr_) TLOC_LOG_SUCCESS_FILENAME_ONLY_IF(_expr_, &tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_DEBUG_FILENAME_ONLY_IF(_expr_)   TLOC_LOG_DEBUG_FILENAME_ONLY_IF(_expr_, &tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_WARN_FILENAME_ONLY_IF(_expr_)    TLOC_LOG_WARN_FILENAME_ONLY_IF(_expr_, &tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_ERR_FILENAME_ONLY_IF(_expr_)     TLOC_LOG_ERR_FILENAME_ONLY_IF(_expr_, &tloc::prefab::GetLogger())

#define TLOC_LOG_PREF_INFO_NO_FILENAME()    TLOC_LOG_INFO_NO_FILENAME(&tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_SUCCESS_NO_FILENAME() TLOC_LOG_SUCCESS_NO_FILENAME(&tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_DEBUG_NO_FILENAME()   TLOC_LOG_DEBUG_NO_FILENAME(&tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_WARN_NO_FILENAME()    TLOC_LOG_WARN_NO_FILENAME(&tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_ERR_NO_FILENAME()     TLOC_LOG_ERR_NO_FILENAME(&tloc::prefab::GetLogger())

#define TLOC_LOG_PREF_INFO_NO_FILENAME_IF(_expr_)    TLOC_LOG_INFO_NO_FILENAME_IF(_expr_, &tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_SUCCESS_NO_FILENAME_IF(_expr_) TLOC_LOG_SUCCESS_NO_FILENAME_IF(_expr_, &tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_DEBUG_NO_FILENAME_IF(_expr_)   TLOC_LOG_DEBUG_NO_FILENAME_IF(_expr_, &tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_WARN_NO_FILENAME_IF(_expr_)    TLOC_LOG_WARN_NO_FILENAME_IF(_expr_, &tloc::prefab::GetLogger())
#define TLOC_LOG_PREF_ERR_NO_FILENAME_IF(_expr_)     TLOC_LOG_ERR_NO_FILENAME_IF(_expr_, &tloc::prefab::GetLogger())

#endif
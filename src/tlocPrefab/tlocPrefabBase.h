#ifndef _TLOC_PREFAB_BASE_H_
#define _TLOC_PREFAB_BASE_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/error/tlocError.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>

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

  template <typename T_Derived, typename T_ComponentType>
  class Prefab_TI
    : public core_bclass::PolicyBase_TI<T_Derived>
  {
  public:
    typedef core_bclass::PolicyBase_TI<T_Derived>         base_type;
    typedef typename base_type::derived_type              derived_type;

    typedef T_ComponentType                               component_type;
    typedef core_sptr::SharedPtr<component_type>          component_ptr;
    typedef Prefab_TI<derived_type, component_type>       this_type;

    typedef core_cs::EventManager::listeners_list         listeners_cont;
    typedef core_cs::EventManager::listener_ptr           listener_ptr;
    typedef core_cs::EntityManager::Params                insert_params;

    typedef core_cs::entity_manager_vptr                  entity_mgr_ptr;
    typedef core_cs::component_pool_mgr_vptr              comp_pool_mgr_ptr;
    typedef core_cs::Entity                               entity_type;
    typedef core_cs::entity_vptr                          entity_ptr;
    typedef core_err::Error                               error_type;

  public:
    derived_type& DispatchTo(listener_ptr a_system)
    { m_listeners.push_back(a_system); return *This(); }

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(listeners_cont, GetListeners, m_listeners);

  protected:
    Prefab_TI(entity_mgr_ptr  a_entMgr, comp_pool_mgr_ptr  a_poolMgr)
      : m_entMgr(a_entMgr)
      , m_compPoolMgr(a_poolMgr)
    { }

    using base_type::This;

  protected:
    entity_mgr_ptr          m_entMgr;
    comp_pool_mgr_ptr       m_compPoolMgr;
    listeners_cont          m_listeners;
  };

};

namespace tl_pref        = tloc::prefab;
namespace tl_pref_core   = tloc::prefab::core;
namespace tl_pref_math   = tloc::prefab::math;
namespace tl_pref_gfx    = tloc::prefab::graphics;
namespace tl_pref_input  = tloc::prefab::input;
namespace tl_pref_phys   = tloc::prefab::physics;
namespace tl_pref_anim   = tloc::prefab::animation;

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
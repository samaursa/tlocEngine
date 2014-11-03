#ifndef _TLOC_CORE_COMPONENT_SYSTEM_ECS_H_
#define _TLOC_CORE_COMPONENT_SYSTEM_ECS_H_

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/component_system/tlocSystemsProcessor.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/utilities/tlocContainerUtils.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

namespace tloc { namespace core { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // ECS - the class that wraps most of the ECS in the engine

  class ECS
    : public core_bclass::DebugName
  {
  public:
    typedef ECS                                         this_type;
    typedef systems_processor_vso                       sys_processor_vso;
    typedef systems_processor_vptr                      sys_processor_ptr;

    typedef event_manager_vso                           event_manager_vso;
    typedef entity_manager_vso                          entity_manager_vso;
    typedef component_pool_mgr_vso                      component_pool_manager_vso;

    typedef event_manager_vptr                          event_manager_ptr;
    typedef entity_manager_vptr                         entity_manager_ptr;
    typedef component_pool_mgr_vptr                     component_pool_manager_ptr;

    typedef core_conts::Array<entity_system_base_vptr>  systems_cont;

  public:
    ECS(BufferArg a_debugName = "ECS");

  public: // system construction - no need to pass in event and entity managers. 
          // that is done automatically

    template <typename T_System>
    core_sptr::VirtualPtr<T_System> 
      AddSystem();

    template <typename T_System, 
              typename T1>
    core_sptr::VirtualPtr<T_System> 
      AddSystem(const Args<T1>& a_param);

    template <typename T_System, 
              typename T1, typename T2>
    core_sptr::VirtualPtr<T_System> 
      AddSystem(const Args<T1, T2>& a_param);

    template <typename T_System, 
              typename T1, typename T2, typename T3>
    core_sptr::VirtualPtr<T_System> 
      AddSystem(const Args<T1, T2, T3>& a_param);
    
    template <typename T_System, 
              typename T1, typename T2, typename T3, typename T4>
    core_sptr::VirtualPtr<T_System> 
      AddSystem(const Args<T1, T2, T3, T4>& a_param);

    template <typename T_System, 
              typename T1, typename T2, typename T3, typename T4, typename T5>
    core_sptr::VirtualPtr<T_System> 
      AddSystem(const Args<T1, T2, T3, T4, T5>& a_param);

  public: // prefab construction

    template <typename T_Prefab>
    T_Prefab
      CreatePrefab();

    template <typename T_Prefab, 
              typename T1>
    T_Prefab
      CreatePrefab(const Args<T1>& a_param);

    template <typename T_Prefab, 
              typename T1, typename T2>
    T_Prefab
      CreatePrefab(const Args<T1, T2>& a_param);

    template <typename T_Prefab, 
              typename T1, typename T2, typename T3>
    T_Prefab
      CreatePrefab(const Args<T1, T2, T3>& a_param);
    
    template <typename T_Prefab, 
              typename T1, typename T2, typename T3, typename T4>
    T_Prefab
      CreatePrefab(const Args<T1, T2, T3, T4>& a_param);

    template <typename T_Prefab, 
              typename T1, typename T2, typename T3, typename T4, typename T5>
    T_Prefab
      CreatePrefab(const Args<T1, T2, T3, T4, T5>& a_param);

  public:
    TLOC_DECL_AND_DEF_GETTER_NON_CONST
      (sys_processor_ptr, GetSystemsProcessor, m_sysProcessor.get());

    TLOC_DECL_AND_DEF_GETTER_NON_CONST
      (event_manager_ptr, GetEventManager, m_eventMgr.get());
    TLOC_DECL_AND_DEF_GETTER_NON_CONST
      (entity_manager_ptr, GetEntityManager, m_entMgr.get());
    TLOC_DECL_AND_DEF_GETTER_NON_CONST
      (component_pool_manager_ptr, GetComponentPoolManager, m_compPoolMgr.get());

  private:
    component_pool_manager_vso  m_compPoolMgr;
    event_manager_vso           m_eventMgr;
    entity_manager_vso          m_entMgr;

    systems_cont                m_systems;
    sys_processor_vso           m_sysProcessor;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_System>
  core_sptr::VirtualPtr<T_System> 
    ECS::
    AddSystem()
  { 
    core_sptr::VirtualPtr<T_System> sys(new T_System(m_eventMgr, m_entMgr));
    m_systems.push_back(sys);
    return sys;
  }

  template <typename T_System, 
            typename T1>
  core_sptr::VirtualPtr<T_System> 
  ECS::
    AddSystem(const Args<T1>& a_param)
  { 
    core_sptr::VirtualPtr<T_System> sys
      (new T_System(m_eventMgr, m_entMgr, a_param.m_arg1));
    m_systems.push_back(sys);
    return sys;
  }

  template <typename T_System, 
            typename T1, typename T2>
  core_sptr::VirtualPtr<T_System> 
  ECS::
    AddSystem(const Args<T1, T2>& a_param)
  { 
    core_sptr::VirtualPtr<T_System> sys
      (new T_System(m_eventMgr, m_entMgr, a_param.m_arg1, a_param.m_arg2));
    m_systems.push_back(sys);
    return sys;
  }

  template <typename T_System, 
            typename T1, typename T2, typename T3>
  core_sptr::VirtualPtr<T_System> 
  ECS::
    AddSystem(const Args<T1, T2, T3>& a_param)
  { 
    core_sptr::VirtualPtr<T_System> sys
      (new T_System(m_eventMgr, m_entMgr, 
                    a_param.m_arg1, a_param.m_arg2, a_param.m_arg3));
    m_systems.push_back(sys);
    return sys;
  }
  
  template <typename T_System, 
            typename T1, typename T2, typename T3, typename T4>
  core_sptr::VirtualPtr<T_System> 
  ECS::
    AddSystem(const Args<T1, T2, T3, T4>& a_param)
  { 
    core_sptr::VirtualPtr<T_System> sys
      (new T_System(m_eventMgr, m_entMgr, 
                    a_param.m_arg1, a_param.m_arg2, a_param.m_arg3, 
                    a_param.m_arg4));
    m_systems.push_back(sys);
    return sys;
  }

  template <typename T_System, 
            typename T1, typename T2, typename T3, typename T4, typename T5>
  core_sptr::VirtualPtr<T_System> 
  ECS::
    AddSystem(const Args<T1, T2, T3, T4, T5>& a_param)
  { 
    core_sptr::VirtualPtr<T_System> sys
      (new T_System(m_eventMgr, m_entMgr, 
                    a_param.m_arg1, a_param.m_arg2, a_param.m_arg3, 
                    a_param.m_arg4, a_param.m_arg5));
    m_systems.push_back(sys);
    return sys;
  }

  // -----------------------------------------------------------------------
  // typedefs


};};};

#endif
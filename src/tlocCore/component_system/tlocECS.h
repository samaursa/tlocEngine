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
    typedef SystemsProcessor::time_type                 time_type;

    typedef event_manager_vso                           event_manager_vso;
    typedef entity_manager_vso                          entity_manager_vso;
    typedef component_pool_mgr_vso                      component_pool_manager_vso;

    typedef event_manager_vptr                          event_manager_ptr;
    typedef entity_manager_vptr                         entity_manager_ptr;
    typedef component_pool_mgr_vptr                     component_pool_manager_ptr;

    typedef core_conts::Array<entity_system_base_uptr>  systems_cont;

  public:
    ECS(BufferArg a_debugName = "ECS");
    virtual ~ECS();

  public: // system construction - no need to pass in event and entity managers. 
          // that is done automatically

    template <typename T_System>
    core_sptr::VirtualPtr<T_System> 
      AddSystem(bool a_processManually = false);

    template <typename T_System, 
              typename T1>
    core_sptr::VirtualPtr<T_System> 
      AddSystem(const Args<T1>& a_param, bool a_processManually = false);

    template <typename T_System, 
              typename T1, typename T2>
    core_sptr::VirtualPtr<T_System> 
      AddSystem(const Args<T1, T2>& a_param, bool a_processManually = false);

    template <typename T_System, 
              typename T1, typename T2, typename T3>
    core_sptr::VirtualPtr<T_System> 
      AddSystem(const Args<T1, T2, T3>& a_param, bool a_processManually = false);
    
    template <typename T_System, 
              typename T1, typename T2, typename T3, typename T4>
    core_sptr::VirtualPtr<T_System> 
      AddSystem(const Args<T1, T2, T3, T4>& a_param,
                bool a_processManually = false);

    template <typename T_System, 
              typename T1, typename T2, typename T3, typename T4, typename T5>
    core_sptr::VirtualPtr<T_System> 
      AddSystem(const Args<T1, T2, T3, T4, T5>& a_param, 
                bool a_processManually = false);

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
    void  Initialize();
    void  Update();
    void  Process(time_type a_deltaT);

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
    AddSystem(bool a_processManually)
  { 
    core_sptr::UniquePtr<T_System> sys = 
      core_sptr::MakeUnique<T_System>(m_eventMgr.get(), m_entMgr.get());

    auto sysPtr = core_sptr::ToVirtualPtr(sys);

    m_systems.push_back(core_sptr::static_pointer_cast<EntitySystemBase>(sys));
    if (!a_processManually) { m_sysProcessor->Add(sysPtr); }

    return sysPtr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_System, 
            typename T1>
  core_sptr::VirtualPtr<T_System> 
  ECS::
    AddSystem(const Args<T1>& a_param, bool a_processManually)
  { 
    core_sptr::UniquePtr<T_System> sys = 
      core_sptr::MakeUnique<T_System>(m_eventMgr.get(), m_entMgr.get(), a_param.m_arg1);

    auto sysPtr = core_sptr::ToVirtualPtr(sys);

    m_systems.push_back(core_sptr::static_pointer_cast<EntitySystemBase>(sys));
    if (!a_processManually) { m_sysProcessor->Add(sysPtr); }

    return sysPtr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_System, 
            typename T1, typename T2>
  core_sptr::VirtualPtr<T_System> 
  ECS::
    AddSystem(const Args<T1, T2>& a_param, bool a_processManually)
  { 
    core_sptr::UniquePtr<T_System> sys = 
      core_sptr::MakeUnique<T_System>(m_eventMgr.get(), m_entMgr.get(), 
      a_param.m_arg1, a_param.m_arg2);

    auto sysPtr = core_sptr::ToVirtualPtr(sys);

    m_systems.push_back(core_sptr::static_pointer_cast<EntitySystemBase>(sys));
    m_sysProcessor->Add(sysPtr);

    return sysPtr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_System, 
            typename T1, typename T2, typename T3>
  core_sptr::VirtualPtr<T_System> 
  ECS::
    AddSystem(const Args<T1, T2, T3>& a_param, bool a_processManually)
  { 
    core_sptr::UniquePtr<T_System> sys = 
      core_sptr::MakeUnique<T_System>(m_eventMgr.get(), m_entMgr.get(), 
      a_param.m_arg1, a_param.m_arg2, a_param.m_arg3);

    auto sysPtr = core_sptr::ToVirtualPtr(sys);

    m_systems.push_back(core_sptr::static_pointer_cast<EntitySystemBase>(sys));
    if (!a_processManually) { m_sysProcessor->Add(sysPtr); }

    return sysPtr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  
  template <typename T_System, 
            typename T1, typename T2, typename T3, typename T4>
  core_sptr::VirtualPtr<T_System> 
  ECS::
    AddSystem(const Args<T1, T2, T3, T4>& a_param, bool a_processManually)
  { 
    core_sptr::UniquePtr<T_System> sys = 
      core_sptr::MakeUnique<T_System>(m_eventMgr.get(), m_entMgr.get(), 
      a_param.m_arg1, a_param.m_arg2, a_param.m_arg3, a_param.m_arg4);

    auto sysPtr = core_sptr::ToVirtualPtr(sys);

    m_systems.push_back(core_sptr::static_pointer_cast<EntitySystemBase>(sys));
    if (!a_processManually) { m_sysProcessor->Add(sysPtr); }

    return sysPtr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_System, 
            typename T1, typename T2, typename T3, typename T4, typename T5>
  core_sptr::VirtualPtr<T_System> 
  ECS::
    AddSystem(const Args<T1, T2, T3, T4, T5>& a_param, bool a_processManually)
  { 
    core_sptr::UniquePtr<T_System> sys = 
      core_sptr::MakeUnique<T_System>(m_eventMgr.get(), m_entMgr.get(), 
      a_param.m_arg1, a_param.m_arg2, a_param.m_arg3, a_param.m_arg4,
      a_param.m_arg5);

    auto sysPtr = core_sptr::ToVirtualPtr(sys);

    m_systems.push_back(core_sptr::static_pointer_cast<EntitySystemBase>(sys));
    if (!a_processManually) { m_sysProcessor->Add(sysPtr); }

    return sysPtr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Prefab>
  T_Prefab
    ECS::
    CreatePrefab()
  { 
    T_Prefab pref(m_entMgr.get(), m_compPoolMgr.get());
    return pref;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Prefab, 
            typename T1>
  T_Prefab
  ECS::
    CreatePrefab(const Args<T1>& a_param)
  { 
    T_Prefab pref(m_entMgr.get(), m_compPoolMgr.get(), a_param.m_arg1);
    return pref;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Prefab, 
            typename T1, typename T2>
  T_Prefab
  ECS::
    CreatePrefab(const Args<T1, T2>& a_param)
  { 
    T_Prefab pref(m_entMgr.get(), m_compPoolMgr.get(), 
                  a_param.m_arg1, a_param.m_args2);
    return pref;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Prefab, 
            typename T1, typename T2, typename T3>
  T_Prefab
  ECS::
    CreatePrefab(const Args<T1, T2, T3>& a_param)
  { 
    T_Prefab pref(m_entMgr.get(), m_compPoolMgr.get(), 
                  a_param.m_arg1, a_param.m_args2, a_param.m_arg3);
    return pref;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  
  template <typename T_Prefab, 
            typename T1, typename T2, typename T3, typename T4>
  T_Prefab
  ECS::
    CreatePrefab(const Args<T1, T2, T3, T4>& a_param)
  { 
    T_Prefab pref(m_entMgr.get(), m_compPoolMgr.get(), 
                  a_param.m_arg1, a_param.m_args2, a_param.m_arg3, 
                  a_param.m_arg4);
    return pref;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Prefab, 
            typename T1, typename T2, typename T3, typename T4, typename T5>
  T_Prefab
  ECS::
    CreatePrefab(const Args<T1, T2, T3, T4, T5>& a_param)
  { 
    T_Prefab pref(m_entMgr.get(), m_compPoolMgr.get(), 
                  a_param.m_arg1, a_param.m_args2, a_param.m_arg3, 
                  a_param.m_arg4, a_param.m_arg5);
    return pref;
  }

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(ECS, ecs);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(ECS, ecs);

};};};

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::core_cs::ECS);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(tloc::core_cs::ECS);

#endif
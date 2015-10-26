#ifndef _TLOC_CORE_COMPONENT_SYSTEM_ECS_H_
#define _TLOC_CORE_COMPONENT_SYSTEM_ECS_H_

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/time/tlocTime.h>
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
    typedef SystemsProcessor::sys_info_iterator         sys_info_itr;

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
      AddSystem(time_type a_deltaT = 1.0/60.0, bool a_processManually = false);

    template <typename T_System, typename... T_Args>
    core_sptr::VirtualPtr<T_System> 
      AddSystem(T_Args&&... a_args, time_type a_deltaT = 1.0/60.0, 
                bool a_processManually = false);

    template <typename T_ComponentPtr>
    void 
      InsertComponent(core_cs::entity_vptr a_ent, T_ComponentPtr a_comp);

  public: // prefab construction

    template <typename T_Prefab, typename... T_Args>
    T_Prefab
      CreatePrefab(T_Args&&... a_args);

  public:
    void  Initialize();
    void  Update();
    void  Process(time_type a_deltaT = 1.0/60.0);
    void  RecycleAllUnusedComponents();

  public:
    TLOC_DECL_AND_DEF_GETTER_NON_CONST
      (sys_processor_ptr, GetSystemsProcessor, m_sysProcessor.get());

    TLOC_DECL_AND_DEF_GETTER_NON_CONST
      (event_manager_ptr, GetEventManager, m_eventMgr.get());
    TLOC_DECL_AND_DEF_GETTER_NON_CONST
      (entity_manager_ptr, GetEntityManager, m_entMgr.get());
    TLOC_DECL_AND_DEF_GETTER_NON_CONST
      (component_pool_manager_ptr, GetComponentPoolManager, m_compPoolMgr.get());

    TLOC_DECL_AND_DEF_GETTER(time_type, SetRecycleDeltaT, m_autoRecycleDeltaT);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN
      (time_type, SetRecycleDeltaT, m_autoRecycleDeltaT);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN
      (bool, SetAutoRecycleUnusedComponents, m_autoRecycleUnusedComponents);

  private:
    component_pool_manager_vso  m_compPoolMgr;
    event_manager_vso           m_eventMgr;
    entity_manager_vso          m_entMgr;

    systems_cont                m_systems;
    sys_processor_vso           m_sysProcessor;

    time_type                   m_autoRecycleDeltaT;
    time_type                   m_autoRecycleTimer;
    bool                        m_autoRecycleUnusedComponents;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_System>
  core_sptr::VirtualPtr<T_System> 
    ECS::
    AddSystem(time_type a_deltaT, bool a_processManually)
  {
    core_sptr::UniquePtr<T_System> sys = 
      core_sptr::MakeUnique<T_System>(m_eventMgr.get(), m_entMgr.get());

    auto sysPtr = core_sptr::ToVirtualPtr(sys);

    m_systems.push_back(core_sptr::static_pointer_cast<EntitySystemBase>(sys));
    if (!a_processManually) { m_sysProcessor->Add(sysPtr, a_deltaT); }

    return sysPtr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_System, typename... T_Args>
  core_sptr::VirtualPtr<T_System> 
    ECS::
    AddSystem(T_Args&&... a_args, time_type a_deltaT, bool a_processManually)
  { 
    core_sptr::UniquePtr<T_System> sys = 
      core_sptr::MakeUnique<T_System>(m_eventMgr.get(), m_entMgr.get(), Forward(a_args)...);

    auto sysPtr = core_sptr::ToVirtualPtr(sys);

    m_systems.push_back(core_sptr::static_pointer_cast<EntitySystemBase>(sys));
    if (!a_processManually) { m_sysProcessor->Add(sysPtr, a_deltaT); }

    return sysPtr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_ComponentPtr>
  void
    ECS::
    InsertComponent(core_cs::entity_vptr a_ent, T_ComponentPtr a_comp)
  { m_entMgr->InsertComponent(core_cs::EntityManager::Params(a_ent, a_comp)); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Prefab, typename... T_Args>
  T_Prefab
    ECS::
    CreatePrefab(T_Args&&... a_args)
  { 
    T_Prefab pref(m_entMgr.get(), m_compPoolMgr.get(), Forward(a_args)...);
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
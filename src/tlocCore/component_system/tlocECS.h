#ifndef _TLOC_CORE_COMPONENT_SYSTEM_ECS_H_
#define _TLOC_CORE_COMPONENT_SYSTEM_ECS_H_

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/time/tlocTime.h>
#include <tlocCore/component_system/tlocSystemsProcessor.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/utilities/tlocContainerUtils.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

namespace tloc { namespace core { namespace component_system {

  class ECS;

  class ECS_Group
  {
  public:
    typedef ECS_Group                                   this_type;
    typedef systems_processor_vso                       sys_processor_vso;
    typedef systems_processor_vptr                      sys_processor_ptr;
    typedef const_systems_processor_vptr                const_sys_processor_ptr;
    typedef SystemsProcessor::processing_system_ptr     sys_ptr;
    typedef core_str::String                            name_type;

    typedef core_cs::entity_processing_system_uptr      ent_proc_sys_uptr;
    typedef core_conts::Array<ent_proc_sys_uptr>        systems_cont;

  public:
    ECS_Group(BufferArg a_name);

    this_type& AddSystem(ent_proc_sys_uptr a_system);

  private:
    systems_cont            m_systems;
    sys_processor_vso       m_systemsProcessor;
    name_type               m_groupName;

  public:
    TLOC_DECL_AND_DEF_GETTER_NON_CONST(sys_processor_ptr, GetSystemsProcessor, 
                                       m_systemsProcessor.get());

    TLOC_DECL_AND_DEF_GETTER_AUTO(GetGroupName, m_groupName);
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(ECS_Group, ecs_group);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(ECS_Group, ecs_group);

  // ///////////////////////////////////////////////////////////////////////
  // ECS - the class that wraps most of the ECS in the engine

  class ECS
    : public core_bclass::DebugName
  {
  public:
    typedef ECS                                         this_type;
    typedef SystemsProcessor::time_type                 time_type;
    typedef SystemsProcessor::sys_info_iterator         sys_info_itr;
    typedef ecs_group_uptr                              ecs_group_ptr;
    typedef ecs_group_vptr                              ecs_group_vptr;
    typedef core_conts::Array<ecs_group_ptr>            ecs_group_cont;
    typedef ecs_group_cont::iterator                    ecs_group_itr;
    typedef ecs_group_cont::const_iterator              const_ecs_group_itr;

    typedef event_manager_vso                           event_manager_vso;
    typedef entity_manager_vso                          entity_manager_vso;
    typedef component_pool_mgr_vso                      component_pool_manager_vso;

    typedef event_manager_vptr                          event_manager_ptr;
    typedef entity_manager_vptr                         entity_manager_ptr;
    typedef component_pool_mgr_vptr                     component_pool_manager_ptr;

  public:
    ECS(BufferArg a_debugName = "ECS");
    virtual ~ECS();

  public: // system construction - no need to pass in event and entity managers. 
          // that is done automatically

    template <typename T_System>
    core_sptr::VirtualPtr<T_System>
      AddSystem(BufferArg groupName = "Default");

    template <typename T_System, typename... T_Args>
    core_sptr::VirtualPtr<T_System> 
      AddSystem(BufferArg a_groupName, T_Args&&... a_args);

    template <typename T_ComponentPtr>
    void        InsertComponent(core_cs::entity_vptr a_ent, T_ComponentPtr a_comp);

  public: // prefab construction

    template <typename T_Prefab, typename... T_Args>
    T_Prefab    CreatePrefab(T_Args&&... a_args);

  public:
    time_type   Initialize(BufferArg a_groupName);
    time_type   Initialize();

    void        Update(time_type a_deltaT);

    time_type   Process(BufferArg a_groupName, time_type a_deltaT);
    time_type   Process(time_type a_deltaT);

    void        RecycleAllUnusedComponents();

    ecs_group_vptr GetSystemsGroup(BufferArg a_groupName = "Default");
    ecs_group_vptr CreateSystemsGroup(BufferArg a_groupName);
    ecs_group_vptr GetOrCreateSystemsGroup(BufferArg a_groupName = "Default");

  private:
    component_pool_manager_vso  m_compPoolMgr;
    event_manager_vso           m_eventMgr;
    entity_manager_vso          m_entMgr;

    time_type                   m_autoRecycleDeltaT;
    time_type                   m_autoRecycleTimer;
    bool                        m_autoRecycleUnusedComponents;

    ecs_group_cont              m_systemsGroups;

  public:
    TLOC_DECL_AND_DEF_GETTER_NON_CONST
      (event_manager_ptr, GetEventManager, m_eventMgr.get());
    TLOC_DECL_AND_DEF_GETTER_NON_CONST
      (entity_manager_ptr, GetEntityManager, m_entMgr.get());
    TLOC_DECL_AND_DEF_GETTER_NON_CONST
      (component_pool_manager_ptr, GetComponentPoolManager, m_compPoolMgr.get());

    TLOC_DECL_AND_DEF_GETTER_AUTO(SetRecycleDeltaT, m_autoRecycleDeltaT);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN_AUTO(SetRecycleDeltaT, 
                                                 m_autoRecycleDeltaT);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN_AUTO(SetAutoRecycleUnusedComponents, 
                                                 m_autoRecycleUnusedComponents);

    TLOC_DECL_AND_DEF_CONTAINER_ALL_METHODS(_systems_groups, m_systemsGroups);
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_System>
  core_sptr::VirtualPtr<T_System> 
    ECS::
    AddSystem(BufferArg a_groupName)
  {
    core_sptr::UniquePtr<T_System> sys = 
      core_sptr::MakeUnique<T_System>(m_eventMgr.get(), m_entMgr.get());

    auto sysPtr = core_sptr::ToVirtualPtr(sys);

    auto group = GetOrCreateSystemsGroup(a_groupName);
    auto baseSys = core_sptr::static_pointer_cast<EntityProcessingSystem>(sys);

    group->AddSystem(baseSys);

    return sysPtr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_System, typename... T_Args>
  core_sptr::VirtualPtr<T_System> 
    ECS::
    AddSystem(BufferArg a_groupName, T_Args&&... a_args)
  { 
    core_sptr::UniquePtr<T_System> sys = 
      core_sptr::MakeUnique<T_System>(m_eventMgr.get(), m_entMgr.get(), Forward<T_Args>(a_args)...);

    auto sysPtr = core_sptr::ToVirtualPtr(sys);

    auto group = GetOrCreateSystemsGroup(a_groupName);
    auto baseSys = core_sptr::static_pointer_cast<EntityProcessingSystem>(sys);

    group->AddSystem(baseSys);

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

  namespace algos { namespace ecs  {

    // ///////////////////////////////////////////////////////////////////////
    // initialize

    TLOC_DECL_ALGO_WITH_CTOR_UNARY(GroupName_T, BufferArg, const);
    TLOC_DEFINE_ALGO_WITH_CTOR_UNARY(GroupName_T, const)
    { extract()(a).GetGroupName(); return true; }

    typedef GroupName_T<core::use_reference>   GroupName;
    typedef GroupName_T<core::use_pointee>     GroupName_Deref;

  };};

};};};

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::core_cs::ECS);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(tloc::core_cs::ECS);

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::core_cs::ECS_Group);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::core_cs::ECS_Group);

#endif
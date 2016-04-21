#include "tlocECS.h"
#include <tlocCore/logging/tlocLogger.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc { namespace core { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////

  ECS_Group::
    ECS_Group(BufferArg a_name)
    : m_groupName(a_name)
  { }

  auto
    ECS_Group::
    AddSystem(ent_proc_sys_uptr a_system) -> this_type&
  {
    auto sysPtr = core_sptr::ToVirtualPtr(a_system);
    m_systems.push_back(a_system);

    m_systemsProcessor->Add(sysPtr);
    return *this;
  }

  // ///////////////////////////////////////////////////////////////////////

  ECS::
   ECS(BufferArg a_debugName)
   : core_bclass::DebugName(a_debugName)
   , m_entMgr(m_eventMgr.get())
   , m_autoRecycleUnusedComponents(true)
   , m_autoRecycleDeltaT(0.5)
   , m_autoRecycleTimer(0.0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ECS::
    ~ECS()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    ECS::
    Initialize(BufferArg a_groupName) -> time_type
  { 
    auto group = GetSystemsGroup(a_groupName);
    time_type timeToInit = 0;

    if (group)
    { timeToInit = group->GetSystemsProcessor()->Initialize(); }
    else
    {
      TLOC_LOG_CORE_ERR_FILENAME_ONLY() << 
        "Systems group " << a_groupName << " does not exist";
    }

    return timeToInit;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    ECS::
    Initialize() -> time_type
  { 
    time_type timeToInit = 0;

    for (auto itr = begin_systems_groups(), itrEnd = end_systems_groups();
         itr != itrEnd; ++itr)
    {
      timeToInit += (*itr)->GetSystemsProcessor()->Initialize();
    }

    return timeToInit;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ECS::
    Update(time_type )
  { 
    m_entMgr->Update();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    ECS::
    Process(BufferArg a_groupName, time_type a_deltaT) -> time_type
  { 
    auto group = GetSystemsGroup(a_groupName);
    time_type timeToProcess = 0;

    if (group)
    { timeToProcess = group->GetSystemsProcessor()->Process(a_deltaT); }
    else
    {
      TLOC_LOG_CORE_ERR_FILENAME_ONLY() <<
        "Systems group " << a_groupName << " does not exist";
    }

    m_autoRecycleTimer += a_deltaT;
    if (m_autoRecycleTimer > m_autoRecycleDeltaT && m_autoRecycleUnusedComponents)
    {
      RecycleAllUnusedComponents();
      m_autoRecycleTimer = 0.0;
    }

    return timeToProcess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    ECS::
    Process(time_type a_deltaT) -> time_type
  { 
    time_type timeToProcess = 0;

    for (auto itr = begin_systems_groups(), itrEnd = end_systems_groups();
         itr != itrEnd; ++itr)
    {
      timeToProcess += (*itr)->GetSystemsProcessor()->Process(a_deltaT);
    }

    return timeToProcess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ECS::
    RecycleAllUnusedComponents()
  { m_compPoolMgr->RecycleAllUnused(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    ECS::
    GetSystemsGroup(BufferArg a_groupName) -> ecs_group_vptr
  {
    auto itr = core::find_if(m_systemsGroups.begin(), m_systemsGroups.end(), 
                              algos::ecs::GroupName_Deref(a_groupName));
    if (itr == m_systemsGroups.end())
    { return nullptr; }

    return core_sptr::ToVirtualPtr(*itr);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    ECS::
    CreateSystemsGroup(BufferArg a_groupName) -> ecs_group_vptr
  {
    TLOC_ASSERT(GetSystemsGroup(a_groupName) == nullptr,
                "Systems group with name already exists");

    m_systemsGroups.push_back(core_sptr::MakeUnique<ECS_Group>(a_groupName));
    return core_sptr::ToVirtualPtr(*(m_systemsGroups.end() - 1));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    ECS::
    GetOrCreateSystemsGroup(BufferArg a_groupName) -> ecs_group_vptr
  {
    auto group = GetSystemsGroup(a_groupName);
    
    if (group == nullptr)
    { group = CreateSystemsGroup(a_groupName); }

    return group;
  }

};};};

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::core_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(ECS);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(ECS);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(ECS_Group);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(ECS_Group);

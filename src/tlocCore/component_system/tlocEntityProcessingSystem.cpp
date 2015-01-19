#include "tlocEntityProcessingSystem.h"

#include <tlocCore/logging/tlocLogger.h>
#include <tlocCore/utilities/tlocPointerUtils.h>

namespace tloc { namespace core { namespace component_system {

  typedef EntityProcessingSystem::error_type    error_type;

  // ///////////////////////////////////////////////////////////////////////
  // EntityProcessingSystem

  EntityProcessingSystem::
    EntityProcessingSystem(event_manager_ptr a_eventMgr, 
                           entity_manager_ptr a_entityMgr, 
                           register_type a_compsToRegister,
                           BufferArg a_debugName)
    : base_type(a_eventMgr, a_entityMgr, a_compsToRegister, a_debugName)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::Pre_Initialize()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::
    DoInitialize(const entity_count_cont& a_entities)
  {
    TLOC_LOG_CORE_WARN_IF(a_entities.size() == 0) 
      <<  GetDebugName() << " (" << core_utils::GetMemoryAddress(this) 
      << ") does not have any components to Initialize (or process)";

    for (entity_count_cont::const_iterator itr = a_entities.begin(),
         itrEnd = a_entities.end(); itr != itrEnd; ++itr)
    {
      InitializeEntity(itr->first).Ignore();
    }

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::
    DoReInitialize(const entity_count_cont& a_entities)
  {
    TLOC_LOG_CORE_WARN_IF(a_entities.size() == 0) 
      <<  GetDebugName() << " (" << core_utils::GetMemoryAddress(this) 
      << ") does not have any components to ReInitialize (or process)";

    for (entity_count_cont::const_iterator itr = a_entities.begin(),
         itrEnd = a_entities.end(); itr != itrEnd; ++itr)
    {
      ReInitializeEntity(itr->first).Ignore();
    }

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::Post_Initialize()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::Pre_ReInitialize()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::
    ReInitializeEntity(entity_vptr a_ent)
  { 
    return InitializeEntity(a_ent); 
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::Post_ReInitialize()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::Pre_Reactivate()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::
    ReactivateEntity(entity_vptr a_ent)
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::Post_Reactivate()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::Pre_Deactivate()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::
    DeactivateEntity(entity_vptr a_ent)
  { 
    return ShutdownEntity(a_ent); 
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::Post_Deactivate()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool EntityProcessingSystem::CheckProcessing()
  { return IsProcessingDisabled() == false; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void EntityProcessingSystem::Pre_ProcessActiveEntities(f64)
  { 
    //////////////////////////////////////////////////////////////////////////
    // Reinit
    if (m_entsToReInit.empty() == false)
    {
      Pre_ReInitialize();
      for (auto itr = m_entsToReInit.begin(), 
                itrEnd = m_entsToReInit.end(); itr != itrEnd; ++itr)
      { ReInitializeEntity(*itr); }
      Post_ReInitialize();

      m_entsToReInit.clear();
    }

    //////////////////////////////////////////////////////////////////////////
    // Reactivate
    if (m_entsActivated.empty() == false)
    {
      Pre_Reactivate();
      for (auto itr = m_entsActivated.begin(), 
                itrEnd = m_entsActivated.end(); itr != itrEnd; ++itr)
      { ReactivateEntity(*itr); }
      Post_Reactivate();

      m_entsActivated.clear();
    }

    //////////////////////////////////////////////////////////////////////////
    // Deactivate
    if (m_entsDeactivated.empty() == false)
    {
      Pre_Deactivate();
      for (auto itr = m_entsDeactivated.begin(), 
                itrEnd = m_entsDeactivated.end(); itr != itrEnd; ++itr)
      { DeactivateEntity(*itr); }
      Post_Deactivate();

      m_entsDeactivated.clear();
    }

    //////////////////////////////////////////////////////////////////////////
    // Shutdown
    if (m_entsToShutdown.empty() == false)
    {
      Pre_Shutdown();
      for (core_cs::entity_ptr_array::iterator itr = m_entsToShutdown.begin(),
           itrEnd = m_entsToShutdown.end(); itr != itrEnd; ++itr)
      { ShutdownEntity(*itr); }
      Post_Shutdown();

      m_entsToShutdown.clear();
    }

  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void EntityProcessingSystem::
    DoProcessActiveEntities(const entity_count_cont& a_entities,
                            f64 a_deltaT)
  {
    for (auto itr = a_entities.begin(), 
              itrEnd = a_entities.end(); 
              itr != itrEnd; ++itr)
    {
      if ( itr->first->IsActive())
      { ProcessEntity(itr->first, a_deltaT); }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void EntityProcessingSystem::Post_ProcessActiveEntities(f64)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::Pre_Shutdown()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::ShutdownEntity(entity_ptr)
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::
    DoShutdown(const entity_count_cont& a_entities)
  {
    for (entity_count_cont::const_iterator itr = a_entities.begin(),
         itrEnd = a_entities.end(); itr != itrEnd; ++itr)
    {
      ShutdownEntity(itr->first).Ignore();
    }

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::Post_Shutdown()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    EntityProcessingSystem::
    OnComponentInsert(const core_cs::EntityComponentEvent& a_event)
  {
    if (IsInitialized())
    { m_entsToReInit.push_back(a_event.GetEntity()); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  void 
    EntityProcessingSystem::
    OnComponentRemove(const EntityComponentEvent& a_event)
  {
    if (IsInitialized())
    { m_entsToShutdown.push_back(a_event.GetEntity()); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    EntityProcessingSystem::
    OnComponentDisable(const entity_comp_event_type& a_event)
  {
    if (IsInitialized())
    { m_entsDeactivated.push_back(a_event.GetEntity()); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    EntityProcessingSystem::
    OnComponentEnable(const entity_comp_event_type& a_event)
  {
    if (IsInitialized())
    { m_entsActivated.push_back(a_event.GetEntity()); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    EntityProcessingSystem::
    OnEntityActivate(const EntityComponentEvent& a_event)
  {
    if (IsInitialized())
    { m_entsActivated.push_back(a_event.GetEntity()); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  void 
    EntityProcessingSystem::
    OnEntityDeactivate(const EntityComponentEvent& a_event)
  {
    if (IsInitialized())
    { m_entsDeactivated.push_back(a_event.GetEntity()); }
  }

};};};

#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(tloc::core_cs::EntityProcessingSystem);
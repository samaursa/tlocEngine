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

  error_type EntityProcessingSystem::Post_Initialize()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::Pre_ReInitialize()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::
    ReInitializeEntity(entity_vptr a_ent)
  { return InitializeEntity(a_ent); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::Post_ReInitialize()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool EntityProcessingSystem::CheckProcessing()
  { return true; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void EntityProcessingSystem::Pre_ProcessActiveEntities(f64)
  { 
    if (m_entsToReInit.empty() == false)
    {
      Pre_ReInitialize();
      for (core_cs::entity_ptr_array::iterator itr = m_entsToReInit.begin(),
           itrEnd = m_entsToReInit.end(); itr != itrEnd; ++itr)
      { ReInitializeEntity(*itr); }
      Post_ReInitialize();

      m_entsToReInit.clear();
    }

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
    for (entity_count_cont::const_iterator itr = a_entities.begin(),
         itrEnd = a_entities.end(); itr != itrEnd; ++itr)
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
    OnComponentRemove(const core_cs::EntityComponentEvent& a_event)
  {
    if (IsInitialized())
    { m_entsToShutdown.push_back(a_event.GetEntity()); }
  }

};};};

#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(tloc::core_cs::EntityProcessingSystem);
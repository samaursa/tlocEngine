#include "tlocEntityProcessingSystem.h"

namespace tloc { namespace core { namespace component_system {

  typedef EntityProcessingSystem::error_type    error_type;

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::Pre_Initialize()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type EntityProcessingSystem::
    DoInitialize(const entity_count_cont& a_entities)
  {
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

  bool EntityProcessingSystem::CheckProcessing()
  { return true; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void EntityProcessingSystem::Pre_ProcessActiveEntities(f64)
  { }

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

};};};
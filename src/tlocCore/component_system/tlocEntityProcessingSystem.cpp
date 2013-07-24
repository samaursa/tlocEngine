#include "tlocEntityProcessingSystem.h"

namespace tloc { namespace core { namespace component_system {

  typedef EntityProcessingSystem::error_type    error_type;

  //````````````````````````````````````````````````````````````````````````
  // Initialization

  error_type EntityProcessingSystem::Pre_Initialize()
  { return ErrorSuccess; }

  error_type EntityProcessingSystem::
    DoInitialize(const EntityManager* a_mgr, const entity_ptr_array& a_entities)
  {
    for (entity_ptr_array::const_iterator itr = a_entities.begin(),
         itrEnd = a_entities.end(); itr != itrEnd; ++itr)
    {
      InitializeEntity(a_mgr, *itr).Ignore();
    }

    return ErrorSuccess;
  }

  error_type EntityProcessingSystem::Post_Initialize()
  { return ErrorSuccess; }

  //````````````````````````````````````````````````````````````````````````
  // Processing

  bool EntityProcessingSystem::CheckProcessing()
  { return true; }

  void EntityProcessingSystem::Pre_ProcessActiveEntities(f64)
  { }

  void EntityProcessingSystem::
    DoProcessActiveEntities(const EntityManager* a_mgr,
                            const entity_ptr_array& a_entities,
                            f64 a_deltaT)
  {
    for (entity_ptr_array::const_iterator itr = a_entities.begin(),
         itrEnd = a_entities.end(); itr != itrEnd; ++itr)
    {
      if ( (*itr)->IsActive())
      { ProcessEntity(a_mgr, *itr, a_deltaT); }
    }
  }

  void EntityProcessingSystem::Post_ProcessActiveEntities(f64)
  { }

  //````````````````````````````````````````````````````````````````````````
  // Shutdown

  error_type EntityProcessingSystem::Pre_Shutdown()
  { return ErrorSuccess; }

  error_type EntityProcessingSystem::
    DoShutdown(const EntityManager* a_mgr, const entity_ptr_array& a_entities)
  {
    for (entity_ptr_array::const_iterator itr = a_entities.begin(),
         itrEnd = a_entities.end(); itr != itrEnd; ++itr)
    {
      ShutdownEntity(a_mgr, *itr).Ignore();
    }

    return ErrorSuccess;
  }

  error_type EntityProcessingSystem::Post_Shutdown()
  { return ErrorSuccess; }

};};};
#include "tlocEntityProcessingSystem.h"

namespace tloc { namespace core { namespace component_system {

  typedef EntityProcessingSystem::error_type    error_type;

  //````````````````````````````````````````````````````````````````````````
  // Initialization

  error_type EntityProcessingSystem::Pre_Initialize()
  { return ErrorSuccess(); }

  error_type EntityProcessingSystem::
    DoInitialize(EntityManager* a_mgr, const entity_ptr_array& a_entities)
  {
    for (entity_ptr_array::const_iterator itr = a_entities.begin(),
         itrEnd = a_entities.end(); itr != itrEnd; ++itr)
    {
      InitializeEntity(a_mgr, *itr);
    }

    return ErrorSuccess();
  }

  error_type EntityProcessingSystem::Post_Initialize()
  { return ErrorSuccess(); }

  //````````````````````````````````````````````````````````````````````````
  // Processing

  bool EntityProcessingSystem::CheckProcessing()
  { return true; }

  void EntityProcessingSystem::Pre_ProcessActiveEntities()
  { }

  void EntityProcessingSystem::
    DoProcessActiveEntities(EntityManager* a_mgr, const entity_ptr_array& a_entities)
  {
    for (entity_ptr_array::const_iterator itr = a_entities.begin(),
         itrEnd = a_entities.end(); itr != itrEnd; ++itr)
    {
      ProcessEntity(a_mgr, *itr);
    }
  }

  void EntityProcessingSystem::Post_ProcessActiveEntities()
  { }

  //````````````````````````````````````````````````````````````````````````
  // Shutdown

  error_type EntityProcessingSystem::Pre_Shutdown()
  { return ErrorSuccess(); }

  error_type EntityProcessingSystem::
    DoShutdown(EntityManager* a_mgr, const entity_ptr_array& a_entities)
  {
    for (entity_ptr_array::const_iterator itr = a_entities.begin(),
         itrEnd = a_entities.end(); itr != itrEnd; ++itr)
    {
      ShutdownEntity(a_mgr, *itr);
    }

    return ErrorSuccess();
  }

  error_type EntityProcessingSystem::Post_Shutdown()
  { return ErrorSuccess(); }

};};};
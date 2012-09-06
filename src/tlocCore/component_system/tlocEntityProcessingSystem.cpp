#include "tlocEntityProcessingSystem.h"

namespace tloc { namespace core { namespace component_system {

  EntityProcessingSystem::~EntityProcessingSystem() { }

  bool EntityProcessingSystem::CheckProcessing() { return true; }

  void EntityProcessingSystem::Pre_ProcessActiveEntities() { }

  void EntityProcessingSystem::
    ProcessActiveEntities(EntityManager* a_mgr, const entity_array& a_entities)
  {
    for (entity_array::const_iterator itr = a_entities.begin(),
         itrEnd = a_entities.end(); itr != itrEnd; ++itr)
    {
      ProcessEntity(a_mgr, *itr);
    }
  }

  void EntityProcessingSystem::Post_ProcessingActiveEntities() { }

};};};
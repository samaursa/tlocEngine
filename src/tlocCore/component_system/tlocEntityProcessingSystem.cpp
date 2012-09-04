#include "tlocEntityProcessingSystem.h"

namespace tloc { namespace core { namespace component_system {

  EntityProcessingSystem::
    EntityProcessingSystem(EventManager* a_eventMgr, EntityManager* a_entityMgr,
                           component_type a_typeBits)
                           : EntitySystemBase(a_eventMgr, a_entityMgr, a_typeBits)
  {
  }

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
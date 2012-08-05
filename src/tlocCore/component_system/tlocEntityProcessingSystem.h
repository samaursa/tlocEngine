#ifndef TLOC_ENTITY_PROCESSING_SYSTEM_H
#define TLOC_ENTITY_PROCESSING_SYSTEM_H

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocEntitySystemBase.h>

namespace tloc { namespace core { namespace component_system {

  class EntityProcessingSystem : EntitySystemBase
  {
  public:

    typedef components::value_type      component_type;

    EntityProcessingSystem(EventManager* a_eventMgr, EntityManager* a_entityMgr,
                           component_type a_typeBits);
    virtual ~EntityProcessingSystem();

    virtual bool CheckProcessing();
    virtual void Pre_ProcessActiveEntities();
    virtual void ProcessEntity(EntityManager* a_mgr, Entity* a_ent) = 0;
    virtual void ProcessActiveEntities (EntityManager* a_mgr,
                                        const entity_array& a_entities);
    virtual void Post_ProcessingActiveEntities();
  };

};};};

#endif
#ifndef TLOC_ENTITY_MANAGER_H
#define TLOC_ENTITY_MANAGER_H

#include <tlocCore/containers/tlocContainers.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityEvent.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentType.h>

namespace tloc { namespace core { namespace component_system {

  class EntityManager
  {
  public:
    typedef tl_array<Entity*>::type               entity_list;
    typedef tl_array<Entity::entity_id>::type     entity_id_list;
    typedef tl_array<entity_list>::type           component_entity_list;

    typedef Entity::component_list                component_list;
    typedef Entity::entity_id                     entity_id;

    EntityManager(EventManager* a_eventManager);
    virtual ~EntityManager();

    Entity*     CreateEntity();
    void        DestroyEntity(Entity* a_entity);
    Entity*     GetEntity(tl_int a_index);

    void        InsertComponent(Entity* a_entity, Component* a_component);
    bool        RemoveComponent(Entity* a_entity, Component* a_component);

    component_list* GetComponents(Entity* a_entity, components::value_type a_type);

  private:

    entity_list             m_entities;
    entity_id_list          m_removedEntities;
    component_entity_list   m_componentsAndEntities;
    EventManager*           m_eventMgr;
    entity_id               m_nextId;
  };

};};};

#endif
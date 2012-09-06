#include "tlocEntityManager.h"

#include <tlocCore/component_system/tlocEntity.inl>

namespace tloc { namespace core { namespace component_system {

  EntityManager::EntityManager(EventManager *a_eventManager)
    : m_eventMgr(a_eventManager), m_nextId(0)
  {
    m_componentsAndEntities.resize(components_group::count);
  }

  EntityManager::~EntityManager()
  {
    for (entity_list::iterator itr = m_entities.begin(),
         itrEnd = m_entities.end(); itr != itrEnd; ++itr)
    {
      if (*itr) { DestroyEntity(*itr); }
    }
  }

  Entity* EntityManager::CreateEntity()
  {
    Entity* e = new Entity(m_nextId++);

    if (m_removedEntities.size() > 0)
    {
      e->m_index = m_removedEntities.back();
      m_removedEntities.pop_back();

      m_entities[e->m_index] = e;
    }
    else
    {
      e->m_index = m_entities.size();
      m_entities.push_back(e);
    }

    m_eventMgr->DispatchNow( EntityEvent(entity_events::create_entity, e) );

    return e;
  }

  void EntityManager::DestroyEntity(Entity* a_entity)
  {
    m_entities[a_entity->m_index] = NULL;
    m_removedEntities.push_back(a_entity->m_index);

    m_eventMgr->DispatchNow( EntityEvent(entity_events::destroy_entity, a_entity) );

    delete a_entity;
  }

  Entity* EntityManager::GetEntity(tloc::tl_int a_index)
  {
    TLOC_ASSERT(a_index < (tl_int)m_entities.size(), "Index out of range!");
    return m_entities[a_index];
  }

  void EntityManager::InsertComponent(Entity *a_entity, Component *a_component)
  {
    TLOC_ASSERT(core::find(m_entities, a_entity) != m_entities.end(),
                "Entity not found!");

    entity_list& entities = m_componentsAndEntities[a_component->GetType()];

    entities.push_back(a_entity);
    a_entity->m_allComponents[a_component->GetType()].push_back(a_component);

    m_eventMgr->DispatchNow(
      EntityComponentEvent(entity_events::insert_component, a_entity,
                           a_component->GetType()) );
  }

  bool EntityManager::RemoveComponent(Entity* a_entity, Component* a_component)
  {
    component_list& entityComps = a_entity->m_allComponents[a_component->GetType()];
    entity_list& entityList = m_componentsAndEntities[a_component->GetType()];

    {// Remove it from the entity
      component_list::iterator itr = core::find(entityComps, a_component);
      if (itr != entityComps.end()) { entityComps.erase(itr); }
      else { return false; }
    }

    {// Remove it from the component list
      entity_list::iterator itr = core::find(entityList, a_entity);
      TLOC_ASSERT(itr != entityList.end(), "Entity not found for component!");
      if (itr != entityList.end()) { entityList.erase(itr); }
    }

    return true;
  }

  EntityManager::component_list*
    EntityManager::GetComponents(Entity* a_entity, components::value_type a_type)
  {
    typedef Entity::component_list_list comp_d_list;

    comp_d_list::iterator itr     = a_entity->m_allComponents.begin();
    comp_d_list::iterator itrEnd  = a_entity->m_allComponents.end();

    for (; itr != itrEnd; ++itr)
    {
      if (itr->size() > 0 && (*itr)[0]->GetType() == a_type)
      {
        return &(*itr);
      }
    }

    return NULL;
  }

};};};
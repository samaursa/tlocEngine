#include "tlocEntityManager.h"

#include <tlocCore/component_system/tlocEntity.inl.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

namespace tloc { namespace core { namespace component_system {

  EntityManager::
    EntityManager(event_manager_sptr a_eventManager)
    : m_eventMgr(a_eventManager), m_nextId(0)
  {
    m_componentsAndEntities.resize(components_group::count);
  }

  EntityManager::
    ~EntityManager()
  {
    for (entity_cont::iterator itr = m_entities.begin(),
         itrEnd = m_entities.end(); itr != itrEnd; ++itr)
    {
      if (*itr) { DestroyEntity(*itr); }
    }
  }

  EntityManager::entity_ptr_type EntityManager::
    CreateEntity()
  {
    Entity* e = new Entity(m_nextId++);

    if (m_removedEntities.size() > 0)
    {
      e->SetIndex(m_removedEntities.back());
      m_removedEntities.pop_back();

      m_entities[e->GetIndex()] = e;
    }
    else
    {
      e->SetIndex(m_entities.size());
      m_entities.push_back(e);
    }

    m_eventMgr->DispatchNow( EntityEvent(entity_events::create_entity, e) );

    return e;
  }

  void EntityManager::
    DestroyEntity(Entity* a_entity)
  {
    TLOC_ASSERT(core::find_all(m_entities, a_entity) != m_entities.end(),
      "Entity does not exist!");

    m_entities[a_entity->GetIndex()] = nullptr;
    m_entitiesToRemove.push_back(a_entity);

    m_eventMgr->DispatchNow(EntityEvent(entity_events::destroy_entity, a_entity));
  }

  EntityManager::entity_ptr_type EntityManager::
    GetEntity(tloc::tl_int a_index)
  {
    TLOC_ASSERT(a_index < (tl_int)m_entities.size(), "Index out of range!");
    return m_entities[a_index];
  }

  void EntityManager::
    InsertComponent(Entity *a_entity, Component *a_component)
  {
    TLOC_ASSERT(core::find_all(m_entities, a_entity) != m_entities.end(),
                "Entity not found!");

    entity_cont& entities = m_componentsAndEntities[a_component->GetType()];

    entities.push_back(a_entity);
    a_entity->InsertComponent(a_component);

    m_eventMgr->DispatchNow(
      EntityComponentEvent(entity_events::insert_component, a_entity,
                           a_component) );
  }

  bool EntityManager::
    RemoveComponent(Entity* a_entity, Component* a_component)
  {
    component_cont& entityComps = a_entity->DoGetComponents(a_component->GetType());
    component_cont::iterator itr = core::find_all(entityComps, a_component);

    if (itr == entityComps.end())
    { return false; }

    m_compToRemove.push_back(MakePair(a_entity, a_component));
    EntityComponentEvent evt(entity_events::remove_component, a_entity,
                             a_component);
    m_eventMgr->DispatchNow(evt);

    return true;
  }

  bool EntityManager::
    DoRemoveComponent(Entity* a_entity, Component* a_component)
  {
    // LOGIC: We allow the client to remove a component even if the component
    // does not exist in the entity. Return true if it exists, o/w false. Then,
    // remove it from the component list in manager which HAS TO exist (hence
    // the assertion)

    {// Remove it from the entity
      if (a_entity)
      {
        component_cont& entityComps = a_entity->DoGetComponents(a_component->GetType());
        component_cont::iterator itr = core::find_all(entityComps, a_component);

        if (itr != entityComps.end())
        { entityComps.erase(itr); }
        else
        { return false; }
      }
    }

    {// Remove it from the component list
      entity_cont& entityList = m_componentsAndEntities[a_component->GetType()];
      entity_cont::iterator itr = core::find_all(entityList, a_entity);
      TLOC_ASSERT(itr != entityList.end(), "Entity not found for component!");
      if (itr != entityList.end()) { entityList.erase(itr); }
    }

    return true;
  }

  void EntityManager::
    DoUpdateAndCleanComponents()
  {
    typedef ent_comp_pair_cont::iterator ent_comp_pair_itr;
    ent_comp_pair_itr itr = m_compToRemove.begin();
    ent_comp_pair_itr itrEnd = m_compToRemove.end();

    for (; itr != itrEnd; ++itr)
    {
      DoRemoveComponent(itr->first, itr->second);
    }

    m_compToRemove.clear();
  }

  void EntityManager::
    DoUpdateAndCleanEntities()
  {
    delete_ptrs(m_entitiesToRemove.begin(), m_entitiesToRemove.end());
    m_entitiesToRemove.clear();
  }

  void EntityManager::Update()
  {
    // Go through all the entities that we have to remove, and mark their
    // components for removal
    entity_cont::iterator itr = m_entitiesToRemove.begin();
    entity_cont::iterator itrEnd = m_entitiesToRemove.end();

    for(; itr != itrEnd; ++itr)
    {
      for (components::value_type currComp = 0;
           currComp < components_group::count; ++currComp)
      {
        if ( (*itr)->HasComponent(currComp))
        {
          component_cont& clist = (*itr)->DoGetComponents(currComp);

          component_cont::iterator itrComp = clist.begin();
          component_cont::iterator itrCompEnd = clist.end();

          for (; itrComp != itrCompEnd; ++itrComp)
          {
            RemoveComponent(*itr, *itrComp);
          }
        }
      }

      m_removedEntities.push_back( (*itr)->GetIndex());
    }

    // Update the components (which involves removing them)
    DoUpdateAndCleanComponents();
    // Update the entities (which involves removing them)
    DoUpdateAndCleanEntities();
  }

  EntityManager::component_cont* EntityManager::
    GetComponents(Entity* a_entity, components::value_type a_type)
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

    return nullptr;
  }

};};};

//------------------------------------------------------------------------
// Explicit instantiations

TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(tloc::core_cs::EntityManager);
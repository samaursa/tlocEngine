#include "tlocEntityManager.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
#include <tlocCore/component_system/tlocEntity.inl.h>
#include <tlocCore/logging/tlocLogger.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc { namespace core { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // InsertParams

  EntityManager::Params::
    Params()
    : m_orphan(false)
  { } 

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  EntityManager::Params::
    Params(ent_comp_pair_type a_entCompPair)
    : m_entity(a_entCompPair.first)
    , m_component(a_entCompPair.second)
    , m_orphan(false)
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  EntityManager::Params::
    Params(entity_ptr_type a_ent, component_ptr_type a_component)
    : m_entity(a_ent)
    , m_component(a_component)
    , m_orphan(false)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  EntityManager::Params::this_type&
    EntityManager::Params::
    DispatchTo(listeners_ptr a_system)
  { m_dispatchTo.push_back(a_system); return *this; }

  // ///////////////////////////////////////////////////////////////////////
  // EntityManager

  EntityManager::
    EntityManager(event_manager_vptr a_eventManager)
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

    // update releases components and deletes entities marked for destruction
    Update();

    // delete the remaining entities, if any
    for_each_all(m_entities, core_sptr::algos::virtual_ptr::DeleteAndReset());
  }

  EntityManager::entity_ptr_type EntityManager::
    CreateEntity()
  {
    entity_ptr_type e(new Entity(m_nextId++));

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
    DestroyEntity(entity_ptr_type a_entity)
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
    InsertComponent(const Params& a_params)
  {
    TLOC_ASSERT(core::find_all(m_entities, a_params.m_entity) != m_entities.end(),
                "Entity not found!");

    entity_cont& entities = 
      m_componentsAndEntities[a_params.m_component->GetType()];

    entities.push_back(a_params.m_entity);
    a_params.m_entity->InsertComponent(a_params.m_component);

    EntityComponentEvent evt(entity_events::insert_component, a_params.m_entity,
                             a_params.m_component);

    if (m_eventMgr->DispatchNow(evt, a_params.m_dispatchTo) == false)
    {
      TLOC_LOG_CORE_WARN_FILENAME_ONLY_IF(a_params.m_orphan == false) 
        << a_params.m_component->GetDebugName() 
        << " component inserted into Entity (" 
        << a_params.m_entity->GetDebugName() 
        << ") is without a system.";
    }
  }

  bool EntityManager::
    RemoveComponent(ent_comp_pair_type  a_entComp)
  {
    entity_ptr_type     a_entity  = a_entComp.first;
    component_ptr_type  a_comp    = a_entComp.second;

    component_cont& entityComps = a_entity->DoGetComponents(a_comp->GetType());
    component_cont::iterator itr = core::find_all(entityComps, a_comp);

    if (itr == entityComps.end())
    { return false; }

    m_compToRemove.push_back(MakePair(a_entity, a_comp));
    EntityComponentEvent evt(entity_events::remove_component, a_entity,
                             a_comp);
    m_eventMgr->DispatchNow(evt);

    return true;
  }

  bool EntityManager::
    DoRemoveComponent(entity_ptr_type a_entity, component_ptr_type a_component)
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
    for_each_all(m_entitiesToRemove, core_sptr::algos::virtual_ptr::DeleteAndReset());
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
            RemoveComponent(MakePair(*itr, *itrComp));
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
    GetComponents(entity_ptr_type a_entity, components::value_type a_type)
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

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(tloc::core_cs::EntityManager);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::core_cs::EntityManager);
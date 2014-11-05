#include "tlocEntityManager.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
#include <tlocCore/logging/tlocLogger.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc { namespace core { namespace component_system {

  using core_sptr::ToVirtualPtr;

  // ///////////////////////////////////////////////////////////////////////
  // InsertParams

  EntityManager::Params::
    Params()
    : m_orphan(false)
  { } 

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  EntityManager::Params::
    Params(entity_ptr a_ent, component_ptr_type a_component)
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
  { }

  EntityManager::
    ~EntityManager()
  {
    for (entity_cont::iterator itr = m_entities.begin(),
         itrEnd = m_entities.end(); itr != itrEnd; ++itr)
    {
      if (*itr) { DestroyEntity(ToVirtualPtr(*itr)); }
    }

    // update releases components and deletes entities marked for destruction
    Update();

    // delete the remaining entities, if any
    m_entities.clear();
  }

  EntityManager::entity_ptr 
    EntityManager::
    CreateEntity()
  {
    auto e = core_sptr::MakeUnique<Entity>(m_nextId++);

    entity_ptr ePtr;

    if (m_removedEntities.size() > 0)
    {
      e->DoSetIndex(m_removedEntities.back());
      m_removedEntities.pop_back();

      const auto index = e->GetIndex();

      m_entities[index] = e;
      ePtr = core_sptr::ToVirtualPtr(m_entities[index]);
    }
    else
    {
      e->DoSetIndex(m_entities.size());
      m_entities.push_back(e);
      ePtr = ToVirtualPtr(m_entities.back());
    }

    m_eventMgr->DispatchNow( EntityEvent(entity_events::create_entity, ePtr) );

    return ePtr;
  }

  void
    EntityManager::
    DeactivateEntity(entity_ptr a_entity)
  {
    a_entity->DoDeactivate();
    m_eventMgr->DispatchNow( EntityEvent( entity_events::deactivate_entity, 
                                          ToVirtualPtr(a_entity)) );
  }

  void
    EntityManager::
    ActivateEntity(entity_ptr a_entity)
  {
    a_entity->DoActivate();
    m_eventMgr->DispatchNow( EntityEvent( entity_events::activate_entity, 
                                          ToVirtualPtr(a_entity)) );
  }

  void EntityManager::
    DestroyEntity(entity_ptr a_entity)
  {
    TLOC_ASSERT(core::find_all(m_entities, a_entity) != m_entities.end(),
      "Entity does not exist!");

    m_entitiesToRemove.push_back(m_entities[a_entity->GetIndex()]);

    m_eventMgr->DispatchNow(EntityEvent(entity_events::destroy_entity, 
                                        ToVirtualPtr(a_entity)) );
  }

  EntityManager::entity_ptr EntityManager::
    GetEntity(tloc::tl_int a_index)
  {
    TLOC_ASSERT(a_index < (tl_int)m_entities.size(), "Index out of range!");
    return ToVirtualPtr(m_entities[a_index]);
  }

  void EntityManager::
    InsertComponent(const Params& a_params)
  {
    TLOC_ASSERT(core::find_all(m_entities, a_params.m_entity) != m_entities.end(),
                "Entity pointer not found in this EntityManager.");

    a_params.m_entity->DoInsertComponent(a_params.m_component);

    EntityComponentEvent evt(entity_events::insert_component, 
                             ToVirtualPtr(a_params.m_entity),
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
    entity_ptr     a_entity  = a_entComp.first;
    component_ptr_type  a_comp    = a_entComp.second;

    component_iterator itr    = a_entity->begin_components(a_comp->GetInfo());
    component_iterator itrEnd = a_entity->end_components(a_comp->GetInfo());

    if (itr == itrEnd)
    { return false; }

    component_iterator foundItr = core::find(itr, itrEnd, a_comp);

    if (foundItr == itrEnd)
    { return false; }

    m_compToRemove.push_back(MakePair(a_entity, a_comp));
    EntityComponentEvent evt(entity_events::remove_component, 
                             ToVirtualPtr(a_entity),
                             a_comp);
    m_eventMgr->DispatchNow(evt);

    return true;
  }

  bool EntityManager::
    DoRemoveComponent(entity_ptr a_entity, component_ptr_type a_comp)
  {
    // LOGIC: We allow the client to remove a component. If the component
    // does not exist in the entity false. Then, remove it from the component 
    // list in manager which HAS TO exist (hence the assertion)

    {// Remove it from the entity
      if (a_entity)
      {
        component_iterator itr = a_entity->begin_components(a_comp->GetInfo());
        component_iterator itrEnd = a_entity->end_components(a_comp->GetInfo());

        component_iterator foundItr = core::find(itr, itrEnd, a_comp);

        if (foundItr != itrEnd)
        { a_entity->DoRemoveComponent(*foundItr); }
        else
        { return false; }
      }
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
  { m_entitiesToRemove.clear(); }

  void EntityManager::Update()
  {
    // Go through all the entities that we have to remove, and mark their
    // components for removal
    auto itr = m_entitiesToRemove.begin();
    auto itrEnd = m_entitiesToRemove.end();

    for(; itr != itrEnd; ++itr)
    {
      component_group_iterator groupItr    = (*itr)->begin_component_groups();
      component_group_iterator groupItrEnd = (*itr)->end_component_groups();

      for ( ; groupItr != groupItrEnd; ++groupItr)
      {
        component_iterator compItr    = groupItr->begin();
        component_iterator compItrEnd = groupItr->end();

        for ( ; compItr != compItrEnd; ++compItr)
        {
          RemoveComponent(MakePair(ToVirtualPtr(*itr), *compItr));
        }
      }

      m_removedEntities.push_back( (*itr)->GetIndex());
    }

    // Update the components (which involves removing them)
    DoUpdateAndCleanComponents();
    // Update the entities (which involves removing them)
    DoUpdateAndCleanEntities();
  }

};};};

//------------------------------------------------------------------------
// Explicit instantiations

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(tloc::core_cs::EntityManager);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::core_cs::EntityManager);
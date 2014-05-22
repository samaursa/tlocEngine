#ifndef TLOC_ENTITY_MANAGER_H
#define TLOC_ENTITY_MANAGER_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityEvent.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace core { namespace component_system {

  class EntityManager
    : public core_bclass::NonCopyable_I
  {
  public:
    typedef Entity                                entity_type;
    typedef entity_vptr                           entity_ptr_type;
    typedef component_sptr                        component_ptr_type;

    typedef containers::
      tl_array<entity_ptr_type>::type             entity_cont;
    typedef containers::
      tl_array<Entity::entity_id>::type           entity_id_cont;
    typedef containers::
      tl_array<entity_cont>::type                 component_entity_cont;

    typedef Pair<entity_ptr_type,
                 component_ptr_type>              ent_comp_pair_type;
    typedef containers::
      tl_array<ent_comp_pair_type>::type          ent_comp_pair_cont;

    typedef Entity::component_list                component_cont;
    typedef Entity::entity_id                     entity_id_type;

    typedef core_t::StrongType_T<bool, 0>         orphan;

  public:
    struct Params
    {
    public:
      typedef Params                              this_type;
      typedef EventManager::listeners_list        listeners_list;
      typedef listeners_list::value_type          listeners_ptr;

    public:
      Params();
      Params(entity_ptr_type a_ent,  component_ptr_type a_component);

      this_type& DispatchTo(listeners_ptr a_system);

      TLOC_DECL_PARAM_VAR(entity_ptr_type,  Entity, m_entity);
      TLOC_DECL_PARAM_VAR(component_ptr_type, Component, m_component);
      TLOC_DECL_PARAM_VAR(bool, Orphan, m_orphan);
      TLOC_DECL_PARAM_VAR(listeners_list, DispatchTo, m_dispatchTo);
    };

  public:
    EntityManager(event_manager_vptr a_eventManager);
    virtual ~EntityManager();

    entity_ptr_type   CreateEntity();
    void              DestroyEntity(entity_ptr_type a_entity);
    entity_ptr_type   GetEntity(tl_int a_index);

    // A component is an orphan if there is no system present to receive it/
    // This will suppress the warning that a component was added without a 
    // system
    void              InsertComponent(const Params& a_params);
    bool              RemoveComponent(ent_comp_pair_type a_entityAndComponent);

    void              Update();

    component_cont*   GetComponents(entity_ptr_type a_entity,
                                    components::value_type a_type);

    TLOC_DECL_AND_DEF_GETTER(entity_cont::size_type, GetUnusedEntities,
                             m_removedEntities.size());

  private:
    EntityManager(const EntityManager&);

    void DoUpdateAndCleanComponents();
    void DoUpdateAndCleanEntities();

    bool DoRemoveComponent(entity_ptr_type a_entity, component_ptr_type a_component);

  private:

    entity_cont             m_entities;
    entity_id_cont          m_removedEntities;
    component_entity_cont   m_componentsAndEntities;
    event_manager_vptr      m_eventMgr;
    entity_id_type          m_nextId;

    ent_comp_pair_cont      m_compToRemove;
    entity_cont             m_entitiesToRemove;
  };


  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(EntityManager, entity_manager);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(EntityManager, entity_manager);

};};};

#endif
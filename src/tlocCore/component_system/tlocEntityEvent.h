#ifndef TLOC_ENTITY_EVENT_H
#define TLOC_ENTITY_EVENT_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocEvent.h>

namespace tloc { namespace core { namespace component_system {

  namespace entity_events
  {
    enum Type
    {
      create_entity   = events::k_entity_events_begin,
      destroy_entity,
      activate_entity,
      deactivate_entity,
      insert_component,
      remove_component,
      disable_component,
      enable_component,
    }; typedef tl_int value_type;
  };

  class EntityEvent : public EventBase
  {
  public:
    using EventBase::event_type;

    EntityEvent(event_type a_eventType, entity_vptr a_entity)
      : EventBase(a_eventType), m_entity(a_entity) {}

    TLOC_DECL_AND_DEF_GETTERS_DIRECT(entity_vptr, GetEntity, m_entity);

  private:
    entity_vptr m_entity;
  };

  class EntityComponentEvent : public EventBase
  {
  public:
    typedef component_sptr             component_ptr_type;

    using EventBase::event_type;

    EntityComponentEvent(event_type a_eventType, entity_vptr a_entity,
                         component_ptr_type a_type)
                         : EventBase(a_eventType)
                         , m_entity(a_entity)
                         , m_component(a_type) {}

    TLOC_DECL_AND_DEF_GETTERS_DIRECT(entity_vptr, GetEntity, m_entity);
    TLOC_DECL_AND_DEF_GETTERS_DIRECT(component_ptr_type, GetComponent, m_component);

  private:
    entity_vptr         m_entity;
    component_ptr_type  m_component;
  };

};};};

#endif
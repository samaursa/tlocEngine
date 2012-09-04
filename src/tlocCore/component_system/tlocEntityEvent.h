#ifndef TLOC_ENTITY_EVENT_H
#define TLOC_ENTITY_EVENT_H

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocEvent.h>

namespace tloc { namespace core { namespace component_system {

  namespace entity_events
  {
    enum Type
    {
      create_entity   = events::entity_events_begin,
      destroy_entity,
      insert_component,
      remove_component,
    }; typedef tl_int value_type;
  };

  class EntityEvent : public EventBase
  {
  public:
    using EventBase::event_type;

    EntityEvent(event_type a_eventType, Entity* a_entity)
      : EventBase(a_eventType), m_entity(a_entity) {}

    Entity* m_entity;
  };

  class EntityComponentEvent : public EventBase
  {
  public:
    using EventBase::event_type;
    typedef components::value_type  components_type;

    EntityComponentEvent(event_type a_eventType, Entity* a_entity,
                         components_type a_type)
                         : EventBase(a_eventType)
                         , m_entity(a_entity)
                         , m_type(a_type) {}

    Entity*         m_entity;
    components_type m_type;
  };

};};};

#endif
#ifndef TLOC_COMPONENT_SYSTEM_EVENT_H
#define TLOC_COMPONENT_SYSTEM_EVENT_H

#include <tlocCore/types/tlocTypes.h>

namespace tloc { namespace core { namespace component_system {

  namespace events
  {
    enum default_events
    {
      reserved_events_begin = 0,
      entity_events_begin   = 1000,
      user_events_begin     = 10000,
    }; typedef tl_int value_type;
  };

  class EventBase
  {
  public:
    typedef events::value_type      event_type;

    EventBase(event_type a_type) : m_type(a_type) {}
    event_type GetType() const { return m_type; }

    template <typename T_RetType>
    T_RetType& GetAs()
    { return static_cast<T_RetType&>(*this); }

    template <typename T_RetType>
    const T_RetType& GetAs() const
    { return static_cast<const T_RetType&>(*this); }

  protected:
    event_type m_type;
  };

  struct EventListener
  {
    virtual ~EventListener() {}
    virtual bool OnEvent(const EventBase& a_event) = 0;
  };


};};};

#endif
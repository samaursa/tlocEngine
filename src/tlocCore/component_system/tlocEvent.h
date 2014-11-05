#ifndef TLOC_COMPONENT_SYSTEM_EVENT_H
#define TLOC_COMPONENT_SYSTEM_EVENT_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

namespace tloc { namespace core { namespace component_system {

  namespace events
  {
    enum default_events
    {
      k_reserved_events_begin = 0,
      k_entity_events_begin   = 1000,
      k_user_events_begin     = 10000,
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

  struct EventReturn
  {
    EventReturn(bool a_veto, bool a_componentAdded)
      : m_veto(a_veto)
      , m_componentInSystem(a_componentAdded)
    { }

    bool m_veto;
    bool m_componentInSystem;
  };

  class EventListener
  {
  public:
    typedef EventReturn                             return_type;

  public:
    virtual ~EventListener() {}
    virtual return_type OnEvent(const EventBase& a_event) = 0;
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(EventListener, event_listener);

};};};

#endif
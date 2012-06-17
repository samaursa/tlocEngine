#ifndef TLOC_COMPONENT_SYSTEM_EVENT_H
#define TLOC_COMPONENT_SYSTEM_EVENT_H

namespace tloc { namespace core { namespace component_system {

  namespace events
  {
    enum default_events
    {
      none,
    }; typedef unsigned int event_type;
  };

  class EventBase
  {
  public:
    typedef events::event_type      event_type;

    EventBase(event_type a_type) : m_type(a_type) {}
    event_type GetType() const { return m_type; }

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
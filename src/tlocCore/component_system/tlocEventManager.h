#ifndef TLOC_EVENT_MANAGER_H
#define TLOC_EVENT_MANAGER_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/smart_ptr/tlocVirtualPtr.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>

#include <tlocCore/component_system/tlocEvent.h>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>

namespace tloc { namespace core { namespace component_system {

  class EventManager
    : public core_bclass::NonCopyable_I
  {
  public:
    typedef events::value_type                    event_type;
    typedef containers::
      tl_doubly_list <EventListener*>::type       listeners_list;
    typedef containers::
      tl_hash_map<event_type,
                  listeners_list>::type           listener_map;
    typedef listener_map::value_type              map_value_type;
    typedef containers::
      tl_array<const EventBase*>::type            event_list;

  public:

    EventManager();
    virtual ~EventManager();

    void AddListener(EventListener* a_listener, event_type a_type);
    void RemoveListener(EventListener* a_listener, event_type a_type);

    void AddGlobalListener(EventListener* a_listener);
    void RemoveGlobalListener(EventListener* a_listener);

    void RemoveAllListeners();

    bool DispatchNow(const EventBase& a_event) const;
    void Dispatch(const EventBase& a_event);

    void Update();

  protected:
    listener_map          m_listeners;
    listeners_list        m_globalListeners;
    event_list            m_events;
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_SHARED_PTR(EventManager, event_manager);
  TLOC_TYPEDEF_VIRTUAL_PTR(EventManager, event_manager);

};};};

#endif
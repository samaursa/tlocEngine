#ifndef TLOC_EVENT_MANAGER_H
#define TLOC_EVENT_MANAGER_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

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
    typedef listeners_list::iterator              itr_listeners;
    typedef listeners_list::const_iterator        const_itr_listeners;

    typedef containers::
      tl_hash_map<event_type,
                  listeners_list>::type           listener_map;
    typedef listener_map::value_type              map_value_type;

  public:

    EventManager();
    virtual ~EventManager();

    void AddListener(EventListener* a_listener, event_type a_type);
    void RemoveListener(EventListener* a_listener, event_type a_type);

    void AddGlobalListener(EventListener* a_listener);
    void RemoveGlobalListener(EventListener* a_listener);

    void RemoveAllListeners();

    bool DispatchNow(const EventBase& a_event) const;
    bool DispatchNow(const EventBase& a_event, 
                     const listeners_list& a_includeOnly) const;

    template <tl_int T_Size>
    bool DispatchNow(const EventBase& a_event,
                     const core_ds::Tuple<EventListener*, T_Size>& a_includeOnly) const;

  protected:
    bool DoDispatchNow(const EventBase& a_event, 
                       const_itr_listeners a_begin, const_itr_listeners a_end) const;

  protected:
    listener_map          m_listeners;
    listeners_list        m_globalListeners;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <tl_int T_Size>
  bool
    EventManager::
    DispatchNow(const EventBase& a_event, 
                const core_ds::Tuple<EventListener*, T_Size>& a_includeOnly) const
  {
    TLOC_STATIC_ASSERT(T_Size <= 5, Use_DispatchNow_with_listeners_list_instead);

    listeners_list list;
    for (tl_size i = 0; i < a_includeOnly.size(); ++i)
    { list.push_back(a_includeOnly[i]); }

    return DispatchNow(a_event, list);
  }

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(EventManager, event_manager);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(EventManager, event_manager);

};};};

#endif
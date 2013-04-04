#include "tlocEventManager.h"

#include <tlocCore/component_system/tlocEvent.inl>
#include <tlocCore/containers/tlocContainers.inl>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl>

namespace tloc { namespace core { namespace component_system {

  EventManager::EventManager() { }
  EventManager::~EventManager() { }

  void EventManager::AddListener(EventListener* a_listener, event_type a_type)
  {
    listener_map::iterator itr = m_listeners.find(a_type);
    if (itr == m_listeners.end())
    {
      itr = m_listeners.insert( map_value_type(a_type, listeners_list()) ).first;
    }

    listeners_list& li = itr->second;
    li.push_back(a_listener);
  }

  void EventManager::RemoveListener(EventListener* a_listener, event_type a_type)
  {
    listener_map::iterator itr = m_listeners.find(a_type);
    if (itr != m_listeners.end())
    {
      (*itr).second.remove(a_listener);
    }
    else
    {
      TLOC_ASSERT(false,
      "Trying to remove a listener that does not exist with event_type");
      // LOG: Trying to remove a listener that does not exist with event_type
    }
  }

  void EventManager::AddGlobalListener(EventListener* a_listener)
  {
    m_globalListeners.push_back(a_listener);
  }

  void EventManager::RemoveGlobalListener(EventListener* a_listener)
  {
    listeners_list::iterator itr = find(m_globalListeners.begin(),
                                        m_globalListeners.end(), a_listener);
    if (itr != m_globalListeners.end())
    {
      m_globalListeners.erase(itr);
    }
  }

  void EventManager::RemoveAllListeners()
  {
    m_listeners.clear();
    m_globalListeners.clear();
  }

  bool EventManager::DispatchNow(const EventBase& a_event) const
  {
    typedef listeners_list::const_iterator lis_itr;
    for (lis_itr itr = m_globalListeners.begin(),
                 itrEnd = m_globalListeners.end();
                 itr != itrEnd; ++itr)
    {
      // If the event is being vetoed, then no need to go through the whole list
      if ( (*itr)->OnEvent(a_event) ) { return true; }
    }

    typedef listener_map::const_iterator map_itr;
    map_itr found = m_listeners.find( a_event.GetType() );
    if (found != m_listeners.end() )
    {
      const listeners_list& list = found->second;
      for (lis_itr itr = list.begin(), itrEnd = list.end();
           itr != itrEnd; ++itr)
      {
        if ( (*itr)->OnEvent(a_event) ) { return true; }
      }
    }

    return false;
  }

  void EventManager::Dispatch(const EventBase& a_event)
  {
    m_events.push_back(&a_event);
  }

  void EventManager::Update()
  {
    typedef event_list::iterator      event_itr;
    typedef listeners_list::iterator  lis_itr;
    typedef listener_map::iterator    map_itr;

    // Dispatch all events to all global listeners
    for (event_itr eventItr = m_events.begin(), eventItrEnd = m_events.end();
         eventItr != eventItrEnd; ++eventItr)
    {
      for (lis_itr itr = m_globalListeners.begin(),
                   itrEnd = m_globalListeners.end();
                   itr != itrEnd; ++itr)
      {
        if ( (*itr)->OnEvent( *(*eventItr)) )
        {
          itr = m_globalListeners.erase(itr);
          --itr; // because the for loop is going perform a ++
        }
      }
    }

    // Dispatch remaining events to all mapped listeners
    for (event_itr eventItr = m_events.begin(), eventItrEnd = m_events.end();
         eventItr != eventItrEnd; ++eventItr)
    {
      map_itr mapItr = m_listeners.find( (*(*eventItr)).GetType());
      if (mapItr != m_listeners.end())
      {
        listeners_list& list = mapItr->second;
        for (lis_itr itr = list.begin(), itrEnd = list.end();
                     itr != itrEnd; ++itr)
        {
          if ( (*itr)->OnEvent( *(*eventItr) ) ) { break; }
        }
      }
    }

    // Clear the event list
    m_events.clear();
  }

  //------------------------------------------------------------------------
  // Explicit instantiations

  template class core_sptr::SharedPtr<EventManager>;
  template class core_sptr::SharedPtr<const EventManager>;

};};};
#include "tlocEventManager.h"

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

#include <tlocCore/component_system/tlocEvent.inl.h>
#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/logging/tlocLogger.h>

namespace tloc { namespace core { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // EventManager

  EventManager::
    EventManager() { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  EventManager::
    ~EventManager() { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    EventManager::
    AddListener(EventListener* a_listener, event_type a_type)
  {
    listener_map::iterator itr = m_listeners.find(a_type);
    if (itr == m_listeners.end())
    {
      itr = m_listeners.insert( map_value_type(a_type, listeners_list()) ).first;
    }

    listeners_list& li = itr->second;
    li.push_back(a_listener);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void EventManager::RemoveListener(EventListener* a_listener, event_type a_type)
  {
    listener_map::iterator itr = m_listeners.find(a_type);
    if (itr != m_listeners.end())
    {
      (*itr).second.remove(a_listener);
    }
    else
    {
      TLOC_LOG_CORE_WARN() <<
        "Trying to remove a listener that does not exist with even_type";
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    EventManager::
    AddGlobalListener(EventListener* a_listener)
  {
    m_globalListeners.push_back(a_listener);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void 
    EventManager::
    RemoveGlobalListener(EventListener* a_listener)
  {
    listeners_list::iterator itr = find(m_globalListeners.begin(),
                                        m_globalListeners.end(), a_listener);
    if (itr != m_globalListeners.end())
    {
      m_globalListeners.erase(itr);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void EventManager::RemoveAllListeners()
  {
    m_listeners.clear();
    m_globalListeners.clear();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool 
    EventManager::
    DispatchNow(const EventBase& a_event) const
  {
    bool componentAdded = false;

    // global listeners include all listeners
    componentAdded = 
      DoDispatchNow(a_event, m_globalListeners.begin(), m_globalListeners.end());

    // find matching listeners and dispatch event
    typedef listener_map::const_iterator map_itr;
    map_itr found = m_listeners.find( a_event.GetType() );
    if (found != m_listeners.end() )
    {
      const listeners_list& list = found->second;
      componentAdded = DoDispatchNow(a_event, list.begin(), list.end());
    }

    return componentAdded;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    EventManager::
    DispatchNow(const EventBase& a_event, 
                const listeners_list& a_includeOnly) const
  {
    if (a_includeOnly.size() > 0)
    {
      return DoDispatchNow(a_event, a_includeOnly.begin(), 
                           a_includeOnly.end());
    }
    else
    {
      return DispatchNow(a_event);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool 
    EventManager::
    DoDispatchNow(const EventBase& a_event, 
                  const_itr_listeners a_begin, const_itr_listeners a_end) const
  {
    bool componentAdded = false;

    for ( ; a_begin != a_end; ++a_begin)
    {
      EventReturn evt = (*a_begin)->OnEvent(a_event);
      if (evt.m_componentInSystem)
      { componentAdded = true; }

      if (evt.m_veto)
      { break; }
    }

    return componentAdded;
  }

};};};

//------------------------------------------------------------------------
// Explicit instantiations

using namespace tloc::core_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(EventManager);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(EventManager);

#include <tlocCore/data_structures/tlocTupleExplicitMacros.h>

TLOC_EXPLICITLY_INSTANTIATE_TUPLE(EventListener*, 1);
TLOC_EXPLICITLY_INSTANTIATE_TUPLE(EventListener*, 2);
TLOC_EXPLICITLY_INSTANTIATE_TUPLE(EventListener*, 3);
TLOC_EXPLICITLY_INSTANTIATE_TUPLE(EventListener*, 4);
TLOC_EXPLICITLY_INSTANTIATE_TUPLE(EventListener*, 5);
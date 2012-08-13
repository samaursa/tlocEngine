#include "tlocTestCommon.h"

#include <tlocCore/tlocBase.h>

#define protected public
#define private public
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityEvent.h>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl>

namespace TestingEventManager
{
  using namespace tloc;
  using namespace core;
  using namespace component_system;

  class EventTracker : public EventListener
  {
  public:
    typedef Pair<events::value_type, tl_int> pair_type;
    typedef tl_array<pair_type>::type         container_type;

    EventTracker()
    {
      m_eventsToTest.push_back(MakePair(entity_events::create_entity, 0));
      m_eventsToTest.push_back(MakePair(entity_events::destroy_entity, 0));
      m_eventsToTest.push_back(MakePair(entity_events::insert_component, 0));
      m_eventsToTest.push_back(MakePair(entity_events::remove_component, 0));
    }

    tl_int GetEventCount(entity_events::value_type a_eventType)
    {
      typedef container_type::iterator itr_type;

      for (itr_type itr = m_eventsToTest.begin(), itrEnd = m_eventsToTest.end();
           itr != itrEnd; ++itr)
      {
        if (itr->first == a_eventType)
        {
          return itr->second;
        }
      }

      return -1;
    }

    void IncrementEventCount(entity_events::value_type a_eventType)
    {
      for (tl_size i = 0; i < m_eventsToTest.size(); ++i)
      {
        if (m_eventsToTest[i].first == a_eventType)
        {
          m_eventsToTest[i].second++;
          return;
        }
      }

      WARN("Increment attemp on invalid event");
    }

    virtual bool OnEvent(const EventBase& a_event)
    {
      events::value_type eventType = a_event.GetType();
      switch(eventType)
      {
      case entity_events::create_entity:
      case entity_events::destroy_entity:
      case entity_events::insert_component:
      case entity_events::remove_component:
        {
          IncrementEventCount(eventType);
          return false; // we do not want to veto the event just so that other
                        // listeners get the chance to read the event
        }
      default:
        {
          return false;
        }
      }
    }

    container_type m_eventsToTest;
  };


  TEST_CASE("Core/component_system/EventManager/General", "")
  {
    EventTracker globalTracker;
    EventTracker tracker;

    Entity       dummyEnt(0);

    EventManager mgr;
    mgr.AddGlobalListener(&globalTracker);
    mgr.AddListener(&tracker, entity_events::create_entity);

    events::value_type currentEvent = entity_events::create_entity;

    CHECK(globalTracker.GetEventCount(currentEvent) == 0);
    CHECK(tracker.GetEventCount(currentEvent) == 0);

    mgr.DispatchNow(EntityEvent(currentEvent, &dummyEnt));

    CHECK(globalTracker.GetEventCount(currentEvent) == 1);
    CHECK(tracker.GetEventCount(currentEvent) == 1);

    currentEvent = entity_events::destroy_entity;
    mgr.DispatchNow(EntityEvent(currentEvent, &dummyEnt));

    CHECK(globalTracker.GetEventCount(currentEvent) == 1);
    CHECK(tracker.GetEventCount(currentEvent) == 0);

  }
};
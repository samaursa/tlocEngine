#include "tlocTestCommon.h"

#include <tlocCore/tlocBase.h>

#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntity.inl.h>
#include <tlocCore/component_system/tlocEntityEvent.h>
#include <tlocCore/component_system/tlocComponent.h>

#include <tlocCore/smart_ptr/tlocVirtualStackObject.h>
#include <tlocCore/smart_ptr/tlocVirtualStackObject.inl.h>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl.h>

namespace TestingEventManager
{
  using namespace tloc;
  using namespace core;
  using namespace core::containers;
  using namespace component_system;

  class EventTracker : public EventListener
  {
  public:
    typedef Pair<events::value_type, tl_int>  pair_type;
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

    virtual EventReturn OnEvent(const EventBase& a_event)
    {
      events::value_type eventType = a_event.GetType();

      EventReturn evtRet(false, false);

      switch(eventType)
      {
      case entity_events::create_entity:
      case entity_events::destroy_entity:
      case entity_events::insert_component:
        evtRet.m_componentInSystem = true;
      case entity_events::remove_component:
        {
          IncrementEventCount(eventType);
          return evtRet; // we do not want to veto the event just so that other
                        // listeners get the chance to read the event
        }
      default:
        {
          return evtRet;
        }
      }
    }

    container_type m_eventsToTest;
  };

  class CompToTest
    : public core::component_system::Component_T<CompToTest, components::listener>
  {
  public:
    typedef core::component_system::Component_T
      <CompToTest, components::listener>            base_type;
  public:
    CompToTest() : base_type(k_component_type, "CompToTest")
    {}
  };

  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(CompToTest, comp_to_test);
  TLOC_TYPEDEF_SHARED_PTR(CompToTest, comp_to_test);

  using core_sptr::MakeShared;

  TEST_CASE("Core/component_system/EventManager/General", "")
  {
    EventTracker globalTracker;
    EventTracker tracker, tracker2;

    entity_vso         dummyEnt( MakeArgs(0) );
    comp_to_test_sptr  transComp = MakeShared<CompToTest>();
    component_sptr     dummyComp = MakeShared<component_sptr::value_type>(*transComp);

    EventManager mgr;
    mgr.AddGlobalListener(&globalTracker);
    mgr.AddListener(&tracker, entity_events::create_entity);

    events::value_type currentEvent = entity_events::create_entity;

    CHECK(globalTracker.GetEventCount(currentEvent) == 0);
    CHECK(tracker.GetEventCount(currentEvent) == 0);

    mgr.DispatchNow(EntityEvent(currentEvent, dummyEnt.get()));

    CHECK(globalTracker.GetEventCount(currentEvent) == 1);
    CHECK(tracker.GetEventCount(currentEvent) == 1);

    currentEvent = entity_events::destroy_entity;
    mgr.DispatchNow(EntityEvent(currentEvent, dummyEnt.get()));

    CHECK(globalTracker.GetEventCount(currentEvent) == 1);
    CHECK(tracker.GetEventCount(currentEvent) == 0);

    currentEvent = entity_events::insert_component;
    mgr.AddListener(&tracker, entity_events::insert_component);
    mgr.DispatchNow(EntityComponentEvent(currentEvent, dummyEnt.get(), transComp));

    CHECK(globalTracker.GetEventCount(currentEvent) == 1);
    CHECK(tracker.GetEventCount(currentEvent) == 1);

    mgr.RemoveListener(&tracker, entity_events::insert_component);
    mgr.DispatchNow(EntityComponentEvent(currentEvent, dummyEnt.get(), transComp));

    CHECK(globalTracker.GetEventCount(currentEvent) == 2);
    CHECK(tracker.GetEventCount(currentEvent) == 1); // no change

    currentEvent = entity_events::create_entity;
    mgr.DispatchNow(EntityEvent(currentEvent, dummyEnt.get()));

    CHECK(globalTracker.GetEventCount(currentEvent) == 2);
    CHECK(tracker.GetEventCount(currentEvent) == 2);

    mgr.RemoveAllListeners();

    mgr.DispatchNow(EntityEvent(currentEvent, dummyEnt.get()));
    CHECK(globalTracker.GetEventCount(currentEvent) == 2);
    CHECK(tracker.GetEventCount(currentEvent) == 2);

    // dispatching to selective listeners
    CHECK(tracker2.GetEventCount(currentEvent) == 0);
    mgr.DispatchNow(EntityEvent(currentEvent, dummyEnt.get()), 
                    core_ds::MakeTuple<EventListener*>(&tracker2));
    CHECK(tracker2.GetEventCount(currentEvent) == 1);
    CHECK(globalTracker.GetEventCount(currentEvent) == 2);
    CHECK(tracker.GetEventCount(currentEvent) == 2);

  }
};
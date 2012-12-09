#include "tlocTestCommon.h"

#include <tlocCore/tlocBase.h>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntity.inl>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntityManager.inl>
#include <tlocCore/component_system/tlocEvent.h>

namespace TestingEntityManager
{
  using namespace tloc;
  using namespace core::component_system;

  struct EmptyComponent1 : public Component
  {
    EmptyComponent1() : Component(components::listener) {}
  };

  struct EmptyComponent2 : public Component
  {
    EmptyComponent2() : Component(components::listener + 1) {}
  };

  struct EntityTracker : public EventListener
  {
    EntityTracker() : m_entEventCounter(0)
                    , m_compEventCounter(0)
                    , m_totalEvents(0)
    {}

    virtual bool OnEvent(const EventBase& a_event)
    {
      m_totalEvents++;

      events::value_type eventType = a_event.GetType();
      switch(eventType)
      {
      case entity_events::create_entity:
        {
          m_entEventCounter++;
          return true;
        }
      case entity_events::destroy_entity:
        {
          m_entEventCounter--;
          return true;
        }
      case entity_events::insert_component:
        {
          m_compEventCounter++;
          return true;
        }
      case entity_events::remove_component:
        {
          m_compEventCounter--;
          return true;
        }
      default:
        {
          return false;
        }
      }
    }

    tl_int m_entEventCounter;
    tl_int m_compEventCounter;
    tl_int m_totalEvents;
  };

  TEST_CASE("Core/component_system/EntityManager/CreateDestroy", "")
  {
    EntityTracker   entTrack;
    EventManager    evtMgr;
    evtMgr.AddGlobalListener(&entTrack);

    EntityManager   eMgr(&evtMgr);

    Entity* newEnt = eMgr.CreateEntity();
    CHECK(newEnt != NULL);
    CHECK(entTrack.m_entEventCounter == 1);

    eMgr.DestroyEntity(newEnt);
    CHECK(entTrack.m_entEventCounter == 0);

    bool stressTestPassed = true;
    EntityManager::entity_list myList;

    for (tl_uint i = 0; i < 100; ++i)
    {
      newEnt = eMgr.CreateEntity();
      myList.push_back(newEnt);
      if (newEnt == NULL) { stressTestPassed = false; break; }
    }
    CHECK(eMgr.GetUnusedEntities() == 0);
    CHECK(entTrack.m_entEventCounter == 100);
    CHECK(stressTestPassed);

    for (EntityManager::entity_list::iterator itr = myList.begin(),
      itrEnd = myList.end(); itr != itrEnd; ++itr)
    {
      eMgr.DestroyEntity(*itr);
    }
    eMgr.Update();
    CHECK(entTrack.m_entEventCounter == 0);
    CHECK(eMgr.GetUnusedEntities() == 100);

    newEnt = eMgr.CreateEntity();
    CHECK(entTrack.m_entEventCounter == 1);
    CHECK(entTrack.m_compEventCounter == 0);

    Component testComp(components::listener);
    eMgr.InsertComponent(newEnt, &testComp);
    CHECK(entTrack.m_compEventCounter == 1);

    Component invalidComp(components::listener + 1);

    CHECK_FALSE(eMgr.RemoveComponent(newEnt, &invalidComp));
    eMgr.Update();
    CHECK(entTrack.m_compEventCounter == 1);

    CHECK(eMgr.RemoveComponent(newEnt, &testComp));
    eMgr.Update();
    CHECK(entTrack.m_compEventCounter == 0);

    eMgr.DestroyEntity(newEnt);
    eMgr.Update();
    CHECK(entTrack.m_entEventCounter == 0);
    CHECK(eMgr.GetUnusedEntities() == 100);
  }
};
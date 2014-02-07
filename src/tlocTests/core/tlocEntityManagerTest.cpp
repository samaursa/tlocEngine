#include "tlocTestCommon.h"

#include <tlocCore/tlocBase.h>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntity.inl.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntityManager.inl.h>
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

    tl_uint m_entEventCounter;
    tl_int  m_compEventCounter;
    tl_int  m_totalEvents;
  };

  TEST_CASE("Core/component_system/EntityManager/CreateDestroy", "")
  {
    const tl_uint entityCount = 100;

    EntityTracker   entTrack;
    event_manager_sptr evtMgr(new EventManager());
    evtMgr->AddGlobalListener(&entTrack);

    EntityManager   eMgr(evtMgr);

    EntityManager::entity_ptr_type newEnt = eMgr.CreateEntity();
    CHECK( (newEnt != nullptr) );
    CHECK(entTrack.m_entEventCounter == 1);

    eMgr.DestroyEntity(newEnt);
    CHECK(entTrack.m_entEventCounter == 0);

    bool stressTestPassed = true;
    EntityManager::entity_cont myList;

    for (tl_uint i = 0; i < entityCount; ++i)
    {
      newEnt = eMgr.CreateEntity();
      myList.push_back(newEnt);
      if (newEnt == nullptr) { stressTestPassed = false; break; }
    }
    CHECK(eMgr.GetUnusedEntities() == 0);
    CHECK(entTrack.m_entEventCounter == entityCount);
    CHECK(stressTestPassed);

    for (EntityManager::entity_cont::iterator itr = myList.begin(),
      itrEnd = myList.end(); itr != itrEnd; ++itr)
    {
      eMgr.DestroyEntity(*itr);
    }

    // clear and reset the virtual pointers to ensure that the entity manager
    // is able to delete the entities flagged for destruction without any
    // assertions firing
    newEnt.reset();
    myList.clear();

    eMgr.Update();
    CHECK(entTrack.m_entEventCounter == 0);
    CHECK(eMgr.GetUnusedEntities() == entityCount + 1); // +1 because of line 84

    newEnt = eMgr.CreateEntity();
    CHECK(entTrack.m_entEventCounter == 1);
    CHECK(entTrack.m_compEventCounter == 0);

    component_vso testComp = component_vso(Component(components::listener));
    eMgr.InsertComponent(newEnt, testComp.get());
    CHECK(entTrack.m_compEventCounter == 1);

    component_vso invalidComp = component_vso( Component(components::listener + 1) );

    CHECK_FALSE(eMgr.RemoveComponent(newEnt, invalidComp.get()));
    eMgr.Update();
    CHECK(entTrack.m_compEventCounter == 1);

    CHECK(eMgr.RemoveComponent(newEnt, testComp.get()));
    eMgr.Update();
    CHECK(entTrack.m_compEventCounter == 0);

    eMgr.DestroyEntity(newEnt);
    newEnt.reset();

    eMgr.Update();
    CHECK(entTrack.m_entEventCounter == 0);
    CHECK(eMgr.GetUnusedEntities() == entityCount + 1); // +1 because of line 84
  }
};
#include "tlocTestCommon.h"

#include <tlocCore/tlocBase.h>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntity.inl.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntityManager.inl.h>
#include <tlocCore/component_system/tlocEvent.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

namespace TestingEntityManager
{
  using namespace tloc;
  using namespace core::component_system;

  struct EmptyComponent1 : public Component
  {
    EmptyComponent1()
      : Component(components::listener, "EmptyComponent1")
    { }

    ~EmptyComponent1()
    { m_dtor++; }

    static tl_int m_dtor;
  };
  TLOC_TYPEDEF_ALL_SMART_PTRS(EmptyComponent1, empty_comp1);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(EmptyComponent1, empty_comp1);

  tl_int EmptyComponent1::m_dtor = 0;

  struct EmptyComponent2 : public Component
  {
    EmptyComponent2()
      : Component(components::listener + 1, "EmptyComponent2")
    { }

    ~EmptyComponent2()
    { m_dtor++; }

    static tl_int m_dtor;
  };
  TLOC_TYPEDEF_ALL_SMART_PTRS(EmptyComponent2, empty_comp2);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(EmptyComponent2, empty_comp2);

  tl_int EmptyComponent2::m_dtor = 0;

  struct EntityTracker : public EventListener
  {
    EntityTracker() : m_entEventCounter(0)
                    , m_compEventCounter(0)
                    , m_totalEvents(0)
    {}

    virtual EventReturn OnEvent(const EventBase& a_event)
    {
      m_totalEvents++;

      events::value_type eventType = a_event.GetType();
      switch(eventType)
      {
      case entity_events::create_entity:
        {
          m_entEventCounter++;
          return EventReturn(true, false);
        }
      case entity_events::destroy_entity:
        {
          m_entEventCounter--;
          return EventReturn(true, false);
        }
      case entity_events::insert_component:
        {
          m_compEventCounter++;
          return EventReturn(true, true);
        }
      case entity_events::remove_component:
        {
          m_compEventCounter--;
          return EventReturn(true, false);
        }
      default:
        {
          return EventReturn(false, false);
        }
      }
    }

    tl_uint m_entEventCounter;
    tl_int  m_compEventCounter;
    tl_int  m_totalEvents;
  };

  using core_sptr::MakeShared;

  TEST_CASE("Core/component_system/EntityManager/CreateDestroy", "")
  {
    //SECTION("CreateEntity() and DestroyEntity()", "")
    {
      const tl_uint entityCount = 100;

      EntityTracker   entTrack;
      event_manager_vso  evtMgr;
      evtMgr->AddGlobalListener(&entTrack);

      EntityManager   eMgr(evtMgr.get());

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

      component_sptr testComp = MakeShared<Component>(Component(components::listener, "temp"));
      eMgr.InsertComponent(newEnt, testComp, EntityManager::orphan(true));
      CHECK(entTrack.m_compEventCounter == 1);

      component_sptr invalidComp = MakeShared<Component>(Component(components::listener + 1, "temp"));

      CHECK_FALSE(eMgr.RemoveComponent(newEnt, invalidComp));
      eMgr.Update();
      CHECK(entTrack.m_compEventCounter == 1);

      CHECK(eMgr.RemoveComponent(newEnt, testComp));
      eMgr.Update();
      CHECK(entTrack.m_compEventCounter == 0);

      eMgr.DestroyEntity(newEnt);
      newEnt.reset();

      eMgr.Update();
      CHECK(entTrack.m_entEventCounter == 0);
      CHECK(eMgr.GetUnusedEntities() == entityCount + 1); // +1 because of line 84
    }

    //SECTION("Destructor memory leak", "")
    {
      // The dtor was calling DestroyEntity but was not doing an update to
      // clean the entities causing memory leaks

      EmptyComponent1::m_dtor = 0;
      EmptyComponent2::m_dtor = 0;

      tl_int c1dtorCount, c2dtorCount;
      {
        // component VSOs come first because they cannot be destroyed before
        // EntityManager has a chance to clean up its VirtualPtrs to the VSOs
        empty_comp1_sptr c1, c2, c3;
        empty_comp2_sptr c4, c5, c6;

        c1 = MakeShared<EmptyComponent1>();
        c2 = MakeShared<EmptyComponent1>();
        c3 = MakeShared<EmptyComponent1>();

        c4 = MakeShared<EmptyComponent2>();
        c5 = MakeShared<EmptyComponent2>();
        c6 = MakeShared<EmptyComponent2>();

        // VSO creates some temps, so we start from that count
        c1dtorCount = EmptyComponent1::m_dtor;
        c2dtorCount = EmptyComponent2::m_dtor;

        const tl_uint entityCount = 100;

        EntityTracker   entTrack;
        event_manager_vso evtMgr;
        evtMgr->AddGlobalListener(&entTrack);

        EntityManager   eMgr(evtMgr.get());

        // create a few entities
        for (tl_uint i = 0; i < entityCount / 2; ++i)
        {
          EntityManager::entity_ptr_type ent = eMgr.CreateEntity();
          eMgr.InsertComponent(ent, c1, EntityManager::orphan(true));
          eMgr.InsertComponent(ent, c2, EntityManager::orphan(true));
          eMgr.InsertComponent(ent, c3, EntityManager::orphan(true));
        }

        for (tl_uint i = entityCount / 2; i < entityCount; ++i)
        {
          EntityManager::entity_ptr_type ent = eMgr.CreateEntity();
          eMgr.InsertComponent(ent, c4, EntityManager::orphan(true));
          eMgr.InsertComponent(ent, c5, EntityManager::orphan(true));
          eMgr.InsertComponent(ent, c6, EntityManager::orphan(true));
        }
      }

      CHECK(EmptyComponent1::m_dtor == c1dtorCount + 3);
      CHECK(EmptyComponent2::m_dtor == c2dtorCount + 3);
    }
  }
};
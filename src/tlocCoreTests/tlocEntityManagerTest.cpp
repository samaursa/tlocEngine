#include "tlocTestCommon.h"

#include <tlocCore/tlocBase.h>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntityManager.inl.h>
#include <tlocCore/component_system/tlocEvent.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

namespace TestingEntityManager
{
  using namespace tloc;
  using namespace core::component_system;

  struct EmptyComponent1 
    : public Component
  {
    EmptyComponent1()
      : Component(info_type().GroupIndex(component_group::k_core)
                    .Type(components::k_listener), "EmptyComponent1")
    { }

    ~EmptyComponent1()
    { m_dtor++; }

    static tl_int m_dtor;
  };
  TLOC_TYPEDEF_ALL_SMART_PTRS(EmptyComponent1, empty_comp1);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(EmptyComponent1, empty_comp1);

  tl_int EmptyComponent1::m_dtor = 0;

  struct EmptyComponent2 
    : public Component
  {
    EmptyComponent2()
      : Component(info_type().GroupIndex(component_group::k_core)
                    .Type(components::k_listener + 1), "EmptyComponent2")
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
                    , m_disableEntityCounter(0)
                    , m_compEventCounter(0)
                    , m_disableComponentCounter(0)
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
      case entity_events::activate_entity:
        {
          m_disableEntityCounter--;
          return EventReturn(true, false);
        }
      case entity_events::deactivate_entity:
        {
          m_disableEntityCounter++;
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
      case entity_events::disable_component:
        {
          m_disableComponentCounter++;
          return EventReturn(true, true);
        }
      case entity_events::enable_component:
        {
          m_disableComponentCounter--;
          return EventReturn(true, false);
        }
      default:
        {
          return EventReturn(false, false);
        }
      }
    }

    tl_uint m_entEventCounter;
    tl_int  m_disableEntityCounter;
    tl_int  m_compEventCounter;
    tl_int  m_disableComponentCounter;
    tl_int  m_totalEvents;
  };
  TLOC_TYPEDEF_ALL_SMART_PTRS(EntityTracker, entity_tracker);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(EntityTracker, entity_tracker);

  using core_sptr::MakeShared;

  TEST_CASE("Core/component_system/EntityManager/CreateDestroy", "")
  {
    //SECTION("CreateEntity() and DestroyEntity()", "")
    {
      const tl_uint entityCount = 1000;

      entity_tracker_vso  entTrack, entTrack2;
      event_manager_vso   evtMgr;
      evtMgr->AddGlobalListener(entTrack.get().get());
      evtMgr->AddListener(entTrack2.get().get(), entity_events::insert_component);
      evtMgr->AddListener(entTrack2.get().get(), entity_events::remove_component);

      EntityManager   eMgr(evtMgr.get());

      eMgr.DestroyAllEntities();

      EntityManager::entity_ptr newEnt = eMgr.CreateEntity();
      CHECK( (newEnt != nullptr) );
      CHECK(entTrack->m_entEventCounter == 1);

      CHECK(newEnt->IsActive());
      eMgr.DeactivateEntity(newEnt);
      CHECK_FALSE(newEnt->IsActive());
      eMgr.ActivateEntity(newEnt);
      CHECK(newEnt->IsActive());

      eMgr.DestroyEntity(newEnt);
      CHECK(entTrack->m_entEventCounter == 0);

      eMgr.CreateEntity();
      eMgr.CreateEntity();
      eMgr.CreateEntity();
      CHECK(entTrack->m_entEventCounter == 3);

      eMgr.DestroyAllEntities();
      CHECK(entTrack->m_entEventCounter == 0);

      eMgr.Update();
      eMgr.Update(); // second update required because entity destruction is delayed by one frame

      // -----------------------------------------------------------------------
      // create entity with count entityCount

      bool stressTestPassed = true;
      core_cs::entity_ptr_array myList;

      for (tl_uint i = 0; i < entityCount; ++i)
      {
        newEnt = eMgr.CreateEntity();

        myList.push_back(newEnt);
        if (newEnt == nullptr) { stressTestPassed = false; break; }
      }
      CHECK(eMgr.GetUnusedEntities() == 0);
      CHECK(entTrack->m_entEventCounter == entityCount);
      CHECK(stressTestPassed);

      // -----------------------------------------------------------------------
      // enable disable entity

      core_cs::entity_vso badEnt(0, entity_manager_vptr(&eMgr) );

      TLOC_TEST_ASSERT
      { eMgr.DeactivateEntity(badEnt.get()); }
      TLOC_TEST_ASSERT_CHECK();

      for (auto itr = myList.begin(),
        itrEnd = myList.end(); itr != itrEnd; ++itr)
      {
        eMgr.DeactivateEntity(core_sptr::ToVirtualPtr(*itr));
      }
      CHECK(entTrack->m_disableEntityCounter == entityCount);
      CHECK(entTrack2->m_disableEntityCounter == 0); // not listening for this event


      TLOC_TEST_ASSERT
      { eMgr.ActivateEntity(badEnt.get()); }
      TLOC_TEST_ASSERT_CHECK();

      for (auto itr = myList.begin(),
        itrEnd = myList.end(); itr != itrEnd; ++itr)
      {
        eMgr.ActivateEntity(core_sptr::ToVirtualPtr(*itr));
      }
      CHECK(entTrack->m_disableEntityCounter == 0);
      CHECK(entTrack2->m_disableEntityCounter == 0);

      // -----------------------------------------------------------------------
      // we can also enable/disable the entities directly
      for (auto itr = myList.begin(),
                itrEnd = myList.end(); itr != itrEnd; ++itr)
      {
        (*itr)->Deactivate();
      }
      eMgr.Update();
      eMgr.Update();
      CHECK(entTrack->m_disableEntityCounter == entityCount);
      CHECK(entTrack2->m_disableEntityCounter == 0); // not listening for this event

      for (auto itr = myList.begin(),
                itrEnd = myList.end(); itr != itrEnd; ++itr)
      {
        (*itr)->Activate();
      }
      eMgr.Update();
      eMgr.Update(); // second update required because entity destruction is delayed by one frame
      CHECK(entTrack->m_disableEntityCounter == 0);
      CHECK(entTrack2->m_disableEntityCounter == 0);

      // -----------------------------------------------------------------------
      // destroy entity

      for (auto itr = myList.begin(),
        itrEnd = myList.end(); itr != itrEnd; ++itr)
      {
        eMgr.DestroyEntity(core_sptr::ToVirtualPtr(*itr));
      }

      // clear and reset the virtual pointers to ensure that the entity manager
      // is able to delete the entities flagged for destruction without any
      // assertions firing
      newEnt.reset();
      myList.clear();

      eMgr.Update();
      eMgr.Update(); // second update required because entity destruction is delayed by one frame
      CHECK(entTrack->m_entEventCounter == 0);
      CHECK(eMgr.GetUnusedEntities() == entityCount);

      newEnt = eMgr.CreateEntity();
      CHECK(entTrack->m_entEventCounter == 1);
      CHECK(entTrack->m_compEventCounter == 0);

      component_sptr testComp = MakeShared<EmptyComponent1>();

      { // dispatch to all
        eMgr.InsertComponent(EntityManager::Params()
                             .Entity(newEnt).Component(testComp).Orphan(true));
        CHECK(entTrack->m_compEventCounter == 1);
        CHECK(entTrack2->m_compEventCounter == 1);
      }

      { // dispatch selectively
        component_sptr testComp2 = MakeShared<EmptyComponent2>();
        eMgr.InsertComponent(EntityManager::Params(newEnt, testComp2).Orphan(true)
                             .DispatchTo(entTrack2.get().get()) );
          CHECK(entTrack->m_compEventCounter == 1);
          CHECK(entTrack2->m_compEventCounter == 2);
      }

      {
        auto compCounter = entTrack->m_disableComponentCounter;
        eMgr.DisableComponent(core::MakePair(newEnt, testComp));
        CHECK(entTrack->m_disableComponentCounter == compCounter + 1);
        eMgr.EnableComponent(core::MakePair(newEnt, testComp));
        CHECK(entTrack->m_disableComponentCounter == compCounter);
      }

      component_sptr invalidComp = MakeShared<EmptyComponent2>();

      CHECK_FALSE(eMgr.RemoveComponent( core::MakePair(newEnt, invalidComp)) );
      eMgr.Update();
      eMgr.Update(); // second update required because entity destruction is delayed by one frame
      CHECK(entTrack->m_compEventCounter == 1);

      CHECK(eMgr.RemoveComponent( core::MakePair(newEnt, testComp)) );
      eMgr.Update();
      eMgr.Update(); // second update required because entity destruction is delayed by one frame
      CHECK(entTrack->m_compEventCounter == 0);

      eMgr.DestroyEntity(newEnt);
      newEnt.reset();

      eMgr.Update();
      eMgr.Update(); // second update required because entity destruction is delayed by one frame
      CHECK(entTrack->m_entEventCounter == 0);
      CHECK(eMgr.GetUnusedEntities() == entityCount); // +1 because of line 84
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

        entity_tracker_vso  entTrack;
        event_manager_vso   evtMgr;
        evtMgr->AddGlobalListener(entTrack.get().get());

        EntityManager   eMgr(evtMgr.get());

        // create a few entities
        for (tl_uint i = 0; i < entityCount / 2; ++i)
        {
          EntityManager::entity_ptr ent = eMgr.CreateEntity();
          eMgr.InsertComponent(EntityManager::Params()
                               .Entity(ent).Component(c1).Orphan(true));
          eMgr.InsertComponent(EntityManager::Params()
                               .Entity(ent).Component(c2).Orphan(true));
          eMgr.InsertComponent(EntityManager::Params()
                               .Entity(ent).Component(c3).Orphan(true));
        }

        for (tl_uint i = entityCount / 2; i < entityCount; ++i)
        {
          EntityManager::entity_ptr ent = eMgr.CreateEntity();
          eMgr.InsertComponent(EntityManager::Params()
                               .Entity(ent).Component(c4).Orphan(true));
          eMgr.InsertComponent(EntityManager::Params()
                               .Entity(ent).Component(c5).Orphan(true));
          eMgr.InsertComponent(EntityManager::Params()
                               .Entity(ent).Component(c6).Orphan(true));
        }
      }

      CHECK(EmptyComponent1::m_dtor == c1dtorCount + 3);
      CHECK(EmptyComponent2::m_dtor == c2dtorCount + 3);
    }
  }
};

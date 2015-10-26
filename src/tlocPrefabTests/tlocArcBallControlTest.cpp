#include "tlocTestCommon.h"

#include <tlocInput/component_system/tlocArcballControlSystem.h>
#include <tlocPrefab/input/tlocArcBallControl.h>

namespace 
{
  using namespace tloc;

  typedef core_cs::entity_vptr                    entity_ptr;
  typedef input_cs::ArcBallControl                component_type;
  typedef input_cs::arc_ball_control_sptr         component_ptr;

  typedef input_cs::arc_ball_control_system_vso   system_vso;

  TEST_CASE("prefab/input/ArcBallControl", "")
  {
    core_cs::component_pool_mgr_vso compMgr;
    core_cs::event_manager_vso      evtMgr;
    core_cs::entity_manager_vso     entMgr(evtMgr.get());

    system_vso                      system(evtMgr.get(), entMgr.get());
    TLOC_UNUSED(system);
    
    //SECTION("Construct", "")
    {
      component_ptr ptr = pref_input::ArcBallControl(entMgr.get(), compMgr.get())
        .GlobalMultiplier(math_t::Vec2f(0.5f, 0.5f))
        .RotationMultiplier(math_t::Vec2f(0.1f, 0.1f))
        .PanMultiplier(math_t::Vec2f(0.2f, 0.2f))
        .DollyMultiplier(0.01f)
        .Construct();

      CHECK(ptr->GetGlobalMultiplier()    == math_t::Vec2f(0.5f, 0.5f));
      CHECK(ptr->GetRotationMultiplier()  == math_t::Vec2f(0.1f, 0.1f));
      CHECK(ptr->GetPanMultiplier()       == math_t::Vec2f(0.2f, 0.2f));
      CHECK(ptr->GetDollyMultiplier()     == Approx(0.01f));
    }

    //SECTION("Create", "")
    {
      entity_ptr ent = pref_input::ArcBallControl(entMgr.get(), compMgr.get())
        .Create();

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK(ptr->GetGlobalMultiplier()    == math_t::Vec2f(1.0f, 1.0f));
      CHECK(ptr->GetRotationMultiplier()  == math_t::Vec2f(1.0f, 1.0f));
      CHECK(ptr->GetPanMultiplier()       == math_t::Vec2f(1.0f, 1.0f));
      CHECK(ptr->GetDollyMultiplier()     == Approx(1.0f));
    }

    //SECTION("Add", "")
    {
      entity_ptr ent = entMgr->CreateEntity();

      pref_input::ArcBallControl(entMgr.get(), compMgr.get())
        .GlobalMultiplier(math_t::Vec2f(0.5f, 0.5f))
        .RotationMultiplier(math_t::Vec2f(0.1f, 0.1f))
        .PanMultiplier(math_t::Vec2f(0.2f, 0.2f))
        .DollyMultiplier(0.01f)
        .Add(ent);

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK(ptr->GetGlobalMultiplier()    == math_t::Vec2f(0.5f, 0.5f));
      CHECK(ptr->GetRotationMultiplier()  == math_t::Vec2f(0.1f, 0.1f));
      CHECK(ptr->GetPanMultiplier()       == math_t::Vec2f(0.2f, 0.2f));
      CHECK(ptr->GetDollyMultiplier()     == Approx(0.01f));
    }

    system->Initialize();
    system->ProcessActiveEntities();
  }
};
#include "tlocTestCommon.h"

#include <tlocGraphics/component_system/tlocArcBallSystem.h>
#include <tlocPrefab/graphics/tlocArcBall.h>

namespace 
{
  using namespace tloc;

  typedef core_cs::entity_vptr                    entity_ptr;
  typedef gfx_cs::ArcBall                         component_type;
  typedef gfx_cs::arcball_sptr                    component_ptr;

  typedef gfx_cs::arc_ball_system_vso             system_vso;

  TEST_CASE("prefab/gfx/ArcBall", "")
  {
    core_cs::component_pool_mgr_vso compMgr;
    core_cs::event_manager_vso      evtMgr;
    core_cs::entity_manager_vso     entMgr(evtMgr.get());

    system_vso                      system(evtMgr.get(), entMgr.get());
    TLOC_UNUSED(system);
    
    //SECTION("Construct", "")
    {
      component_ptr ptr = pref_gfx::ArcBall(entMgr.get(), compMgr.get())
        .Focus(math_t::Vec3f32(2.0f, 1.0f, 1.0f))
        .Construct();

      CHECK(ptr->GetFocus() == math_t::Vec3f32(2.0f, 1.0f, 1.0f));
    }

    //SECTION("Create", "")
    {
      entity_ptr ent = pref_gfx::ArcBall(entMgr.get(), compMgr.get())
        .Focus(math_t::Vec3f32(1.0f, 2.0f, 3.0f))
        .Create();

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK(ptr->GetFocus() == math_t::Vec3f32(1.0f, 2.0f, 3.0f));
    }

    //SECTION("Add", "")
    {
      entity_ptr ent = entMgr->CreateEntity();

      pref_gfx::ArcBall(entMgr.get(), compMgr.get())
        .Focus(math_t::Vec3f32(1.0f, 2.0f, 3.0f))
        .Add(ent);

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK(ptr->GetFocus() == math_t::Vec3f32(1.0f, 2.0f, 3.0f));
    }

    system->Initialize();
    system->ProcessActiveEntities();
  }
};

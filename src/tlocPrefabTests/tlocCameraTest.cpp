#include "tlocTestCommon.h"

#include <tlocGraphics/component_system/tlocCameraSystem.h>
#include <tlocGraphics/component_system/tlocCameraSystem.h>
#include <tlocPrefab/graphics/tlocCamera.h>

namespace 
{
  using namespace tloc;

  typedef core_cs::entity_vptr                    entity_ptr;
  typedef gfx_cs::Camera                          component_type;
  typedef gfx_cs::camera_sptr                     component_ptr;

  typedef gfx_cs::camera_system_vso               system_vso;

  TEST_CASE("prefab/gfx/Camera", "")
  {
    core_cs::component_pool_mgr_vso compMgr;
    core_cs::event_manager_vso      evtMgr;
    core_cs::entity_manager_vso     entMgr(MakeArgs(evtMgr.get()));

    system_vso                      system(MakeArgs(evtMgr.get(), entMgr.get()) );
    TLOC_UNUSED(system);
    
    //SECTION("Construct", "")
    {
      component_ptr ptr = pref_gfx::Camera(entMgr.get(), compMgr.get())
        .Near(1.0f)
        .Far(100.0)
        .Position(math_t::Vec3f32(2.0f, 1.0f, 1.0f))
        .VerticalFOV(math_t::Degree(60.0f))
        .Construct(core_ds::MakeTuple(800, 600));

      TLOC_UNUSED(ptr);
    }

    //SECTION("Create", "")
    {
      entity_ptr ent = pref_gfx::Camera(entMgr.get(), compMgr.get())
        .Near(1.0f)
        .Far(100.0)
        .Position(math_t::Vec3f32(2.0f, 1.0f, 1.0f))
        .VerticalFOV(math_t::Degree(60.0f))
        .Create(core_ds::MakeTuple(800, 600));

      REQUIRE(ent->HasComponent<component_type>());
    }

    //SECTION("Add", "")
    {
      entity_ptr ent = entMgr->CreateEntity();

      pref_gfx::Camera(entMgr.get(), compMgr.get())
        .Near(1.0f)
        .Far(100.0)
        .Position(math_t::Vec3f32(2.0f, 1.0f, 1.0f))
        .VerticalFOV(math_t::Degree(60.0f))
        .Add(ent, core_ds::MakeTuple(800, 600));

      REQUIRE(ent->HasComponent<component_type>());
    }

    system->Initialize();
    system->ProcessActiveEntities();
  }
};

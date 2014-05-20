#include "tlocTestCommon.h"

#include <tlocGraphics/component_system/tlocSceneGraphSystem.h>
#include <tlocPrefab/graphics/tlocSceneNode.h>

namespace 
{
  using namespace tloc;

  typedef core_cs::entity_vptr                    entity_ptr;
  typedef gfx_cs::SceneNode                       component_type;
  typedef gfx_cs::scene_node_sptr                 component_ptr;

  typedef gfx_cs::scene_graph_system_vso          system_vso;

  TEST_CASE("prefab/gfx/SceneNode", "")
  {
    core_cs::component_pool_mgr_vso compMgr;
    core_cs::event_manager_vso      evtMgr;
    core_cs::entity_manager_vso     entMgr(MakeArgs(evtMgr.get()));

    system_vso                      system(MakeArgs(evtMgr.get(), entMgr.get()) );
    TLOC_UNUSED(system);
    
    //SECTION("Construct", "")
    {
      core_cs::entity_vso ent(MakeArgs(0));

      component_ptr ptr = pref_gfx::SceneNode(entMgr.get(), compMgr.get())
        .Construct(ent.get());

      CHECK( (ptr->GetEntity() == ent.get()) );
    }

    //SECTION("Create", "")
    {
      entity_ptr ent = pref_gfx::SceneNode(entMgr.get(), compMgr.get())
        .Position(math_t::Vec3f32(2.0f, 1.0f, 5.0f))
        .Create();

      REQUIRE(ent->HasComponent<component_type>());
      REQUIRE(ent->HasComponent<math_cs::Transform>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK( (ptr->GetEntity() == ent) );
      CHECK(ent->GetComponent<math_cs::Transform>()->GetPosition() == 
            math_t::Vec3f32(2.0f, 1.0f, 5.0f));

      entity_ptr ent2 = pref_gfx::SceneNode(entMgr.get(), compMgr.get())
        .Position(math_t::Vec3f32(0.0f, 0.0f, 0.0f))
        .Parent(core_sptr::ToVirtualPtr(ent->GetComponent<component_type>()) )
        .Create();

      REQUIRE(ent2->HasComponent<component_type>());
      REQUIRE(ent2->HasComponent<math_cs::Transform>());

      component_ptr ptr2 = ent2->GetComponent<component_type>();

      CHECK( (ptr2->GetEntity() == ent2) );
      CHECK( (ptr2->GetParent()->GetEntity() == ent) );
      CHECK(ent2->GetComponent<math_cs::Transform>()->GetPosition() == 
            math_t::Vec3f32(0.0f, 0.0f, 0.0f));
    }

    //SECTION("Add", "")
    {
      entity_ptr ent = entMgr->CreateEntity();

      pref_gfx::SceneNode(entMgr.get(), compMgr.get())
        .Position(math_t::Vec3f32(2.0f, 1.0f, 5.0f))
        .Add(ent);

      REQUIRE(ent->HasComponent<component_type>());
      REQUIRE(ent->HasComponent<math_cs::Transform>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK( (ptr->GetEntity() == ent) );
    }

    system->Initialize();
    system->ProcessActiveEntities();
  }
};

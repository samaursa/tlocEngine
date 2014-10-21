#include "tlocTestCommon.h"

#include <tlocCore/logging/tlocLogger.h>
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

      // testing Issue #83
      TLOC_TEST_ASSERT
      {
        entity_ptr parentEnt = pref_gfx::SceneNode(entMgr.get(), compMgr.get())
          .Create();

        gfx_cs::scene_node_sptr parentEntSN = 
          parentEnt->GetComponent<gfx_cs::SceneNode>();

        parentEntSN->AddChild(core_sptr::ToVirtualPtr(parentEntSN));
      }
      TLOC_TEST_ASSERT_CHECK();

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

    // testing Issue #83
    gfx_cs::scene_node_sptr sn = core_sptr::MakeShared<gfx_cs::SceneNode>();

    graphics::GetLogger().SetBreakOnSeverity(core_log::p_log::severity::Info::s_value);
    TLOC_TEST_ASSERT
    {
      entity_ptr dummyEnt = entMgr->CreateEntity();

      math_cs::transform_sptr t = core_sptr::MakeShared<math_cs::Transform>();
      gfx_cs::scene_node_sptr sn = core_sptr::MakeShared<gfx_cs::SceneNode>();

      entMgr->InsertComponent(core_cs::EntityManager::Params(dummyEnt, t).Orphan(true));
      entMgr->InsertComponent(core_cs::EntityManager::Params(dummyEnt, sn));

      system->Initialize();
    }
    TLOC_TEST_ASSERT_CHECK();

    graphics::GetLogger().SetBreakOnSeverity(core_log::p_log::severity::Warning::s_value);
    TLOC_TEST_ASSERT
    {
      entity_ptr dummyEnt = entMgr->CreateEntity();
      entity_ptr dummyEnt2 = entMgr->CreateEntity();

      math_cs::transform_sptr t = core_sptr::MakeShared<math_cs::Transform>();
      gfx_cs::scene_node_sptr sn = core_sptr::MakeShared<gfx_cs::SceneNode>(dummyEnt2);

      entMgr->InsertComponent(core_cs::EntityManager::Params(dummyEnt, t).Orphan(true));
      entMgr->InsertComponent(core_cs::EntityManager::Params(dummyEnt, sn));

      system->Initialize();
    }
    TLOC_TEST_ASSERT_CHECK();

    graphics::GetLogger().ResetBreakOnSeverity();

    system->ProcessActiveEntities();
  }
};

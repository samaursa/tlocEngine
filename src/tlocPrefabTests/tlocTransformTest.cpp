#include "tlocTestCommon.h"

#include <tlocPrefab/math/tlocTransform.h>

namespace TestingTransform
{
  using namespace tloc;

  typedef core_cs::entity_vptr                    entity_ptr;
  typedef math_cs::Transform                      component_type;
  typedef math_cs::transform_sptr                 component_ptr;

  TEST_CASE("prefab/math/Transform", "")
  {
    core_cs::component_pool_mgr_vso compMgr;
    core_cs::event_manager_vso      evtMgr;
    core_cs::entity_manager_vso     entMgr(evtMgr.get());

    //SECTION("Construct", "")
    {
      component_ptr ptr = pref_math::Transform(entMgr.get(), compMgr.get())
        .Position(math_t::Vec3f32(5.0f, 0.5f, 7.0f))
        .Construct();

      CHECK(ptr->GetPosition() == math_t::Vec3f32(5.0f, 0.5f, 7.0f));
    }

    //SECTION("Create", "")
    {
      entity_ptr ent = pref_math::Transform(entMgr.get(), compMgr.get())
        .Position(math_t::Vec3f32(1.0f, 2.0f, 3.0f))
        .Create();

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = 
        ent->GetComponent<component_type>();

      CHECK(ptr->GetPosition() == math_t::Vec3f32(1.0f, 2.0f, 3.0f));
    }

    //SECTION("Add", "")
    {
      entity_ptr ent = entMgr->CreateEntity();

      pref_math::Transform(entMgr.get(), compMgr.get())
        .Position(math_t::Vec3f32(1.0f, 2.0f, 3.0f))
        .Add(ent);

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = 
        ent->GetComponent<component_type>();

      CHECK(ptr->GetPosition() == math_t::Vec3f32(1.0f, 2.0f, 3.0f));
    }
  }
};
#include "tlocTestCommon.h"

#include <tlocPrefab/graphics/tlocTextureCoords.h>

namespace 
{
  using namespace tloc;

  typedef core_cs::entity_vptr                    entity_ptr;
  typedef gfx_cs::TextureCoords                   component_type;
  typedef gfx_cs::texture_coords_sptr             component_ptr;

  TEST_CASE("prefab/graphics/TextureCoords", "")
  {
    core_cs::component_pool_mgr_vso compMgr;
    core_cs::event_manager_vso      evtMgr;
    core_cs::entity_manager_vso     entMgr(MakeArgs(evtMgr.get()));

    //SECTION("Construct", "")
    {
      component_ptr ptr = pref_gfx::TextureCoords(entMgr.get(), compMgr.get())
        .AddCoord(math_t::Vec2f32(0.0f, 0.0f))
        .AddCoord(math_t::Vec2f32(0.0f, 1.0f))
        .AddCoord(math_t::Vec2f32(1.0f, 1.0f))
        .AddCoord(math_t::Vec2f32(1.0f, 0.0f))
        .Construct();

      CHECK(ptr->GetNumSets() == 1);
      CHECK( (ptr->GetCoord(0) == math_t::Vec2f32(0.0f, 0.0f)) );
      CHECK( (ptr->GetCoord(1) == math_t::Vec2f32(0.0f, 1.0f)) );
      CHECK( (ptr->GetCoord(2) == math_t::Vec2f32(1.0f, 1.0f)) );
      CHECK( (ptr->GetCoord(3) == math_t::Vec2f32(1.0f, 0.0f)) );
    }

    //SECTION("Create", "")
    {
      entity_ptr ent = pref_gfx::TextureCoords(entMgr.get(), compMgr.get())
        .AddCoord(math_t::Vec2f32(0.0f, 0.0f))
        .AddCoord(math_t::Vec2f32(0.0f, 1.0f))
        .AddCoord(math_t::Vec2f32(1.0f, 1.0f))
        .AddCoord(math_t::Vec2f32(1.0f, 0.0f))
        .Create();

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = 
        ent->GetComponent<component_type>();

      CHECK(ptr->GetNumSets() == 1);
      CHECK( (ptr->GetCoord(0) == math_t::Vec2f32(0.0f, 0.0f)) );
      CHECK( (ptr->GetCoord(1) == math_t::Vec2f32(0.0f, 1.0f)) );
      CHECK( (ptr->GetCoord(2) == math_t::Vec2f32(1.0f, 1.0f)) );
      CHECK( (ptr->GetCoord(3) == math_t::Vec2f32(1.0f, 0.0f)) );
    }

    //SECTION("Add", "")
    {
      entity_ptr ent = entMgr->CreateEntity();

      pref_gfx::TextureCoords(entMgr.get(), compMgr.get())
        .AddCoord(math_t::Vec2f32(0.0f, 0.0f))
        .AddCoord(math_t::Vec2f32(0.0f, 1.0f))
        .AddCoord(math_t::Vec2f32(1.0f, 1.0f))
        .AddCoord(math_t::Vec2f32(1.0f, 0.0f))
        .Add(ent);

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = 
        ent->GetComponent<component_type>();

      CHECK(ptr->GetNumSets() == 1);
      CHECK( (ptr->GetCoord(0) == math_t::Vec2f32(0.0f, 0.0f)) );
      CHECK( (ptr->GetCoord(1) == math_t::Vec2f32(0.0f, 1.0f)) );
      CHECK( (ptr->GetCoord(2) == math_t::Vec2f32(1.0f, 1.0f)) );
      CHECK( (ptr->GetCoord(3) == math_t::Vec2f32(1.0f, 0.0f)) );
    }
  }
};

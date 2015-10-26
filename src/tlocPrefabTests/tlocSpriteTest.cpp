#include "tlocTestCommon.h"

#include <tlocCore/io/tlocFileIO.h>

#include <tlocGraphics/component_system/tlocTextureAnimatorSystem.h>
#include <tlocGraphics/component_system/tlocTextureAnimator.h>
#include <tlocGraphics/media/tlocSpriteLoader.h>
#include <tlocPrefab/graphics/tlocSprite.h>

namespace 
{
  using namespace tloc;

  typedef core_cs::entity_vptr                    entity_ptr;
  typedef gfx_cs::TextureAnimator                 component_type;
  typedef gfx_cs::texture_animator_sptr           component_ptr;

  typedef gfx_cs::texture_animation_system_vso    system_vso;

  TEST_CASE("", "")
  {
    core_cs::component_pool_mgr_vso compMgr;
    core_cs::event_manager_vso      evtMgr;
    core_cs::entity_manager_vso     entMgr(evtMgr.get());

    system_vso                      system(evtMgr.get(), entMgr.get());
    TLOC_UNUSED(system);

    // Load the sprite
    core_io::Path p(GetAssetsPath() + core_str::String("/spriteTexturePacker.xml"));
    core_io::FileIO_ReadA f(p);
    f.Open();

    core_str::String xmlContents;
    f.GetContents(xmlContents);

    gfx_med::SpriteLoader_TexturePacker tp;
    REQUIRE(tp.IsSupported(xmlContents));
    REQUIRE(tp.Init(xmlContents, core_ds::MakeTuple(2380, 2040)).Succeeded());

    //SECTION("Construct", "")
    {
      component_ptr ptr = pref_gfx::SpriteAnimation(entMgr.get(), compMgr.get())
        .Loop(false).Fps(10).Construct(tp.begin(), tp.end());

      CHECK(ptr->GetFPS() == 10);
      CHECK_FALSE(ptr->IsLooping());
      CHECK(ptr->GetCurrentSpriteSequence().GetNumSets() == 52);
    }

    //SECTION("Add", "")
    {
      entity_ptr ent = entMgr->CreateEntity();

      pref_gfx::SpriteAnimation(entMgr.get(), compMgr.get())
        .Loop(true).Fps(24).Add(ent, tp.begin(), tp.end());

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK(ptr->GetFPS() == 24);
      CHECK(ptr->IsLooping());
      CHECK(ptr->GetCurrentSpriteSequence().GetNumSets() == 52);
    }
  }
};

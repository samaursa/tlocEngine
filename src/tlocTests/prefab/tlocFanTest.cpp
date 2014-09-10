#include "tlocTestCommon.h"

#include <tlocGraphics/component_system/tlocFan.h>
#include <tlocGraphics/component_system/tlocFanRenderSystem.h>

#include <tlocGraphics/window/tlocWindow.h>
#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocPrefab/graphics/tlocFan.h>
#include <tlocPrefab/graphics/tlocTextureCoords.h>

namespace 
{
  using namespace tloc;

  typedef core_cs::entity_vptr                    entity_ptr;
  typedef gfx_cs::Fan                             component_type;
  typedef gfx_cs::fan_sptr                        component_ptr;

  typedef gfx_cs::fan_render_system_vso           system_vso;

  TEST_CASE("prefab/gfx/Fan", "")
  {
    core_cs::component_pool_mgr_vso compMgr;
    core_cs::event_manager_vso      evtMgr;
    core_cs::entity_manager_vso     entMgr(MakeArgs(evtMgr.get()));

    system_vso                      system(MakeArgs(evtMgr.get(), entMgr.get()) );
    TLOC_UNUSED(system);

    // -----------------------------------------------------------------------
    // renderer and window

    gfx_win::Window win;
    win.Create( gfx_win::Window::graphics_mode::Properties(1024, 768),
                gfx_win::WindowSettings("Object File Loader") );
    core_err::Error err = gfx_gl::InitializePlatform();
    REQUIRE(err.Succeeded());
    
    //SECTION("Construct", "")
    {
      component_ptr ptr = pref_gfx::Fan(entMgr.get(), compMgr.get())
        .Circle(math_t::Circlef(math_t::Circlef::diameter(2.0f)) )
        .Sides(24)
        .Construct();

      CHECK(ptr->GetEllipseRef().GetRadius() == Approx(1.0f));
      CHECK(ptr->GetNumSides() == 24);
    }

    //SECTION("Create", "")
    {
      entity_ptr ent = pref_gfx::Fan(entMgr.get(), compMgr.get())
        .Circle(math_t::Circlef(math_t::Circlef::diameter(4.0f)) )
        .Sides(100)
        .Create();

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK(ent->HasComponent<gfx_cs::TextureCoords>());
      CHECK(ptr->GetEllipseRef().GetRadius() == Approx(2.0f));
      CHECK(ptr->GetNumSides() == 100);
    }

    //SECTION("Add", "")
    {
      entity_ptr ent = entMgr->CreateEntity();

      ent = pref_gfx::Fan(entMgr.get(), compMgr.get())
        .Circle(math_t::Circlef(math_t::Circlef::diameter(4.0f)) )
        .Sides(100)
        .TexCoords(false)
        .Create();

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK_FALSE(ent->HasComponent<gfx_cs::TextureCoords>());
      CHECK(ptr->GetEllipseRef().GetRadius() == Approx(2.0f));
      CHECK(ptr->GetNumSides() == 100);
    }

    system->SetRenderer(win.GetRenderer());
    system->Initialize();
    system->ProcessActiveEntities(); 
  }
};

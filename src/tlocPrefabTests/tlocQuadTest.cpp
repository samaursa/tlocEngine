#include "tlocTestCommon.h"

#include <tlocGraphics/component_system/tlocQuad.h>
#include <tlocGraphics/component_system/tlocMeshRenderSystem.h>

#include <tlocGraphics/window/tlocWindow.h>
#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocPrefab/graphics/tlocQuad.h>
#include <tlocPrefab/graphics/tlocTextureCoords.h>

namespace 
{
  using namespace tloc;

  typedef core_cs::entity_vptr                    entity_ptr;
  typedef gfx_cs::Mesh                            component_type;
  typedef gfx_cs::mesh_sptr                       component_ptr;

  typedef gfx_cs::mesh_render_system_vso          system_vso;

  TEST_CASE("prefab/gfx/Quad", "")
  {
    core_cs::component_pool_mgr_vso compMgr;
    core_cs::event_manager_vso      evtMgr;
    core_cs::entity_manager_vso     entMgr(evtMgr.get());

    system_vso                      system(evtMgr.get(), entMgr.get());
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
      using math_t::Rectf_c;

      component_ptr ptr = pref_gfx::Quad(entMgr.get(), compMgr.get())
        .Dimensions(Rectf_c(Rectf_c::width(1.0f), Rectf_c::height(2.0f)) )
        .Construct();
    }

    //SECTION("Create", "")
    {
      using math_t::Rectf_bl;

      entity_ptr ent = pref_gfx::Quad(entMgr.get(), compMgr.get())
        .Dimensions(Rectf_bl(Rectf_bl::width(2.0f), Rectf_bl::height(1.0f)) )
        .Create();

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK_FALSE(ent->HasComponent<gfx_cs::TextureCoords>());
    }

    {
      using math_t::Rectf_bl;

      entity_ptr ent = pref_gfx::QuadNoTexCoords(entMgr.get(), compMgr.get())
        .Dimensions(Rectf_bl(Rectf_bl::width(2.0f), Rectf_bl::height(1.0f)) )
        .Sprite(true)
        .Create();

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK(ent->HasComponent<gfx_cs::TextureCoords>());
    }

    //SECTION("Add", "")
    {
      using math_t::Rectf_bl;

      entity_ptr ent = entMgr->CreateEntity();

      pref_gfx::QuadNoTexCoords(entMgr.get(), compMgr.get())
        .Dimensions(Rectf_bl(Rectf_bl::width(2.0f), Rectf_bl::height(1.0f)) )
        .Add(ent);

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK_FALSE(ent->HasComponent<gfx_cs::TextureCoords>());
    }

    system->SetRenderer(win.GetRenderer());
    system->Initialize();
    system->ProcessActiveEntities(); 
  }
};

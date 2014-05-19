#include "tlocTestCommon.h"

#include <tlocGraphics/component_system/tlocMesh.h>
#include <tlocGraphics/component_system/tlocMeshRenderSystem.h>

#include <tlocGraphics/window/tlocWindow.h>
#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocPrefab/graphics/tlocCuboid.h>

namespace 
{
  using namespace tloc;

  typedef core_cs::entity_vptr                    entity_ptr;
  typedef gfx_cs::Mesh                            component_type;
  typedef gfx_cs::mesh_sptr                       component_ptr;

  typedef gfx_cs::mesh_render_system_vso          system_vso;

  TEST_CASE("prefab/gfx/Mesh", "")
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
      using math_t::Cuboidf;

      component_ptr ptr = pref_gfx::Cuboid(entMgr.get(), compMgr.get())
        .Dimensions(Cuboidf(Cuboidf::width(2.0f), 
                            Cuboidf::height(2.0f), 
                            Cuboidf::depth(2.0f)) )
        .Construct();

      CHECK(ptr->IsNormalsEnabled());
      CHECK(ptr->IsTexCoordsEnabled());
    }

    //SECTION("Create", "")
    {
      using math_t::Cuboidf;

      entity_ptr ent = pref_gfx::Cuboid(entMgr.get(), compMgr.get())
        .Dimensions(Cuboidf(Cuboidf::width(2.0f), 
                            Cuboidf::height(2.0f), 
                            Cuboidf::depth(2.0f)) )
        .Normals(false)
        .TexCoords(false)
        .Create();

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK_FALSE(ptr->IsNormalsEnabled());
      CHECK_FALSE(ptr->IsTexCoordsEnabled());
    }

    //SECTION("Add", "")
    {
      using math_t::Cuboidf;

      entity_ptr ent = entMgr->CreateEntity();

      pref_gfx::Cuboid(entMgr.get(), compMgr.get())
        .Dimensions(Cuboidf(Cuboidf::width(2.0f), 
                            Cuboidf::height(2.0f), 
                            Cuboidf::depth(2.0f)) )
        .Normals(false)
        .TexCoords(false)
        .Add(ent);

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK_FALSE(ptr->IsNormalsEnabled());
      CHECK_FALSE(ptr->IsTexCoordsEnabled());
    }

    system->SetRenderer(win.GetRenderer());
    system->Initialize();
    system->ProcessActiveEntities(); 
  }
};

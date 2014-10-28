#include "tlocTestCommon.h"

#include <tlocCore/io/tlocFileIO.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocMaterialSystem.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocPrefab/graphics/tlocMaterial.h>

#include <tlocGraphics/window/tlocWindow.h>
#include <tlocGraphics/opengl/tlocOpenGL.h>

namespace 
{
  using namespace tloc;

  typedef core_cs::entity_vptr                    entity_ptr;
  typedef gfx_cs::Material                        component_type;
  typedef gfx_cs::material_sptr                   component_ptr;

  typedef gfx_cs::material_system_vso             system_vso;

#if defined (TLOC_OS_WIN)
  core_str::String shaderPathVS("/shaders/simple_vertex_shader.glsl");
#elif defined (TLOC_OS_IPHONE)
  core_str::String shaderPathVS("/shaders/simple_vertex_shader_gl_es_2_0.glsl");
#endif

#if defined (TLOC_OS_WIN)
  core_str::String shaderPathFS("/shaders/simple_fragment_shader.glsl");
#elif defined (TLOC_OS_IPHONE)
  core_str::String shaderPathFS("/shaders/simple_fragment_shader_gl_es_2_0.glsl");
#endif

  TEST_CASE("prefab/gfx/Material", "")
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

    // -----------------------------------------------------------------------
    // shader files

    core_str::String vsSource, fsSource;
    {
      core_io::FileIO_ReadA f(core_io::Path(GetAssetsPath() + shaderPathVS));
      f.Open();
      f.GetContents(vsSource);
    }

    {
      core_io::FileIO_ReadA f(core_io::Path(GetAssetsPath() + shaderPathFS));
      f.Open();
      f.GetContents(fsSource);
    }
    
    //SECTION("Construct", "")
    {
      component_ptr ptr = pref_gfx::Material(entMgr.get(), compMgr.get())
        .Construct(vsSource, fsSource);

      CHECK(ptr->GetVertexSource().compare(vsSource) == 0);
      CHECK(ptr->GetFragmentSource().compare(fsSource) == 0);
    }

    //SECTION("Create", "")
    {
      entity_ptr ent = pref_gfx::Material(entMgr.get(), compMgr.get())
        .Create(vsSource, fsSource);

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK(ptr->GetVertexSource().compare(vsSource) == 0);
      CHECK(ptr->GetFragmentSource().compare(fsSource) == 0);
    }

    //SECTION("Add", "")
    {
      entity_ptr ent = entMgr->CreateEntity();

      gfx_gl::uniform_vso u1; u1->SetName("u1");
      gfx_gl::uniform_vso u2; u2->SetName("u2");
      gfx_gl::uniform_vso u3; u3->SetName("u3");

      pref_gfx::Material matPrefab(entMgr.get(), compMgr.get());
      matPrefab.AssetsPath(GetAssetsPath()) 
               .AddUniform(u1.get())
               .AddUniform(u2.get())
               .AddUniform(u3.get())
               .Add(ent, core_io::Path(shaderPathVS), core_io::Path(shaderPathFS));

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK(ptr->GetVertexSource().compare(vsSource) == 0);
      CHECK(ptr->GetFragmentSource().compare(fsSource) == 0);

      REQUIRE(matPrefab.size_uniforms() == 3);
      pref_gfx::Material::uniform_itr itr = matPrefab.begin_uniforms();
      CHECK( (*itr)->GetName().compare("u1") == 0); ++itr;
      CHECK( (*itr)->GetName().compare("u2") == 0); ++itr;
      CHECK( (*itr)->GetName().compare("u3") == 0);
    }

    REQUIRE(gfx_gl::Error().Succeeded());

    system->Initialize();
    system->ProcessActiveEntities();
  }
};

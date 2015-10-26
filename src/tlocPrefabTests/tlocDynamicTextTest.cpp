#include "tlocTestCommon.h"

#include <tlocCore/io/tlocFileIO.h>
#include <tlocCore/string/tlocString.h>

#include <tlocGraphics/component_system/tlocDynamicText.h>
#include <tlocGraphics/component_system/tlocDynamicTextRenderSystem.h>

#include <tlocGraphics/window/tlocWindow.h>
#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocPrefab/graphics/tlocDynamicText.h>

namespace {

  using namespace tloc;

  const core_str::StringW 
    g_symbols = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ" 
                L"abcdefghijklmnopqrstuvwxyz" 
                L"1234567890!@#$%^&*()_+-=[]" 
                L"{}\\|;:'\",<.>/?`~ ";

};

namespace 
{
  using namespace tloc;

  typedef core_cs::entity_vptr                    entity_ptr;
  typedef gfx_cs::DynamicText                     component_type;
  typedef gfx_cs::dynamic_text_sptr               component_ptr;

  typedef gfx_cs::dyn_text_render_system_vso      system_vso;

  TEST_CASE("prefab/gfx/DynText", "")
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

    //------------------------------------------------------------------------
    // Load the required font

    core_io::Path fontPath( (core_str::String(GetAssetsPath()) + 
      "fonts/VeraMono-Bold.ttf" ).c_str() );

    core_io::FileIO_ReadB rb(fontPath);
    REQUIRE(rb.Open().Succeeded());

    core_str::String fontContents;
    rb.GetContents(fontContents);

    gfx_med::font_sptr f = core_sptr::MakeShared<gfx_med::Font>();
    f->Initialize(fontContents);

    using gfx_med::FontSize;
    FontSize fSize(FontSize::em(18),
      FontSize::dpi(win.GetDPI()) );

    gfx_med::Font::Params fontParams(fSize);
    fontParams.BgColor(gfx_t::Color(0.0f, 0.0f, 0.0f, 0.0f))
      .PaddingColor(gfx_t::Color(0.0f, 0.0f, 0.0f, 0.0f))
      .PaddingDim(core_ds::MakeTuple(10, 10));

    f->GenerateGlyphCache(g_symbols.c_str(), fontParams);
    
    //SECTION("Construct", "")
    {
      component_ptr ptr = pref_gfx::DynamicText(entMgr.get(), compMgr.get())
        .Construct(L"Test", f);

      CHECK(ptr->Get().compare(L"Test") == 0);
    }

    //SECTION("Create", "")
    {
      entity_ptr ent = pref_gfx::DynamicText(entMgr.get(), compMgr.get())
        .Alignment(gfx_cs::alignment::k_align_left)
        .Create(L"Test", f);

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK(ptr->Get().compare(L"Test") == 0);
      CHECK(ptr->GetAlignment() == gfx_cs::alignment::k_align_left);
    }

    //SECTION("Add", "")
    {
      entity_ptr ent = entMgr->CreateEntity();

      pref_gfx::DynamicText(entMgr.get(), compMgr.get())
        .Alignment(gfx_cs::alignment::k_align_left)
        .Add(ent, L"Test", f);

      REQUIRE(ent->HasComponent<component_type>());

      component_ptr ptr = ent->GetComponent<component_type>();

      CHECK(ptr->Get().compare(L"Test") == 0);
      CHECK(ptr->GetAlignment() == gfx_cs::alignment::k_align_left);
    }

    system->SetRenderer(win.GetRenderer());
    system->Initialize();
    system->ProcessActiveEntities(); 
  }
};

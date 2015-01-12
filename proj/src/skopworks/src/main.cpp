#include <tlocCore/tloc_core.h>
#include <tlocGraphics/tloc_graphics.h>
#include <tlocMath/tloc_math.h>
#include <tlocPrefab/tloc_prefab.h>

#include <gameAssetsPath.h>

using namespace tloc;

namespace {

#if defined (TLOC_OS_WIN)
    core_str::String shaderPathVS("/shaders/tlocOneTextureVS_2D.glsl");
#elif defined (TLOC_OS_IPHONE)
    core_str::String shaderPathVS("/shaders/tlocOneTextureVS_2D_gl_es_2_0.glsl");
#endif

#if defined (TLOC_OS_WIN)
    core_str::String shaderPathFS("/shaders/tlocOneTextureFS.glsl");
#elif defined (TLOC_OS_IPHONE)
    core_str::String shaderPathFS("/shaders/tlocOneTextureFS_gl_es_2_0.glsl");
#endif

};

// ///////////////////////////////////////////////////////////////////////
// WindowCallback handler

class WindowCallback
{
public:
  WindowCallback()
    : m_endProgram(false)
  { }

  core_dispatch::Event 
    OnWindowEvent(const gfx_win::WindowEvent& a_event)
  {
    if (a_event.m_type == gfx_win::WindowEvent::close)
    { m_endProgram = true; }

    return core_dispatch::f_event::Continue();
  }

  bool  m_endProgram;
};
TLOC_DEF_TYPE(WindowCallback);

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int TLOC_MAIN(int argc, char *argv[])
{
  TLOC_UNUSED_2(argc, argv);

  gfx_win::Window win;
  WindowCallback  winCallback;

  win.Register(&winCallback);
  win.Create( gfx_win::Window::graphics_mode::Properties(1024, 768),
    gfx_win::WindowSettings("2LoC Engine") );

  // -----------------------------------------------------------------------
  // Initialize OpenGL for the current platform

  if (gfx_gl::InitializePlatform() != ErrorSuccess)
  { 
    TLOC_LOG_GFX_ERR() << "Renderer failed to initialize"; 
    return 1;
  }

  core_cs::ECS scene;
  scene.AddSystem<gfx_cs::MaterialSystem>();
  auto meshSys = scene.AddSystem<gfx_cs::MeshRenderSystem>();
  meshSys->SetRenderer(win.GetRenderer());

  //------------------------------------------------------------------------

  gfx_med::ImageLoaderPng png;
  core_io::Path path( (core_str::String(GetAssetsPath()) +
    "/images/engine_logo.png").c_str() );

  if (png.Load(path) != ErrorSuccess)
  { TLOC_ASSERT_FALSE("Image did not load!"); }

  // gl::Uniform supports quite a few types, including a TextureObject
  gfx_gl::texture_object_vso to;
  to->Initialize(png.GetImage());

  gfx_gl::uniform_vso  u_to;
  u_to->SetName("s_texture").SetValueAs(*to);

  //------------------------------------------------------------------------

  math_t::Rectf_c rect(math_t::Rectf_c::width(1.0f * 1.5f),
                       math_t::Rectf_c::height(win.GetAspectRatio().Get() * 1.5f ) );

  core_cs::entity_vptr q = scene.CreatePrefab<pref_gfx::Quad>()
    .Dimensions(rect).Create();

  scene.CreatePrefab<pref_gfx::Material>()
    .AssetsPath(GetAssetsPath())
    .AddUniform(u_to.get())
    .Add(q, core_io::Path(shaderPathVS), core_io::Path(shaderPathFS));

  //------------------------------------------------------------------------

  scene.Initialize();

  //------------------------------------------------------------------------
  // Main loop
  auto renderer = win.GetRenderer();
  while (win.IsValid() && !winCallback.m_endProgram)
  {
    gfx_win::WindowEvent  evt;
    while (win.GetEvent(evt))
    { }

    // Finally, process the fan
    renderer->ApplyRenderSettings();
    scene.Process(0.0f);
    renderer->Render();

    win.SwapBuffers();
  }

  //------------------------------------------------------------------------
  // Exiting
  TLOC_LOG_CORE_INFO() << "Exiting normally";

  return 0;

}

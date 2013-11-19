#include <tlocCore/tloc_core.h>
#include <tlocGraphics/tloc_graphics.h>
#include <tlocMath/tloc_math.h>
#include <tlocPrefab/tloc_prefab.h>

#include <tlocCore/memory/tlocLinkMe.cpp>

#include <gameAssetsPath.h>

using namespace tloc;

class WindowCallback
{
public:
  WindowCallback()
    : m_endProgram(false)
  { }

  void OnWindowEvent(const gfx_win::WindowEvent& a_event)
  {
    if (a_event.m_type == gfx_win::WindowEvent::close)
    { m_endProgram = true; }
  }

  bool  m_endProgram;
};
TLOC_DEF_TYPE(WindowCallback);

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
  { printf("\nRenderer failed to initialize"); return 1; }

  //------------------------------------------------------------------------
  // All systems in the engine require an event manager and an entity manager
  core_cs::event_manager_sptr  eventMgr(new core_cs::EventManager());
  core_cs::entity_manager_sptr entityMgr(new core_cs::EntityManager(eventMgr));

  //------------------------------------------------------------------------
  // A component pool manager manages all the components in a particular
  // session/level/section.
  core_cs::ComponentPoolManager cpoolMgr;

  //------------------------------------------------------------------------
  // To render a fan, we need a fan render system - this is a specialized
  // system to render this primitive
  gfx_cs::QuadRenderSystem quadSys(eventMgr, entityMgr);
  quadSys.SetRenderer(win.GetRenderer());

  //------------------------------------------------------------------------
  // We cannot render anything without materials and its system
  gfx_cs::MaterialSystem    matSys(eventMgr, entityMgr);

  // NOTE: The fan render system expects a few shader variables to be declared
  //       and used by the shader (i.e. not compiled out). See the listed
  //       vertex and fragment shaders for more info.
#if defined (TLOC_OS_WIN)
    core_str::String shaderPathVS("/shaders/tlocOneTextureVS.glsl");
#elif defined (TLOC_OS_IPHONE)
    core_str::String shaderPathVS("/shaders/tlocOneTextureVS_gl_es_2_0.glsl");
#endif

#if defined (TLOC_OS_WIN)
    core_str::String shaderPathFS("/shaders/tlocOneTextureFS.glsl");
#elif defined (TLOC_OS_IPHONE)
    core_str::String shaderPathFS("/shaders/tlocOneTextureFS_gl_es_2_0.glsl");
#endif

  //------------------------------------------------------------------------
  // Prepare a texture for the material

  gfx_med::ImageLoaderPng png;
  core_io::Path path( (core_str::String(GetAssetsPath()) +
    "/images/engine_logo.png").c_str() );

  if (png.Load(path) != ErrorSuccess)
  { TLOC_ASSERT(false, "Image did not load!"); }

  // gl::Uniform supports quite a few types, including a TextureObject
  gfx_gl::texture_object_sptr to(new gfx_gl::TextureObject());
  to->Initialize(png.GetImage());
  to->Activate();

  gfx_gl::uniform_sptr  u_to(new gfx_gl::Uniform());
  u_to->SetName("s_texture").SetValueAs(to);

  //------------------------------------------------------------------------
  // The prefab library has some prefabricated entities for us

  math_t::Rectf rect(math_t::Rectf::width(1.0f * 1.5f),
                     math_t::Rectf::height(win.GetAspectRatio().Get() * 1.5f ) );

  core_cs::Entity* q = prefab_gfx::Quad(entityMgr.get(), &cpoolMgr).
    Dimensions(rect).Create();

  prefab_gfx::Material(entityMgr.get(), &cpoolMgr)
    .AssetsPath(GetAssetsPath())
    .AddUniform(u_to)
    .Add(q, core_io::Path(shaderPathVS), core_io::Path(shaderPathFS));

  //------------------------------------------------------------------------
  // All systems need to be initialized once

  quadSys.Initialize();
  matSys.Initialize();

  //------------------------------------------------------------------------
  // Main loop
  while (win.IsValid() && !winCallback.m_endProgram)
  {
    gfx_win::WindowEvent  evt;
    while (win.GetEvent(evt))
    { }

    // Finally, process the fan
    win.GetRenderer()->ApplyRenderSettings();
    quadSys.ProcessActiveEntities();

    win.SwapBuffers();
  }

  //------------------------------------------------------------------------
  // Exiting
  printf("\nExiting normally");

  return 0;

}

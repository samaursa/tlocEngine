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

  //------------------------------------------------------------------------
  // Initialize renderer
  gfx_rend::Renderer  renderer;
  if (renderer.Initialize() != ErrorSuccess)
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

  //------------------------------------------------------------------------
  // We cannot render anything without materials and its system
  gfx_cs::MaterialSystem    matSys(eventMgr, entityMgr);

  // We need a material to attach to our entity (which we have not yet created).
  // NOTE: The fan render system expects a few shader variables to be declared
  //       and used by the shader (i.e. not compiled out). See the listed
  //       vertex and fragment shaders for more info.
  gfx_cs::Material  mat;
  {
#if defined (TLOC_OS_WIN)
    core_str::String shaderPath("/shaders/tlocOneTextureVS.glsl");
#elif defined (TLOC_OS_IPHONE)
    core_str::String shaderPath("/shaders/tlocOneTextureVS_gl_es_2_0.glsl");
#endif

    shaderPath = GetAssetsPath() + shaderPath;
    core_io::FileIO_ReadA shaderFile(shaderPath.c_str());

    if (shaderFile.Open() != ErrorSuccess)
    { printf("\nUnable to open the vertex shader"); return 1;}

    core_str::String code;
    shaderFile.GetContents(code);
    mat.SetVertexSource(code);
  }
  {
#if defined (TLOC_OS_WIN)
    core_str::String shaderPath("/shaders/tlocOneTextureFS.glsl");
#elif defined (TLOC_OS_IPHONE)
    core_str::String shaderPath("/shaders/tlocOneTextureFS_gl_es_2_0.glsl");
#endif

    shaderPath = GetAssetsPath() + shaderPath;
    core_io::FileIO_ReadA shaderFile(shaderPath.c_str());

    if (shaderFile.Open() != ErrorSuccess)
    { printf("\nUnable to open the fragment shader"); return 1;}

    core_str::String code;
    shaderFile.GetContents(code);
    mat.SetFragmentSource(code);
  }

  //------------------------------------------------------------------------
  // Add a texture to the material. We need:
  //  * an image
  //  * a TextureObject (preparing the image for OpenGL)
  //  * a Uniform (all textures are uniforms in shaders)
  //  * a ShaderOperator (this is what the material will take)
  //
  // The material takes in a 'MasterShaderOperator' which is the user defined
  // shader operator and over-rides any shader operators that the systems
  // may be setting. Any uniforms/shaders set in the 'MasterShaderOperator'
  // that have the same name as the one in the system will be given preference.

  gfx_med::ImageLoaderPng png;
  core_io::Path path( (core_str::String(GetAssetsPath()) +
    "/images/engine_logo.png").c_str() );

  if (png.Load(path) != ErrorSuccess)
  { TLOC_ASSERT(false, "Image did not load!"); }

  // gl::Uniform supports quite a few types, including a TextureObject
  gfx_gl::texture_object_sptr to(new gfx_gl::TextureObject());
  to->Initialize(png.GetImage());

  gfx_gl::uniform_sptr  u_to(new gfx_gl::Uniform());
  u_to->SetName("s_texture").SetValueAs(to);

  gfx_gl::shader_operator_sptr so =
    gfx_gl::shader_operator_sptr(new gfx_gl::ShaderOperator());
  so->AddUniform(u_to);

  // Finally, set this shader operator as the master operator (aka user operator)
  // in our material.
  mat.AddShaderOperator(so);

  //------------------------------------------------------------------------
  // The prefab library has some prefabricated entities for us

  math_t::Rectf rect(math_t::Rectf::width(1.0f * 2.0f),
                     math_t::Rectf::height(win.GetAspectRatio().Get() * 2.0f ) );

  core_cs::Entity* q = prefab_gfx::CreateQuad(*entityMgr.get(), cpoolMgr, rect);
  entityMgr->InsertComponent(q, &mat);

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
    quadSys.ProcessActiveEntities();

    win.SwapBuffers();
  }

  //------------------------------------------------------------------------
  // Exiting
  printf("\nExiting normally");

  return 0;

}

#include "tlocTestCommon.h"

#include <tlocCore/io/tlocFileIO.h>

#include <tlocGraphics/renderer/tlocRenderer.h>
#include <tlocGraphics/opengl/tlocShader.h>
#include <tlocGraphics/window/tlocWindow.h>

namespace TestingShaderComponent
{

  const char* vShaderStr =
#if defined (TLOC_OS_WIN)
    "#version 140                       \n"
#elif defined (TLOC_OS_IPHONE)
    "#version 100                       \n"
#endif
    "\n\
    attribute vec4 vVertex;             \n\
    attribute vec4 vColor;              \n\
    \n\
    varying lowp vec4 vVaryingColor;    \n\
    \n\
    void main(void)                     \n\
    {                                   \n\
    vVaryingColor = vColor;             \n\
    gl_Position   = vVertex;            \n\
    }";

  const char* fShaderStr =
#if defined (TLOC_OS_WIN)
    "#version 140                       \n"
#elif defined (TLOC_OS_IPHONE)
    "#version 100                       \n"
#endif
    "\n\
    varying lowp vec4 vVaryingColor;    \n\
    \n\
    void main(void)                     \n\
    {                                   \n\
    gl_FragColor = vVaryingColor;       \n\
    }";

  using namespace tloc;
  using namespace core;
  using namespace string;
  using namespace graphics;

#if defined (TLOC_OS_WIN)
  String g_vShaderPath(GetAssetsPath() + String("/shaders/simple_vertex_shader.glsl") );
  String g_fShaderPath(GetAssetsPath() + String("/shaders/simple_fragment_shader.glsl") );
#elif defined (TLOC_OS_IPHONE)
  String g_vShaderPath(GetAssetsPath() + String("/shaders/simple_vertex_shader_gl_es_2_0.glsl") );
  String g_fShaderPath(GetAssetsPath() + String("/shaders/simple_fragment_shader_gl_es_2_0.glsl") );
#endif

  TEST_CASE("Graphics/ShaderComponent/HardCoded", "")
  {
    using namespace graphics::win;
    using gfx_rend::Renderer;

    typedef Window::graphics_mode         graphics_mode;

    Window win;
    win.Create(graphics_mode(graphics_mode::Properties(1, 1)),
      WindowSettings("Atom & Eve"));

    // Initialize renderer
    REQUIRE(Renderer().Initialize() != common_error_types::error_initialize);

    {
      gl::VertexShader vs;
    }

    gl::VertexShader vShader;

    typedef gl::p_shader_program::shader_type::Vertex vertex_shader_type;
    CHECK(vShader.Load(vShaderStr) == ErrorSuccess);
    CHECK(vShader.Compile() == ErrorSuccess);

    gl::FragmentShader fShader;

    typedef gl::p_shader_program::shader_type::Fragment fragment_shader_type;
    CHECK(fShader.Load(fShaderStr) == ErrorSuccess);
    CHECK(fShader.Compile() == ErrorSuccess);
  }

  TEST_CASE("Graphics/ShaderComponent/FromFile", "")
  {
    using namespace graphics::win;
    using gfx_rend::Renderer;

    typedef Window::graphics_mode       graphics_mode;

    Window win;
    win.Create(graphics_mode(graphics_mode::Properties(1, 1)),
               WindowSettings("Atom & Eve"));

    // Initialize renderer
    REQUIRE(Renderer().Initialize() != common_error_types::error_initialize);

    // Load the files
    io::FileIO_ReadA vsFile = io::FileIO_ReadA( core_io::Path(g_vShaderPath) );
    io::FileIO_ReadA fsFile = io::FileIO_ReadA( core_io::Path(g_fShaderPath) );

    REQUIRE(vsFile.Open() == ErrorSuccess);
    REQUIRE(fsFile.Open() == ErrorSuccess);

    String vsCode, fsCode;
    REQUIRE(vsFile.GetContents(vsCode) == ErrorSuccess);
    REQUIRE(fsFile.GetContents(fsCode) == ErrorSuccess);

    // Start testing the shaders
    gl::VertexShader vShader;

    CHECK(vShader.Load(vsCode.c_str()) == ErrorSuccess);
    CHECK(vShader.Compile() == ErrorSuccess);

    gl::FragmentShader fShader;

    CHECK(fShader.Load(fsCode.c_str()) == ErrorSuccess);
    CHECK(fShader.Compile() == ErrorSuccess);
  }
};

#include "tlocTestCommon.h"

#include <tlocCore/io/tlocFileIO.h>

#include <tlocGraphics/renderer/tlocRenderer.h>
#include <tlocGraphics/opengl/tlocShader.h>
#include <tlocGraphics/window/tlocWindow.h>

namespace TestingShaderComponent
{
  const char* vShaderStr =
    "#ifdef GL_ES                       \n\
     #  version 100                     \n\
     #else                              \n\
     #  version 140                     \n\
     #endif                             \n\
                                        \n\
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
    "#ifdef GL_ES                       \n\
     #  version 100                     \n\
     #else                              \n\
     #  version 140                     \n\
     #endif                             \n\
                                        \n\
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

  String g_vShaderPath(GetAssetPath() + String("/shaders/simple_vertex_shader.glsl") );
  String g_fShaderPath(GetAssetPath() + String("/shaders/simple_fragment_shader.glsl") );

  TEST_CASE("Graphics/ShaderComponent/HardCoded", "")
  {
    using namespace graphics::win;

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
    CHECK(vShader.Load(vShaderStr) == ErrorSuccess());
    CHECK(vShader.Compile() == ErrorSuccess());

    gl::FragmentShader fShader;

    typedef gl::p_shader_program::shader_type::Fragment fragment_shader_type;
    CHECK(fShader.Load(fShaderStr) == ErrorSuccess());
    CHECK(fShader.Compile() == ErrorSuccess());
  }

  TEST_CASE("Graphics/ShaderComponent/FromFile", "")
  {
    using namespace graphics::win;
    typedef Window::graphics_mode       graphics_mode;

    Window win;
    win.Create(graphics_mode(graphics_mode::Properties(1, 1)),
               WindowSettings("Atom & Eve"));

    // Initialize renderer
    REQUIRE(Renderer().Initialize() != common_error_types::error_initialize);

    // Load the files
    io::FileIO_ReadA vsFile( g_vShaderPath.c_str() );
    io::FileIO_ReadA fsFile( g_fShaderPath.c_str() );

    REQUIRE(vsFile.Open() == ErrorSuccess());
    REQUIRE(fsFile.Open() == ErrorSuccess());

    String vsCode, fsCode;
    REQUIRE(vsFile.GetContents(vsCode) == ErrorSuccess());
    REQUIRE(fsFile.GetContents(fsCode) == ErrorSuccess());

    // Start testing the shaders
    gl::VertexShader vShader;

    CHECK(vShader.Load(vsCode.c_str()) == ErrorSuccess());
    CHECK(vShader.Compile() == ErrorSuccess());

    gl::FragmentShader fShader;

    CHECK(fShader.Load(fsCode.c_str()) == ErrorSuccess());
    CHECK(fShader.Compile() == ErrorSuccess());
  }
};

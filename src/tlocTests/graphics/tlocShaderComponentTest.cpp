#include "tlocTestCommon.h"

#include <tlocCore/io/tlocFileIO.h>

#include <tlocGraphics/renderer/tlocRenderer.h>
#include <tlocGraphics/opengl/tlocShaderComponent.h>
#include <tlocGraphics/window/tlocWindow.h>

namespace TestingShaderComponent
{
  const char* vShaderStr =
    "#ifdef GL_ES                       \n\
     #  version 100                     \n\
     #else                              \n\
     #  version 120                     \n\
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
     #  version 120                     \n\
                                        \n\
    varying lowp vec4 vVaryingColor;    \n\
                                        \n\
    void main(void)                     \n\
    {                                   \n\
    gl_FragColor = vVaryingColor;       \n\
    }";


  using namespace tloc;
  using namespace tloc::core;
  using namespace graphics;

  String g_vShaderPath(GetAssetPath() + String("/shaders/simple_vertex_shader.glsl") );
  String g_fShaderPath(GetAssetPath() + String("/shaders/simple_fragment_shader.glsl") );

  TEST_CASE("Graphics/ShaderComponent/HardCoded", "")
  {
    typedef Window<>::graphics_mode         graphics_mode;
    Window<> win;
    win.Create(graphics_mode(graphics_mode::Properties(1, 1)),
      WindowSettings("Atom & Eve"));

    // Initialize renderer
    REQUIRE(Renderer().Initialize() != common_error_types::error_initialize);

    gl::ShaderComponent vShader;

    typedef gl::p_shader_program::shader_type::Vertex vertex_shader_type;
    CHECK(vShader.LoadShader(vShaderStr, vertex_shader_type() ) == true);
    CHECK(vShader.CompileShader() == true);

    gl::ShaderComponent fShader;

    typedef gl::p_shader_program::shader_type::Fragment fragment_shader_type;
    CHECK(fShader.LoadShader(fShaderStr, fragment_shader_type() ) == true);
    CHECK(fShader.CompileShader() == true);
  }

  TEST_CASE("Graphics/ShaderComponent/FromFile", "")
  {
    typedef Window<>::graphics_mode       graphics_mode;
    Window<> win;
    win.Create(graphics_mode(graphics_mode::Properties(1, 1)),
               WindowSettings("Atom & Eve"));

    // Initialize renderer
    REQUIRE(Renderer().Initialize() != common_error_types::error_initialize);

    // Load the files
    io::FileIO_ReadA vsFile( g_vShaderPath.c_str() );
    io::FileIO_ReadA fsFile( g_fShaderPath.c_str() );

    REQUIRE(vsFile.Open() == common_error_types::error_success);
    REQUIRE(fsFile.Open() == common_error_types::error_success);

    String vsCode, fsCode;
    REQUIRE(vsFile.GetContents(vsCode) == common_error_types::error_success);
    REQUIRE(fsFile.GetContents(fsCode) == common_error_types::error_success);

    // Start testing the shaders
    gl::ShaderComponent vShader;

    typedef gl::p_shader_program::shader_type::Vertex vertex_shader_type;
    CHECK(vShader.LoadShader(vsCode.c_str(), vertex_shader_type()) == true);
    CHECK(vShader.CompileShader() == true);

  }
};
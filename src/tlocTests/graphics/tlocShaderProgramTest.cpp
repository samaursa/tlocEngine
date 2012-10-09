#include "tlocTestCommon.h"

#include <tlocGraphics/renderer/tlocRenderer.h>
#include <tlocGraphics/window/tlocWindow.h>
#include <tlocGraphics/opengl/tlocShaderComponent.h>
#include <tlocGraphics/opengl/tlocShaderProgram.h>

namespace TestingShaderProgram
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
  using namespace graphics;

  TEST_CASE("Graphics/ShaderProgram/HardCoded", "")
  {
    typedef Window<>::graphics_mode         graphics_mode;
    Window<> win;
    win.Create(graphics_mode(graphics_mode::Properties(1, 1)),
      WindowSettings("Atom & Eve"));

    // Initialize glew
    REQUIRE(Renderer().Initialize() != common_error_types::error_initialize);

    gl::ShaderComponent vShader;
    typedef gl::p_shader_program::shader_type::Vertex vertex_shader_type;
    REQUIRE(vShader.LoadShader(vShaderStr, vertex_shader_type()) == true);
    REQUIRE(vShader.CompileShader() == true);

    gl::ShaderComponent fShader;

    typedef gl::p_shader_program::shader_type::Fragment fragment_shader_type;
    REQUIRE(fShader.LoadShader(fShaderStr, fragment_shader_type() ) == true);
    REQUIRE(fShader.CompileShader() == true);

    gl::ShaderProgram sp;
    sp.AttachShaders(gl::ShaderProgram::two_shader_components(&vShader, &fShader));
    CHECK(sp.Link() == true);
  }
};

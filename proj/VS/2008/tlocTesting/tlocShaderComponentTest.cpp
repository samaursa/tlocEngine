#include "tlocTestCommon.h"

#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocOpenGLExt.h>

#include <tlocGraphics/opengl/tlocShaderComponent.h>
#include <tlocGraphics/window/tlocWindow.h>

namespace TestingShaderComponent
{
  const char* vShaderStr =
"#version 140                       \n\
                                    \n\
in vec4 vVertex;                    \n\
in vec4 vColor;                     \n\
                                    \n\
out vec4 vVaryingColor;             \n\
                                    \n\
void main(void)                     \n\
{                                   \n\
   vVaryingColor = vColor;          \n\
   gl_Position   = vVertex;         \n\
}";

  const char* fShaderStr =
"#version 140                       \n\
                                    \n\
out vec4 vFragColor;                \n\
in  vec4 vVaryingColor;             \n\
                                    \n\
void main(void)                     \n\
{                                   \n\
   vFragColor = vVaryingColor;      \n\
}";


  using namespace tloc;
  using namespace graphics;

  TEST_CASE("Graphics/ShaderComponent", "")
  {
    //typedef Window<>::graphics_mode         graphics_mode;
    //Window<> win;
    //win.Create(graphics_mode(graphics_mode::Properties(0, 0)),
    //  WindowSettings("Atom & Eve"));

    //// Initialize glew
    //REQUIRE(OpenGLExt::Initialize() != OpenGLExt::error_init);

    //gl::ShaderComponent vShader;

    //typedef gl::p_shader_program::shader_type::Vertex vertex_shader_type;
    //CHECK(vShader.LoadShader(vShaderStr, vertex_shader_type() ) == true);
    //CHECK(vShader.CompileShader() == true);

    //gl::ShaderComponent fShader;

    //typedef gl::p_shader_program::shader_type::Fragment fragment_shader_type;
    //CHECK(fShader.LoadShader(fShaderStr, fragment_shader_type() ) == true);
    //CHECK(fShader.CompileShader() == true);
  }
};
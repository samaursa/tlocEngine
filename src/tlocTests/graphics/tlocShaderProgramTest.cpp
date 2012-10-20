#include "tlocTestCommon.h"

#include <tlocGraphics/renderer/tlocRenderer.h>
#include <tlocGraphics/window/tlocWindow.h>
#include <tlocGraphics/opengl/tlocShader.h>
#include <tlocGraphics/opengl/tlocShaderProgram.h>

namespace TestingShaderProgram
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

  const char* vShaderStrWithAttrAndUni =
    "#ifdef GL_ES                       \n\
     #  version 100                     \n\
     #else                              \n\
     #  version 140                     \n\
     #endif                             \n\
                                        \n\
    attribute vec4 vVertex;             \n\
    attribute vec4 vColor;              \n\
    uniform   vec4 vUni;                \n\
                                        \n\
    varying lowp vec4 vVaryingColor;    \n\
                                        \n\
    void main(void)                     \n\
    {                                   \n\
    vVaryingColor = vColor;             \n\
    vVaryingColor.x = vUni.x;           \n\
    gl_Position   = vVertex;            \n\
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

    gl::VertexShader vShader;
    REQUIRE(vShader.Load(vShaderStr) == ErrorSuccess());
    REQUIRE(vShader.CompileShader() == ErrorSuccess());

    gl::FragmentShader fShader;

    REQUIRE(fShader.Load(fShaderStr) == ErrorSuccess());
    REQUIRE(fShader.CompileShader() == ErrorSuccess());

    gl::ShaderProgram sp;
    sp.AttachShaders(gl::ShaderProgram::two_shader_components(&vShader, &fShader));
    CHECK(sp.Link() == ErrorSuccess());
  }

  TEST_CASE("Graphics/ShaderProgram/AttributesAndUniforms", "")
  {
    typedef Window<>::graphics_mode         graphics_mode;
    Window<> win;
    win.Create(graphics_mode(graphics_mode::Properties(1, 1)),
      WindowSettings("Atom & Eve"));

    REQUIRE(Renderer().Initialize() != common_error_types::error_initialize);

    gl::VertexShader vShader;
    REQUIRE(vShader.Load(vShaderStrWithAttrAndUni) == ErrorSuccess());
    REQUIRE(vShader.CompileShader() == ErrorSuccess());

    gl::ShaderProgram sp;
    sp.AttachShaders(gl::ShaderProgram::one_shader_component(&vShader));
    CHECK(sp.Link() == ErrorSuccess());

    CHECK(sp.GetNumAttributes() == 2);
    CHECK(sp.GetNumUniforms() == 1);

    CHECK(sp.GetInfo<gl::p_shader_program::DeleteStatus>() == 0);
    CHECK(sp.GetInfo<gl::p_shader_program::LinkStatus>() == 1);
    CHECK(sp.GetInfo<gl::p_shader_program::ValidateStatus>() == 1);
    CHECK(sp.GetInfo<gl::p_shader_program::AttachedShaders>() == 1);
    CHECK(sp.GetInfo<gl::p_shader_program::ActiveUniformMaxLength>() == 5);
    CHECK(sp.GetInfo<gl::p_shader_program::ActiveAttributeMaxLength>() == 8);
  }
};

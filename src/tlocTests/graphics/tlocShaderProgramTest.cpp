#include "tlocTestCommon.h"

#include <tlocGraphics/renderer/tlocRenderer.h>
#include <tlocGraphics/window/tlocWindow.h>
#include <tlocGraphics/opengl/tlocShader.h>
#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/types/tlocColor.h>
#include <tlocGraphics/opengl/tlocError.h>

#include <tlocMath/types/tlocVector4.h>

namespace TestingShaderProgram
{

#if defined (TLOC_OS_WIN)

  const char* vShaderStr =
    "#  version 140                     \n\
                                        \n\
    attribute vec4 vVertex;             \n\
    attribute vec4 vColor;              \n\
                                        \n\
    uniform vec4 u_Color;               \n\
                                        \n\
    varying lowp vec4 vVaryingColor;    \n\
                                        \n\
    void main(void)                     \n\
    {                                   \n\
    vVaryingColor = vColor * u_Color;   \n\
    gl_Position   = vVertex;            \n\
    }";

  const char* fShaderStr =
    "#  version 140                     \n\
                                        \n\
    varying lowp vec4 vVaryingColor;    \n\
                                        \n\
    void main(void)                     \n\
    {                                   \n\
    gl_FragColor = vVaryingColor;       \n\
    }";

#elif defined (TLOC_OS_IPHONE)

  const char* vShaderStr =
    "#  version 100                     \n\
    \n\
    attribute vec4 vVertex;             \n\
    attribute vec4 vColor;              \n\
    \n\
    uniform vec4 u_Color;               \n\
    \n\
    varying lowp vec4 vVaryingColor;    \n\
    \n\
    void main(void)                     \n\
    {                                   \n\
    vVaryingColor = vColor * u_Color;   \n\
    gl_Position   = vVertex;            \n\
    }";

  const char* fShaderStr =
    "#  version 100                     \n\
    \n\
    varying lowp vec4 vVaryingColor;    \n\
    \n\
    void main(void)                     \n\
    {                                   \n\
    gl_FragColor = vVaryingColor;       \n\
    }";

#endif

  using namespace tloc;
  using namespace graphics;

  TEST_CASE("Graphics/ShaderProgram/HardCoded", "")
  {
    using namespace graphics::win;
    using gfx_rend::Renderer;

    typedef win::Window::graphics_mode         graphics_mode;

    Window window;
    window.Create(graphics_mode(graphics_mode::Properties(1, 1)),
      WindowSettings("Atom & Eve"));

    // Initialize glew
    REQUIRE(Renderer().Initialize() != common_error_types::error_initialize);

    gl::VertexShader vShader;
    REQUIRE(vShader.Load(vShaderStr) == ErrorSuccess);
    REQUIRE(vShader.Compile() == ErrorSuccess);

    gl::FragmentShader fShader;

    REQUIRE(fShader.Load(fShaderStr) == ErrorSuccess);
    REQUIRE(fShader.Compile() == ErrorSuccess);

    gl::ShaderProgram sp;
    sp.AttachShaders(gl::ShaderProgram::two_shader_components(&vShader, &fShader));
    CHECK(sp.Link() == ErrorSuccess);

    CHECK(gl::Error().Succeeded());
    sp.LoadAttributeInfo();
    sp.LoadUniformInfo();
    CHECK(gl::Error().Succeeded());

    CHECK(sp.HasAttribute("vVertex"));
    CHECK(sp.HasAttribute("vColor"));
    CHECK_FALSE(sp.HasAttribute("vColorNotInShader"));
    CHECK(sp.HasUniform("u_Color"));
    CHECK_FALSE(sp.HasUniform("u_ColorNotInShader"));
  }

  TEST_CASE("Graphics/ShaderProgram/Get<>", "")
  {
    using namespace graphics::win;
    using gfx_rend::Renderer;
    typedef Window::graphics_mode         graphics_mode;

    Window win;
    win.Create(graphics_mode(graphics_mode::Properties(1, 1)),
      WindowSettings("Atom & Eve"));

    REQUIRE(Renderer().Initialize() != common_error_types::error_initialize);

    gl::VertexShader vShader;
    REQUIRE(vShader.Load(vShaderStr) == ErrorSuccess);
    REQUIRE(vShader.Compile() == ErrorSuccess);

    gl::FragmentShader fShader;
    REQUIRE(fShader.Load(fShaderStr) == ErrorSuccess);
    REQUIRE(fShader.Compile() == ErrorSuccess);

    gl::ShaderProgram sp;
    sp.AttachShaders(gl::ShaderProgram::two_shader_components(&vShader, &fShader));
    CHECK(sp.Link() == ErrorSuccess);

    sp.LoadAttributeInfo();
    sp.LoadUniformInfo();

    CHECK(sp.Get<gl::p_shader_program::DeleteStatus>() == 0);
    CHECK(sp.Get<gl::p_shader_program::LinkStatus>() == 1);
    CHECK(sp.Get<gl::p_shader_program::ValidateStatus>() == 1);
    CHECK(sp.Get<gl::p_shader_program::AttachedShaders>() == 2);
    CHECK(sp.Get<gl::p_shader_program::ActiveUniforms>() == 1);
    CHECK(sp.Get<gl::p_shader_program::ActiveUniformMaxLength>() == 8);
    CHECK(sp.Get<gl::p_shader_program::ActiveAttributes>() == 2);
    CHECK(sp.Get<gl::p_shader_program::ActiveAttributeMaxLength>() == 8);
  }

  /*TEST_CASE("Graphics/ShaderProgram/Uniforms", "")
  {
    using namespace math;

    typedef Window::graphics_mode         graphics_mode;
    Window win;
    win.Create(graphics_mode(graphics_mode::Properties(1, 1)),
      WindowSettings("Atom & Eve"));

    REQUIRE(Renderer().Initialize() != common_error_types::error_initialize);

    gl::VertexShader vShader;
    REQUIRE(vShader.Load(vShaderStrWithAttrAndUni) == ErrorSuccess);
    REQUIRE(vShader.Compile() == ErrorSuccess);

    gl::ShaderProgram sp;
    sp.AttachShaders(gl::ShaderProgram::one_shader_component(&vShader));
    CHECK(sp.Link() == ErrorSuccess);

    sp.AddUniform( gl::Uniform().SetName("uUni").SetValueAs(Vec4f32(0, 0, 0, 1)) );
    REQUIRE(sp.Enable() == ErrorSuccess );
    CHECK(sp.LoadAllUniforms() == ErrorSuccess);
    CHECK(sp.Disable() == ErrorSuccess );

    Vec4f32 colVec;
    graphics::types::Color col(0.5f, 0.5f, 0.5f, 1.0f);
    col.GetAs<graphics::types::p_color::format::RGBA>(colVec);

    sp.AddAttribute( gl::Attribute().SetName("vVertex").SetValueAs(Vec4f32(0, 0, 0, 1)) );
    sp.AddAttribute( gl::Attribute().SetName("vColor").SetValueAs(colVec) );
    REQUIRE(sp.Enable() == ErrorSuccess );
    CHECK(sp.LoadAllAttributes() == ErrorSuccess );
    CHECK(sp.Disable() == ErrorSuccess );
  }*/
};

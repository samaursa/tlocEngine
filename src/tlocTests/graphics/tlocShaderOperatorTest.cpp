#include "tlocTestCommon.h"

#include <tlocGraphics/renderer/tlocRenderer.h>
#include <tlocGraphics/window/tlocWindow.h>
#include <tlocGraphics/opengl/tlocShader.h>
#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>
#include <tlocGraphics/data_types/tlocColor.h>

#include <tlocMath/vector/tlocVector4.h>

namespace TestingShaderOperator
{
  const char* vShaderStr =
    "#ifdef GL_ES                       \n"
    "#  version 100                     \n"
    "#else                              \n"
    "#  version 140                     \n"
    "#endif                             \n"
    "                                   \n"
    "  uniform float u_float;           \n"
    "  uniform vec2  u_vec2;            \n"
    "  uniform vec3  u_vec3;            \n"
    "  uniform vec4  u_vec4;            \n"
    "  uniform int   u_int;             \n"
    "  uniform ivec2 u_ivec2;           \n"
    "  uniform ivec3 u_ivec3;           \n"
    "  uniform ivec4 u_ivec4;           \n"
    "  uniform uint  u_uint;            \n"
    "  uniform uvec2 u_uvec2;           \n"
    "  uniform uvec3 u_uvec3;           \n"
    "  uniform uvec4 u_uvec4;           \n"
    "  uniform bool  u_bool;            \n"
    "  uniform bvec2 u_bvec2;           \n"
    "  uniform bvec3 u_bvec3;           \n"
    "  uniform bvec4 u_bvec4;           \n"
    "                                   \n"
    "void main(void)                    \n"
    "{                                  \n"
    "  float pos  = u_float;            \n"
    "  vec2  pos2 = u_vec2;             \n"
    "  vec3  pos3 = u_vec3;             \n"
    "  vec4  pos4 = u_vec4;             \n"
    "                                   \n"
    "  int   index = u_int;             \n"
    "  ivec2 index2 = u_ivec2;\n"
    "  ivec3 index3 = u_ivec3;\n"
    "  ivec4 index4 = u_ivec4;\n"
    "\n"
    "  uint  uindex = u_uint;\n"
    "  uvec2 uindex2 = u_uvec2;\n"
    "  uvec3 uindex3 = u_uvec3;\n"
    "  uvec4 uindex4 = u_uvec4;\n"
    "\n"
    "  bool  tf = u_bool;\n"
    "  bvec2 tf2 = u_bvec2;\n"
    "  bvec3 tf3 = u_bvec3;\n"
    "  bvec4 tf4 = u_bvec4;\n"
    "\n"
    "  gl_Position   = pos4;            \n"
    "}\n";

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
  using namespace graphics;

  struct fixture
  {
    typedef gl::UniformPtr      uniform_ptr_type;
    typedef gl::AttributePtr    attribute_ptr_type;
  };

  TEST_CASE_METHOD(fixture, "Graphics/ShaderOperator/", "Basic functionality")
  {
    typedef Window::graphics_mode       graphics_mode;

    Window win;
    win.Create(graphics_mode(graphics_mode::Properties(1, 1)),
               WindowSettings("Atom & Eve"));

    // Initialize glew
    REQUIRE(Renderer().Initialize() != common_error_types::error_initialize);

    gl::VertexShader  vShader;
    REQUIRE(vShader.Load(vShaderStr) == ErrorSuccess());
    REQUIRE(vShader.Compile() == ErrorSuccess());

    uniform_ptr_type    uniform;
    attribute_ptr_type  attribute;

    gl::ShaderOperator  so;
  }

  //TEST_CASE("Graphics/ShaderProgram/Uniforms", "")
  //{
  //  using namespace math;

  //  typedef Window::graphics_mode         graphics_mode;
  //  Window win;
  //  win.Create(graphics_mode(graphics_mode::Properties(1, 1)),
  //    WindowSettings("Atom & Eve"));

  //  REQUIRE(Renderer().Initialize() != common_error_types::error_initialize);

  //  gl::VertexShader vShader;
  //  REQUIRE(vShader.Load(vShaderStrWithAttrAndUni) == ErrorSuccess());
  //  REQUIRE(vShader.Compile() == ErrorSuccess());

  //  gl::ShaderProgram sp;
  //  sp.AttachShaders(gl::ShaderProgram::one_shader_component(&vShader));
  //  CHECK(sp.Link() == ErrorSuccess());

  //  sp.AddUniform( gl::Uniform().SetName("uUni").SetValueAs(Vec4f32(0, 0, 0, 1)) );
  //  REQUIRE(sp.Enable() == ErrorSuccess() );
  //  CHECK(sp.LoadAllUniforms() == ErrorSuccess());
  //  CHECK(sp.Disable() == ErrorSuccess() );

  //  Vec4f32 colVec;
  //  graphics::types::Color col(0.5f, 0.5f, 0.5f, 1.0f);
  //  col.GetAs<graphics::types::p_color::format::RGBA>(colVec);

  //  sp.AddAttribute( gl::Attribute().SetName("vVertex").SetValueAs(Vec4f32(0, 0, 0, 1)) );
  //  sp.AddAttribute( gl::Attribute().SetName("vColor").SetValueAs(colVec) );
  //  REQUIRE(sp.Enable() == ErrorSuccess() );
  //  CHECK(sp.LoadAllAttributes() == ErrorSuccess() );
  //  CHECK(sp.Disable() == ErrorSuccess() );
  //}
};

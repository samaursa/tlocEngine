#include "tlocTestCommon.h"

#include <tlocGraphics/renderer/tlocRenderer.h>
#include <tlocGraphics/window/tlocWindow.h>
#include <tlocGraphics/opengl/tlocShader.h>
#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/data_types/tlocColor.h>

#include <tlocMath/vector/tlocVector2.h>
#include <tlocMath/vector/tlocVector2.inl>
#include <tlocMath/vector/tlocVector3.h>
#include <tlocMath/vector/tlocVector3.inl>
#include <tlocMath/vector/tlocVector4.h>
#include <tlocMath/vector/tlocVector4.inl>

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
    "  bool  tf = u_bool;\n"
    "  bvec2 tf2 = u_bvec2;\n"
    "  bvec3 tf3 = u_bvec3;\n"
    "  bvec4 tf4 = u_bvec4;\n"
    "\n"
    "  gl_Position   = pos4;            \n"
    "  gl_Position.x = u_float * u_vec2.x * u_vec3.x;            \n"
    "  gl_Position.y = u_int * u_ivec2.x * u_ivec3.x * u_ivec4.x;            \n"
    "  gl_Position.z = float(u_bool) * float(u_bvec2.x) * float(u_bvec3.x) * float(u_bvec4.x);            \n"
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
    typedef gl::UniformPtr          uniform_ptr_type;
    typedef gl::AttributePtr        attribute_ptr_type;
    typedef gl::ShaderOperatorPtr   shader_op_ptr;
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

    gl::ShaderProgram sp;
    sp.AttachShaders(gl::ShaderProgram::one_shader_component(&vShader));
    REQUIRE(sp.Link() == ErrorSuccess());
    CHECK(gl::Error().Succeeded());

    // Cache the attributes and uniforms
    sp.Enable();
    sp.LoadAttributeInfo();
    sp.LoadUniformInfo();
    sp.Disable();
    CHECK(gl::Error().Succeeded());

    shader_op_ptr so(new gl::ShaderOperator());

    //------------------------------------------------------------------------
    // Add all the uniforms
    {
      uniform_ptr_type    uniform(new gl::Uniform());
      uniform->SetName("u_float");
      uniform->SetValueAs(f32(5.0f));

      so->AddUniform(uniform);
    }
    {
      uniform_ptr_type    uniform(new gl::Uniform());
      uniform->SetName("u_vec2");
      uniform->SetValueAs(math::Vec2f32(0.1f, 0.2f));

      so->AddUniform(uniform);
    }
    {
      uniform_ptr_type    uniform(new gl::Uniform());
      uniform->SetName("u_vec3");
      uniform->SetValueAs(math::Vec3f32(0.1f, 0.2f, 0.3f));

      so->AddUniform(uniform);
    }
    {
      uniform_ptr_type    uniform(new gl::Uniform());
      uniform->SetName("u_vec4");
      uniform->SetValueAs(math::Vec4f32(0.1f, 0.2f, 0.3f, 0.4f));

      so->AddUniform(uniform);
    }
    {
      uniform_ptr_type    uniform(new gl::Uniform());
      uniform->SetName("u_int");
      uniform->SetValueAs(s32(5));

      so->AddUniform(uniform);
    }
    {
      uniform_ptr_type    uniform(new gl::Uniform());
      uniform->SetName("u_ivec2");
      uniform->SetValueAs(math::Vector2<s32>(1, 2));

      so->AddUniform(uniform);
    }
    {
      uniform_ptr_type    uniform(new gl::Uniform());
      uniform->SetName("u_ivec3");
      uniform->SetValueAs(math::Vector3<s32>(2, 3, 4));

      so->AddUniform(uniform);
    }
    {
      uniform_ptr_type    uniform(new gl::Uniform());
      uniform->SetName("u_ivec4");
      uniform->SetValueAs(math::Vector4<s32>(4, 5, 6, 7));

      so->AddUniform(uniform);
    }
    {
      uniform_ptr_type    uniform(new gl::Uniform());
      uniform->SetName("u_bool");
      uniform->SetValueAs(true);

      so->AddUniform(uniform);
    }
    {
      uniform_ptr_type    uniform(new gl::Uniform());
      uniform->SetName("u_bvec2");
      uniform->SetValueAs(core::Tuple<bool, 2>(true));

      so->AddUniform(uniform);
    }
    {
      uniform_ptr_type    uniform(new gl::Uniform());
      uniform->SetName("u_bvec3");
      uniform->SetValueAs(core::Tuple<bool, 3>(false));

      so->AddUniform(uniform);
    }
    {
      uniform_ptr_type    uniform(new gl::Uniform());
      uniform->SetName("u_bvec4");
      uniform->SetValueAs(core::Tuple<bool, 4>(false));

      so->AddUniform(uniform);
    }

    //------------------------------------------------------------------------
    // Add all the attributes
    {
      attribute_ptr_type  attribute(new gl::Attribute());
    }

    sp.Enable();
    CHECK(gl::Error().Succeeded());
    CHECK(so->PrepareAllUniforms(sp) == ErrorSuccess());
    CHECK(gl::Error().Succeeded());
    sp.Disable();
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

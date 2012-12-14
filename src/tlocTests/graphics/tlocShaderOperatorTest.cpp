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
    "#ifdef GL_ES                                                      \n"
    "#  version 100                                                    \n"
    "#else                                                             \n"
    "#  version 140                                                    \n"
    "#endif                                                            \n"
    "                                                                  \n"
    "  uniform float u_float;                                          \n"
    "  uniform vec2  u_vec2;                                           \n"
    "  uniform vec3  u_vec3;                                           \n"
    "  uniform vec4  u_vec4;                                           \n"
    "  uniform int   u_int;                                            \n"
    "  uniform ivec2 u_ivec2;                                          \n"
    "  uniform ivec3 u_ivec3;                                          \n"
    "  uniform ivec4 u_ivec4;                                          \n"
    "  uniform mat2  u_mat2;                                           \n"
    "  uniform mat3  u_mat3;                                           \n"
    "  uniform mat4  u_mat4;                                           \n"
    "                                                                  \n"
    "void main(void)                                                   \n"
    "{                                                                 \n"
    "  gl_Position   = u_vec4;                                         \n"
    "  gl_Position.x = u_float * u_vec2.x * u_vec3.x;                  \n"
    "  gl_Position.y = u_int * u_ivec2.x * u_ivec3.x * u_ivec4.x;      \n"
    "  gl_Position.z = u_mat2[0].x + u_mat3[0].x + u_mat4[0].x;        \n"
    "}\n";

const char* vShaderStr2 =
    "#ifdef GL_ES                                                      \n"
    "#  version 100                                                    \n"
    "#else                                                             \n"
    "#  version 140                                                    \n"
    "#endif                                                            \n"
    "                                                                  \n"
    "  uniform float u_float[2];                                       \n"
    "  uniform vec2  u_vec2[2];                                        \n"
    "  uniform vec3  u_vec3[2];                                        \n"
    "  uniform vec4  u_vec4[2];                                        \n"
    "  uniform int   u_int[2];                                         \n"
    "  uniform ivec2 u_ivec2[2];                                       \n"
    "  uniform ivec3 u_ivec3[2];                                       \n"
    "  uniform ivec4 u_ivec4[2];                                       \n"
    "                                                                  \n"
    "void main(void)                                                   \n"
    "{                                                                 \n"
    "  gl_Position   = u_vec4[0];                                      \n"
    "  gl_Position.x = u_float[0] * u_vec2[0].x * u_vec3[0].x;         \n"
    "  gl_Position.y = u_int[0] * u_ivec2[0].x * u_ivec3[0].x  *       \n"
    "                  u_ivec4[0].x;                                   \n"
    "}\n";

  using namespace tloc;
  using namespace graphics;

  struct fixture
  {
    typedef gl::UniformPtr          uniform_ptr_type;
    typedef gl::AttributePtr        attribute_ptr_type;
    typedef gl::ShaderOperatorPtr   shader_op_ptr;
  };

  TEST_CASE_METHOD(fixture, "Graphics/ShaderOperator/Uniforms", "")
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

  TEST_CASE_METHOD(fixture, "Graphics/ShaderOperator/UniformArrays", "")
  {
    typedef Window::graphics_mode       graphics_mode;

    Window win;
    win.Create(graphics_mode(graphics_mode::Properties(1, 1)),
               WindowSettings("Atom & Eve"));

    // Initialize glew
    REQUIRE(Renderer().Initialize() != common_error_types::error_initialize);

    gl::VertexShader  vShader;
    REQUIRE(vShader.Load(vShaderStr2) == ErrorSuccess());
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

      core::Array<f32>  floats(2, 2.0f);
      uniform->SetValueAs(floats, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(uniform);
    }
    {
      uniform_ptr_type    uniform(new gl::Uniform());
      uniform->SetName("u_vec2");

      core::Array<math::Vec2f32>  floats(2, math::Vec2f32(5.0f, 6.0f));
      uniform->SetValueAs(floats, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(uniform);
    }
    {
      uniform_ptr_type    uniform(new gl::Uniform());
      uniform->SetName("u_vec3");

      core::Array<math::Vec3f32>  floats(2, math::Vec3f32(1, 2, 3));
      uniform->SetValueAs(floats, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(uniform);
    }
    {
      uniform_ptr_type    uniform(new gl::Uniform());
      uniform->SetName("u_vec4");

      core::Array<math::Vec4f32>  floats(2, math::Vec4f32(1, 2, 3, 4));
      uniform->SetValueAs(floats, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(uniform);
    }
    {
      uniform_ptr_type    uniform(new gl::Uniform());
      uniform->SetName("u_int");

      core::Array<s32>  ints(2, 1);
      uniform->SetValueAs(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(uniform);
    }
    {
      uniform_ptr_type    uniform(new gl::Uniform());
      uniform->SetName("u_ivec2");

      core::Array<math::Vec2s32>  ints(2, math::Vec2s32(1, 2));
      uniform->SetValueAs(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(uniform);
    }
    {
      uniform_ptr_type    uniform(new gl::Uniform());
      uniform->SetName("u_ivec3");

      core::Array<math::Vec3s32>  ints(2, math::Vec3s32(1, 2, 3));
      uniform->SetValueAs(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(uniform);
    }
    {
      uniform_ptr_type    uniform(new gl::Uniform());
      uniform->SetName("u_ivec4");

      core::Array<math::Vec4s32>  ints(2, math::Vec4s32(1, 2, 3, 4));
      uniform->SetValueAs(ints, gl::p_shader_variable_ti::SwapArray());

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

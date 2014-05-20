#include "tlocTestCommon.h"

#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/window/tlocWindow.h>
#include <tlocGraphics/opengl/tlocShader.h>
#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/types/tlocColor.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector2.inl.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocVector3.inl.h>
#include <tlocMath/types/tlocVector4.h>
#include <tlocMath/types/tlocVector4.inl.h>

namespace TestingShaderOperator
{

#if defined (TLOC_OS_WIN)

  const char* vShaderStr =
    "#  version 140                                                    \n"
    "                                                                  \n"
    "  uniform float  u_float;                                         \n"
    "  uniform vec2   u_vec2;                                          \n"
    "  uniform vec3   u_vec3;                                          \n"
    "  uniform vec4   u_vec4;                                          \n"
    "  uniform int    u_int;                                           \n"
    "  uniform ivec2  u_ivec2;                                         \n"
    "  uniform ivec3  u_ivec3;                                         \n"
    "  uniform ivec4  u_ivec4;                                         \n"
    "  uniform uint   u_uint;                                          \n"
    "  uniform uvec2  u_uivec2;                                        \n"
    "  uniform uvec3  u_uivec3;                                        \n"
    "  uniform uvec4  u_uivec4;                                        \n"
    "  uniform mat2   u_mat2;                                          \n"
    "  uniform mat3   u_mat3;                                          \n"
    "  uniform mat4   u_mat4;                                          \n"
    "  uniform mat4   u_mat5; // bug fix - see below                   \n"
    "                                                                  \n"
    "void main(void)                                                   \n"
    "{                                                                 \n"
    "  gl_Position.x = u_float * u_vec2.x * u_vec3.x * u_vec4.x;       \n"
    "  gl_Position.y = u_int * u_ivec2.x * u_ivec3.x * u_ivec4.x;      \n"
    "  gl_Position.z = u_mat2[0].x + u_mat3[0].x + u_mat4[0].x         \n"
    "                  + u_mat5[0].x;                                  \n"
    "  gl_Position.a = u_uint * u_uivec2.x * u_uivec3.x * u_uivec4.x;  \n"
    "}\n";

#elif defined (TLOC_OS_IPHONE)

  const char* vShaderStr =
    "#  version 100                                                       \n"
    "                                                                     \n"
    "  uniform float  u_float;                                            \n"
    "  uniform vec2   u_vec2;                                             \n"
    "  uniform vec3   u_vec3;                                             \n"
    "  uniform vec4   u_vec4;                                             \n"
    "  uniform int    u_int;                                              \n"
    "  uniform ivec2  u_ivec2;                                            \n"
    "  uniform ivec3  u_ivec3;                                            \n"
    "  uniform ivec4  u_ivec4;                                            \n"
    "  uniform mat2   u_mat2;                                             \n"
    "  uniform mat3   u_mat3;                                             \n"
    "  uniform mat4   u_mat4;                                             \n"
    "  uniform mat4   u_mat5; // bug fix - see below                      \n"
    "                                                                     \n"
    "void main(void)                                                      \n"
    "{                                                                    \n"
    "  gl_Position.x = u_float * u_vec2.x * u_vec3.x * u_vec4.x;          \n"
    "  gl_Position.y = float(u_int * u_ivec2.x * u_ivec3.x * u_ivec4.x);  \n"
    "  gl_Position.z = u_mat2[0].x + u_mat3[0].x + u_mat4[0].x;           \n"
    "                  + u_mat5[0].x;                                     \n"
    "}\n";

#endif

  const char* fShaderStr =
#if defined (TLOC_OS_WIN)
    "#  version 140                                                    \n"
#elif defined (TLOC_OS_IPHONE)
    "#  version 100                                                    \n"
#endif
    "void main(void)                                                   \n\
    {                                                                  \n\
    gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);                           \n\
    }";

  using namespace tloc;
  using namespace graphics;
  using namespace core;
  using namespace core::containers;
  using namespace core::data_structs;

  struct fixture
  {
    typedef gl::uniform_sptr           uniform_ptr_type;
    typedef gl::attribute_sptr         attribute_ptr_type;
    typedef gl::shader_operator_sptr   shader_op_ptr;
  };

  TEST_CASE_METHOD(fixture, "Graphics/ShaderOperator/Uniforms", "")
  {
    using namespace math::types;
    using namespace graphics::win;

    typedef Window::graphics_mode       graphics_mode;

    Window win;
    win.Create(graphics_mode(graphics_mode::Properties(1, 1)),
               WindowSettings("Atom & Eve"));

    // Initialize glew
    REQUIRE(gl::InitializePlatform() == ErrorSuccess);

    gl::VertexShader  vShader;
    REQUIRE(vShader.Load(vShaderStr) == ErrorSuccess);
    REQUIRE(vShader.Compile() == ErrorSuccess);

    gl::FragmentShader  fShader;
    REQUIRE(fShader.Load(fShaderStr) == ErrorSuccess);
    REQUIRE(fShader.Compile() == ErrorSuccess);

    gl::ShaderProgram sp;
    sp.AttachShaders(gl::ShaderProgram::two_shader_components(&vShader, &fShader));
    REQUIRE(sp.Link() == ErrorSuccess);
    CHECK(gl::Error().Succeeded());

    // Cache the attributes and uniforms
    sp.Enable();
    sp.LoadUniformInfo();
    sp.Disable();
    CHECK(gl::Error().Succeeded());

    // stores all uniforms to keep 1 reference alive at all times
    gl::uniform_sptr_cont uniCont;

    shader_op_ptr so(new gl::ShaderOperator());

    //------------------------------------------------------------------------
    // Add all the uniforms
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_float");
      uniform->SetValueAs(f32(5.0f));

      so->AddUniform(*uniform);
      CHECK_FALSE(so->IsUniformsCached());

      gl::ShaderOperator::uniform_iterator itr =
        core::find_if(so->begin_uniforms(), so->end_uniforms(),
          gl::algos::shader_operator::compare::UniformName("u_float"));

      REQUIRE(itr != so->end_uniforms());
      CHECK(itr->first->GetName().compare("u_float") == 0);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_vec2");
      uniform->SetValueAs(Vec2f32(0.1f, 0.2f));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_vec3");
      uniform->SetValueAs(Vec3f32(0.1f, 0.2f, 0.3f));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_vec4");
      uniform->SetValueAs(Vec4f32(0.1f, 0.2f, 0.3f, 0.4f));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_int");
      uniform->SetValueAs(s32(5));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_ivec2");
      uniform->SetValueAs(Tuple2s32(2));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_ivec3");
      uniform->SetValueAs(Tuple3s32(3));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_ivec4");
      uniform->SetValueAs(Tuple4s32(4));

      so->AddUniform(*uniform);
    }
#if defined (TLOC_OS_WIN)
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_uint");
      uniform->SetValueAs(u32(5));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_uivec2");
      uniform->SetValueAs(Tuple2u32(2));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_uivec3");
      uniform->SetValueAs(Tuple3u32(3));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_uivec4");
      uniform->SetValueAs(Tuple4u32(4));

      so->AddUniform(*uniform);
    }
#endif
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_mat2");
      uniform->SetValueAs(Mat2f32(1, 0,
                                  0, 1));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_mat3");
      uniform->SetValueAs(Mat3f32(1, 0, 0,
                                  0, 1, 0,
                                  0, 0, 1));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_mat4");
      uniform->SetValueAs(Mat4f32(1, 0, 0, 0,
                                  0, 1, 0, 0,
                                  0, 0, 1, 0,
                                  0, 0, 0, 1));

      so->AddUniform(*uniform);
    }

    gl::uniform_vptr uniformBugFix;
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_mat5");
      uniform->SetValueAs(Mat4f32(1, 0, 0, 0,
                                  0, 1, 0, 0,
                                  0, 0, 1, 0,
                                  0, 0, 0, 1));
      uniformBugFix = so->AddUniform(*uniform);
    }

    // Copy the operator
    shader_op_ptr soCopy(so);
    shader_op_ptr soCopy2;
    soCopy2 = so;

    sp.Enable();
    CHECK(gl::Error().Succeeded());
    CHECK(so->PrepareAllUniforms(sp) == ErrorSuccess);

    so->EnableAllUniforms(sp);
    CHECK(so->IsUniformsCached());
    CHECK(so->PrepareAllUniforms(sp) == ErrorSuccess); // testing cache

    SECTION("Bug Fix", "Purposefully invalidating the uniform and disabling it")
    {
      uniformBugFix->ResetValue();
      uniformBugFix->SetValueAs(5.0f);

      TLOC_TEST_ASSERT
      {
        so->EnableAllUniforms(sp);
      }
      TLOC_TEST_ASSERT_CHECK();

      uniformBugFix->SetEnabled(false);
    }

    so->EnableAllUniforms(sp);

    CHECK(soCopy->PrepareAllUniforms(sp) == ErrorSuccess);
    soCopy->EnableAllUniforms(sp);
    CHECK(soCopy->PrepareAllUniforms(sp) == ErrorSuccess); // testing cache
    soCopy->EnableAllUniforms(sp);
    CHECK(soCopy->IsUniformsCached());

    CHECK(soCopy2->PrepareAllUniforms(sp) == ErrorSuccess);
    soCopy2->EnableAllUniforms(sp);
    CHECK(soCopy2->PrepareAllUniforms(sp) == ErrorSuccess); // testing cache
    soCopy2->EnableAllUniforms(sp);
    CHECK(soCopy2->IsUniformsCached());
    CHECK(gl::Error().Succeeded());
    sp.Disable();

    // Do it again - this time clearing the cache
    sp.Enable();
    CHECK(gl::Error().Succeeded());

    so->ClearUniformsCache();
    CHECK_FALSE(so->IsUniformsCached());
    CHECK(so->PrepareAllUniforms(sp) == ErrorSuccess);
    so->EnableAllUniforms(sp);
    CHECK(so->IsUniformsCached());

    soCopy->ClearCache();
    CHECK_FALSE(soCopy->IsUniformsCached());
    CHECK(soCopy->PrepareAllUniforms(sp) == ErrorSuccess);
    soCopy->EnableAllUniforms(sp);
    CHECK(soCopy->IsUniformsCached());

    soCopy2->ClearCache();
    CHECK_FALSE(soCopy2->IsUniformsCached());
    CHECK(soCopy2->PrepareAllUniforms(sp) == ErrorSuccess);
    soCopy2->EnableAllUniforms(sp);
    CHECK(soCopy2->IsUniformsCached());

    CHECK(gl::Error().Succeeded());
    sp.Disable();

    // Test Removal
    typedef shader_op_ptr::value_type::size_type size_type;
    const size_type numUniforms = so->GetNumberOfUniforms();

    // Note that removing uniforms does not affect cache
    gl::ShaderOperator::uniform_iterator uniItr =
      core::find_if(so->begin_uniforms(), so->end_uniforms(),
        core::algos::compare::pair::MakeFirst(so->begin_uniforms()->first));

    so->RemoveUniform(uniItr);
    CHECK(so->GetNumberOfUniforms() == numUniforms - 1);

    uniItr =
      core::find_if(so->begin_uniforms(), so->end_uniforms(),
        core::algos::compare::pair::MakeFirst(so->begin_uniforms()->first));

    so->RemoveUniform(uniItr);
    CHECK(so->GetNumberOfUniforms() == numUniforms - 2);

    sp.Enable();
    CHECK(so->PrepareAllUniforms(sp) == ErrorSuccess);
    so->EnableAllUniforms(sp);
    CHECK(so->IsUniformsCached());
    sp.Disable();

    so->RemoveAllUniforms();
    CHECK(so->GetNumberOfUniforms() == 0);
  }

#if defined (TLOC_OS_WIN)

  const char* vShaderStr2 =
    "#version 140                                                      \n"
    "                                                                  \n"
    "  uniform float u_float[2];                                       \n"
    "  uniform vec2  u_vec2[2];                                        \n"
    "  uniform vec3  u_vec3[2];                                        \n"
    "  uniform vec4  u_vec4[2];                                        \n"
    "  uniform int   u_int[2];                                         \n"
    "  uniform ivec2 u_ivec2[2];                                       \n"
    "  uniform ivec3 u_ivec3[2];                                       \n"
    "  uniform ivec4 u_ivec4[2];                                       \n"
    "  uniform uint  u_uint[2];                                        \n"
    "  uniform uvec2 u_uivec2[2];                                      \n"
    "  uniform uvec3 u_uivec3[2];                                      \n"
    "  uniform uvec4 u_uivec4[2];                                      \n"
    "                                                                  \n"
    "void main(void)                                                   \n"
    "{                                                                 \n"
    "  gl_Position.x = u_float[0] * u_vec2[0].x * u_vec3[0].x *        \n"
    "                  u_vec4[0].x;                                    \n"
    "  gl_Position.y = u_int[0] * u_ivec2[0].x * u_ivec3[0].x  *       \n"
    "                  u_ivec4[0].x;                                   \n"
    "  gl_Position.z = u_uint[0] + u_uivec2[0].x + u_uivec3[0].x *     \n"
    "                  u_uivec4[0].x;                                  \n"
    "}\n";

#elif defined (TLOC_OS_IPHONE)

  const char* vShaderStr2 =
    "#version 100                                                      \n"
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
    "  gl_Position.x = u_float[0] * u_vec2[0].x * u_vec3[0].x *        \n"
    "                  u_vec4[0].x;                                    \n"
    "  gl_Position.y = float(u_int[0] * u_ivec2[0].x * u_ivec3[0].x  * \n"
    "                  u_ivec4[0].x);                                  \n"
    "}\n";

#endif

  TEST_CASE_METHOD(fixture, "Graphics/ShaderOperator/UniformArrays", "")
  {
    using namespace graphics::win;
    using namespace math::types;

    typedef Window::graphics_mode       graphics_mode;

    Window win;
    win.Create(graphics_mode(graphics_mode::Properties(1, 1)),
               WindowSettings("Atom & Eve"));

    // Initialize glew
    REQUIRE(gl::InitializePlatform() == ErrorSuccess);

    gl::VertexShader  vShader;
    REQUIRE(vShader.Load(vShaderStr2) == ErrorSuccess);
    REQUIRE(vShader.Compile() == ErrorSuccess);

    gl::FragmentShader  fShader;
    REQUIRE(fShader.Load(fShaderStr) == ErrorSuccess);
    REQUIRE(fShader.Compile() == ErrorSuccess);

    gl::ShaderProgram sp;
    sp.AttachShaders(gl::ShaderProgram::two_shader_components(&vShader, &fShader));
    REQUIRE(sp.Link() == ErrorSuccess);
    CHECK(gl::Error().Succeeded());

    // Cache the attributes and uniforms
    sp.Enable();
    sp.LoadUniformInfo();
    sp.Disable();
    CHECK(gl::Error().Succeeded());

    // stores all uniforms to keep 1 reference alive at all times
    gl::uniform_sptr_cont uniCont;

    shader_op_ptr so(new gl::ShaderOperator());

    //------------------------------------------------------------------------
    // Add all the uniforms
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_float");

      Array<f32>  floats(2, 2.0f);
      uniform->SetValueAs(floats, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);

      gl::ShaderOperator::uniform_iterator itr =
        core::find_if(so->begin_uniforms(), so->end_uniforms(),
          gl::algos::shader_operator::compare::UniformName("u_float"));

      REQUIRE(itr != so->end_uniforms());
      CHECK(itr->first->GetName().compare("u_float") == 0);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_vec2");

      Array<Vec2f32>  floats(2, Vec2f32(5.0f, 6.0f));
      uniform->SetValueAs(floats, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_vec3");

      Array<Vec3f32>  floats(2, Vec3f32(1, 2, 3));
      uniform->SetValueAs(floats, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_vec4");

      Array<Vec4f32>  floats(2, Vec4f32(1, 2, 3, 4));
      uniform->SetValueAs(floats, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_int");

      Array<s32>  ints(2, 1);
      uniform->SetValueAs(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_ivec2");

      Array<Tuple2s32>  ints(2, Tuple2s32(2));
      uniform->SetValueAs(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_ivec3");

      Array<Tuple3s32>  ints(2, Tuple3s32(3));
      uniform->SetValueAs(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_ivec4");

      Array<Tuple4s32>  ints(2, Tuple4s32(4));
      uniform->SetValueAs(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
#if defined (TLOC_OS_WIN)
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_uint");

      Array<u32>  ints(2, 1);
      uniform->SetValueAs(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_uivec2");

      Array<Tuple2u32>  ints(2, Tuple2u32(2));
      uniform->SetValueAs(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_uivec3");

      Array<Tuple3u32>  ints(2, Tuple3u32(3));
      uniform->SetValueAs(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(uniform_ptr_type(new gl::Uniform()) );

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_uivec4");

      Array<Tuple4u32>  ints(2, Tuple4u32(4));
      uniform->SetValueAs(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
#endif

    sp.Enable();
    CHECK(gl::Error().Succeeded());
    CHECK(so->PrepareAllUniforms(sp) == ErrorSuccess);
    so->EnableAllUniforms(sp);
    CHECK(gl::Error().Succeeded());
    sp.Disable();
  }

#if defined (TLOC_OS_WIN)

  const char* vShaderStr3 =
    "#  version 140                                                    \n"
    "                                                                  \n"
    "  attribute float u_float;                                        \n"
    "  attribute vec2  u_vec2;                                         \n"
    "  attribute vec3  u_vec3;                                         \n"
    "  attribute vec4  u_vec4;                                         \n"
    "  attribute vec4  u_vec5;                                         \n"
    "  attribute int   u_int;                                          \n"
    "  attribute ivec2 u_ivec2;                                        \n"
    "  attribute ivec3 u_ivec3;                                        \n"
    "  attribute ivec4 u_ivec4;                                        \n"
    "  attribute uint  u_uint;                                         \n"
    "  attribute uvec2 u_uivec2;                                       \n"
    "  attribute uvec3 u_uivec3;                                       \n"
    "  attribute uvec4 u_uivec4;                                       \n"
    "                                                                  \n"
    "void main(void)                                                   \n"
    "{                                                                 \n"
    "  gl_Position   = u_vec4 + u_vec5;                                \n"
    "  gl_Position.x = u_float * u_vec2.x * u_vec3.x;                  \n"
    "  gl_Position.y = u_int * u_ivec2.x * u_ivec3.x * u_ivec4.x;      \n"
    "  gl_Position.z = u_uint * u_uivec2.x * u_uivec3.x * u_uivec4.x;  \n"
    "}\n";

#elif defined (TLOC_OS_IPHONE)

  const char* vShaderStr3 =
  "#  version 100                                                    \n"
  "                                                                  \n"
  "  attribute float u_float;                                        \n"
  "  attribute vec2  u_vec2;                                         \n"
  "  attribute vec3  u_vec3;                                         \n"
  "  attribute vec4  u_vec4;                                         \n"
  "  attribute vec4  u_vec5;                                         \n"
  "                                                                  \n"
  "void main(void)                                                   \n"
  "{                                                                 \n"
  "  gl_Position   = u_vec4 + u_vec5;                                \n"
  "  gl_Position.x = u_float * u_vec2.x * u_vec3.x;                  \n"
  "}\n";

#endif

  TEST_CASE_METHOD(fixture, "Graphics/ShaderOperator/ConstantAttributes", "")
  {
    using namespace math::types;
    using namespace graphics::win;

    typedef Window::graphics_mode       graphics_mode;

    Window win;
    win.Create(graphics_mode(graphics_mode::Properties(1, 1)),
               WindowSettings("Atom & Eve"));

    // Initialize glew
    REQUIRE(gl::InitializePlatform() == ErrorSuccess);

    gl::VertexShader  vShader;
    REQUIRE(vShader.Load(vShaderStr3) == ErrorSuccess);
    REQUIRE(vShader.Compile() == ErrorSuccess);

    gl::FragmentShader  fShader;
    REQUIRE(fShader.Load(fShaderStr) == ErrorSuccess);
    REQUIRE(fShader.Compile() == ErrorSuccess);

    gl::ShaderProgram sp;
    sp.AttachShaders(gl::ShaderProgram::two_shader_components(&vShader, &fShader));
    REQUIRE(sp.Link() == ErrorSuccess);
    CHECK(gl::Error().Succeeded());

    // Cache the attributes and uniforms
    sp.Enable();
    sp.LoadAttributeInfo();
    sp.Disable();
    CHECK(gl::Error().Succeeded());

    // stores all uniforms to keep 1 reference alive at all times
    gl::attribute_sptr_cont attribCont;

    shader_op_ptr so(new gl::ShaderOperator());

    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_float");
      attribute->SetValueAs(f32(5.0f));

      so->AddAttribute(*attribute);
      CHECK_FALSE(so->IsAttributesCached());
    }
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_vec2");
      attribute->SetValueAs(Vec2f32(0.1f, 0.2f));

      so->AddAttribute(*attribute);
    }
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_vec3");
      attribute->SetValueAs(Vec3f32(0.1f, 0.2f, 0.3f));

      so->AddAttribute(*attribute);
    }
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_vec4");
      attribute->SetValueAs(Vec4f32(0.1f, 0.2f, 0.3f, 0.4f));

      so->AddAttribute(*attribute);
    }
    gl::attribute_vptr attributeBugFix;
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_vec5");
      attribute->SetValueAs(Vec4f32(0.1f, 0.2f, 0.3f, 0.4f));

      attributeBugFix = so->AddAttribute(*attribute);
    }
#if defined (TLOC_OS_WIN)
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_int");
      attribute->SetValueAs(s32(5));

      so->AddAttribute(*attribute);
    }
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_ivec2");
      attribute->SetValueAs(Tuple2s32(2));

      so->AddAttribute(*attribute);
    }
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_ivec3");
      attribute->SetValueAs(Tuple3s32(3));

      so->AddAttribute(*attribute);
    }
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_ivec4");
      attribute->SetValueAs(Tuple4s32(4));

      so->AddAttribute(*attribute);
    }

    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_uint");
      attribute->SetValueAs(u32(5));

      so->AddAttribute(*attribute);
    }
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_uivec2");
      attribute->SetValueAs(Tuple2u32(2));

      so->AddAttribute(*attribute);
    }
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_uivec3");
      attribute->SetValueAs(Tuple3u32(3));

      so->AddAttribute(*attribute);
    }
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_uivec4");
      attribute->SetValueAs(Tuple4u32(4));

      so->AddAttribute(*attribute);
    }

    // for windows, we'll have to get the pointer for attributeFix again since
    // more attributes were added
    attributeBugFix = core::find_if(so->begin_attributes(), so->end_attributes(),
      gfx_gl::algos::shader_operator::compare::AttributeName("u_vec5"))->first.get();
#endif

    // Copy the operator
    shader_op_ptr soCopy(so);
    shader_op_ptr soCopy2;
    soCopy2 = so;

    sp.Enable();
    CHECK(gl::Error().Succeeded());
    CHECK(so->PrepareAllAttributes(sp) == ErrorSuccess);
    so->EnableAllAttributes(sp);
    CHECK(so->IsAttributesCached());
    CHECK(so->PrepareAllAttributes(sp) == ErrorSuccess); // check the cache

    SECTION("Bug Fix", "Purposefully invalidating the attribute and disabling it")
    {
      attributeBugFix->ResetValue();
      attributeBugFix->SetValueAs(5.0f);

      TLOC_TEST_ASSERT
      {
        so->EnableAllAttributes(sp);
      }
      TLOC_TEST_ASSERT_CHECK();

      attributeBugFix->SetEnabled(false);
    }

    so->EnableAllAttributes(sp);

    CHECK(soCopy->PrepareAllAttributes(sp) == ErrorSuccess);
    soCopy->EnableAllAttributes(sp);
    CHECK(soCopy->IsAttributesCached());
    CHECK(soCopy->PrepareAllAttributes(sp) == ErrorSuccess); // check the cache
    soCopy->EnableAllAttributes(sp);

    CHECK(soCopy2->PrepareAllAttributes(sp) == ErrorSuccess);
    soCopy2->EnableAllAttributes(sp);
    CHECK(soCopy2->IsAttributesCached());
    CHECK(soCopy2->PrepareAllAttributes(sp) == ErrorSuccess); // check the cache
    soCopy2->EnableAllAttributes(sp);
    CHECK(gl::Error().Succeeded());
    sp.Disable();

    // Do it again - this time clearing the cache
    sp.Enable();
    CHECK(gl::Error().Succeeded());

    so->ClearAttributesCache();
    CHECK_FALSE(so->IsAttributesCached());
    CHECK(so->PrepareAllAttributes(sp) == ErrorSuccess);
    so->EnableAllAttributes(sp);
    CHECK(so->IsAttributesCached());

    soCopy->ClearAttributesCache();
    CHECK_FALSE(soCopy->IsAttributesCached());
    CHECK(soCopy->PrepareAllAttributes(sp) == ErrorSuccess);
    soCopy->EnableAllAttributes(sp);
    CHECK(soCopy->IsAttributesCached());

    soCopy->ClearAttributesCache();
    CHECK_FALSE(soCopy2->IsAttributesCached());
    CHECK(soCopy2->PrepareAllAttributes(sp) == ErrorSuccess);
    soCopy2->EnableAllAttributes(sp);
    CHECK(soCopy2->IsAttributesCached());

    CHECK(gl::Error().Succeeded());
    sp.Disable();

    // Test Removal
    typedef shader_op_ptr::value_type::size_type size_type;
    const size_type numAttributes = so->GetNumberOfAttributes();

    gl::ShaderOperator::attribute_iterator attrItr =
      core::find_if(so->begin_attributes(), so->end_attributes(),
        core::algos::compare::pair::MakeFirst(so->begin_attributes()->first));

    // Note that removing uniforms does not affect cache
    so->RemoveAttribute(attrItr);
    CHECK(so->GetNumberOfAttributes() == numAttributes - 1);

    attrItr =
      core::find_if(so->begin_attributes(), so->end_attributes(),
        core::algos::compare::pair::MakeFirst(so->begin_attributes()->first));

    so->RemoveAttribute(attrItr);
    CHECK(so->GetNumberOfAttributes() == numAttributes - 2);

    sp.Enable();
    CHECK(so->PrepareAllAttributes(sp) == ErrorSuccess);
    so->EnableAllAttributes(sp);
    CHECK(so->IsAttributesCached());
    sp.Disable();

    so->RemoveAllAttributes();
    CHECK(so->GetNumberOfAttributes() == 0);
  }

#if defined (TLOC_OS_WIN)

  const char* vShaderStr4 =
    "#  version 140                                                    \n"
    "                                                                  \n"
    "  attribute float u_float;                                        \n"
    "  attribute vec2  u_vec2;                                         \n"
    "  attribute vec3  u_vec3;                                         \n"
    "  attribute vec4  u_vec4;                                         \n"
    "  attribute int   u_int;                                          \n"
    "  attribute ivec2 u_ivec2;                                        \n"
    "  attribute ivec3 u_ivec3;                                        \n"
    "  attribute ivec4 u_ivec4;                                        \n"
    "  attribute uint  u_uint;                                         \n"
    "  attribute uvec2 u_uivec2;                                       \n"
    "  attribute uvec3 u_uivec3;                                       \n"
    "  attribute uvec4 u_uivec4;                                       \n"
    "                                                                  \n"
    "void main(void)                                                   \n"
    "{                                                                 \n"
    "  gl_Position   = u_vec4;                                         \n"
    "  gl_Position.x = u_float * u_vec2.x * u_vec3.x;                  \n"
    "  gl_Position.y = u_int * u_ivec2.x * u_ivec3.x * u_ivec4.x;      \n"
    "  gl_Position.z = u_uint * u_uivec2.x * u_uivec3.x * u_uivec4.x;  \n"
    "}\n";

#elif defined (TLOC_OS_IPHONE)

  const char* vShaderStr4 =
  "#  version 100                                                    \n"
  "                                                                  \n"
  "  attribute float u_float;                                        \n"
  "  attribute vec2  u_vec2;                                         \n"
  "  attribute vec3  u_vec3;                                         \n"
  "  attribute vec4  u_vec4;                                         \n"
  "                                                                  \n"
  "void main(void)                                                   \n"
  "{                                                                 \n"
  "  gl_Position   = u_vec4;                                         \n"
  "  gl_Position.x = u_float * u_vec2.x * u_vec3.x;                  \n"
  "}\n";

#endif

  TEST_CASE_METHOD(fixture, "Graphics/ShaderOperator/AttributesArrays", "")
  {
    using namespace math::types;
    using namespace graphics::win;

    typedef Window::graphics_mode       graphics_mode;

    Window win;
    win.Create(graphics_mode(graphics_mode::Properties(1, 1)),
               WindowSettings("Atom & Eve"));

    // Initialize glew
    REQUIRE(gl::InitializePlatform() == ErrorSuccess);

    gl::VertexShader  vShader;
    REQUIRE(vShader.Load(vShaderStr4) == ErrorSuccess);
    REQUIRE(vShader.Compile() == ErrorSuccess);

    gl::FragmentShader  fShader;
    REQUIRE(fShader.Load(fShaderStr) == ErrorSuccess);
    REQUIRE(fShader.Compile() == ErrorSuccess);

    gl::ShaderProgram sp;
    sp.AttachShaders(gl::ShaderProgram::two_shader_components(&vShader, &fShader));
    REQUIRE(sp.Link() == ErrorSuccess);
    CHECK(gl::Error().Succeeded());

    // Cache the attributes and uniforms
    sp.Enable();
    sp.LoadAttributeInfo();
    sp.Disable();
    CHECK(gl::Error().Succeeded());

    // stores all uniforms to keep 1 reference alive at all times
    gl::attribute_sptr_cont attribCont;

    shader_op_ptr so(new gl::ShaderOperator());

    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_float");

      Array<f32>  floats(2, 2.0f);
      attribute->SetVertexArray(floats, gl::p_shader_variable_ti::SwapArray());

      so->AddAttribute(*attribute);

      gl::ShaderOperator::attribute_iterator itr =
        core::find_if(so->begin_attributes(), so->end_attributes(),
          gl::algos::shader_operator::compare::AttributeName("u_float"));

      REQUIRE(itr != so->end_attributes());
      CHECK(itr->first->GetName().compare("u_float") == 0);
    }
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_vec2");

      Array<Vec2f32>  floats(2, Vec2f32(5.0f, 6.0f));
      attribute->SetVertexArray(floats, gl::p_shader_variable_ti::SwapArray());

      so->AddAttribute(*attribute);
    }
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_vec3");

      Array<Vec3f32>  floats(2, Vec3f32(1, 2, 3));
      attribute->SetVertexArray(floats, gl::p_shader_variable_ti::SwapArray());

      so->AddAttribute(*attribute);
    }
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_vec4");

      Array<Vec4f32>  floats(2, Vec4f32(1, 2, 3, 4));
      attribute->SetVertexArray(floats, gl::p_shader_variable_ti::SwapArray());

      so->AddAttribute(*attribute);
    }
#if defined (TLOC_OS_WIN)
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_int");

      Array<s32>  ints(2, 1);
      attribute->SetVertexArray(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddAttribute(*attribute);
    }
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_ivec2");

      Array<Tuple2s32>  ints(2, Tuple2s32(2));
      attribute->SetVertexArray(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddAttribute(*attribute);
    }
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_ivec3");

      Array<Tuple3s32>  ints(2, Tuple3s32(3));
      attribute->SetVertexArray(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddAttribute(*attribute);
    }
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_ivec4");

      Array<Tuple4s32>  ints(2, Tuple4s32(4));
      attribute->SetVertexArray(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddAttribute(*attribute);
    }

    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_uint");

      Array<u32>  ints(2, 1);
      attribute->SetVertexArray(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddAttribute(*attribute);
    }
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_uivec2");

      Array<Tuple2u32>  ints(2, Tuple2u32(2));
      attribute->SetVertexArray(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddAttribute(*attribute);
    }
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_uivec3");

      Array<Tuple3u32>  ints(2, Tuple3u32(3));
      attribute->SetVertexArray(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddAttribute(*attribute);
    }
    {
      attribCont.push_back(attribute_ptr_type(new gl::Attribute()) );
      attribute_ptr_type attribute = attribCont.back();
      attribute->SetName("u_uivec4");

      Array<Tuple4u32>  ints(2, Tuple4u32(4));
      attribute->SetVertexArray(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddAttribute(*attribute);
    }
#endif

    sp.Enable();
    CHECK(gl::Error().Succeeded());
    CHECK(so->PrepareAllAttributes(sp) == ErrorSuccess);
    so->EnableAllAttributes(sp);
    CHECK(gl::Error().Succeeded());
    sp.Disable();
  }
};

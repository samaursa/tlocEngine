#include "tlocTestCommon.h"

#include <tlocCore/logging/tlocLogger.h>

#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/window/tlocWindow.h>
#include <tlocGraphics/opengl/tlocShader.h>
#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/types/tlocColor.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocVector4.h>

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
    "  gl_Position.z = u_mat2[0].x + u_mat3[0].x + u_mat4[0].x            \n"
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

    gl::uniform_sptr_cont uniCont;

    auto so = core_sptr::MakeShared<gl::ShaderOperator>();
    gl::uniform_vptr uniformPtrToCheckWarning; // test warning when adding uniforms

    //------------------------------------------------------------------------
    // Add all the uniforms
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_float");
      uniform->SetValueAs(f32(5.0f));

      uniformPtrToCheckWarning = so->AddUniform(*uniform);
      CHECK_FALSE(so->IsUniformsCached());

      gl::ShaderOperator::uniform_iterator itr =
        core::find_if(so->begin_uniforms(), so->end_uniforms(),
          gl::algos::shader_operator::compare::UniformName("u_float"));

      REQUIRE(itr != so->end_uniforms());
      CHECK(itr->first->GetName().compare("u_float") == 0);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_vec2");
      uniform->SetValueAs(Vec2f32(0.1f, 0.2f));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_vec3");
      uniform->SetValueAs(Vec3f32(0.1f, 0.2f, 0.3f));

      graphics::GetLogger().SetBreakOnSeverity(core_log::p_log::severity::Warning::k_value);
      TLOC_TEST_ASSERT
      { so->AddUniform(*uniform); }
      TLOC_TEST_ASSERT_REQUIRE();
      graphics::GetLogger().ResetBreakOnSeverity();

      uniformPtrToCheckWarning.reset();
      // now add the uniform normally
      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_vec4");
      uniform->SetValueAs(Vec4f32(0.1f, 0.2f, 0.3f, 0.4f));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_int");
      uniform->SetValueAs(s32(5));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_ivec2");
      uniform->SetValueAs(Tuple2s32(2));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_ivec3");
      uniform->SetValueAs(Tuple3s32(3));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_ivec4");
      uniform->SetValueAs(Tuple4s32(4));

      so->AddUniform(*uniform);
    }
#if defined (TLOC_OS_WIN)
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_uint");
      uniform->SetValueAs(u32(5));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_uivec2");
      uniform->SetValueAs(Tuple2u32(2));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_uivec3");
      uniform->SetValueAs(Tuple3u32(3));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_uivec4");
      uniform->SetValueAs(Tuple4u32(4));

      so->AddUniform(*uniform);
    }
#endif
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_mat2");
      uniform->SetValueAs(Mat2f32(1, 0,
                                  0, 1));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_mat3");
      uniform->SetValueAs(Mat3f32(1, 0, 0,
                                  0, 1, 0,
                                  0, 0, 1));

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

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
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

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
    const size_type numUniforms = so->size_uniforms();

    // Note that removing uniforms does not affect cache
    gl::ShaderOperator::uniform_iterator uniItr =
      core::find_if(so->begin_uniforms(), so->end_uniforms(),
        core::algos::pair::compare::MakeFirst(so->begin_uniforms()->first));

    so->RemoveUniform(uniItr);
    CHECK(so->size_uniforms() == numUniforms - 1);

    uniItr =
      core::find_if(so->begin_uniforms(), so->end_uniforms(),
        core::algos::pair::compare::MakeFirst(so->begin_uniforms()->first));

    so->RemoveUniform(uniItr);
    CHECK(so->size_uniforms() == numUniforms - 2);

    sp.Enable();
    CHECK(so->PrepareAllUniforms(sp) == ErrorSuccess);
    so->EnableAllUniforms(sp);
    CHECK(so->IsUniformsCached());
    sp.Disable();

    so->RemoveAllUniforms();
    CHECK(so->size_uniforms() == 0);
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

    auto so = core_sptr::MakeShared<gl::ShaderOperator>();

    //------------------------------------------------------------------------
    // Add all the uniforms
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

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

      gl::uniform_vptr ptr = gl::f_shader_operator::GetUniform(*so, "u_float");
      REQUIRE(ptr);
      CHECK(ptr->GetName().compare("u_float") == 0);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_vec2");

      Array<Vec2f32>  floats(2, Vec2f32(5.0f, 6.0f));
      uniform->SetValueAs(floats, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_vec3");

      Array<Vec3f32>  floats(2, Vec3f32(1, 2, 3));
      uniform->SetValueAs(floats, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_vec4");

      Array<Vec4f32>  floats(2, Vec4f32(1, 2, 3, 4));
      uniform->SetValueAs(floats, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_int");

      Array<s32>  ints(2, 1);
      uniform->SetValueAs(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_ivec2");

      Array<Tuple2s32>  ints(2, Tuple2s32(2));
      uniform->SetValueAs(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_ivec3");

      Array<Tuple3s32>  ints(2, Tuple3s32(3));
      uniform->SetValueAs(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_ivec4");

      Array<Tuple4s32>  ints(2, Tuple4s32(4));
      uniform->SetValueAs(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
#if defined (TLOC_OS_WIN)
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_uint");

      Array<u32>  ints(2, 1);
      uniform->SetValueAs(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_uivec2");

      Array<Tuple2u32>  ints(2, Tuple2u32(2));
      uniform->SetValueAs(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

      gl::uniform_sptr uniform = uniCont.back();
      uniform->SetName("u_uivec3");

      Array<Tuple3u32>  ints(2, Tuple3u32(3));
      uniform->SetValueAs(ints, gl::p_shader_variable_ti::SwapArray());

      so->AddUniform(*uniform);
    }
    {
      uniCont.push_back(core_sptr::MakeShared<gl::Uniform>());

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
    "  attribute mat2  u_matrix2;                                      \n"
    "  attribute mat3  u_matrix3;                                      \n"
    "                                                                  \n"
    "void main(void)                                                   \n"
    "{                                                                 \n"
    "  gl_Position   = u_vec4 + u_vec5;                                \n"
    "  gl_Position.x = u_float * u_vec2.x * u_vec3.x;                  \n"
    "  gl_Position.y = u_int * u_ivec2.x * u_ivec3.x * u_ivec4.x;      \n"
    "  gl_Position.z = u_matrix2[0].x * u_matrix3[0].x;                \n"
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
  "  attribute mat2  u_matrix2;                                      \n"
  "  attribute mat3  u_matrix3;                                      \n"
  "                                                                  \n"
  "void main(void)                                                   \n"
  "{                                                                 \n"
  "  gl_Position   = u_vec4 + u_vec5;                                \n"
  "  gl_Position.x = u_float * u_vec2.x * u_vec3.x;                  \n"
  "  gl_Position.z = u_matrix2[0].x * u_matrix3[0].x;                \n"
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

    auto so = core_sptr::MakeShared<gl::ShaderOperator>();
    {
      gl::AttributeVBO attribute;
      attribute.AddName("u_float");

      core_conts::Array<f32> array(1, 5.0f);
      attribute.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                           gl::p_vbo::usage::StaticDraw>(array);

      so->AddAttributeVBO(attribute);
    }
    {
      gl::AttributeVBO attribute;
      attribute.AddName("u_vec2");

      core_conts::Array<Vec2f32> array(1, Vec2f32(0.1f, 0.2f));
      attribute.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                           gl::p_vbo::usage::StaticDraw>(array);

      so->AddAttributeVBO(attribute);
    }
    {
      gl::AttributeVBO attribute;
      attribute.AddName("u_vec3");

      core_conts::Array<Vec3f32> array(1, Vec3f32(0.1f, 0.2f, 0.3f));
      attribute.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                           gl::p_vbo::usage::StaticDraw>(array);

      so->AddAttributeVBO(attribute);
    }
    {
      gl::AttributeVBO attribute;
      attribute.AddName("u_vec4");

      core_conts::Array<Vec4f32> array(1, Vec4f32(0.1f, 0.2f, 0.3f, 0.4f));
      attribute.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                           gl::p_vbo::usage::StaticDraw>(array);

      so->AddAttributeVBO(attribute);
    }
    {
      gl::AttributeVBO attribute;
      attribute.AddName("u_vec4");

      core_conts::Array<Vec4f32> array(1, Vec4f32(0.1f, 0.2f, 0.3f, 0.4f));
      attribute.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                           gl::p_vbo::usage::StaticDraw>(array);

      so->AddAttributeVBO(attribute);
    }
    {
      gl::AttributeVBO attribute;
      attribute.AddName("u_matrix2");

      core_conts::Array<Mat2f32> array(1, Mat2f32::IDENTITY);
      attribute.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                           gl::p_vbo::usage::StaticDraw>(array);

      so->AddAttributeVBO(attribute);
    }
    {
      gl::AttributeVBO attribute;
      attribute.AddName("u_matrix3");

      core_conts::Array<Mat3f32> array(1, Mat3f32::IDENTITY);
      attribute.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                           gl::p_vbo::usage::StaticDraw>(array);

      so->AddAttributeVBO(attribute);
    }

#if defined (TLOC_OS_WIN)

    {
      gl::AttributeVBO attribute;
      attribute.AddName("u_int");

      core_conts::Array<s32> array(1, s32(5));
      attribute.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                           gl::p_vbo::usage::StaticDraw>(array);

      so->AddAttributeVBO(attribute);
    }
    {
      gl::AttributeVBO attribute;
      attribute.AddName("u_ivec2");

      core_conts::Array<Tuple2s32> array(1, Tuple2s32(2));
      attribute.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                           gl::p_vbo::usage::StaticDraw>(array);

      so->AddAttributeVBO(attribute);
    }
    {
      gl::AttributeVBO attribute;
      attribute.AddName("u_ivec3");

      core_conts::Array<Tuple3s32> array(1, Tuple3s32(3));
      attribute.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                           gl::p_vbo::usage::StaticDraw>(array);

      so->AddAttributeVBO(attribute);
    }
    {
      gl::AttributeVBO attribute;
      attribute.AddName("u_ivec4");

      core_conts::Array<Tuple4s32> array(1, Tuple4s32(4));
      attribute.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                           gl::p_vbo::usage::StaticDraw>(array);

      so->AddAttributeVBO(attribute);
    }

    { // test meta function
      gl::attributeVBO_vptr vboPtr = 
        gl::f_shader_operator::GetAttributeVBO(*so, "u_ivec4");

      REQUIRE(vboPtr);
      CHECK(vboPtr->GetName().compare("u_ivec4") == 0);
    }

#endif

    // Copy the operator
    shader_op_ptr soCopy(so);
    shader_op_ptr soCopy2;
    soCopy2 = so;

    gl::VertexArrayObject vao;
    sp.Enable();
    CHECK(gl::Error().Succeeded());
    CHECK(so->PrepareAllAttributeVBOs(sp, vao) == ErrorSuccess);

    {
      gl::VertexArrayObject::Bind b(vao);
      CHECK(so->IsAttributeVBOsCached());
    }

    {
      CHECK(soCopy->PrepareAllAttributeVBOs(sp, vao) == ErrorSuccess);
      CHECK(soCopy->IsAttributeVBOsCached());
      CHECK(soCopy->PrepareAllAttributeVBOs(sp, vao) == ErrorSuccess); // check the cache
    }

    {
      CHECK(soCopy2->PrepareAllAttributeVBOs(sp, vao) == ErrorSuccess);
      CHECK(soCopy2->IsAttributeVBOsCached());
      CHECK(soCopy2->PrepareAllAttributeVBOs(sp, vao) == ErrorSuccess); // check the cache
    }
    sp.Disable();

    // Do it again - this time clearing the cache
    sp.Enable();
    CHECK(gl::Error().Succeeded());

    so->ClearAttributeVBOsCache();
    {
      CHECK_FALSE(so->IsAttributeVBOsCached());
      CHECK(so->PrepareAllAttributeVBOs(sp, vao) == ErrorSuccess);
      CHECK(so->IsAttributeVBOsCached());
    }

    soCopy->ClearAttributeVBOsCache();
    {
      CHECK_FALSE(soCopy->IsAttributeVBOsCached());
      CHECK(soCopy->PrepareAllAttributeVBOs(sp, vao) == ErrorSuccess);
      CHECK(soCopy->IsAttributeVBOsCached());
    }

    soCopy2->ClearAttributeVBOsCache();
    {
      CHECK_FALSE(soCopy2->IsAttributeVBOsCached());
      CHECK(soCopy2->PrepareAllAttributeVBOs(sp, vao) == ErrorSuccess);
      CHECK(soCopy2->IsAttributeVBOsCached());
    }

    CHECK(gl::Error().Succeeded());
    sp.Disable();

    // Test Removal
    typedef shader_op_ptr::value_type::size_type size_type;
    const size_type numAttributes = so->size_attributeVBOs();

    gl::ShaderOperator::attributeVBO_iterator attrItr =
      core::find_if(so->begin_attributeVBOs(), so->end_attributeVBOs(),
        core::algos::pair::compare::MakeFirst(so->begin_attributeVBOs()->first));

    // Note that removing uniforms does not affect cache
    so->RemoveAttributeVBO(attrItr);
    CHECK(so->size_attributeVBOs() == numAttributes - 1);

    attrItr =
      core::find_if(so->begin_attributeVBOs(), so->end_attributeVBOs(),
        core::algos::pair::compare::MakeFirst(so->begin_attributeVBOs()->first));

    so->RemoveAttributeVBO(attrItr);
    CHECK(so->size_attributeVBOs() == numAttributes - 2);

    sp.Enable();
    CHECK(so->PrepareAllAttributeVBOs(sp, vao) == ErrorSuccess);

    CHECK(so->IsAttributeVBOsCached());
    sp.Disable();

    so->RemoveAllAttributeVBOs();
    CHECK(so->size_attributeVBOs() == 0);
  }
};

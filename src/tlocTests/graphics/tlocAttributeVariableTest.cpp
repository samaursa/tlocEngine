#include "tlocTestCommon.h"

#include <tlocGraphics/opengl/tlocAttribute.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

namespace TestingAttributeVariable
{
  using namespace tloc;
  using namespace tloc::graphics;

  TEST_CASE("Graphics/gl/Attribute/copy", "")
  {
    using namespace tloc::core_ds;
    using namespace tloc::core_conts;
    using namespace tloc::math_t;

    Vec2f32 v(0.0f, 1.0f);

    gl::Attribute a;
    a.SetValueAs(v);

    {
      gl::Attribute acopy(a);
      CHECK( (acopy.GetValueAs<Vec2f32>() == v) );
    }

    {
      gl::Attribute acopy;
      acopy = a;
      CHECK( (acopy.GetValueAs<Vec2f32>() == v) );
    }
  }

  TEST_CASE("Graphics/gl/Attribute", "")
  {
    using namespace tloc::core_ds;
    using namespace tloc::core_conts;
    using namespace tloc::math_t;

    {
      gl::Attribute a;
      a.SetValueAs(1.0f);
      CHECK( a.GetValueAs<f32>() == Approx(1.0f) );
    }

    {
      gl::Attribute a;
      a.SetValueAs(Vec2f32(0.0f, 1.0f));
      CHECK( a.GetValueAs<Vec2f32>()[0] == Approx(0.0f));
      CHECK( a.GetValueAs<Vec2f32>()[1] == Approx(1.0f));
    }

    {
      gl::Attribute a;
      a.SetValueAs(Vec3f32(0.0f, 1.0f, 2.0f));
      CHECK( a.GetValueAs<Vec3f32>()[0] == Approx(0.0f));
      CHECK( a.GetValueAs<Vec3f32>()[1] == Approx(1.0f));
      CHECK( a.GetValueAs<Vec3f32>()[2] == Approx(2.0f));
    }

    {
      gl::Attribute a;
      a.SetValueAs(Vec4f32(0.0f, 1.0f, 2.0f, 3.0f));
      CHECK( a.GetValueAs<Vec4f32>()[0] == Approx(0.0f));
      CHECK( a.GetValueAs<Vec4f32>()[1] == Approx(1.0f));
      CHECK( a.GetValueAs<Vec4f32>()[2] == Approx(2.0f));
      CHECK( a.GetValueAs<Vec4f32>()[3] == Approx(3.0f));
    }

#if defined (TLOC_OS_WIN)
    {
      gl::Attribute a;
      a.SetValueAs(s32(1));
      CHECK(a.GetValueAs<s32>() == 1);
    }

    {
      gl::Attribute a;
      a.SetValueAs( Tuple2s32(Variadic2s32(1, 2)) );
      CHECK(a.GetValueAs<Tuple2s32>()[0] == 1);
      CHECK(a.GetValueAs<Tuple2s32>()[1] == 2);
    }

    {
      gl::Attribute a;
      a.SetValueAs( Tuple3s32(Variadic3s32(1, 2, 3)) );
      CHECK(a.GetValueAs<Tuple3s32>()[0] == 1);
      CHECK(a.GetValueAs<Tuple3s32>()[1] == 2);
      CHECK(a.GetValueAs<Tuple3s32>()[2] == 3);
    }

    {
      gl::Attribute a;
      a.SetValueAs( Tuple4s32(Variadic4s32(1, 2, 3, 4)) );
      CHECK(a.GetValueAs<Tuple4s32>()[0] == 1);
      CHECK(a.GetValueAs<Tuple4s32>()[1] == 2);
      CHECK(a.GetValueAs<Tuple4s32>()[2] == 3);
      CHECK(a.GetValueAs<Tuple4s32>()[3] == 4);
    }

    {
      gl::Attribute a;
      a.SetValueAs(u32(1));
      CHECK(a.GetValueAs<u32>() == 1);
    }

    {
      gl::Attribute a;
      a.SetValueAs( Tuple2u32(Variadic2u32(1, 2)) );
      CHECK(a.GetValueAs<Tuple2u32>()[0] == 1);
      CHECK(a.GetValueAs<Tuple2u32>()[1] == 2);
    }

    {
      gl::Attribute a;
      a.SetValueAs( Tuple3u32(Variadic3u32(1, 2, 3)) );
      CHECK(a.GetValueAs<Tuple3u32>()[0] == 1);
      CHECK(a.GetValueAs<Tuple3u32>()[1] == 2);
      CHECK(a.GetValueAs<Tuple3u32>()[2] == 3);
    }

    {
      gl::Attribute a;
      a.SetValueAs( Tuple4u32(Variadic4u32(1, 2, 3, 4)) );
      CHECK(a.GetValueAs<Tuple4u32>()[0] == 1);
      CHECK(a.GetValueAs<Tuple4u32>()[1] == 2);
      CHECK(a.GetValueAs<Tuple4u32>()[2] == 3);
      CHECK(a.GetValueAs<Tuple4u32>()[3] == 4);
    }
#endif

    {// Shared
      core::smart_ptr::SharedPtr<f32>  sp( new f32(1.0f) );
      gl::Attribute a;
      a.SetValueAs(sp);
      CHECK( *a.GetValueAsShared<f32>() == Approx(1.0f) );
    }
  }

  TEST_CASE("Graphics/gl/Attribute/arrays", "")
  {
    using namespace tloc::core_ds;
    using namespace tloc::core_conts;
    using namespace tloc::math_t;

    {
      gl::Attribute a;
      Array<f32> array(1, 1.0f);
      a.SetVertexArray(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK( a.GetValueAs<Array<f32> >()[0] == Approx(1.0f) );
    }

    {
      gl::Attribute a;
      Array<Vec2f32> array(1, Vec2f32(0.0f, 1.0f));
      a.SetVertexArray(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK( a.GetValueAs<Array<Vec2f32> >()[0][0] == Approx(0.0f));
      CHECK( a.GetValueAs<Array<Vec2f32> >()[0][1] == Approx(1.0f));
    }

    {
      gl::Attribute a;
      Array<Vec3f32> array(1, Vec3f32(0.0f, 1.0f, 2.0f));
      a.SetVertexArray(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK( a.GetValueAs<Array<Vec3f32> >()[0][0] == Approx(0.0f));
      CHECK( a.GetValueAs<Array<Vec3f32> >()[0][1] == Approx(1.0f));
      CHECK( a.GetValueAs<Array<Vec3f32> >()[0][2] == Approx(2.0f));
    }

    {
      gl::Attribute a;
      Array<Vec4f32> array(1, Vec4f32(0.0f, 1.0f, 2.0f, 3.0f));
      a.SetVertexArray(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK( a.GetValueAs<Array<Vec4f32> >()[0][0] == Approx(0.0f));
      CHECK( a.GetValueAs<Array<Vec4f32> >()[0][1] == Approx(1.0f));
      CHECK( a.GetValueAs<Array<Vec4f32> >()[0][2] == Approx(2.0f));
      CHECK( a.GetValueAs<Array<Vec4f32> >()[0][3] == Approx(3.0f));
    }

#if defined (TLOC_OS_WIN)
    {
      gl::Attribute a;
      Array<s32> array(1, s32(1));
      a.SetVertexArray(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(a.GetValueAs<Array<s32> >()[0] == 1);
    }

    {
      gl::Attribute a;
      Array<Tuple2s32> array(1, Tuple2s32(Variadic2s32(1, 2)) );
      a.SetVertexArray(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(a.GetValueAs<Array<Tuple2s32> >()[0][0] == 1);
      CHECK(a.GetValueAs<Array<Tuple2s32> >()[0][1] == 2);
    }

    {
      gl::Attribute a;
      Array<Tuple3s32> array(1, Tuple3s32(Variadic3s32(1, 2, 3)) );
      a.SetVertexArray(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(a.GetValueAs<Array<Tuple3s32> >()[0][0] == 1);
      CHECK(a.GetValueAs<Array<Tuple3s32> >()[0][1] == 2);
      CHECK(a.GetValueAs<Array<Tuple3s32> >()[0][2] == 3);
    }

    {
      gl::Attribute a;
      Array<Tuple4s32> array(1, Tuple4s32(Variadic4s32(1, 2, 3, 4)) );
      a.SetVertexArray(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(a.GetValueAs<Array<Tuple4s32> >()[0][0] == 1);
      CHECK(a.GetValueAs<Array<Tuple4s32> >()[0][1] == 2);
      CHECK(a.GetValueAs<Array<Tuple4s32> >()[0][2] == 3);
      CHECK(a.GetValueAs<Array<Tuple4s32> >()[0][3] == 4);
    }

    {
      gl::Attribute a;
      Array<u32> array(1, u32(1));
      a.SetVertexArray(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(a.GetValueAs<Array<u32> >()[0] == 1);
    }

    {
      gl::Attribute a;
      Array<Tuple2u32> array(1, Tuple2u32(Variadic2u32(1, 2)) );
      a.SetVertexArray(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(a.GetValueAs<Array<Tuple2u32> >()[0][0] == 1);
      CHECK(a.GetValueAs<Array<Tuple2u32> >()[0][1] == 2);
    }

    {
      gl::Attribute a;
      Array<Tuple3u32> array(1, Tuple3u32(Variadic3u32(1, 2, 3)) );
      a.SetVertexArray(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(a.GetValueAs<Array<Tuple3u32> >()[0][0] == 1);
      CHECK(a.GetValueAs<Array<Tuple3u32> >()[0][1] == 2);
      CHECK(a.GetValueAs<Array<Tuple3u32> >()[0][2] == 3);
    }

    {
      gl::Attribute a;
      Array<Tuple4u32> array(1, Tuple4u32(Variadic4u32(1, 2, 3, 4)) );
      a.SetVertexArray(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(a.GetValueAs<Array<Tuple4u32> >()[0][0] == 1);
      CHECK(a.GetValueAs<Array<Tuple4u32> >()[0][1] == 2);
      CHECK(a.GetValueAs<Array<Tuple4u32> >()[0][2] == 3);
      CHECK(a.GetValueAs<Array<Tuple4u32> >()[0][3] == 4);
    }
#endif

    {// Shared
      core::smart_ptr::SharedPtr<Array<f32> >  sp( new Array<f32>(1, f32(1.0f)) );
      gl::Attribute u;
      u.SetVertexArray(sp, gl::p_shader_variable_ti::Shared());
      CHECK( (*u.GetValueAsShared<Array<f32> >())[0] == Approx(1.0f) );
    }
  }
};
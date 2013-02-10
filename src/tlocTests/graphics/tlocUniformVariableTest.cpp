#include "tlocTestCommon.h"

// TODO - remove the following after a merge with Neil's changeset
#include <tlocCore/tloc_core.h>
#include <tlocMath/tloc_math.h>
using namespace tloc::core_ds;
using namespace tloc::core_conts;
using namespace tloc::math_t;

#include <tlocGraphics/opengl/tlocUniform.h>
#include <tlocGraphics/opengl/tlocAttribute.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>

namespace TestingGraphicsVertex
{
  using namespace tloc;
  using namespace tloc::graphics;

  TEST_CASE("Graphics/gl/Uniform", "")
  {
    using namespace tloc::core_ds;
    using namespace tloc::core_conts;
    using namespace tloc::math_t;

    {
      gl::Uniform u;
      u.SetValueAs(1.0f);
      CHECK( u.GetValueAs<f32>() == Approx(1.0f) );
    }

    {
      gl::Uniform u;
      u.SetValueAs(Vec2f32(0.0f, 1.0f));
      CHECK( u.GetValueAs<Vec2f32>()[0] == Approx(0.0f));
      CHECK( u.GetValueAs<Vec2f32>()[1] == Approx(1.0f));
    }

    {
      gl::Uniform u;
      u.SetValueAs(Vec3f32(0.0f, 1.0f, 2.0f));
      CHECK( u.GetValueAs<Vec3f32>()[0] == Approx(0.0f));
      CHECK( u.GetValueAs<Vec3f32>()[1] == Approx(1.0f));
      CHECK( u.GetValueAs<Vec3f32>()[2] == Approx(2.0f));
    }

    {
      gl::Uniform u;
      u.SetValueAs(Vec4f32(0.0f, 1.0f, 2.0f, 3.0f));
      CHECK( u.GetValueAs<Vec4f32>()[0] == Approx(0.0f));
      CHECK( u.GetValueAs<Vec4f32>()[1] == Approx(1.0f));
      CHECK( u.GetValueAs<Vec4f32>()[2] == Approx(2.0f));
      CHECK( u.GetValueAs<Vec4f32>()[3] == Approx(3.0f));
    }

    {
      gl::Uniform u;
      u.SetValueAs(s32(1));
      CHECK(u.GetValueAs<s32>() == 1);
    }

    {
      gl::Uniform u;
      u.SetValueAs( Tuple2s32(Variadic2i(1, 2)) );
      CHECK(u.GetValueAs<Tuple2s32>()[0] == 1);
      CHECK(u.GetValueAs<Tuple2s32>()[1] == 2);
    }

    {
      gl::Uniform u;
      u.SetValueAs( Tuple3s32(Variadic3i(1, 2, 3)) );
      CHECK(u.GetValueAs<Tuple3s32>()[0] == 1);
      CHECK(u.GetValueAs<Tuple3s32>()[1] == 2);
      CHECK(u.GetValueAs<Tuple3s32>()[2] == 3);
    }

    {
      gl::Uniform u;
      u.SetValueAs( Tuple4s32(Variadic4i(1, 2, 3, 4)) );
      CHECK(u.GetValueAs<Tuple4s32>()[0] == 1);
      CHECK(u.GetValueAs<Tuple4s32>()[1] == 2);
      CHECK(u.GetValueAs<Tuple4s32>()[2] == 3);
      CHECK(u.GetValueAs<Tuple4s32>()[3] == 4);
    }

    {
      gl::Uniform u;
      u.SetValueAs(u32(1));
      CHECK(u.GetValueAs<u32>() == 1);
    }

    {
      gl::Uniform u;
      u.SetValueAs( Tuple2u32(Variadic2u(1, 2)) );
      CHECK(u.GetValueAs<Tuple2u32>()[0] == 1);
      CHECK(u.GetValueAs<Tuple2u32>()[1] == 2);
    }

    {
      gl::Uniform u;
      u.SetValueAs( Tuple3u32(Variadic3u(1, 2, 3)) );
      CHECK(u.GetValueAs<Tuple3u32>()[0] == 1);
      CHECK(u.GetValueAs<Tuple3u32>()[1] == 2);
      CHECK(u.GetValueAs<Tuple3u32>()[2] == 3);
    }

    {
      gl::Uniform u;
      u.SetValueAs( Tuple4u32(Variadic4u(1, 2, 3, 4)) );
      CHECK(u.GetValueAs<Tuple4u32>()[0] == 1);
      CHECK(u.GetValueAs<Tuple4u32>()[1] == 2);
      CHECK(u.GetValueAs<Tuple4u32>()[2] == 3);
      CHECK(u.GetValueAs<Tuple4u32>()[3] == 4);
    }

    {
      gl::Uniform u;
      u.SetValueAs(Mat2f32(1, 2,
                           3, 4) ); // col-major
      CHECK(u.GetValueAs<Mat2f32>()[0] == 1);
      CHECK(u.GetValueAs<Mat2f32>()[1] == 3);
      CHECK(u.GetValueAs<Mat2f32>()[2] == 2);
      CHECK(u.GetValueAs<Mat2f32>()[3] == 4);
    }

    {
      gl::Uniform u;
      u.SetValueAs(Mat3f32(1, 2, 3,
                           4, 5, 6,
                           7, 8, 9) ); // col-major
      CHECK(u.GetValueAs<Mat3f32>()[0] == 1);
      CHECK(u.GetValueAs<Mat3f32>()[1] == 4);
      CHECK(u.GetValueAs<Mat3f32>()[2] == 7);
      CHECK(u.GetValueAs<Mat3f32>()[3] == 2);
      CHECK(u.GetValueAs<Mat3f32>()[4] == 5);
      CHECK(u.GetValueAs<Mat3f32>()[5] == 8);
      CHECK(u.GetValueAs<Mat3f32>()[6] == 3);
      CHECK(u.GetValueAs<Mat3f32>()[7] == 6);
      CHECK(u.GetValueAs<Mat3f32>()[8] == 9);
    }

    {
      gl::Uniform u;
      u.SetValueAs(Mat4f32(1 , 2 , 3 , 4 ,
                           5 , 6 , 7 , 8 ,
                           9 , 10, 11, 12,
                           13, 14, 15, 16) ); // col-major
      CHECK(u.GetValueAs<Mat4f32>()[0]  == 1);
      CHECK(u.GetValueAs<Mat4f32>()[1]  == 5);
      CHECK(u.GetValueAs<Mat4f32>()[2]  == 9);
      CHECK(u.GetValueAs<Mat4f32>()[3]  == 13);
      CHECK(u.GetValueAs<Mat4f32>()[4]  == 2);
      CHECK(u.GetValueAs<Mat4f32>()[5]  == 6);
      CHECK(u.GetValueAs<Mat4f32>()[6]  == 10);
      CHECK(u.GetValueAs<Mat4f32>()[7]  == 14);
      CHECK(u.GetValueAs<Mat4f32>()[8]  == 3);
      CHECK(u.GetValueAs<Mat4f32>()[9]  == 7);
      CHECK(u.GetValueAs<Mat4f32>()[10] == 11);
      CHECK(u.GetValueAs<Mat4f32>()[11] == 15);
      CHECK(u.GetValueAs<Mat4f32>()[12] == 4);
      CHECK(u.GetValueAs<Mat4f32>()[13] == 8);
      CHECK(u.GetValueAs<Mat4f32>()[14] == 12);
      CHECK(u.GetValueAs<Mat4f32>()[15] == 16);
    }

    {// Shared
      core::smart_ptr::SharedPtr<f32>  sp( new f32(1.0f) );
      gl::Uniform u;
      u.SetValueAs(sp);
      CHECK( *u.GetValueAsShared<f32>() == Approx(1.0f) );
    }
  }

  TEST_CASE("Graphics/gl/Uniform/arrays", "")
  {
    using namespace tloc::core_ds;
    using namespace tloc::core_conts;
    using namespace tloc::math_t;

    {
      gl::Uniform u;
      Array<f32> array(1, 1.0f);
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK( u.GetValueAs<Array<f32> >()[0] == Approx(1.0f) );
    }

    {
      gl::Uniform u;
      Array<Vec2f32> array(1, Vec2f32(0.0f, 1.0f));
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK( u.GetValueAs<Array<Vec2f32> >()[0][0] == Approx(0.0f));
      CHECK( u.GetValueAs<Array<Vec2f32> >()[0][1] == Approx(1.0f));
    }

    {
      gl::Uniform u;
      Array<Vec3f32> array(1, Vec3f32(0.0f, 1.0f, 2.0f));
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK( u.GetValueAs<Array<Vec3f32> >()[0][0] == Approx(0.0f));
      CHECK( u.GetValueAs<Array<Vec3f32> >()[0][1] == Approx(1.0f));
      CHECK( u.GetValueAs<Array<Vec3f32> >()[0][2] == Approx(2.0f));
    }

    {
      gl::Uniform u;
      Array<Vec4f32> array(1, Vec4f32(0.0f, 1.0f, 2.0f, 3.0f));
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK( u.GetValueAs<Array<Vec4f32> >()[0][0] == Approx(0.0f));
      CHECK( u.GetValueAs<Array<Vec4f32> >()[0][1] == Approx(1.0f));
      CHECK( u.GetValueAs<Array<Vec4f32> >()[0][2] == Approx(2.0f));
      CHECK( u.GetValueAs<Array<Vec4f32> >()[0][3] == Approx(3.0f));
    }

    {
      gl::Uniform u;
      Array<s32> array(1, s32(1));
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(u.GetValueAs<Array<s32> >()[0] == 1);
    }

    {
      gl::Uniform u;
      Array<Tuple2s32> array(1, Tuple2s32(Variadic2i(1, 2)) );
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(u.GetValueAs<Array<Tuple2s32> >()[0][0] == 1);
      CHECK(u.GetValueAs<Array<Tuple2s32> >()[0][1] == 2);
    }

    {
      gl::Uniform u;
      Array<Tuple3s32> array(1, Tuple3s32(Variadic3i(1, 2, 3)) );
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(u.GetValueAs<Array<Tuple3s32> >()[0][0] == 1);
      CHECK(u.GetValueAs<Array<Tuple3s32> >()[0][1] == 2);
      CHECK(u.GetValueAs<Array<Tuple3s32> >()[0][2] == 3);
    }

    {
      gl::Uniform u;
      Array<Tuple4s32> array(1, Tuple4s32(Variadic4i(1, 2, 3, 4)) );
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(u.GetValueAs<Array<Tuple4s32> >()[0][0] == 1);
      CHECK(u.GetValueAs<Array<Tuple4s32> >()[0][1] == 2);
      CHECK(u.GetValueAs<Array<Tuple4s32> >()[0][2] == 3);
      CHECK(u.GetValueAs<Array<Tuple4s32> >()[0][3] == 4);
    }

    {
      gl::Uniform u;
      Array<u32> array(1, u32(1));
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(u.GetValueAs<Array<u32> >()[0] == 1);
    }

    {
      gl::Uniform u;
      Array<Tuple2u32> array(1, Tuple2u32(Variadic2u(1, 2)) );
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(u.GetValueAs<Array<Tuple2u32> >()[0][0] == 1);
      CHECK(u.GetValueAs<Array<Tuple2u32> >()[0][1] == 2);
    }

    {
      gl::Uniform u;
      Array<Tuple3u32> array(1, Tuple3u32(Variadic3u(1, 2, 3)) );
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(u.GetValueAs<Array<Tuple3u32> >()[0][0] == 1);
      CHECK(u.GetValueAs<Array<Tuple3u32> >()[0][1] == 2);
      CHECK(u.GetValueAs<Array<Tuple3u32> >()[0][2] == 3);
    }

    {
      gl::Uniform u;
      Array<Tuple4u32> array(1, Tuple4u32(Variadic4u(1, 2, 3, 4)) );
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(u.GetValueAs<Array<Tuple4u32> >()[0][0] == 1);
      CHECK(u.GetValueAs<Array<Tuple4u32> >()[0][1] == 2);
      CHECK(u.GetValueAs<Array<Tuple4u32> >()[0][2] == 3);
      CHECK(u.GetValueAs<Array<Tuple4u32> >()[0][3] == 4);
    }

    {// Shared
      core::smart_ptr::SharedPtr<Array<f32> >  sp( new Array<f32>(1, f32(1.0f)) );
      gl::Uniform u;
      u.SetValueAs(sp, gl::p_shader_variable_ti::Shared());
      CHECK( (*u.GetValueAsShared<Array<f32> >())[0] == Approx(1.0f) );
    }
  }
};
#include "tlocTestCommon.h"

#include <tlocGraphics/opengl/tlocUniform.h>

#include <tlocCore/smart_ptr/tlocVirtualStackObject.h>
#include <tlocCore/smart_ptr/tlocVirtualStackObject.inl.h>

namespace TestingUniformVariable
{
  using namespace tloc;
  using namespace tloc::graphics;

  TEST_CASE("Graphics/gl/Uniform/copy", "")
  {
    using namespace tloc::core_ds;
    using namespace tloc::core_conts;
    using namespace tloc::math_t;

    SECTION("Normal values", "")
    {
      Vec2f32 v(0.0f, 1.0f);

      gl::Uniform u;
      u.SetValueAs(v);
      u.SetEnabled(false);

      {
        gl::Uniform ucopy(u);
        CHECK( (ucopy.GetValueAs<Vec2f32>() == v) );
        CHECK_FALSE( ucopy.IsEnabled() );
        CHECK_FALSE( u.IsEnabled() );

        ucopy.SetEnabled(true);
        CHECK( ucopy.IsEnabled() );
        CHECK_FALSE( u.IsEnabled() );
      }

      {
        gl::Uniform ucopy;
        ucopy = u;
        CHECK( (ucopy.GetValueAs<Vec2f32>() == v) );
      }
    }

    SECTION("Arrays", "")
    {
      gl::Uniform u;
      Array<f32> array(1, 1.0f);
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(u.IsArray());
      CHECK_FALSE(u.IsPtr());

      gl::Uniform uCopy(u);
      CHECK( uCopy.IsArray());
      CHECK_FALSE( uCopy.IsPtr());
      CHECK( u.GetValueAs<Array<f32> >()[0] == Approx(1.0f) );
      CHECK( uCopy.GetValueAs<Array<f32> >()[0] == Approx(1.0f) );

      gl::Uniform uCopy2;
      uCopy2 = u;
      CHECK( uCopy2.IsArray());
      CHECK_FALSE( uCopy2.IsPtr());
      CHECK( u.GetValueAs<Array<f32> >()[0] == Approx(1.0f) );
      CHECK( uCopy2.GetValueAs<Array<f32> >()[0] == Approx(1.0f) );

      Array<f32> arrayToGetBack;
      u.GetValueAs(arrayToGetBack);
    }

    SECTION("Array pointers", "")
    {
      TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Array<f32>, array_f32);

      array_f32_vso sp;
      sp->resize(1, 1.0f);

      gl::Uniform u;
      u.SetValueAs(sp.get(), gl::p_shader_variable_ti::Pointer());
      CHECK(u.IsArray());
      CHECK(u.IsPtr());

      gl::Uniform uCopy(u);
      CHECK(uCopy.IsArray());
      CHECK(uCopy.IsPtr());
      CHECK( (*u.GetValueAsPtr<Array<f32> >())[0] == Approx(1.0f) );
      CHECK( (*uCopy.GetValueAsPtr<Array<f32> >())[0] == Approx(1.0f) );

      gl::Uniform uCopy2;
      uCopy2 = u;
      CHECK(uCopy2.IsArray());
      CHECK(uCopy2.IsPtr());
      CHECK( (*u.GetValueAsPtr<Array<f32> >())[0] == Approx(1.0f) );
      CHECK( (*uCopy2.GetValueAsPtr<Array<f32> >())[0] == Approx(1.0f) );

    }
  }

  TEST_CASE("Graphics/gl/Uniform/Reset", "")
  {
    using namespace tloc::core_ds;
    using namespace tloc::core_conts;
    using namespace tloc::math_t;

    SECTION("Normal values", "")
    {
      Vec2f32 v(0.0f, 1.0f);

      gl::Uniform u;
      u.SetValueAs(v);
      u.SetName("TestVar");
      CHECK(u.IsValidType());

      u.Reset();
      CHECK_FALSE(u.IsValidType());
      CHECK(u.GetName().length() == 0);

      Vec3f32 v2(0.0f, 1.0f, 2.0f);
      u.SetValueAs(v2);
      u.SetName("TestVar2");
      CHECK(u.IsValidType());

      CHECK(u.GetValueAs<Vec3f32>()[0] == Approx(0.0f));
      CHECK(u.GetValueAs<Vec3f32>()[1] == Approx(1.0f));
      CHECK(u.GetValueAs<Vec3f32>()[2] == Approx(2.0f));

      u.ResetValue();

      Vec3f32 v3(2.0f, 3.0f, 4.0f);
      u.SetValueAs(v3);
      CHECK(u.IsValidType());

      CHECK(u.GetValueAs<Vec3f32>()[0] == Approx(2.0f));
      CHECK(u.GetValueAs<Vec3f32>()[1] == Approx(3.0f));
      CHECK(u.GetValueAs<Vec3f32>()[2] == Approx(4.0f));
    }

    SECTION("Arrays", "")
    {
      gl::Uniform u;
      Array<f32> array(1, 1.0f);
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      u.SetName("TestVar");
      CHECK(u.IsArray());
      CHECK_FALSE(u.IsPtr());

      u.Reset();
      CHECK_FALSE(u.IsValidType());
      CHECK_FALSE(u.IsArray());
      CHECK_FALSE(u.IsPtr());
      CHECK(u.GetName().length() == 0);

      Array<s32> array2(2, 2);
      u.SetValueAs(array2, gl::p_shader_variable_ti::CopyArray() );
      u.SetName("TestVar2");
      CHECK(u.IsArray());
      CHECK_FALSE(u.IsPtr());

      CHECK(u.GetValueAs<Array<s32> >()[0] == 2);
      CHECK(u.GetValueAs<Array<s32> >()[1] == 2);
    }

    SECTION("Array pointers", "")
    {
      TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Array<f32>, array_f32);
      TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Array<s32>, array_s32);

      array_f32_vso f32Array;
      f32Array->resize(1, 1.0f);

      array_s32_vso s32Array;
      s32Array->resize(2, 2);

      gl::Uniform u;
      u.SetValueAs(f32Array.get(), gl::p_shader_variable_ti::Pointer() );
      u.SetName("TestVar");
      CHECK(u.IsArray());
      CHECK(u.IsPtr());

      u.Reset();
      CHECK_FALSE(u.IsValidType());
      CHECK_FALSE(u.IsArray());
      CHECK_FALSE(u.IsPtr());
      CHECK(u.GetName().length() == 0);

      u.SetValueAs(s32Array.get(), gl::p_shader_variable_ti::Pointer() );
      u.SetName("TestVar2");
      CHECK(u.IsArray());
      CHECK(u.IsPtr());

      CHECK(u.GetValueAsPtr<array_s32_vso::pointer::value_type>()->at(0) == 2);
      CHECK(u.GetValueAsPtr<array_s32_vso::pointer::value_type>()->at(1) == 2);
    }
  }

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
      u.SetValueAs(gfx_t::color_rg(255, 255));
      CHECK( u.GetValueAs<Vec2f32>()[0] == Approx(1.0f));
      CHECK( u.GetValueAs<Vec2f32>()[1] == Approx(1.0f));
    }

    {
      gl::Uniform u;
      u.SetValueAs(gfx_t::color_rgb(255, 255, 255));
      CHECK( u.GetValueAs<Vec3f32>()[0] == Approx(1.0f));
      CHECK( u.GetValueAs<Vec3f32>()[1] == Approx(1.0f));
      CHECK( u.GetValueAs<Vec3f32>()[2] == Approx(1.0f));
    }

    {
      gl::Uniform u;
      u.SetValueAs(gfx_t::Color(255, 255, 255, 255));
      CHECK( u.GetValueAs<Vec4f32>()[0] == Approx(1.0f));
      CHECK( u.GetValueAs<Vec4f32>()[1] == Approx(1.0f));
      CHECK( u.GetValueAs<Vec4f32>()[2] == Approx(1.0f));
      CHECK( u.GetValueAs<Vec4f32>()[3] == Approx(1.0f));
    }

    {
      gl::Uniform u;
      u.SetValueAs(gfx_t::color_f32_rgba(1.0f, 0.5f, 0.0f, 1.0f));
      CHECK( u.GetValueAs<Vec4f32>()[0] == Approx(1.0f));
      CHECK( u.GetValueAs<Vec4f32>()[1] == Approx(0.5f));
      CHECK( u.GetValueAs<Vec4f32>()[2] == Approx(0.0f));
      CHECK( u.GetValueAs<Vec4f32>()[3] == Approx(1.0f));
    }

    {
      gl::Uniform u;
      u.SetValueAs(s32(1));
      CHECK(u.GetValueAs<s32>() == 1);
    }

    {
      gl::Uniform u;
      u.SetValueAs( Tuple2s32(Variadic2s32(1, 2)) );
      CHECK(u.GetValueAs<Tuple2s32>()[0] == 1);
      CHECK(u.GetValueAs<Tuple2s32>()[1] == 2);
    }

    {
      gl::Uniform u;
      u.SetValueAs( Tuple3s32(Variadic3s32(1, 2, 3)) );
      CHECK(u.GetValueAs<Tuple3s32>()[0] == 1);
      CHECK(u.GetValueAs<Tuple3s32>()[1] == 2);
      CHECK(u.GetValueAs<Tuple3s32>()[2] == 3);
    }

    {
      gl::Uniform u;
      u.SetValueAs( Tuple4s32(Variadic4s32(1, 2, 3, 4)) );
      CHECK(u.GetValueAs<Tuple4s32>()[0] == 1);
      CHECK(u.GetValueAs<Tuple4s32>()[1] == 2);
      CHECK(u.GetValueAs<Tuple4s32>()[2] == 3);
      CHECK(u.GetValueAs<Tuple4s32>()[3] == 4);
    }

#if defined (TLOC_OS_WIN)
    {
      gl::Uniform u;
      u.SetValueAs(u32(1));
      CHECK(u.GetValueAs<u32>() == 1);
    }

    {
      gl::Uniform u;
      u.SetValueAs( Tuple2u32(Variadic2u32(1, 2)) );
      CHECK(u.GetValueAs<Tuple2u32>()[0] == 1);
      CHECK(u.GetValueAs<Tuple2u32>()[1] == 2);
    }

    {
      gl::Uniform u;
      u.SetValueAs( Tuple3u32(Variadic3u32(1, 2, 3)) );
      CHECK(u.GetValueAs<Tuple3u32>()[0] == 1);
      CHECK(u.GetValueAs<Tuple3u32>()[1] == 2);
      CHECK(u.GetValueAs<Tuple3u32>()[2] == 3);
    }

    {
      gl::Uniform u;
      u.SetValueAs( Tuple4u32(Variadic4u32(1, 2, 3, 4)) );
      CHECK(u.GetValueAs<Tuple4u32>()[0] == 1);
      CHECK(u.GetValueAs<Tuple4u32>()[1] == 2);
      CHECK(u.GetValueAs<Tuple4u32>()[2] == 3);
      CHECK(u.GetValueAs<Tuple4u32>()[3] == 4);
    }
#endif

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

    SECTION("Pointer", "")
    {
      TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(f32, f32);
      f32_vso sp; *sp = 1.0f;

      gl::Uniform u;
      u.SetValueAs(sp.get());
      CHECK( *u.GetValueAsPtr<f32>() == Approx(1.0f) );
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
      Array<Tuple2s32> array(1, Tuple2s32(Variadic2s32(1, 2)) );
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(u.GetValueAs<Array<Tuple2s32> >()[0][0] == 1);
      CHECK(u.GetValueAs<Array<Tuple2s32> >()[0][1] == 2);
    }

    {
      gl::Uniform u;
      Array<Tuple3s32> array(1, Tuple3s32(Variadic3s32(1, 2, 3)) );
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(u.GetValueAs<Array<Tuple3s32> >()[0][0] == 1);
      CHECK(u.GetValueAs<Array<Tuple3s32> >()[0][1] == 2);
      CHECK(u.GetValueAs<Array<Tuple3s32> >()[0][2] == 3);
    }

    {
      gl::Uniform u;
      Array<Tuple4s32> array(1, Tuple4s32(Variadic4s32(1, 2, 3, 4)) );
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(u.GetValueAs<Array<Tuple4s32> >()[0][0] == 1);
      CHECK(u.GetValueAs<Array<Tuple4s32> >()[0][1] == 2);
      CHECK(u.GetValueAs<Array<Tuple4s32> >()[0][2] == 3);
      CHECK(u.GetValueAs<Array<Tuple4s32> >()[0][3] == 4);
    }

#if defined (TLOC_OS_WIN)

    {
      gl::Uniform u;
      Array<u32> array(1, u32(1));
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(u.GetValueAs<Array<u32> >()[0] == 1);
    }

    {
      gl::Uniform u;
      Array<Tuple2u32> array(1, Tuple2u32(Variadic2u32(1, 2)) );
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(u.GetValueAs<Array<Tuple2u32> >()[0][0] == 1);
      CHECK(u.GetValueAs<Array<Tuple2u32> >()[0][1] == 2);
    }

    {
      gl::Uniform u;
      Array<Tuple3u32> array(1, Tuple3u32(Variadic3u32(1, 2, 3)) );
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(u.GetValueAs<Array<Tuple3u32> >()[0][0] == 1);
      CHECK(u.GetValueAs<Array<Tuple3u32> >()[0][1] == 2);
      CHECK(u.GetValueAs<Array<Tuple3u32> >()[0][2] == 3);
    }

    {
      gl::Uniform u;
      Array<Tuple4u32> array(1, Tuple4u32(Variadic4u32(1, 2, 3, 4)) );
      u.SetValueAs(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(u.GetValueAs<Array<Tuple4u32> >()[0][0] == 1);
      CHECK(u.GetValueAs<Array<Tuple4u32> >()[0][1] == 2);
      CHECK(u.GetValueAs<Array<Tuple4u32> >()[0][2] == 3);
      CHECK(u.GetValueAs<Array<Tuple4u32> >()[0][3] == 4);
    }

#endif

    SECTION("Pointer", "")
    {
      TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Array<f32>, array_f32);

      array_f32_vso sp;
      sp->resize(1, 1.0f);

      gl::Uniform u;
      u.SetValueAs(sp.get(), gl::p_shader_variable_ti::Pointer());
      CHECK( (*u.GetValueAsPtr<Array<f32> >())[0] == Approx(1.0f) );
    }
  }
};
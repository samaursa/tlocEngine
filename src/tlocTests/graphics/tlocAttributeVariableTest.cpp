#include "tlocTestCommon.h"

#include <tlocGraphics/opengl/tlocAttribute.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualStackObject.inl.h>

namespace TestingAttributeVariable
{
  using namespace tloc;
  using namespace tloc::graphics;

  TEST_CASE("Graphics/gl/Attribute/copy", "")
  {
    using namespace tloc::core_ds;
    using namespace tloc::core_conts;
    using namespace tloc::math_t;

    SECTION("Normal values", "")
    {
      Vec2f32 v(0.0f, 1.0f);

      gl::Attribute a;
      a.SetName("TestVar");
      a.SetValueAs(v);
      a.SetEnabled(false);

      CHECK(gl::algos::shader_variable::compare::Name("TestVar")(a));
      CHECK_FALSE(gl::algos::shader_variable::compare::Name("TestVars")(a));

      {
        gl::Attribute acopy(a);
        CHECK( acopy.GetType() == a.GetType() );
        CHECK( (acopy.GetName().compare(a.GetName()) == 0) );
        CHECK( (acopy.GetValueAs<Vec2f32>() == v) );

        CHECK_FALSE( acopy.IsEnabled() );
        CHECK_FALSE( a.IsEnabled() );

        acopy.SetEnabled(true);
        CHECK( acopy.IsEnabled() );
        CHECK_FALSE( a.IsEnabled() );
      }

      {
        gl::Attribute acopy;
        acopy = a;
        CHECK( (acopy.GetValueAs<Vec2f32>() == v) );
      }
    }

    SECTION("Arrays", "")
    {
      gl::Attribute a;
      a.SetName("TestVarArray");
      Array<f32> array(1, 1.0f);
      a.SetVertexArray(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(a.IsAttribArray());

      CHECK(gl::algos::shader_variable::compare::Name("TestVarArray")(a));
      CHECK_FALSE(gl::algos::shader_variable::compare::Name("TestVars")(a));

      gl::Attribute aCopy(a);
      CHECK(aCopy.IsAttribArray());
      CHECK( aCopy.GetType() == a.GetType() );
      CHECK( (aCopy.GetName().compare(a.GetName()) == 0) );

      CHECK( a.GetValueAs<Array<f32> >()[0] == Approx(1.0f) );
      CHECK( aCopy.GetValueAs<Array<f32> >()[0] == Approx(1.0f) );

      gl::Attribute aCopy2;
      aCopy2 = a;
      CHECK(aCopy2.IsAttribArray());

      CHECK( a.GetValueAs<Array<f32> >()[0] == Approx(1.0f) );
      CHECK( aCopy2.GetValueAs<Array<f32> >()[0] == Approx(1.0f) );

    }
  }

  TEST_CASE("Graphics/gl/Attribute/Reset", "")
  {
    using namespace tloc::core_ds;
    using namespace tloc::core_conts;
    using namespace tloc::math_t;

    SECTION("Normal values", "")
    {
      Vec2f32 v(0.0f, 1.0f);

      gl::Attribute a;
      a.SetName("TestVar");
      a.SetValueAs(v);
      CHECK(a.IsValidType());

      a.Reset();
      CHECK(a.GetName().length() == 0);
      CHECK_FALSE(a.IsValidType());

      Vec3f32 v2(0.0f, 1.0f, 2.0f);

      // changing type without Reset() is not allowed
      a.SetValueAs(v2);
      a.SetName("TestVar2");
      CHECK( a.IsValidType() );
      CHECK( a.GetValueAs<Vec3f32>()[0] == Approx(0.0f));
      CHECK( a.GetValueAs<Vec3f32>()[1] == Approx(1.0f));
      CHECK( a.GetValueAs<Vec3f32>()[2] == Approx(2.0f));

      Vec3f32 v3(3.0f, 4.0f, 5.0f);

      a.ResetValue();
      a.SetValueAs(v3);
      CHECK( a.IsValidType() );
      CHECK( a.GetValueAs<Vec3f32>()[0] == Approx(3.0f));
      CHECK( a.GetValueAs<Vec3f32>()[1] == Approx(4.0f));
      CHECK( a.GetValueAs<Vec3f32>()[2] == Approx(5.0f));
    }

    SECTION("Arrays", "")
    {
      gl::Attribute a;
      a.SetName("TestVarArray");
      Array<f32> array(1, 1.0f);
      a.SetVertexArray(array, gl::p_shader_variable_ti::CopyArray() );
      CHECK(a.IsAttribArray());

      Array<f32> array2(2, 2);
      a.Reset();
      CHECK(a.GetName().length() == 0);
      CHECK_FALSE(a.IsValidType());

      a.SetVertexArray(array2, gl::p_shader_variable_ti::CopyArray() );
      a.SetName("TestVarArray2");
      CHECK( a.IsValidType() );
      CHECK( a.IsAttribArray() );
      CHECK( a.IsValidType() );
      CHECK( a.GetValueAs<Array<f32> >()[0] == Approx(2));
      CHECK( a.GetValueAs<Array<f32> >()[1] == Approx(2));
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

    SECTION("Pointer", "")
    {
      TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(f32, f32);
      f32_vso sp; *sp = 1.0f;

      gl::Attribute a;
      a.SetValueAs(sp.get());
      CHECK( *a.GetValueAsArrayPtr<f32>() == Approx(1.0f) );
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

    SECTION("Pointer", "")
    {
      TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Array<f32>, array_f32);

      array_f32_vso sp;
      sp->resize(1, 1.0f);

      gl::Attribute u;
      u.SetVertexArray(sp.get(), gl::p_shader_variable_ti::Pointer());
      CHECK( (*u.GetValueAsArrayPtr<Array<f32> >())[0] == Approx(1.0f) );
    }
  }
};
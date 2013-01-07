#include "tlocTestCommon.h"

#define TLOC_VECTOR_ALLOW_EASY_OPERATIONS

#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocVector4.h>

namespace TestingVector4f
{
  using namespace tloc;
  using namespace math;

  struct Vector4fFixture
  {
    Vector4fFixture()
      : b(core::Variadic4f(5, 6, 7, 8))
    {
      a[0] = 1; a[1] = 2; a[2] = 3; a[3] = 4;
    }

    Vec4f a, b, c, d, e;
  };

#define CHECK_VEC4F(vec,x,y,z,w)  CHECK((vec[0]) == (Approx(x)) ); \
                                  CHECK((vec[1]) == (Approx(y)) ); \
                                  CHECK((vec[2]) == (Approx(z)) ); \
                                  CHECK((vec[3]) == (Approx(w)) );

  TEST_CASE("Math/Vector4/Size", "Size my be as below")
  {
    REQUIRE(sizeof(Vec4f) == (sizeof(tl_float) * 4));
    REQUIRE(sizeof(Vec4f32) == (sizeof(f32) * 4));
    REQUIRE(sizeof(Vec4f64) == (sizeof(f64) * 4));
  }

  TEST_CASE_METHOD(Vector4fFixture, "Math/Vector4f/General",
    "Vector tests without math operations")
  {
    CHECK_VEC4F(a, 1.0f, 2.0f, 3.0f, 4.0f); //-V550
    CHECK_VEC4F(b, 5.0f, 6.0f, 7.0f, 8.0f); //-V550

    c = a;
    CHECK_VEC4F(c, 1.0f, 2.0f, 3.0f, 4.0f); //-V550
    CHECK_VEC4F(c, a[0], a[1], a[2], a[3]); //-V550

    d = a; e = b; d.Swap(e);
    CHECK_VEC4F(d, 5.0f, 6.0f, 7.0f, 8.0f); //-V550
    CHECK_VEC4F(e, 1.0f, 2.0f, 3.0f, 4.0f); //-V550
    CHECK_VEC4F(a, 1.0f, 2.0f, 3.0f, 4.0f); //-V550
    CHECK_VEC4F(b, 5.0f, 6.0f, 7.0f, 8.0f); //-V550

    c = Vec4f::ZERO;
    CHECK_VEC4F(c, 0.0f, 0.0f, 0.0f, 0.0f); //-V550
    c = Vec4f::ONE;
    CHECK_VEC4F(c, 1.0f, 1.0f, 1.0f, 1.0f); //-V550
    c = Vec4f::UNIT_X;
    CHECK_VEC4F(c, 1.0f, 0.0f, 0.0f, 0.0f); //-V550
    c = Vec4f::UNIT_Y;
    CHECK_VEC4F(c, 0.0f, 1.0f, 0.0f, 0.0f); //-V550
    c = Vec4f::UNIT_Z;
    CHECK_VEC4F(c, 0.0f, 0.0f, 1.0f, 0.0f); //-V550
    c = Vec4f::UNIT_W;
    CHECK_VEC4F(c, 0.0f, 0.0f, 0.0f, 1.0f); //-V550
    c = Vec4f::NEG_UNIT_X;
    CHECK_VEC4F(c, -1.0f, 0.0f, 0.0f, 0.0f); //-V550
    c = Vec4f::NEG_UNIT_Y;
    CHECK_VEC4F(c, 0.0f, -1.0f, 0.0f, 0.0f); //-V550
    c = Vec4f::NEG_UNIT_Z;
    CHECK_VEC4F(c, 0.0f, 0.0f, -1.0f, 0.0f); //-V550
    c = Vec4f::NEG_UNIT_W;
    CHECK_VEC4F(c, 0.0f, 0.0f, 0.0, -1.0f); //-V550

    // Convert from Tuple to Vec
    c = Vec4f(core::Tuple<tl_float, 4>(1.0f));
    CHECK_VEC4F(c, 1.0f, 1.0f, 1.0f, 1.0f);
  }

  TEST_CASE_METHOD(Vector4fFixture, "Math/Vector4f/Operators",
    "Vector tests with math operations")
  {
    //////////////////////////////////////////////////////////////////////////
    // Addition and subtraction

    // 1 2 3 4
    // 5 6 7 8

    // Addition single
    c = a + b;
    CHECK_VEC4F(c, 6.0f, 8.0f, 10.0f, 12.0f); //-V550

    // Subtraction double
    c = a - b;
    CHECK_VEC4F(c, -4.0f, -4.0f, -4.0f, -4.0f); //-V550

    // Addition single
    c += b;
    CHECK_VEC4F(c, 1.0f, 2.0f, 3.0f, 4.0f); //-V550

    // Subtraction single
    c -= a;
    CHECK_VEC4F(c, 0, 0, 0, 0); //-V550
    c -= a;
    CHECK_VEC4F(c, -1, -2, -3, -4); //-V550

    //////////////////////////////////////////////////////////////////////////
    // Multiplication single
    c.Zero();
    c *= a;
    CHECK_VEC4F(c, 0, 0, 0, 0); //-V550
    c = b; c *= b;
    CHECK_VEC4F(c, 25.0f, 36.0f, 49.0f, 64.0f); //-V550

    // Multiplication double
    c.Zero(); c = a * b;
    CHECK_VEC4F(c, 5.0f, 12.0f, 21.0f, 32.0f); //-V550

    // Multiplication single
    c *= 2;
    CHECK_VEC4F(c, 10.0f, 24.0f, 42.0f, 64.0f); //-V550

    //////////////////////////////////////////////////////////////////////////
    // Division
    c /= a;
    CHECK_VEC4F(c, 10.0f, 12.0f, 14.0f, 16.0f); //-V550

    c /= 14.0f;
    CHECK_VEC4F(c, 10.0f/14.0f, 12.0f/14.0f, 14.0f/14.0f, 16.0f/14.0f); //-V550


    //////////////////////////////////////////////////////////////////////////
    // Vec3 to Vec4 conversion
    math::Vec3f vec2dim(1);
    c.ConvertFrom(vec2dim, core::p_tuple::overflow_zero() );
    CHECK_VEC4F(c, 1.0f, 1.0f, 1.0f, 0.0f);
  }
}
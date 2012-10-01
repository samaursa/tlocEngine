#include "tlocTestCommon.h"

#include <tlocMath/vector/tlocVector4.h>

namespace TestingVector4f
{
  USING_TLOC;
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

  TEST_CASE_METHOD(Vector4fFixture, "Math/Vector4f/General",
    "Vector tests without math operations")
  {
    REQUIRE(sizeof(Vec4f) == (sizeof(tl_float) * 4));

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
  }
}
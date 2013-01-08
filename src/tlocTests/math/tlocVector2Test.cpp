#include "tlocTestCommon.h"

#define TLOC_VECTOR_ALLOW_EASY_OPERATIONS

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector2.inl>

#undef TLOC_VECTOR_ALLOW_EASY_OPERATIONS

namespace TestingVector2f
{
  using namespace tloc;
  using namespace core::data_structs;
  using namespace math::types;

  struct Vector2fFixture
  {
    Vector2fFixture()
      : b(Variadic2f(5, 6))
    {
      a[0] = 1; a[1] = 2;
    }

    Vec2f a, b, c, d, e;
  };

#define CHECK_VEC2F(vec,x,y) CHECK((vec[0]) == (Approx(x)) ); \
                             CHECK((vec[1]) == (Approx(y)) );

  TEST_CASE("Math/Vector2/Size", "Size my be as below")
  {
    REQUIRE(sizeof(Vec2f) == (sizeof(tl_float) * 2));
    REQUIRE(sizeof(Vec2f32) == (sizeof(f32) * 2));
    REQUIRE(sizeof(Vec2f64) == (sizeof(f64) * 2));
  }

  TEST_CASE_METHOD(Vector2fFixture, "Math/Vector2f/General",
    "Vector tests without math operations")
  {
    CHECK_VEC2F(a, 1, 2);
    CHECK_VEC2F(b, 5, 6);

    c = a;
    CHECK_VEC2F(c, 1, 2);
    CHECK_VEC2F(a, 1, 2);

    c.Zero();
    CHECK_VEC2F(c, 0, 0);

    d = a; e = b; d.Swap(e);
    CHECK_VEC2F(d, 5.0f, 6.0f);
    CHECK_VEC2F(e, 1.0f, 2.0f);
    CHECK_VEC2F(a, 1.0f, 2.0f);
    CHECK_VEC2F(b, 5.0f, 6.0f);

    c = Vec2f::ZERO;
    CHECK_VEC2F(c, 0.0f, 0.0f);
    c = Vec2f::ONE;
    CHECK_VEC2F(c, 1.0f, 1.0f);
    c = Vec2f::UNIT_X;
    CHECK_VEC2F(c, 1.0f, 0.0f);
    c = Vec2f::UNIT_Y;
    CHECK_VEC2F(c, 0.0f, 1.0f);
    c = Vec2f::NEG_UNIT_X;
    CHECK_VEC2F(c, -1.0f, 0.0f);
    c = Vec2f::NEG_UNIT_Y;
    CHECK_VEC2F(c, 0.0f, -1.0f);

    // Convert from Tuple to Vec
    c = Vec2f(Tuple<tl_float, 2>(1.0f));
    CHECK_VEC2F(c, 1.0f, 1.0f);
  }

  TEST_CASE_METHOD(Vector2fFixture, "Math/Vector2f/[]Operator",
    "Tests the square bracket operator value retrieval and assignment")
  {
    CHECK_VEC2F(a, 1, 2);
    CHECK_VEC2F(b, 5, 6);
    a[0] = 10; a[1] = 11;
    b[0] = 20; b[1] = 21;
    CHECK_VEC2F(a, 10, 11);
    CHECK_VEC2F(b, 20, 21);
  }

  TEST_CASE_METHOD(Vector2fFixture, "Math/Vector2f/SetAndZero",
                                    "Tests the Set() and Zero() functions")
  {
    a.Set(1);
    CHECK_VEC2F(a, 1, 1);
    a.Set(-1);
    CHECK_VEC2F(a, -1, -1);

#define BIG_FLOAT -0.987654321f
    a.Set(BIG_FLOAT);
    CHECK_VEC2F(a, BIG_FLOAT, BIG_FLOAT);
#undef BIG_FLOAT

    a.Zero();
    CHECK_VEC2F(a, 0, 0);
  }

  TEST_CASE_METHOD(Vector2fFixture, "Math/Vector2f/BasicOperations",
                "Test addition, subtraction, multiplication and division")
  {
    //////////////////////////////////////////////////////////////////////////
    // Addition and subtraction

    // Addition single
    c.Add(a, b);
    CHECK_VEC2F(c, 6, 8);

    // Subtraction double
    c.Sub(a, b);
    CHECK_VEC2F(c, -4, -4);

    // Addition single
    c.Add(b);
    CHECK_VEC2F(c, 1, 2);

    // Subtraction single
    c.Sub(a);
    CHECK_VEC2F(c, 0, 0);
    c.Sub(a);
    CHECK_VEC2F(c, -1, -2);

    //////////////////////////////////////////////////////////////////////////
    // Multiplication single

    c.Zero();
    c.Mul(a);
    CHECK_VEC2F(c, 0, 0);
    c = b; c.Mul(b);
    CHECK_VEC2F(c, 25, 36);
    c.Mul(2);
    CHECK_VEC2F(c, 50, 72);
    c.Div(b);
    CHECK_VEC2F(c, 10, 12);
    c.Div(2);
    CHECK_VEC2F(c, 5, 6);
  }

  TEST_CASE_METHOD(Vector2fFixture, "Math/Vector2f/BasicAssignmentOperators",
    "Test addition, subtraction, multiplication and division operators")
  {
    //////////////////////////////////////////////////////////////////////////
    // Addition and subtraction

    // Addition single
    c = a + b;
    CHECK_VEC2F(c, 6, 8);

    // Subtraction double
    c = a - b;
    CHECK_VEC2F(c, -4, -4);

    // Addition single
    c += b;
    CHECK_VEC2F(c, 1, 2);

    // Subtraction single
    c -= a;
    CHECK_VEC2F(c, 0, 0);
    c -= a;
    CHECK_VEC2F(c, -1, -2);

    //////////////////////////////////////////////////////////////////////////
    // Multiplication single

    c.Zero();
    c *= a;
    CHECK_VEC2F(c, 0, 0);
    c = b; c *= b;
    CHECK_VEC2F(c, 25, 36);
    c *= 2;
    CHECK_VEC2F(c, 50, 72);
    c /= b;
    CHECK_VEC2F(c, 10, 12);
    c /= 2;
    CHECK_VEC2F(c, 5, 6);
  }
}
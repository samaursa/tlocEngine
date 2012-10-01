#include "tlocTestCommon.h"

#define TLOC_VECTOR_ALLOW_EASY_OPERATIONS

#include <tlocMath/vector/tlocVector3.h>
#include <tlocMath/vector/tlocVector2.h>

#undef TLOC_VECTOR_ALLOW_EASY_OPERATIONS


namespace TestingVector3f
{
  USING_TLOC;
  using namespace math;

  struct Vector3fFixture
  {
    Vector3fFixture()
      : b(core::Variadic3f(5, 6, 7))
    {
      a[0] = 1; a[1] = 2; a[2] = 3;
    }

    Vec3f a, b, c, d, e;
  };

#define CHECK_VEC3F(vec,x,y,z) CHECK((vec[0]) == (Approx(x)) ); \
                               CHECK((vec[1]) == (Approx(y)) ); \
                               CHECK((vec[2]) == (Approx(z)) );

  TEST_CASE_METHOD(Vector3fFixture, "Math/Vector3f/General",
    "Vector tests without math operations")
  {
    REQUIRE(sizeof(Vec3f) == (sizeof(tl_float) * 3));

    CHECK_VEC3F(a, 1.0f, 2.0f, 3.0f); //-V550
    CHECK_VEC3F(b, 5.0f, 6.0f, 7.0f); //-V550

    c = a;
    CHECK_VEC3F(c, 1.0f, 2.0f, 3.0f); //-V550
    CHECK_VEC3F(c, a[0], a[1], a[2]); //-V550

    c.Zero();
    CHECK_VEC3F(c, 0, 0, 0); //-V550

    d = a; e = b; d.Swap(e);
    CHECK_VEC3F(d, 5.0f, 6.0f, 7.0f); //-V550
    CHECK_VEC3F(e, 1.0f, 2.0f, 3.0f); //-V550
    CHECK_VEC3F(a, 1.0f, 2.0f, 3.0f); //-V550
    CHECK_VEC3F(b, 5.0f, 6.0f, 7.0f); //-V550

    c = Vec3f::ZERO;
    CHECK_VEC3F(c, 0.0f, 0.0f, 0.0f); //-V550
    c = Vec3f::ONE;
    CHECK_VEC3F(c, 1.0f, 1.0f, 1.0f); //-V550
    c = Vec3f::UNIT_X;
    CHECK_VEC3F(c, 1.0f, 0.0f, 0.0f); //-V550
    c = Vec3f::UNIT_Y;
    CHECK_VEC3F(c, 0.0f, 1.0f, 0.0f); //-V550
    c = Vec3f::UNIT_Z;
    CHECK_VEC3F(c, 0.0f, 0.0f, 1.0f); //-V550
    c = Vec3f::NEG_UNIT_X;
    CHECK_VEC3F(c, -1.0f, 0.0f, 0.0f); //-V550
    c = Vec3f::NEG_UNIT_Y;
    CHECK_VEC3F(c, 0.0f, -1.0f, 0.0f); //-V550
    c = Vec3f::NEG_UNIT_Z;
    CHECK_VEC3F(c, 0.0f, 0.0f, -1.0f); //-V550

  }

  TEST_CASE_METHOD(Vector3fFixture, "Math/Vector3f/[]Operator",
    "Tests the square bracket operator value retrieval and assignment")
  {
    CHECK_VEC3F(a, 1, 2, 3); //-V550
    CHECK_VEC3F(b, 5, 6, 7); //-V550
    a[0] = 10; a[1] = 11; a[2] = 12;
    b[0] = 20; b[1] = 21; b[2] = 22;
    CHECK_VEC3F(a, 10, 11, 12); //-V550
    CHECK_VEC3F(b, 20, 21, 22); //-V550
  }

  TEST_CASE_METHOD(Vector3fFixture, "Math/Vector3f/SetAndZero",
                                    "Tests the Set() and Zero() functions")
  {
    a.Set(1);
    CHECK_VEC3F(a, 1, 1, 1); //-V550
    a.Set(-1);
    CHECK_VEC3F(a, -1, -1, -1); //-V550

#define BIG_FLOAT -0.987654321f
    a.Set(BIG_FLOAT);
    CHECK_VEC3F(a, BIG_FLOAT, BIG_FLOAT, BIG_FLOAT); //-V550
#undef BIG_FLOAT

    a.Zero();
    CHECK_VEC3F(a, 0, 0, 0); //-V550
  }

  TEST_CASE_METHOD(Vector3fFixture, "Math/Vector3f/BasicOperations",
                  "Test addition, subtraction, multiplication and division")
  {
    //////////////////////////////////////////////////////////////////////////
    // Addition and subtraction

    // Addition single
    c.Add(a, b);
    CHECK_VEC3F(c, 6.0f, 8.0f, 10.0f); //-V550

    // Subtraction double
    c.Sub(a, b);
    CHECK_VEC3F(c, -4.0f, -4.0f, -4.0f); //-V550

    // Addition single
    c.Add(b);
    CHECK_VEC3F(c, 1.0f, 2.0f, 3.0f); //-V550

    // Subtraction single
    c.Sub(a);
    CHECK_VEC3F(c, 0, 0, 0); //-V550
    c.Sub(a);
    CHECK_VEC3F(c, -1, -2, -3); //-V550

    //////////////////////////////////////////////////////////////////////////
    // Multiplication single
    c.Zero();
    c.Mul(a);
    CHECK_VEC3F(c, 0, 0, 0); //-V550
    c = b; c.Mul(b);
    CHECK_VEC3F(c, 25.0f, 36.0f, 49.0f); //-V550

    // Multiplication double
    c.Zero(); c.Mul(a, b);
    CHECK_VEC3F(c, 5.0f, 12.0f, 21.0f); //-V550

    // Multiplication single
    c.Mul(2);
    CHECK_VEC3F(c, 10.0f, 24.0f, 42.0f); //-V550

    //////////////////////////////////////////////////////////////////////////
    // Division
    c.Div(a);
    CHECK_VEC3F(c, 10.0f, 12.0f, 14.0f); //-V550

    c.Div(14.0f);
    CHECK_VEC3F(c, 10.0f/14.0f, 12.0f/14.0f, 14.0f/14.0f); //-V550
  }

  TEST_CASE_METHOD(Vector3fFixture, "Math/Vector3f/BasicAssignmentOperators",
    "Test addition, subtraction, multiplication and division")
  {
    //////////////////////////////////////////////////////////////////////////
    // Addition and subtraction

    // Addition single
    c = a + b;
    CHECK_VEC3F(c, 6.0f, 8.0f, 10.0f); //-V550

    // Subtraction double
    c = a - b;
    CHECK_VEC3F(c, -4.0f, -4.0f, -4.0f); //-V550

    // Addition single
    c += b;
    CHECK_VEC3F(c, 1.0f, 2.0f, 3.0f); //-V550

    // Subtraction single
    c -= a;
    CHECK_VEC3F(c, 0, 0, 0); //-V550
    c -= a;
    CHECK_VEC3F(c, -1, -2, -3); //-V550

    //////////////////////////////////////////////////////////////////////////
    // Multiplication single
    c.Zero();
    c *= a;
    CHECK_VEC3F(c, 0, 0, 0); //-V550
    c = b; c *= b;
    CHECK_VEC3F(c, 25.0f, 36.0f, 49.0f); //-V550

    // Multiplication double
    c.Zero(); c = a * b;
    CHECK_VEC3F(c, 5.0f, 12.0f, 21.0f); //-V550

    // Multiplication single
    c *= 2;
    CHECK_VEC3F(c, 10.0f, 24.0f, 42.0f); //-V550

    //////////////////////////////////////////////////////////////////////////
    // Division
    c /= a;
    CHECK_VEC3F(c, 10.0f, 12.0f, 14.0f); //-V550

    c /= 14.0f;
    CHECK_VEC3F(c, 10.0f/14.0f, 12.0f/14.0f, 14.0f/14.0f); //-V550


    //////////////////////////////////////////////////////////////////////////
    // Vec2 to Vec3 conversion
    math::Vec2f vec2dim(0);
    c.ConvertFrom(vec2dim, core::p_tuple::overflow_zero() );
    CHECK_VEC3F(c, 0.0f, 0.0f, 0.0f);
  }

  TEST_CASE_METHOD(Vector3fFixture, "Math/Vector3f/Length", "Tests the "
    "length and length squared")
  {
    c.Zero(); c[0] = 2; c[1] = 2; c[2] = 2;
    tl_float lengthSq = c.LengthSquared();
    CHECK(lengthSq == Approx(12.0f)); //-V550

    c.Zero();
    tl_float length = c.Length();
    CHECK(length == Approx(0.0f)); //-V550

    c[0] = 1, c[1] = 1, c[2] = 0;
    length = c.Length();
    CHECK(length == Approx(1.414213562373095f)); //-V550
  }

  TEST_CASE_METHOD(Vector3fFixture, "Math/Vector3f/NormalizeLengthDis",
    "Tests the normalize, length and distance functions")
  {
    c[0] = 2, c[1] = 0; c[2] = 0;
    c.Norm();
    CHECK_VEC3F(c, 1, 0, 0); //-V550

    d = c;
    c.Add(d);
    CHECK_VEC3F(c, 2, 0, 0); //-V550
    c[1] = 2; c[2] = 2;
    d.Norm(c);

    CHECK_VEC3F(d, 0.5773503f, 0.5773503f, 0.5773503f); //-V550
    c.Norm();
    CHECK_VEC3F(c, 0.5773503f, 0.5773503f, 0.5773503f); //-V550
    tl_float length = c.NormLength();
    CHECK(length == Approx(1.0f)); //-V550

    c[0] = 2; c[1] = 2; c[2] = 2;
    c.FastNorm();
    tl_float percDiff = abs((c[0] - 0.577f) / c[0]);
    // Make sure all the values are the same
    CHECK_VEC3F(c, c[0], c[0], c[0]); //-V550
    CHECK (percDiff < 0.03f);
    length = c.Length();
    CHECK (length > 0.99f);

    c.Zero(); c[0] = 1;
    d.Zero(); d[0] = 2;
    tl_float dis = c.Distance(d);
    CHECK_VEC3F(c, 1, 0, 0); //-V550
    CHECK_VEC3F(d, 2, 0, 0); //-V550
    CHECK(dis == Approx(1)); //-V550

    d[0] = 3;
    dis = c.DistanceSquared(d);
    CHECK_VEC3F(c, 1, 0, 0); //-V550
    CHECK_VEC3F(d, 3, 0, 0); //-V550
    CHECK(dis == Approx(4)); //-V550
  }

  TEST_CASE_METHOD(Vector3fFixture, "Math/Vector3f/DotAndCross",
    "Tests the dot and cross methods")
  {
    c.Zero(); d.Zero(); e.Zero();
    c[0] = 1; d[1] = 1; e = c;
    CHECK(c.Dot(d) == Approx(0)); //-V550
    CHECK(c.Dot(e) == Approx(1)); //-V550
    d.Zero(); d[2] = 1;
    e = c; e.Neg();
    CHECK(c.Dot(d) == Approx(0)); //-V550
    CHECK(c.Dot(e) == Approx(-1)); //-V550

    c.Zero(); c[0] = -1; c[1] = 1;
    d.Zero(); d[0] = 0.5f; d[1] = 0.3f;
    d.Norm();
    CHECK(d.Length() == Approx(1.0f)); //-V550
    CHECK(c.Dot(d) < 0);
    CHECK(c.DotAbs(d) >= 0);

    c.Zero(); c[0] = 1;
    d.Zero(); d[0] = 2;
    e.Midpoint(c, d);
    CHECK_VEC3F(e, 1.5f, 0, 0); //-V550
    c.Set(1); d.Set(2);
    e.Midpoint(c, d);
    CHECK_VEC3F(e, 1.5f, 1.5f, 1.5f); //-V550
    e.Midpoint(d);
    CHECK_VEC3F(e, 1.75f, 1.75f, 1.75f); //-V550

    c.Zero(); c[0] = 1;
    d.Zero(); d[1] = 1;
    c.Cross(d);
    CHECK_VEC3F(c, 0, 0, 1); //-V550
    c.Cross(d);
    CHECK_VEC3F(c, -1, 0, 0); //-V550
    e.Cross(c, d);
    CHECK_VEC3F(e, 0, 0, -1); //-V550
  }

  TEST_CASE_METHOD(Vector3fFixture, "Math/Vector3f/ComparisonsAndChecks",
    "Tests == and != comparisons as well as checks")
  {
    CHECK((a != b) == true);
    a = b;
    CHECK((a == b) == true);
    a[0] = 0.0000001f; b[0] = 0.0000002f;
    CHECK((a == b) == true);
    a[0] = 0.000002f; b[0] = 0.000005f;
    CHECK((a != b) == true);

    a.Zero();
    CHECK(a.IsZero() == true);
    CHECK(a.IsValid() == true);
    a[2] = sqrt(-2.0f);
    CHECK(a.IsValid() == false);
  }

}
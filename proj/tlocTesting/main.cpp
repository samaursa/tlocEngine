#include "catch_with_main.hpp"
#include "catch.hpp"

#include "tlocMath/tlocVector.h"
#include "tlocCore/tlocBase.h"

using namespace Catch::Detail;

struct Vector3fFixture
{
  Vector3fFixture() 
  {
    a[0] = 1; a[1] = 2; a[2] = 3;
    b[0] = 5; b[1] = 6; b[2] = 7;
  }

  tloc::Vector<float, 3> a, b, c, d, e;
};
#define REQUIRE_VEC3F(vec,x,y,z) REQUIRE((vec[0]) == (Approxf(x)) ); \
                                 REQUIRE((vec[1]) == (Approxf(y)) ); \
                                 REQUIRE((vec[2]) == (Approxf(z)) );

TEST_CASE_METHOD(Vector3fFixture, "vector3f/general", "Vector tests without math operations")
{
  REQUIRE_VEC3F(a, 1.0f, 2.0f, 3.0f);
  REQUIRE_VEC3F(b, 5.0f, 6.0f, 7.0f);

  c = a;
  REQUIRE_VEC3F(c, 1.0f, 2.0f, 3.0f);
  REQUIRE_VEC3F(c, a[0], a[1], a[2]);
  
  c.Zero();
  REQUIRE_VEC3F(c, 0, 0, 0);

  d = a; e = b; d.Swap(e);
  REQUIRE_VEC3F(d, 5.0f, 6.0f, 7.0f);
  REQUIRE_VEC3F(e, 1.0f, 2.0f, 3.0f);
}

TEST_CASE_METHOD(Vector3fFixture, "vector3f/math", "Vector math operations tests")
{
  c.Add(a, b);
  REQUIRE_VEC3F(c, 6.0f, 8.0f, 10.0f);

  c.Zero(); 
  c.Sub(a, b);
  REQUIRE_VEC3F(c, -4.0f, -4.0f, -4.0f);
  
  c.Add(b);
  REQUIRE_VEC3F(c, 1.0f, 2.0f, 3.0f);
  
  c.Sub(a);
  REQUIRE_VEC3F(c, 0, 0, 0);

  c.Mul(a);
  REQUIRE_VEC3F(c, 0, 0, 0);

  c = b; c.Mul(b);
  REQUIRE_VEC3F(c, 25.0f, 36.0f, 49.0f);

  c.Zero(); c.Mul(a, b);
  REQUIRE_VEC3F(c, 5.0f, 12.0f, 21.0f);

  c.Mul(2);
  REQUIRE_VEC3F(c, 10.0f, 24.0f, 42.0f);

  c.Div(a);
  REQUIRE_VEC3F(c, 10.0f, 12.0f, 14.0f);

  c.Div(14.0f);
  REQUIRE_VEC3F(c, 10.0f/14.0f, 12.0f/14.0f, 14.0f/14.0f);

  c.Zero(); c[0] = 2; c[1] = 2; c[2] = 2;
  float lengthSq;
  c.LengthSquared(lengthSq);
  REQUIRE(lengthSq == Approxf(12.0f));

  float length;
  c.Zero(); c.Length(length);
  REQUIRE(length == Approxf(0.0f));
  
  c[0] = 1, c[1] = 1, c[2] = 0;
  c.Length(length);
  REQUIRE(length == Approxf(1.414213562373095f));

  c[0] = 2, c[1] = 0; c[2] = 0;
  c.Norm();
  REQUIRE_VEC3F(c, 1, 0, 0);

  d = c;
  c.Add(d);
  REQUIRE_VEC3F(c, 2, 0, 0);
  c[1] = 2; c[2] = 2;
  d.Norm(c);

  REQUIRE_VEC3F(d, 0.5773503f, 0.5773503f, 0.5773503f);
  c.Norm();
  REQUIRE_VEC3F(c, 0.5773503f, 0.5773503f, 0.5773503f);
  length = c.NormLength();
  REQUIRE(length == Approxf(1.0f));

  c[0] = 2; c[1] = 2; c[2] = 2;
  c.FastNorm();
  float percDiff = abs((c[0] - 0.577f) / c[0]);
  // Make sure all the values are the same
  REQUIRE_VEC3F(c, c[0], c[0], c[0]);
  REQUIRE (percDiff < 0.03f);
  c.Length(length);
  REQUIRE (length > 0.99f);
}
namespace TestingVector3f
{
  struct Vector3fFixture
  {
    Vector3fFixture() 
    {
      a[0] = 1; a[1] = 2; a[2] = 3;
      b[0] = 5; b[1] = 6; b[2] = 7;
    }

    tloc::Vec3f a, b, c, d, e;
  };

#define REQUIRE_VEC3F(vec,x,y,z) REQUIRE((vec[0]) == (Approxf(x)) ); \
  REQUIRE((vec[1]) == (Approxf(y)) ); \
  REQUIRE((vec[2]) == (Approxf(z)) );

  TEST_CASE_METHOD(Vector3fFixture, "Math/Vector3f/General", 
    "Vector tests without math operations")
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
    REQUIRE_VEC3F(a, 1.0f, 2.0f, 3.0f);
    REQUIRE_VEC3F(b, 5.0f, 6.0f, 7.0f);
  }

  TEST_CASE_METHOD(Vector3fFixture, "Math/Vector3f/[]Operator", 
    "Tests the square bracket operator value retrieval and assignment")
  {
    REQUIRE_VEC3F(a, 1, 2, 3);
    REQUIRE_VEC3F(b, 5, 6, 7);
    a[0] = 10; a[1] = 11; a[2] = 12;
    b[0] = 20; b[1] = 21; b[2] = 22;
    REQUIRE_VEC3F(a, 10, 11, 12);
    REQUIRE_VEC3F(b, 20, 21, 22);
  }

  TEST_CASE_METHOD(Vector3fFixture, "Math/Vector3f/SetAndZero", 
                                    "Tests the Set() and Zero() functions")
  {
    a.Set(1);
    REQUIRE_VEC3F(a, 1, 1, 1);
    a.Set(-1);
    REQUIRE_VEC3F(a, -1, -1, -1);

#define BIG_FLOAT -0.987654321f
    a.Set(BIG_FLOAT);
    REQUIRE_VEC3F(a, BIG_FLOAT, BIG_FLOAT, BIG_FLOAT);
#undef BIG_FLOAT

    a.Zero();
    REQUIRE_VEC3F(a, 0, 0, 0);
  }

  TEST_CASE_METHOD(Vector3fFixture, "Math/Vector3f/BasicOperations", 
                  "Test addition, subtraction, multiplication and division")
  {
    //////////////////////////////////////////////////////////////////////////
    // Addition and subtraction

    // Addition single
    c.Add(a, b);
    REQUIRE_VEC3F(c, 6.0f, 8.0f, 10.0f);

    // Subtraction double 
    c.Sub(a, b);
    REQUIRE_VEC3F(c, -4.0f, -4.0f, -4.0f);

    // Addition single
    c.Add(b);
    REQUIRE_VEC3F(c, 1.0f, 2.0f, 3.0f);

    // Subtraction single
    c.Sub(a);
    REQUIRE_VEC3F(c, 0, 0, 0);
    c.Sub(a);
    REQUIRE_VEC3F(c, -1, -2, -3);

    //////////////////////////////////////////////////////////////////////////
    // Multiplication single
    c.Zero();
    c.Mul(a);
    REQUIRE_VEC3F(c, 0, 0, 0);
    c = b; c.Mul(b);
    REQUIRE_VEC3F(c, 25.0f, 36.0f, 49.0f);

    // Multiplication double
    c.Zero(); c.Mul(a, b);
    REQUIRE_VEC3F(c, 5.0f, 12.0f, 21.0f);

    // Multiplication single
    c.Mul(2);
    REQUIRE_VEC3F(c, 10.0f, 24.0f, 42.0f);

    //////////////////////////////////////////////////////////////////////////
    // Division
    c.Div(a);
    REQUIRE_VEC3F(c, 10.0f, 12.0f, 14.0f);

    c.Div(14.0f);
    REQUIRE_VEC3F(c, 10.0f/14.0f, 12.0f/14.0f, 14.0f/14.0f);
  }

  TEST_CASE_METHOD(Vector3fFixture, "Math/Vector3f/Length", "Tests the "
    "length and length squared")
  {
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
  }

  TEST_CASE_METHOD(Vector3fFixture, "Math/Vector3f/NormalizeLengthDis", 
    "Tests the normalize, length and distance functions")
  {
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
    float length = c.NormLength();
    REQUIRE(length == Approxf(1.0f));

    c[0] = 2; c[1] = 2; c[2] = 2;
    c.FastNorm();
    float percDiff = abs((c[0] - 0.577f) / c[0]);
    // Make sure all the values are the same
    REQUIRE_VEC3F(c, c[0], c[0], c[0]);
    REQUIRE (percDiff < 0.03f);
    c.Length(length);
    REQUIRE (length > 0.99f);

    c.Zero(); c[0] = 1;
    d.Zero(); d[0] = 2;
    float dis = c.Distance(d);
    REQUIRE_VEC3F(c, 1, 0, 0);
    REQUIRE_VEC3F(d, 2, 0, 0);
    REQUIRE(dis == 1);

    d[0] = 3;
    dis = c.DistanceSquared(d);
    REQUIRE_VEC3F(c, 1, 0, 0);
    REQUIRE_VEC3F(d, 3, 0, 0);
    REQUIRE(dis == 4);
  }

  TEST_CASE_METHOD(Vector3fFixture, "Math/Vector3f/DotAndCross", 
    "Tests the dot and cross methods")
  {
    c.Zero(); d.Zero(); e.Zero();
    c[0] = 1; d[1] = 1; e = c;
    REQUIRE(c.Dot(d) == 0);
    REQUIRE(c.Dot(e) == 1);
    d.Zero(); d[2] = 1;
    e = c; e.Neg();
    REQUIRE(c.Dot(d) == 0);
    REQUIRE(c.Dot(e) == -1);

    c.Zero(); c[0] = -1; c[1] = 1;
    d.Zero(); d[0] = 0.5f; d[1] = 0.3f;
    d.Norm();
    REQUIRE(d.Length() == Approxf(1.0f));
    REQUIRE(c.Dot(d) < 0);
    REQUIRE(c.DotAbs(d) >= 0);

    c.Zero(); c[0] = 1;
    d.Zero(); d[0] = 2;
    e.Midpoint(c, d);
    REQUIRE_VEC3F(e, 1.5f, 0, 0);
    c.Set(1); d.Set(2);
    e.Midpoint(c, d);
    REQUIRE_VEC3F(e, 1.5f, 1.5f, 1.5f);
    e.Midpoint(d);
    REQUIRE_VEC3F(e, 1.75f, 1.75f, 1.75f);

    c.Zero(); c[0] = 1;
    d.Zero(); d[1] = 1;
    c.Cross(d);
    REQUIRE_VEC3F(c, 0, 0, 1);
    c.Cross(d);
    REQUIRE_VEC3F(c, -1, 0, 0);
    e.Cross(c, d);
    REQUIRE_VEC3F(e, 0, 0, -1);
  }

  TEST_CASE_METHOD(Vector3fFixture, "Math/Vector3f/ComparisonsAndChecks", 
    "Tests == and != comparisons as well as checks")
  {
    REQUIRE(a != b);
    a = b;
    REQUIRE(a == b);
    a[0] = 0.0000001f; b[5] = 0.0000002f;
    REQUIRE(a == b);
    a[0] = 0.000002f; b[0] = 0.000005f;
    REQUIRE(a != b);

    a.Zero();
    REQUIRE(a.IsZero() == true);
    REQUIRE(a.IsValid() == true);
    a[2] = sqrt(-2.0f);
    REQUIRE(a.IsValid() == false);
  }

#undef REQUIRE_VEC3F
}
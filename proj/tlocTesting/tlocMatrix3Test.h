#include "tlocMath/tlocMatrix3.h"

namespace TestingMatrix3
{
  struct Matrix3Fixture
  {
    Matrix3Fixture() 
    {
    }

    tloc::Mat3f a, b, c, d, e;
  };

  TEST_CASE_METHOD(Matrix3Fixture, "Math/Matrix3/General", 
    "Test general/basic functionality")
  {
    a.Zero();
    tloc::Mat3f f(a);
    CHECK_MATRIX3F(f, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    tloc::Mat3f g(1, 2, 3, 4, 5, 6, 7, 8, 9);
    CHECK_MATRIX3F(g, 1, 4, 7, 2, 5, 8, 3, 6, 9);

    tloc::Mat3f h(4, 5, 6);
    CHECK_MATRIX3F(h, 4, 0, 0, 0, 5, 0, 0, 0, 6);

    tloc::Mat3f i(90);
    CHECK_MATRIX3F(i, 90, 90, 90, 90, 90, 90, 90, 90, 90);

    tloc::Vec3f v1(1, 2, 3), v2(4, 5, 6), v3(7, 8, 9);
    tloc::Mat3f j(v1, v2, v3, tloc::Mat3f::ROW_MAJOR);
    CHECK_MATRIX3F(j, 1, 4, 7, 2, 5, 8, 3, 6, 9);

    tloc::Mat3f k(v1, v2, v3, tloc::Mat3f::COL_MAJOR);
    CHECK_MATRIX3F(k, 1, 2, 3, 4, 5, 6, 7, 8, 9);

    f32 values[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    tloc::Mat3f m(values, tloc::Mat3f::ROW_MAJOR);
    CHECK_MATRIX3F(m, 1, 4, 7, 2, 5, 8, 3, 6, 9);

    tloc::Mat3f n(values, tloc::Mat3f::COL_MAJOR);
    CHECK_MATRIX3F(n, 1, 2, 3, 4, 5, 6, 7, 8, 9);

  }

  TEST_CASE_METHOD(Matrix3Fixture, "Math/Matrix3/Math/Mul",
    "Test multiplication")
  {
    f32 values[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    a.Set(values, Mat3f::ROW_MAJOR);
    b.Set(values, Mat3f::ROW_MAJOR);

    c.Mul(a, b);
    CHECK_MATRIX3F(c, 30, 66, 102, 36, 81, 126, 42, 96, 150);

    c.Set(values, Mat3f::ROW_MAJOR);
    c.Mul(a);
    CHECK_MATRIX3F(c, 30, 66, 102, 36, 81, 126, 42, 96, 150);

    Vec3f vec1(1, 2, 3), vec2;
    c.Set(values, Mat3f::ROW_MAJOR);
    c.Mul(vec1, vec2);
    CHECK_VEC3F(vec2, 14, 32, 50);
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Math/Matrix3/Det", 
    "Test determinant")
  {
    f32 values[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    a.Set(values, Mat3f::ROW_MAJOR);

    CHECK(a.Determinant() == Approx(0));

    f32 values2[9] = {4, 5, 6, 4, 9, 6, 4, 9, 9};
    a.Set(values2, Mat3f::ROW_MAJOR);
    CHECK(a.Determinant() == Approx(48));
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Math/Matrix3/Inv", 
    "Test inverse")
  {
    f32 values[9] = {4, 5, 6, 4, 9, 6, 4, 9, 9};
    a.Set(values, Mat3f::ROW_MAJOR);

    REQUIRE(b.Inverse(a) == true);
    CHECK_MATRIX3F(b, 0.5625f, -0.25f, 0, 0.1875f, 0.25, -0.33333f, -0.5f, 0, .33333f);

    f32 values2[9] = {89, 58, 23, 97, 78, 72, 54, 32, 90};
    a.Set(values2, Mat3f::ROW_MAJOR);
    a.Inverse();
    CHECK_MATRIX3F(a, 0.041585f, -0.04269f, -0.00977f, 
                     -0.03954f,   0.059680,  0.002504f, 
                      0.021004f, -0.03683f,  0.011604f);
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Math/Matrix3/Adj", 
    "Test adjoint")
  {
    f32 values[9] = {2, 0, 1, 3, 2, -1, 1, 0, 0};
    a.Set(values, Mat3f::ROW_MAJOR);
    b.Adjoint(a);

    CHECK_MATRIX3F(b, 0, -1, -2, 0, -1, 0, -2, 5, 4);

    a.Adjoint();
    CHECK_MATRIX3F(a, 0, -1, -2, 0, -1, 0, -2, 5, 4);
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Math/Matrix3/OrthoNorm", 
    "Test orthonormalize")
  {
    f32 values[9] = {1, 4, 7, 4, 5, 8, 9, 15, 5};
    a.Set(values, Mat3f::ROW_MAJOR);

    a.Orthonormalize();
    CHECK_MATRIX3F(a, 0.10101525f, 0.40406102f, 0.90913731f,
                      0.83898753f, -0.52571768f, 0.14043106f,
                      0.53469253f, 0.74856889f, -0.39210755f);
    Vec3f col1, col2, col3;
    a.GetCol(0, col1);
    a.GetCol(1, col2);
    a.GetCol(2, col3);    
    CHECK(col1.Length() == Approx(1));
    CHECK(col2.Length() == Approx(1));
    CHECK(col3.Length() == Approx(1));

    a.Zero();
    a.Set(values, Mat3f::ROW_MAJOR);
    a.FastOrthonormalize();
    f32 prec = 1e-1f;
    CHECK( (Mathf::Approx(a[0], 0.10f, prec)) == true );
    CHECK( (Mathf::Approx(a[1], 0.40f, prec)) == true );
    CHECK( (Mathf::Approx(a[2], 0.90f, prec)) == true );
    CHECK( (Mathf::Approx(a[3], 0.83f, prec)) == true );
    CHECK( (Mathf::Approx(a[4], -0.52f, prec)) == true );
    CHECK( (Mathf::Approx(a[5], 0.14f, prec)) == true );
    CHECK( (Mathf::Approx(a[6], 0.53f, prec)) == true );
    CHECK( (Mathf::Approx(a[7], 0.74f, prec)) == true );
    CHECK( (Mathf::Approx(a[8], -0.39f, prec)) == true );
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Math/Matrix3/EigenDecomp", 
    "Test eigen decomposition")
  {
  }
};
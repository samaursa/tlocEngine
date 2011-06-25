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
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Math/Matrix3/Det", 
    "Test determinant")
  {
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Math/Matrix3/Inv", 
    "Test inverse")
  {
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Math/Matrix3/Adj", 
    "Test adjoint")
  {
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Math/Matrix3/OrthoNorm", 
    "Test orthonormalize")
  {
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Math/Matrix3/EigenDecomp", 
    "Test eigen decomposition")
  {
  }
};
#include "tlocMath/tlocMatrix2.h"

namespace TestingMatrix2
{
  struct Matrix2Fixture
  {
    Matrix2Fixture() 
    {
      tloc::Vec2f row1;
      tloc::Vec2f row2;

      tloc::Vec2f col1;
      tloc::Vec2f col2;

      row1[0] = 1; row1[1] = 2;
      row2[0] = 4; row2[1] = 5;

      col1[0] = 1; col1[1] = 2;
      col2[0] = 4; col2[1] = 5;

      a.SetRow(0, row1);
      a.SetRow(1, row2);

      b.SetCol(0, col1);
      b.SetCol(1, col2);
    }

    tloc::Mat2f a, b, c, d, e;
  };

#define CHECK_MATRIX2F(mat,x1,y1,x2,y2) \
  CHECK((mat[0]) == (Approx(x1)) ); CHECK((mat[1]) == (Approx(y1)) ); \
  CHECK((mat[2]) == (Approx(x2)) ); CHECK((mat[3]) == (Approx(y2)) );

  TEST_CASE_METHOD(Matrix2Fixture, "Math/Matrix2/General", 
    "Test general/basic functionality")
  {
    CHECK_MATRIX2F(a, 1, 4, 2, 5);
    CHECK_MATRIX2F(b, 1, 2, 4, 5);

    Mat2f e(a);
    CHECK_MATRIX2F(e, 1, 4, 2, 5);
    Mat2f g(10);
    CHECK_MATRIX2F(g, 10, 10, 10, 10);

    f32 array[4] = {9, 10, 11, 12};
    Mat2f h(array, Mat2f::ROW_MAJOR);
    CHECK_MATRIX2F(h, 9, 11, 10, 12);

    Mat2f i(array, Mat2f::COL_MAJOR);
    CHECK_MATRIX2F(i, 9, 10, 11, 12);

    Mat2f j(1.0f, 2.0f, 3.0f, 4.0f);
    CHECK_MATRIX2F(j, 1, 2, 3, 4);
  }

  TEST_CASE_METHOD(Matrix2Fixture, "Math/Matrix2/Math/Mul",
    "Test multiplication")
  {
    c.Identity();
    d = c;
    c.Mul(d);
    CHECK_MATRIX2F(c, 1, 0, 0, 1);

    c.Zero();
    d.Zero();
    f32 values[4] = {1, 2, 3, 4};
    c.Set(values, Mat2f::ROW_MAJOR);
    d.Set(values, Mat2f::COL_MAJOR);

    e.Mul(c, d);
    CHECK_MATRIX2F(e, 5, 11, 11, 25);

    c.Mul(d);
    CHECK_MATRIX2F(c, 5, 11, 11, 25);

    Vec2f v1(1, 2);
    Vec2f v2;
    c.Set(values, Mat2f::ROW_MAJOR);

    c.Mul(v1, v2);
    CHECK_VEC2F(v2, 5, 11);
  }

  TEST_CASE_METHOD(Matrix2Fixture, "Math/Matrix2/Det", 
    "Test determinant")
  {
    f32 values[4] = {1, 2, 3, 4};
    c.Set(values, Mat2f::ROW_MAJOR);
    CHECK(-2 == Approx(c.Determinant()));
  }

  TEST_CASE_METHOD(Matrix2Fixture, "Math/Matrix2/Inv", 
    "Test inverse")
  {
    f32 values[4] = {1, 2, 3, 4};
    c.Set(values, Mat2f::ROW_MAJOR);
    REQUIRE(c.Inverse() == true);
    CHECK_MATRIX2F(c, -2.0f, 1.5f, 1.0f, -0.5f);
  }

  TEST_CASE_METHOD(Matrix2Fixture, "Math/Matrix2/Adj", 
    "Test adjoint")
  {
    f32 values[4] = {1, 2, 3, 4};
    c.Set(values, Mat2f::ROW_MAJOR);
    d.Adjoint(c);
    CHECK_MATRIX2F(d, 4, -3, -2, 1);

    c.Adjoint();
    CHECK_MATRIX2F(c, 4, -3, -2, 1);
  }

  TEST_CASE_METHOD(Matrix2Fixture, "Math/Matrix2/OrthoNorm", 
    "Test orthonormalize")
  {
    f32 values[4] = {1, 0, 0, 1};
    c.Set(values, Mat2f::COL_MAJOR);
    
    c.Orthonormalize();
    CHECK_MATRIX2F(c, 1, 0, 0, 1);

    f32 values2[4] = {2, 0, 0, 2};
    c.Set(values2, Mat2f::COL_MAJOR);
    
    c.Orthonormalize();
    CHECK_MATRIX2F(c, 1, 0, 0, 1);
  }

  TEST_CASE_METHOD(Matrix2Fixture, "Math/Matrix2/EigenDecomp", 
    "Test eigen decomposition")
  {
    f32 values[4] = {1, 2, 3, 4};
    c.Set(values, Mat2f::ROW_MAJOR);

    c.EigenDecomposition(d, e);
    CHECK_MATRIX2F(d, -0.89442718f, 0.44721359f, -0.44721359, -0.89442718f);
    CHECK_MATRIX2F(e, 0, 0, 0, 5);
  }
};
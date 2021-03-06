#include "tlocTestCommon.h"

#include <tlocMath/types/tlocMatrix2.h>
#include <tlocMath/types/tlocVector2.h>

namespace TestingMatrix2
{
  using namespace tloc;
  using namespace core::data_structs;
  using math::types::Mat2f;
  using math::types::Vec2f;
  using math::types::Mat2f32;
  using math::types::Mat2f64;

  struct Matrix2Fixture
  {
    Matrix2Fixture()
    {
      Vec2f row1;
      Vec2f row2;

      Vec2f col1;
      Vec2f col2;

      row1[0] = 1; row1[1] = 2;
      row2[0] = 4; row2[1] = 5;

      col1[0] = 1; col1[1] = 2;
      col2[0] = 4; col2[1] = 5;

      a.SetRow(0, row1);
      a.SetRow(1, row2);

      b.SetCol(0, col1);
      b.SetCol(1, col2);
    }

    Mat2f a, b, c, d, e;
  };

#define CHECK_MATRIX2F(mat,x1,y1,x2,y2) \
  CHECK((mat[0]) == (Approx(x1)) ); CHECK((mat[1]) == (Approx(y1)) ); \
  CHECK((mat[2]) == (Approx(x2)) ); CHECK((mat[3]) == (Approx(y2)) );

#define CHECK_VEC2F(vec,x,y) CHECK((vec[0]) == (Approx(x)) ); \
                             CHECK((vec[1]) == (Approx(y)) );

  TEST_CASE("Math/Matrix2/Size", "Size my be as below")
  {
    REQUIRE(sizeof(Mat2f) == (sizeof(tl_float) * 4));
    REQUIRE(sizeof(Mat2f32) == (sizeof(f32) * 4));
    REQUIRE(sizeof(Mat2f64) == (sizeof(f64) * 4));
  }

  TEST_CASE_METHOD(Matrix2Fixture, "Math/Matrix2/operators", "")
  {
    c = a * b;
  }

  TEST_CASE_METHOD(Matrix2Fixture, "Math/Matrix2/General",
    "Test general/basic functionality")
  {
    CHECK_MATRIX2F(a, 1, 4, 2, 5);
    CHECK_MATRIX2F(b, 1, 2, 4, 5);

    e = Mat2f(a);
    CHECK_MATRIX2F(e, 1, 4, 2, 5);
    Mat2f g(10);
    CHECK_MATRIX2F(g, 10, 10, 10, 10);

    tl_float array[4] = {9, 10, 11, 12};
    Mat2f h(array, Mat2f::k_RowMajor);
    CHECK_MATRIX2F(h, 9, 11, 10, 12);

    Mat2f i(array, Mat2f::k_ColMajor);
    CHECK_MATRIX2F(i, 9, 10, 11, 12);

    Mat2f j(1.0f, 2.0f, 3.0f, 4.0f);
    CHECK_MATRIX2F(j, 1.0f, 3.0f, 2.0f, 4.0f);

    Mat2f k(2.0f, 2.0f);
    CHECK_MATRIX2F(k, 2.0f, 0, 0, 2.0f);

    Vec2f v1(1, 2), v2(3,4);
    Mat2f m(v1, v2, Mat2f::k_RowMajor);
    CHECK_MATRIX2F(m, 1, 3, 2, 4);

    Mat2f n(v1, v2, Mat2f::k_ColMajor);
    CHECK_MATRIX2F(n, 1, 2, 3, 4);

    Mat2f o(Variadic4f(1, 2, 3, 4), Mat2f::k_ColMajor);
    CHECK_MATRIX2F(o, 1, 2, 3, 4);

    // Convert from Table to Matrix
    c = Mat2f(Table<tl_float, 2, 2>(10.0f));
    CHECK_MATRIX2F(c, 10.0f, 10.0f, 10.0f, 10.0f);
  }

  TEST_CASE_METHOD(Matrix2Fixture, "Math/Matrix2/Math/Mul",
    "Test multiplication")
  {
    c.MakeIdentity();
    d = c;
    c = c.Mul(d);
    CHECK_MATRIX2F(c, 1, 0, 0, 1);

    c.MakeZero();
    d.MakeZero();
    tl_float values[4] = {1, 2, 3, 4};
    c.Set(values, Mat2f::k_RowMajor);
    d.Set(values, Mat2f::k_ColMajor);

    e.Mul(c, d);
    CHECK_MATRIX2F(e, 5, 11, 11, 25);

    c = c.Mul(d);
    CHECK_MATRIX2F(c, 5, 11, 11, 25);

    Vec2f v1(1, 2);
    Vec2f v2;
    c.Set(values, Mat2f::k_RowMajor);

    c.Mul(v1, v2);
    CHECK_VEC2F(v2, 5, 11); //-V550
  }

  TEST_CASE_METHOD(Matrix2Fixture, "Math/Matrix2/Det",
    "Test determinant")
  {
    tl_float values[4] = {1, 2, 3, 4};
    c.Set(values, Mat2f::k_RowMajor);
    CHECK(-2 == Approx(c.Determinant()));
  }

  TEST_CASE_METHOD(Matrix2Fixture, "Math/Matrix2/Inv",
    "Test inverse")
  {
    tl_float values[4] = {1, 2, 3, 4};
    c.Set(values, Mat2f::k_RowMajor);
    c = c.Inverse();
    CHECK_MATRIX2F(c, -2.0f, 1.5f, 1.0f, -0.5f);
  }

  TEST_CASE_METHOD(Matrix2Fixture, "Math/Matrix2/Adj",
    "Test adjoint")
  {
    tl_float values[4] = {1, 2, 3, 4};
    c.Set(values, Mat2f::k_RowMajor);
    d.Adjoint(c);
    CHECK_MATRIX2F(d, 4, -3, -2, 1);

    c = c.Adjoint();
    CHECK_MATRIX2F(c, 4, -3, -2, 1);
  }

  TEST_CASE_METHOD(Matrix2Fixture, "Math/Matrix2/OrthoNorm",
    "Test orthonormalize")
  {
    tl_float values[4] = {1, 0, 0, 1};
    c.Set(values, Mat2f::k_ColMajor);

    c = c.Orthonormalize();
    CHECK_MATRIX2F(c, 1, 0, 0, 1);

    tl_float values2[4] = {2, 0, 0, 2};
    c.Set(values2, Mat2f::k_ColMajor);

    c = c.Orthonormalize();
    CHECK_MATRIX2F(c, 1, 0, 0, 1);
  }

  TEST_CASE_METHOD(Matrix2Fixture, "Math/Matrix2/EigenDecomp",
    "Test eigen decomposition")
  {
    tl_float values[4] = {1, 2, 3, 4};
    c.Set(values, Mat2f::k_RowMajor);

    c.EigenDecomposition(d, e);
    CHECK_MATRIX2F(d, -0.89442718f, 0.44721359f, -0.44721359, -0.89442718f);
    CHECK_MATRIX2F(e, 0, 0, 0, 5);
  }
};
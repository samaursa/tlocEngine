#include "tlocMath/tlocMatrix2.h"

namespace TestingMatrix
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

    tloc::Mat2f a, b, c, d;
  };

#define CHECK_MATRIX2F(mat,x1,y1,x2,y2) \
  CHECK((mat[0]) == (Approx(x1)) ); CHECK((mat[1]) == (Approx(y1)) ); \
  CHECK((mat[2]) == (Approx(x2)) ); CHECK((mat[3]) == (Approx(y2)) );

  TEST_CASE_METHOD(Matrix2Fixture, "Core/DataStructures/Matrix2/General", 
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
  }

  TEST_CASE_METHOD(Matrix2Fixture, "Core/DataStructures/Matrix2/General",
    "Test math operations")
  {
  }
};
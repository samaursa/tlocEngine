namespace TestingMatrix
{
  struct Matrix3Fixture
  {
    Matrix3Fixture() 
    {
      tloc::Vec3f row1;
      tloc::Vec3f row2;
      tloc::Vec3f row3;

      tloc::Vec3f col1;
      tloc::Vec3f col2;
      tloc::Vec3f col3;

      row1[0] = 1; row1[1] = 2; row1[2] = 3;
      row2[0] = 4; row2[1] = 5; row2[2] = 6;
      row3[0] = 7; row3[1] = 8; row3[2] = 9;

      col1[0] = 1; col1[1] = 2; col1[2] = 3;
      col2[0] = 4; col2[1] = 5; col2[2] = 6;
      col3[0] = 7; col3[1] = 8; col3[2] = 9;

      a.SetRow(0, row1);
      a.SetRow(1, row2);
      a.SetRow(2, row3);

      b.SetCol(0, col1);
      b.SetCol(1, col2);
      b.SetCol(2, col3);
    }

    tloc::Mat3f a, b, c, d;
  };

#define CHECK_MATRIX3F(mat,x1,y1,z1,x2,y2,z2,x3,y3,z3) \
  CHECK((mat[0]) == (Approxf(x1)) ); CHECK((mat[1]) == (Approxf(y1)) ); \
  CHECK((mat[2]) == (Approxf(z1)) ); CHECK((mat[3]) == (Approxf(x2)) ); \
  CHECK((mat[4]) == (Approxf(y2)) ); CHECK((mat[5]) == (Approxf(z2)) ); \
  CHECK((mat[6]) == (Approxf(x3)) ); CHECK((mat[7]) == (Approxf(y3)) ); \
  CHECK((mat[8]) == (Approxf(z3)) );

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/General", 
    "Test general/basic functionality")
  {
    tloc::Mat3f e(1);
    CHECK_MATRIX3F(e, 1, 1, 1, 1, 1, 1, 1, 1, 1);

    tloc::Mat3f f(e);
    CHECK_MATRIX3F(f, 1, 1, 1, 1, 1, 1, 1, 1, 1);

    float rawArray[9] = {1,2,3,4,5,6,7,8,9};

    tloc::Mat3f g(rawArray, tloc::Mat3f::ROW_MAJOR);
    CHECK_MATRIX3F(g, 1, 4, 7, 2, 5, 8, 3, 6, 9);

    tloc::Mat3f h(rawArray, tloc::Mat3f::COL_MAJOR);
    CHECK_MATRIX3F(h, 1, 2, 3, 4, 5, 6, 7, 8, 9);
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/Math",
    "Test math operations")
  {
    tloc::Mat3f e(1);

    c = a;
    c.Add(a);
    CHECK_MATRIX3F(c, 2, 8, 14, 4, 10, 16, 6, 12, 18);

    d.Add(a, a);
    CHECK_MATRIX3F(c, 2, 8, 14, 4, 10, 16, 6, 12, 18);

    c.Set(0);
    c(0, 0) = 1;
    c(1, 1) = 1;
    c(2, 2) = 1;

    d = c;
    d.Mul(c);
    CHECK_MATRIX3F(d, 1, 0, 0, 0, 1, 0, 0, 0, 1);

    d.Mul(10);
    CHECK_MATRIX3F(d, 10, 0, 0, 0, 10, 0, 0, 0, 10);
    c.Set(1);
    d.Add(c);
    CHECK_MATRIX3F(d, 11, 1, 1, 1, 11, 1, 1, 1, 11);

    d.Set(11);
    CHECK_MATRIX3F(d, 11, 11, 11, 11, 11, 11, 11, 11, 11);
    d.Div(11);
    CHECK_MATRIX3F(d, 1, 1, 1, 1, 1, 1, 1, 1, 1);

    c.Set(0);
    c(0, 0) = 1;
    c(1, 1) = 1;
    c(2, 2) = 1;

    d = c;
    d.Transpose();
    CHECK_MATRIX3F(d, 1, 0, 0, 0, 1, 0, 0, 0, 1);
    d(0, 2) = 1;
    CHECK_MATRIX3F(d, 1, 0, 0, 0, 1, 0, 1, 0, 1);
    d.Transpose();
    CHECK_MATRIX3F(d, 1, 0, 1, 0, 1, 0, 0, 0, 1);

    Vec3f diagVec;
    d.GetDiagonal(diagVec);
    CHECK_VEC3F(diagVec, 1, 1, 1);

    c.Set(0);
    c(0, 0) = 3;
    c(1, 1) = 4;
    c(2, 2) = 5;

    c.GetDiagonal(diagVec);
    CHECK_VEC3F(diagVec, 3, 4, 5);
  }

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

  TEST_CASE_METHOD(Matrix2Fixture, "Core/DataStructures/Matrix2/General", 
    "Test general/basic functionality")
  {

  }
};
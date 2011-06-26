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

    tloc::Matrix<f32, 3> a, b, c, d, e;
  };

#define CHECK_MATRIX3F(mat,x1,y1,z1,x2,y2,z2,x3,y3,z3) \
  CHECK((mat[0]) == (Approx(x1)) ); CHECK((mat[1]) == (Approx(y1)) ); \
  CHECK((mat[2]) == (Approx(z1)) ); CHECK((mat[3]) == (Approx(x2)) ); \
  CHECK((mat[4]) == (Approx(y2)) ); CHECK((mat[5]) == (Approx(z2)) ); \
  CHECK((mat[6]) == (Approx(x3)) ); CHECK((mat[7]) == (Approx(y3)) ); \
  CHECK((mat[8]) == (Approx(z3)) );

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/General",
    "Test general/basic functionality")
  {
    tloc::Matrix<f32, 3> e(1);
    CHECK_MATRIX3F(e, 1, 1, 1, 1, 1, 1, 1, 1, 1);

    tloc::Matrix<f32, 3> f(e);
    CHECK_MATRIX3F(f, 1, 1, 1, 1, 1, 1, 1, 1, 1);

    f32 rawArray[9] = {1,2,3,4,5,6,7,8,9};

    tloc::Matrix<f32, 3> g(rawArray, tloc::Matrix<f32, 3>::ROW_MAJOR);
    CHECK_MATRIX3F(g, 1, 4, 7, 2, 5, 8, 3, 6, 9);

    tloc::Matrix<f32, 3> h(rawArray, tloc::Matrix<f32, 3>::COL_MAJOR);
    CHECK_MATRIX3F(h, 1, 2, 3, 4, 5, 6, 7, 8, 9);

    c.Zero();
    c.Identity();
    CHECK_MATRIX3F(c, 1, 0, 0, 0, 1, 0, 0, 0, 1);
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/Modifiers",
    "Test modifiers")
  {
    c.Zero();
    f32 numbers[3] = {1,2,3};
    c.MakeDiagonal(numbers);

    CHECK_MATRIX3F(c, 1, 0, 0, 0, 2, 0, 0, 0, 3);
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/Math/Add",
    "Test addition")
  {
    c = a;
    c.Add(a);
    CHECK_MATRIX3F(c, 2, 8, 14, 4, 10, 16, 6, 12, 18);

    d.Add(a, a);
    CHECK_MATRIX3F(c, 2, 8, 14, 4, 10, 16, 6, 12, 18);
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/Math/Sub",
    "Test subtraction")
  {
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/Math/Mul",
    "Test multipliciation")
  {
    //------------------------------------------------------------------------
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

    //------------------------------------------------------------------------
    c.Identity();
    Vec3f someVec(1, 0, 0);
    Vec3f result;
    c.Mul(someVec, result);

    CHECK_VEC3F(result, 1, 0, 0);

    //------------------------------------------------------------------------
    c.Zero(); d.Zero();
    f32 numArray[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    c.Set(numArray, Matrix<f32, 3>::ROW_MAJOR);
    d = c;
    e.Mul(c, d);
    CHECK_MATRIX3F(e, 30, 66, 102, 36, 81, 126, 42, 96, 150);
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/Math/Div",
    "Test division")
  {
    d.Set(11);
    CHECK_MATRIX3F(d, 11, 11, 11, 11, 11, 11, 11, 11, 11);
    d.Div(11);
    CHECK_MATRIX3F(d, 1, 1, 1, 1, 1, 1, 1, 1, 1);
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/Math/Div",
    "Test transpose")
  {
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
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/Accessors",
    "Test accessors")
  {
    f32 diagArray[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    d.Set(diagArray, Matrix<f32, 3>::COL_MAJOR);

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

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/Operators",
    "Test operator functions")
  {
    CHECK( (a == b) == false);
    CHECK( (a == b) != true);

    a = b;
    CHECK( (a == b) == true);
    CHECK( (a == b) != false);

    a[0] += 0.0000001f;
    CHECK( (a == b) == true);
  }
};
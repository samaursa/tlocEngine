#include "tlocTestCommon.h"

#include <tlocMath/types/tlocMatrix.h>
#include <tlocMath/types/tlocMatrix.inl.h>

#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocVector3.inl.h>

namespace TestingMatrix
{
  using namespace tloc;
  using namespace core::data_structs;
  using namespace math::types;

#define CHECK_MATRIX3F(mat,x1,y1,z1,x2,y2,z2,x3,y3,z3) \
  CHECK((mat[0]) == (Approx(x1)) ); CHECK((mat[1]) == (Approx(y1)) ); \
  CHECK((mat[2]) == (Approx(z1)) ); CHECK((mat[3]) == (Approx(x2)) ); \
  CHECK((mat[4]) == (Approx(y2)) ); CHECK((mat[5]) == (Approx(z2)) ); \
  CHECK((mat[6]) == (Approx(x3)) ); CHECK((mat[7]) == (Approx(y3)) ); \
  CHECK((mat[8]) == (Approx(z3)) );

#define CHECK_VEC3F(vec,x,y,z) CHECK((vec[0]) == (Approx(x)) ); \
                               CHECK((vec[1]) == (Approx(y)) ); \
                               CHECK((vec[2]) == (Approx(z)) );

#define CHECK_MATRIX4F(mat,x1,y1,z1,w1,x2,y2,z2,w2,x3,y3,z3,w3,x4,y4,z4,w4) \
  CHECK((mat[0]) == Approx(x1)); CHECK((mat[1]) == Approx(y1));\
  CHECK((mat[2]) == Approx(z1)); CHECK((mat[3]) == Approx(w1));\
\
  CHECK((mat[4]) == Approx(x2)); CHECK((mat[5]) == Approx(y2));\
  CHECK((mat[6]) == Approx(z2)); CHECK((mat[7]) == Approx(w2));\
\
  CHECK((mat[8]) == Approx(x3)); CHECK((mat[9]) == Approx(y3));\
  CHECK((mat[10]) == Approx(z3)); CHECK((mat[11]) == Approx(w3));\
\
  CHECK((mat[12]) == Approx(x4)); CHECK((mat[13]) == Approx(y4));\
  CHECK((mat[14]) == Approx(z4)); CHECK((mat[15]) == Approx(w4))


#define CHECK_VEC4F(vec,x,y,z,w)  CHECK((vec[0]) == (Approx(x)) ); \
                                  CHECK((vec[1]) == (Approx(y)) ); \
                                  CHECK((vec[2]) == (Approx(z)) ); \
                                  CHECK((vec[3]) == (Approx(w)) );

  struct Matrix3Fixture
  {
    Matrix3Fixture()
    {
      Vec3f row1;
      Vec3f row2;
      Vec3f row3;

      Vec3f col1;
      Vec3f col2;
      Vec3f col3;

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

    Matrix<tl_float, 3> a, b, c, d, e;
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
    Matrix<tl_float, 3> e(1);
    CHECK_MATRIX3F(e, 1, 1, 1, 1, 1, 1, 1, 1, 1);

    Matrix<tl_float, 3> f(e);
    CHECK_MATRIX3F(f, 1, 1, 1, 1, 1, 1, 1, 1, 1);

    tl_float rawArray[9] = {1,2,3,4,5,6,7,8,9};

    Matrix<tl_float, 3> g(rawArray, Matrix<tl_float, 3>::k_RowMajor);
    CHECK_MATRIX3F(g, 1, 4, 7, 2, 5, 8, 3, 6, 9);

    Matrix<tl_float, 3> h(rawArray, Matrix<tl_float, 3>::k_ColMajor);
    CHECK_MATRIX3F(h, 1, 2, 3, 4, 5, 6, 7, 8, 9);

    c.MakeZero();
    c.MakeIdentity();
    CHECK_MATRIX3F(c, 1, 0, 0, 0, 1, 0, 0, 0, 1);

    Matrix<tl_float, 3> i(Variadic9f(rawArray),
                          Matrix<tl_float, 3>::k_ColMajor);
    CHECK_MATRIX3F(i, 1, 2, 3, 4, 5, 6, 7, 8, 9);
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/Modifiers",
    "Test modifiers")
  {
    c.MakeZero();
    tl_float numbers[3] = {1,2,3};
    c.MakeDiagonal(numbers);
    CHECK_MATRIX3F(c, 1, 0, 0, 0, 2, 0, 0, 0, 3);

    c.MakeDiagonal(Vector3<tl_float>(5, 6, 7));;
    CHECK_MATRIX3F(c, 5, 0, 0, 0, 6, 0, 0, 0, 7);
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/Math/Add",
    "Test addition")
  {
    c = a;
    c = c.Add(a);
    CHECK_MATRIX3F(c, 2, 8, 14, 4, 10, 16, 6, 12, 18);

    d.Add(a, a);
    CHECK_MATRIX3F(c, 2, 8, 14, 4, 10, 16, 6, 12, 18);
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/Math/AddOperator",
    "Test addition operator")
  {
    c = a;
    c += a;
    CHECK_MATRIX3F(c, 2, 8, 14, 4, 10, 16, 6, 12, 18);

    d = a + a;
    CHECK_MATRIX3F(d, 2, 8, 14, 4, 10, 16, 6, 12, 18);
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/Math/Sub",
    "Test subtraction")
  {
    a = a.Sub(b);
    CHECK_MATRIX3F(a, 0, 2, 4, -2, 0, 2, -4, -2, 0);

    d.Sub(b, a);
    CHECK_MATRIX3F(d, 1, 0, -1, 6, 5, 4, 11, 10, 9);
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/Math/SubOperator",
    "Test subtraction operator")
  {
    a -= (b);
    CHECK_MATRIX3F(a, 0, 2, 4, -2, 0, 2, -4, -2, 0);

    d = b - a;
    CHECK_MATRIX3F(d, 1, 0, -1, 6, 5, 4, 11, 10, 9);
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
    d = d.Mul(c);
    CHECK_MATRIX3F(d, 1, 0, 0, 0, 1, 0, 0, 0, 1);

    d = d.Mul(10);
    CHECK_MATRIX3F(d, 10, 0, 0, 0, 10, 0, 0, 0, 10);
    c.Set(1);
    d = d.Add(c);
    CHECK_MATRIX3F(d, 11, 1, 1, 1, 11, 1, 1, 1, 11);

    //------------------------------------------------------------------------
    c.MakeIdentity();
    Vec3f someVec(1, 0, 0);
    Vec3f result;
    c.Mul(someVec, result);

    CHECK_VEC3F(result, 1, 0, 0); //-V550

    //------------------------------------------------------------------------
    c.MakeZero(); d.MakeZero();
    tl_float numArray[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    c.Set(numArray, Matrix<tl_float, 3>::k_RowMajor);
    d = c;
    e.Mul(c, d);
    CHECK_MATRIX3F(e, 30, 66, 102, 36, 81, 126, 42, 96, 150);

    Matrix<tl_float, 4> m(1);
    m(0, 0) = 0.43301266f; m(0, 1) = -0.75f;        m(0, 2) = 0.5f;
    m(1, 0) = 0.78914917f; m(1, 1) = 0.047367137f;  m(1, 2) = -0.6123724f;
    m(2, 0) = 0.43559578f; m(2, 1) = 0.65973961f;   m(2, 2) = 0.6123724f;
    m(3, 0) = 0;           m(3, 1) = 0;             m(3, 2) = 0;

    Vector<tl_float, 4> v4(0), v4res;
    v4[2] = -1; v4[3] = 1;

    m.Mul(v4, v4res);

    CHECK_VEC4F(v4res, 0.5f, 1.6123724f, 0.3876276f, 1);

    v4[0] = 4; v4[1] = 3; v4[2] = 2; v4[3] = 1;
    m.Mul(v4, v4res);

    CHECK_VEC4F(v4res, 1.4820507f, 3.0739534f, 5.9463468f, 1);
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/Math/MulOperator",
    "Test multipliciation operator")
  {
    //------------------------------------------------------------------------
    c.Set(0);
    c(0, 0) = 1;
    c(1, 1) = 1;
    c(2, 2) = 1;

    d = c;
    d *= (c);
    CHECK_MATRIX3F(d, 1, 0, 0, 0, 1, 0, 0, 0, 1);

    d = d * 5;
    CHECK_MATRIX3F(d, 5, 0, 0, 0, 5, 0, 0, 0, 5);

    d *= 2;
    CHECK_MATRIX3F(d, 10, 0, 0, 0, 10, 0, 0, 0, 10);
    c.Set(1);
    d += c;
    CHECK_MATRIX3F(d, 11, 1, 1, 1, 11, 1, 1, 1, 11);

    //------------------------------------------------------------------------
    c.MakeIdentity();
    Vec3f someVec(1, 0, 0);
    Vec3f result;
    result = c * someVec;

    CHECK_VEC3F(result, 1, 0, 0); //-V550

    //------------------------------------------------------------------------
    c.MakeZero(); d.MakeZero();
    tl_float numArray[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    c.Set(numArray, Matrix<tl_float, 3>::k_RowMajor);
    d = c;
    e = c * d;
    CHECK_MATRIX3F(e, 30, 66, 102, 36, 81, 126, 42, 96, 150);
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/Math/Div",
    "Test division")
  {
    d.Set(11);
    CHECK_MATRIX3F(d, 11, 11, 11, 11, 11, 11, 11, 11, 11);
    d = d.Div(11);
    CHECK_MATRIX3F(d, 1, 1, 1, 1, 1, 1, 1, 1, 1);
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/Math/DivOperator",
    "Test division operator")
  {
    d.Set(11);
    CHECK_MATRIX3F(d, 11, 11, 11, 11, 11, 11, 11, 11, 11);
    d /= 11;
    CHECK_MATRIX3F(d, 1, 1, 1, 1, 1, 1, 1, 1, 1);

    e.Set(42);
    CHECK_MATRIX3F(e, 42, 42, 42, 42, 42, 42, 42, 42, 42);
    e = e / 2;
    CHECK_MATRIX3F(e, 21, 21, 21, 21, 21, 21, 21, 21, 21);
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/Math/Transpose",
    "Test transpose")
  {
    c.Set(0);
    c(0, 0) = 1;
    c(1, 1) = 1;
    c(2, 2) = 1;

    d = c;
    d = d.Transpose();
    CHECK_MATRIX3F(d, 1, 0, 0, 0, 1, 0, 0, 0, 1);
    d(0, 2) = 1;
    CHECK_MATRIX3F(d, 1, 0, 0, 0, 1, 0, 1, 0, 1);
    d = d.Transpose();
    CHECK_MATRIX3F(d, 1, 0, 1, 0, 1, 0, 0, 0, 1);

    e = d;
    e.Transpose(d);
    CHECK_MATRIX3F(e, 1, 0, 0, 0, 1, 0, 1, 0, 1);
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/Accessors",
    "Test accessors")
  {
    tl_float diagArray[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    d.Set(diagArray, Matrix<tl_float, 3>::k_ColMajor);

    Vec3f diagVec;
    d.GetDiagonal(diagVec);
    CHECK_VEC3F(diagVec, 1, 1, 1); //-V550

    c.Set(0);
    c(0, 0) = 3;
    c(1, 1) = 4;
    c(2, 2) = 5;

    c.GetDiagonal(diagVec);
    CHECK_VEC3F(diagVec, 3, 4, 5); //-V550
  }

  TEST_CASE_METHOD(Matrix3Fixture, "Core/DataStructures/Matrix/Operators",
    "Test operator functions")
  {
    CHECK( (a == b) == false);
    CHECK( (a == b) != true);

    a = b;
    CHECK( (a == b) == true);
    CHECK( (a == b) != false);

    a[0] += (Mathf::EPSILON * 0.1f);
    CHECK( (a == b) == true);
  }
};
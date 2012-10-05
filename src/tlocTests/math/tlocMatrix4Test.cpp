#include "tlocTestCommon.h"

#include <tlocMath/matrix/tlocMatrix4.h>
#include <tlocMath/matrix/tlocMatrix4.inl>

namespace TestingMatrix4
{
  USING_TLOC;
  using namespace math;

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

  struct Matrix4Fixture
  {
    Matrix4Fixture()
    {
    }

    Mat4f a, b, c, d, e;
  };

  TEST_CASE_METHOD(Matrix4Fixture, "Math/Matrix4/General",
    "Test general/basic functionality")
  {
    a.Zero();
    Mat4f f(a);
    CHECK_MATRIX4F(f, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    Mat4f g(1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16);
    CHECK_MATRIX4F(g, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16);

    Mat4f h(4, 5, 6, 7);
    CHECK_MATRIX4F(h, 4, 0, 0, 0, 0, 5, 0, 0, 0, 0, 6, 0, 0, 0, 0, 7);

    Mat4f i(90);
    CHECK_MATRIX4F(i, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90);

    Vec4f v1(1, 2, 3, 4), v2(5, 6, 7, 8), v3(9, 10, 11, 12), v4(13, 14, 15, 16);
    Mat4f j(v1, v2, v3, v4, Mat4f::k_RowMajor);
    CHECK_MATRIX4F(j, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16);

    Mat4f k(v1, v2, v3, v4, Mat4f::k_ColMajor);
    CHECK_MATRIX4F(k, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

    tl_float values[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    Mat4f m(values, Mat4f::k_RowMajor);
    CHECK_MATRIX4F(m, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16);

    Mat4f n(values, Mat4f::k_ColMajor);
    CHECK_MATRIX4F(n, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

    Mat4f o(core::Variadic16f(values), Mat4f::k_ColMajor);
    CHECK_MATRIX4F(o, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  }
};
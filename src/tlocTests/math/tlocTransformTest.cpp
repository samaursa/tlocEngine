#include "tlocTestCommon.h"

#include <tlocMath/component_system/tlocTransform.h>

namespace TestingTransform
{
  using namespace tloc;
  using namespace math::types;

#define CHECK_VEC3F(vec,x,y,z) CHECK((vec[0]) == (Approx(x)) ); \
                               CHECK((vec[1]) == (Approx(y)) ); \
                               CHECK((vec[2]) == (Approx(z)) );

#define CHECK_MATRIX3F(mat,x1,y1,z1,x2,y2,z2,x3,y3,z3) \
  CHECK((mat[0]) == (Approx(x1)) ); CHECK((mat[1]) == (Approx(y1)) ); \
  CHECK((mat[2]) == (Approx(z1)) ); CHECK((mat[3]) == (Approx(x2)) ); \
  CHECK((mat[4]) == (Approx(y2)) ); CHECK((mat[5]) == (Approx(z2)) ); \
  CHECK((mat[6]) == (Approx(x3)) ); CHECK((mat[7]) == (Approx(y3)) ); \
  CHECK((mat[8]) == (Approx(z3)) );

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

  TEST_CASE("math/component_system/Transform/", "")
  {
    typedef math::component_system::Transformf32  tf32;
    tf32 t;
    tf32::position_type pos(1, 2, 5);
    t.SetPosition(pos);
    CHECK_VEC3F(t.GetPosition(), 1, 2, 5);

    tf32::orientation_type ori;
    ori.MakeRotationX(90);
    t.SetOrientation(ori);

    CHECK_MATRIX3F(t.GetOrientation(),
                   ori[0], ori[1], ori[2],
                   ori[3], ori[4], ori[5],
                   ori[6], ori[7], ori[8]);

    CHECK_MATRIX4F(t.GetTransformation(),
                   ori[0], ori[1], ori[2], 0,
                   ori[3], ori[4], ori[5], 0,
                   ori[6], ori[7], ori[8], 0,
                   pos[0], pos[1], pos[2], 1);

    Vec4f32 pos4(1, 0, 0, 1);
    Vec4f32 answer;

    t.GetTransformation().Mul(pos4, answer);

    Vec3f32 answerToCheck;
    answerToCheck.ConvertFrom(pos4);

    answerToCheck = t.GetOrientation() * answerToCheck;
    answerToCheck += t.GetPosition();

    bool isEqual = answer.ConvertTo<Vec3f32>() == answerToCheck;
    CHECK( isEqual );

    // Position is 1, 2, 5 with the above +=
    tf32 tInv = t.Invert();
    Mat4f32 tInvTrans = tInv.GetTransformation();
    CHECK_MATRIX4F(tInvTrans,
      1.0f,  0.0f       ,  0.0f       , 0.0f,
      0.0f, -0.44807363f, -0.89399666f, 0.0f,
      0.0f,  0.89399666f, -0.44807363f, 0.0f,
     -1.0f, -3.57384f   ,  4.02836f   , 1.0f);

    t = t.Invert();
    tInvTrans = t.GetTransformation();
    CHECK_MATRIX4F(tInvTrans,
      1.0f,  0.0f       ,  0.0f       , 0.0f,
      0.0f, -0.44807363f, -0.89399666f, 0.0f,
      0.0f,  0.89399666f, -0.44807363f, 0.0f,
     -1.0f, -3.57384f   ,  4.02836f   , 1.0f);

  }
};
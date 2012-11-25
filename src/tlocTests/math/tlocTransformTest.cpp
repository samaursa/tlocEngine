#include "tlocTestCommon.h"

#include <tlocMath/component_system/tlocTransform.h>

namespace TestingTransform
{
  using namespace tloc;
  using namespace math;

#define CHECK_VEC3F(vec,x,y,z) CHECK((vec[0]) == (Approx(x)) ); \
                               CHECK((vec[1]) == (Approx(y)) ); \
                               CHECK((vec[2]) == (Approx(z)) );

#define CHECK_MATRIX3F(mat,x1,y1,z1,x2,y2,z2,x3,y3,z3) \
  CHECK((mat[0]) == (Approx(x1)) ); CHECK((mat[1]) == (Approx(y1)) ); \
  CHECK((mat[2]) == (Approx(z1)) ); CHECK((mat[3]) == (Approx(x2)) ); \
  CHECK((mat[4]) == (Approx(y2)) ); CHECK((mat[5]) == (Approx(z2)) ); \
  CHECK((mat[6]) == (Approx(x3)) ); CHECK((mat[7]) == (Approx(y3)) ); \
  CHECK((mat[8]) == (Approx(z3)) );

  TEST_CASE("math/component_system/Transform/", "")
  {
    typedef component_system::Transformf32  tf32;
    tf32 t;
    t.SetPosition(tf32::position_type(1, 2, 5));
    CHECK_VEC3F(t.GetPosition(), 1, 2, 5);

    tf32::orientation_type ori;
    ori.MakeRotationX(90);
    t.SetOrientation(ori);

    tf32::orientation_type oriRet = t.GetOrientation();
    CHECK_MATRIX3F(t.GetOrientation(),
                   ori[0], ori[1], ori[2],
                   ori[3], ori[4], ori[5],
                   ori[6], ori[7], ori[8]);
  }
};
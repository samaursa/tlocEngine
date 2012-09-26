#include "tlocTestCommon.h"

#include <tlocMath/tlocMath.h>
#include <tlocMath/tlocAngle.h>

namespace TestingAngle
{
  using namespace tloc;
  TEST_CASE("Math/Angle/Radian", "")
  {
    tl_float initAngle = 0.1f;

    math::Radian r(initAngle);
    CHECK(r.GetAs<math::Radian>() == Approx(initAngle));
    CHECK(r.GetAs<math::Degree>() == Approx(Mathf::RAD_TO_DEG * initAngle));
    CHECK(r.GetAsDegree() == Approx(Mathf::RAD_TO_DEG * initAngle));

    math::Degree d(r);
    CHECK(d.GetAs<math::Degree>() == Approx(Mathf::RAD_TO_DEG * initAngle));
    CHECK(d.GetAs<math::Radian>() == Approx(initAngle));
    CHECK(d.GetAsRadian() == Approx(initAngle));
  }
};
#include "tlocTestCommon.h"

#include <tlocMath/tlocMath.h>
#include <tlocMath/angle/tlocAngle.h>

namespace TestingAngle
{
  using namespace tloc;
  TEST_CASE("Math/Angle/DegreeAndRadian", "")
  {
    tl_float initAngle = 0.1f;

    math::Radian angle(initAngle);
    CHECK(angle.GetAs<math::Radian>() == Approx(initAngle));
    CHECK(angle.GetAs<math::Degree>() == Approx(Mathf::RAD_TO_DEG * initAngle));
    CHECK(angle.GetAsDegree() == Approx(Mathf::RAD_TO_DEG * initAngle));

    math::Degree d(angle);
    CHECK(d.GetAs<math::Degree>() == Approx(Mathf::RAD_TO_DEG * initAngle));
    CHECK(d.GetAs<math::Radian>() == Approx(initAngle));
    CHECK(d.GetAsRadian() == Approx(initAngle));

    CHECK((angle == d) == true);
    CHECK((angle == angle) == true);
    CHECK((angle <= d) == true);
    CHECK((angle >= d) == true);
    CHECK((angle > d) == false);
    CHECK((angle < d) == false);

    math::Degree dd(math::Radian(initAngle * 2));
    CHECK(dd.Get() == Approx(Mathf::RAD_TO_DEG * initAngle * 2));
    CHECK((angle == dd) == false);
    CHECK((angle <= dd) == true);
    CHECK((angle >= dd) == false);
    CHECK((angle > dd) == false);
    CHECK((angle < dd) == true);

    CHECK(angle.GetAsDegree() == Approx(d.Get()) );
    CHECK(angle.GetAsDegree() != Approx(dd.Get()) );
    CHECK(d.GetAsRadian() == Approx(angle.Get()) );
    CHECK(d.GetAsRadian() != Approx(dd.GetAs<math::Radian>()) );

    // This should not throw a warning
    math::Degree(6.0f);

    math::Radian r1(1.0f);
    r1 = angle; // should not result in an ambiguous call
    CHECK(r1 == angle);

    math::Degree d1(10.0f);
    d1 = d; // should not result in an ambiguous call
    CHECK(d1 == d);
  }
};
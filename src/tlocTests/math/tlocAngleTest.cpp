#include "tlocTestCommon.h"

#include <tlocMath/tlocMath.h>
#include <tlocMath/angle/tlocAngle.h>

namespace TestingAngle
{
  using namespace tloc;
  TEST_CASE("Math/Angle/DegreeAndRadian", "")
  {
    tl_float initAngle = 0.1f;

    math::Radian r(initAngle);
    CHECK(r.GetAngleAs<math::Radian>() == Approx(initAngle));
    CHECK(r.GetAngleAs<math::Degree>() == Approx(Mathf::RAD_TO_DEG * initAngle));
    CHECK(r.GetAsDegree() == Approx(Mathf::RAD_TO_DEG * initAngle));

    math::Degree d(r);
    CHECK(d.GetAngleAs<math::Degree>() == Approx(Mathf::RAD_TO_DEG * initAngle));
    CHECK(d.GetAngleAs<math::Radian>() == Approx(initAngle));
    CHECK(d.GetAsRadian() == Approx(initAngle));

    CHECK((r == d) == true);
    CHECK((r == r) == true);
    CHECK((r <= d) == true);
    CHECK((r >= d) == true);
    CHECK((r > d) == false);
    CHECK((r < d) == false);

    math::Degree dd(math::Radian(initAngle * 2));
    CHECK(dd.GetAngle() == Approx(Mathf::RAD_TO_DEG * initAngle * 2));
    CHECK((r == dd) == false);
    CHECK((r <= dd) == true);
    CHECK((r >= dd) == false);
    CHECK((r > dd) == false);
    CHECK((r < dd) == true);

    CHECK(r.GetAsDegree() == Approx(d.GetAngle()) );
    CHECK(r.GetAsDegree() != Approx(dd.GetAngle()) );
    CHECK(d.GetAsRadian() == Approx(r.GetAngle()) );
    CHECK(d.GetAsRadian() != Approx(dd.GetAngleAs<math::Radian>()) );

    // This should not throw a warning
    math::Degree(6.0f);
  }
};
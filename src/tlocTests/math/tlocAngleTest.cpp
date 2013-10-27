#include "tlocTestCommon.h"

#include <tlocMath/tlocMath.h>
#include <tlocMath/types/tlocAngle.h>

#include <tlocCore/string/tlocString.h>

namespace TestingAngle
{
  using namespace tloc;
  TEST_CASE("Math/Angle/DegreeAndRadian", "")
  {
    using math::types::Radian;
    using math::types::Degree;

    tl_float initAngle = 0.1f;

    Radian angle(initAngle);
    CHECK(angle.GetAs<Radian>() == Approx(initAngle));
    CHECK(angle.GetAs<Degree>() == Approx(Mathf::RAD_TO_DEG * initAngle));
    CHECK(angle.GetAsDegree() == Approx(Mathf::RAD_TO_DEG * initAngle));

    Degree d(angle);
    CHECK(d.GetAs<Degree>() == Approx(Mathf::RAD_TO_DEG * initAngle));
    CHECK(d.GetAs<Radian>() == Approx(initAngle));
    CHECK(d.GetAsRadian() == Approx(initAngle));

    CHECK((angle == d) == true);
    CHECK((angle == angle) == true);
    CHECK((angle <= d) == true);
    CHECK((angle >= d) == true);
    CHECK((angle > d) == false);
    CHECK((angle < d) == false);

    Degree dd(Radian(initAngle * 2));
    CHECK(dd.Get() == Approx(Mathf::RAD_TO_DEG * initAngle * 2));
    CHECK((angle == dd) == false);
    CHECK((angle <= dd) == true);
    CHECK((angle >= dd) == false);
    CHECK((angle > dd) == false);
    CHECK((angle < dd) == true);

    CHECK(angle.GetAsDegree() == Approx(d.Get()) );
    CHECK(angle.GetAsDegree() != Approx(dd.Get()) );
    CHECK(d.GetAsRadian() == Approx(angle.Get()) );
    CHECK(d.GetAsRadian() != Approx(dd.GetAs<Radian>()) );

    // This should not throw a warning
    Degree(6.0f);

    Radian r1(1.0f);
    r1 = angle; // should not result in an ambiguous call
    CHECK(r1 == angle);

    Degree d1(10.0f);
    d1 = d; // should not result in an ambiguous call
    CHECK(d1 == d);
  }
};
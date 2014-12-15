#include "tlocTestCommon.h"

#include <tlocMath/tlocMath.h>
#include <tlocMath/types/tlocAngle.h>

#include <tlocCore/string/tlocString.h>

namespace TestingAngle
{
  using namespace tloc;
  using math_t::Radian;
  using math_t::Degree;
  using math_t::MakeDegree;
  using math_t::MakeRadian;
  TEST_CASE("Math/Angle/DegreeAndRadian", "")
  {
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

  TEST_CASE("Math/Angle/DegreeAndRadian/Make", "")
  {
    const tl_float piDiv2 = Mathf::PI / 2.0f;

    { 
      Degree d = MakeDegree(90.0f);
      CHECK(d.Get() == Approx(90.0f));
    }

    { 
      Degree d = MakeDegree(Radian(piDiv2));
      CHECK(d.Get() == Approx(90.0f));
    }

    { 
      Degree d = MakeDegree(Degree(90.0f));
      CHECK(d.Get() == Approx(90.0f));
    }

    { 
      Radian r = MakeRadian(piDiv2);
      CHECK(r.Get() == Approx(piDiv2));
    }

    { 
      Radian r = MakeDegree(Degree(90.0f));
      CHECK(r.Get() == Approx(piDiv2));
    }

    { 
      Radian r = MakeDegree(Radian(piDiv2));
      CHECK(r.Get() == Approx(piDiv2));
    }
  }
};
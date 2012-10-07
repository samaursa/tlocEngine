#include "tlocTestCommon.h"

#include <tlocMath/tlocMath.h>
#include <tlocMath/utilities/tlocPythagoras.h>

namespace TestingPythagoras
{
  using namespace tloc;
  using namespace math;

  TEST_CASE("Math/Pythagoras/Ctors", "")
  {
    typedef utils::Pythagoras pyth;

    //------------------------------------------------------------------------
    // Triangle side tests

    {
      pyth p(pyth::base(2.0), pyth::hypotenuse(2.5));
      CHECK(p.GetOpposite() == Approx(1.5));
      CHECK(Mathf::Approx(p.GetAngle().GetAngle(), 0.63665f, 0.01f));
      CHECK(Mathf::Approx(p.GetAngleOpposite().GetAngle(),
                          90 - p.GetAngle().GetAngle()) );
    }

    {
      pyth p(pyth::hypotenuse(2.5), pyth::base(2.0));
      CHECK(p.GetOpposite() == Approx(1.5));
      CHECK(Mathf::Approx(p.GetAngle().GetAngle(), 0.63665f, 0.01f));
      CHECK(Mathf::Approx(p.GetAngleOpposite().GetAngle(),
                          90 - p.GetAngle().GetAngle()) );
    }

    {
      pyth p(pyth::opposite(1.5), pyth::base(2.0));
      CHECK(p.GetHypotenuse() == Approx(2.5));
      CHECK(Mathf::Approx(p.GetAngle().GetAngle(), 0.63665f, 0.01f));
      CHECK(Mathf::Approx(p.GetAngleOpposite().GetAngle(),
        90 - p.GetAngle().GetAngle()) );
    }

    {
      pyth p(pyth::base(2.0), pyth::opposite(1.5));
      CHECK(p.GetHypotenuse() == Approx(2.5));
      CHECK(Mathf::Approx(p.GetAngle().GetAngle(), 0.63665f, 0.01f));
      CHECK(Mathf::Approx(p.GetAngleOpposite().GetAngle(),
        90 - p.GetAngle().GetAngle()) );
    }

    {
      pyth p(pyth::opposite(1.5), pyth::hypotenuse(2.5));
      CHECK(p.GetBase() == Approx(2.0));
      CHECK(Mathf::Approx(p.GetAngle().GetAngle(), 0.63665f, 0.01f));
      CHECK(Mathf::Approx(p.GetAngleOpposite().GetAngle(),
        90 - p.GetAngle().GetAngle()) );
    }

    {
      pyth p(pyth::hypotenuse(2.5), pyth::opposite(1.5));
      CHECK(p.GetBase() == Approx(2.0));
      CHECK(Mathf::Approx(p.GetAngle().GetAngle(), 0.63665f, 0.01f));
      CHECK(Mathf::Approx(p.GetAngleOpposite().GetAngle(),
        90 - p.GetAngle().GetAngle()) );
    }

    //------------------------------------------------------------------------
    // Angle tests

    {
      tl_float angle = Mathf::ATan(1.5f / 2.0f);
      pyth p(math::Degree( angle ), pyth::base(2.0));
      CHECK(p.GetOpposite() == Approx(1.5));
      CHECK(p.GetHypotenuse() == Approx(2.5));
      CHECK(Mathf::Approx(p.GetAngleOpposite().GetAngle(),
                          90 - p.GetAngle().GetAngle()) );
    }

    {
      tl_float angle = Mathf::ASin(1.5f / 2.5f);
      pyth p(math::Degree( angle ), pyth::opposite(1.5));
      CHECK(p.GetBase() == Approx(2.0));
      CHECK(p.GetHypotenuse() == Approx(2.5));
      CHECK(Mathf::Approx(p.GetAngleOpposite().GetAngle(),
                          90 - p.GetAngle().GetAngle()) );
    }

    {
      tl_float angle = Mathf::ACos(2.0f / 2.5f);
      pyth p(math::Degree( angle ), pyth::base(2.0));
      CHECK(p.GetOpposite() == Approx(1.5));
      CHECK(p.GetHypotenuse() == Approx(2.5));
      CHECK(Mathf::Approx(p.GetAngleOpposite().GetAngle(),
                          90 - p.GetAngle().GetAngle()) );
    }

    {
      tl_float angle = Mathf::ACos(2.0f / 2.5f);
      pyth p(math::Degree( angle ), pyth::hypotenuse(2.5));
      CHECK(p.GetBase() == Approx(2.0));
      CHECK(p.GetOpposite() == Approx(1.5));
      CHECK(Mathf::Approx(p.GetAngleOpposite().GetAngle(),
                          90 - p.GetAngle().GetAngle()) );
    }
  }
};
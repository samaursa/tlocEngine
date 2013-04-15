#include "tlocTestCommon.h"

#include <tlocMath/tlocMath.h>
#include <tlocMath/tlocMath.inl>
#include <tlocMath/utilities/tlocPythagoras.h>

namespace TestingPythagoras
{
  using namespace tloc;

  TEST_CASE("Math/Pythagoras/Ctors", "")
  {
    typedef math::utils::Pythagoras pyth;
    using math::types::Degree;
    using math::types::Radian;

    //------------------------------------------------------------------------
    // Triangle side tests

    {
      pyth p(pyth::base(2.0), pyth::hypotenuse(2.5));
      CHECK(p.GetSide<pyth::opposite>() == Approx(1.5));
      CHECK(Mathf::Approx(p.GetAngle().Get(), 36.869896f, 0.01f));
      CHECK(Mathf::Approx(p.GetAngleOpposite().Get(),
                          90 - p.GetAngle().Get()) );
    }

    {
      pyth p(pyth::hypotenuse(2.5), pyth::base(2.0));
      CHECK(p.GetSide<pyth::opposite>() == Approx(1.5));
      CHECK(Mathf::Approx(p.GetAngle().Get(), 36.869896f, 0.01f));
      CHECK(Mathf::Approx(p.GetAngleOpposite().Get(),
                          90 - p.GetAngle().Get()) );
    }

    {
      pyth p(pyth::opposite(1.5), pyth::base(2.0));
      CHECK(p.GetSide<pyth::hypotenuse>() == Approx(2.5));
      CHECK(Mathf::Approx(p.GetAngle().Get(), 36.869896f, 0.01f));
      CHECK(Mathf::Approx(p.GetAngleOpposite().Get(), 90 - p.GetAngle().Get()) );
    }

    {
      pyth p(pyth::base(2.0), pyth::opposite(1.5));
      CHECK(p.GetSide<pyth::hypotenuse>() == Approx(2.5));
      CHECK(Mathf::Approx(p.GetAngle().Get(), 36.869896f, 0.01f));
      CHECK(Mathf::Approx(p.GetAngleOpposite().Get(), 90 - p.GetAngle().Get()) );
    }

    {
      pyth p(pyth::opposite(1.5), pyth::hypotenuse(2.5));
      CHECK(p.GetSide<pyth::base>() == Approx(2.0));
      CHECK(Mathf::Approx(p.GetAngle().Get(), 36.869896f, 0.01f));
      CHECK(Mathf::Approx(p.GetAngleOpposite().Get(), 90 - p.GetAngle().Get()) );
    }

    {
      pyth p(pyth::hypotenuse(2.5), pyth::opposite(1.5));
      CHECK(p.GetSide<pyth::base>() == Approx(2.0));
      CHECK(Mathf::Approx(p.GetAngle().Get(), 36.869896f, 0.01f));
      CHECK(Mathf::Approx(p.GetAngleOpposite().Get(), 90 - p.GetAngle().Get()) );
    }

    //------------------------------------------------------------------------
    // Angle tests

    {
      tl_float angle = Mathf::ATan(1.5f / 2.0f);
      pyth p(Degree(Radian(angle) ), pyth::base(2.0));
      CHECK(p.GetSide<pyth::opposite>() == Approx(1.5));
      CHECK(p.GetSide<pyth::hypotenuse>() == Approx(2.5));
      CHECK(p.GetAngle().GetAs<Degree>() == Approx(36.8698f));
      CHECK(Mathf::Approx(p.GetAngleOpposite().Get(), 90 - p.GetAngle().Get()) );
    }

    {
      tl_float angle = Mathf::ASin(1.5f / 2.5f);
      pyth p(Degree(Radian(angle) ), pyth::opposite(1.5));
      CHECK(p.GetSide<pyth::base>() == Approx(2.0));
      CHECK(p.GetSide<pyth::hypotenuse>() == Approx(2.5));
      CHECK(Mathf::Approx(p.GetAngleOpposite().Get(), 90 - p.GetAngle().Get()) );
    }

    {
      tl_float angle = Mathf::ACos(2.0f / 2.5f);
      pyth p(Degree(Radian(angle) ), pyth::base(2.0));
      CHECK(p.GetSide<pyth::opposite>() == Approx(1.5));
      CHECK(p.GetSide<pyth::hypotenuse>() == Approx(2.5));
      CHECK(Mathf::Approx(p.GetAngleOpposite().Get(), 90 - p.GetAngle().Get()) );
    }

    {
      tl_float angle = Mathf::ACos(2.0f / 2.5f);
      pyth p(Degree(Radian(angle) ), pyth::hypotenuse(2.5));
      CHECK(p.GetSide<pyth::base>() == Approx(2.0));
      CHECK(p.GetSide<pyth::opposite>() == Approx(1.5));
      CHECK(Mathf::Approx(p.GetAngleOpposite().Get(), 90 - p.GetAngle().Get()) );
    }

    {
      tl_float angle = Mathf::ACos(2.0f / 2.5f);
      pyth p(Radian( angle ), pyth::hypotenuse(2.5));
      CHECK(p.GetSide<pyth::base>() == Approx(2.0));
      CHECK(p.GetSide<pyth::opposite>() == Approx(1.5));
      CHECK(Mathf::Approx(p.GetAngleOpposite().Get(), 90 - p.GetAngle().Get()) );
    }
  }
};
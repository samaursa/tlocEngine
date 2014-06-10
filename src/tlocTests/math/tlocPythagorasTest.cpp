#include "tlocTestCommon.h"

#include <tlocMath/tlocMath.h>
#include <tlocMath/tlocMath.inl.h>
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
      CHECK(math::Approx(p.GetAngle().Get(), 36.869896f, 0.01f));
      CHECK(math::IsEqual(p.GetAngleOpposite().Get(), 90 - p.GetAngle().Get()) );
    }

    {
      pyth p(pyth::hypotenuse(2.5), pyth::base(2.0));
      CHECK(p.GetSide<pyth::opposite>() == Approx(1.5));
      CHECK(math::Approx(p.GetAngle().Get(), 36.869896f, 0.01f));
      CHECK(math::IsEqual(p.GetAngleOpposite().Get(), 90 - p.GetAngle().Get()) );
    }

    {
      pyth p(pyth::opposite(1.5), pyth::base(2.0));
      CHECK(p.GetSide<pyth::hypotenuse>() == Approx(2.5));
      CHECK(math::Approx(p.GetAngle().Get(), 36.869896f, 0.01f));
      CHECK(math::IsEqual(p.GetAngleOpposite().Get(), 90 - p.GetAngle().Get()) );
    }

    {
      pyth p(pyth::base(2.0), pyth::opposite(1.5));
      CHECK(p.GetSide<pyth::hypotenuse>() == Approx(2.5));
      CHECK(math::Approx(p.GetAngle().Get(), 36.869896f, 0.01f));
      CHECK(math::IsEqual(p.GetAngleOpposite().Get(), 90 - p.GetAngle().Get()) );
    }

    {
      pyth p(pyth::opposite(1.5), pyth::hypotenuse(2.5));
      CHECK(p.GetSide<pyth::base>() == Approx(2.0));
      CHECK(math::Approx(p.GetAngle().Get(), 36.869896f, 0.01f));
      CHECK(math::IsEqual(p.GetAngleOpposite().Get(), 90 - p.GetAngle().Get()) );
    }

    {
      pyth p(pyth::hypotenuse(2.5), pyth::opposite(1.5));
      CHECK(p.GetSide<pyth::base>() == Approx(2.0));
      CHECK(math::Approx(p.GetAngle().Get(), 36.869896f, 0.01f));
      CHECK(math::IsEqual(p.GetAngleOpposite().Get(), 90 - p.GetAngle().Get()) );
    }

    //------------------------------------------------------------------------
    // Angle tests

    {
      tl_float angle = math::ATan(1.5f / 2.0f).Get();
      pyth p(Degree(Radian(angle) ), pyth::base(2.0));
      CHECK(p.GetSide<pyth::opposite>() == Approx(1.5));
      CHECK(p.GetSide<pyth::hypotenuse>() == Approx(2.5));
      CHECK(p.GetAngle().GetAs<Degree>() == Approx(36.8698f));
      CHECK(math::IsEqual(p.GetAngleOpposite().Get(), 90 - p.GetAngle().Get()) );
    }

    {
      tl_float angle = math::ASin(1.5f / 2.5f).Get();
      pyth p(Degree(Radian(angle) ), pyth::opposite(1.5));
      CHECK(p.GetSide<pyth::base>() == Approx(2.0));
      CHECK(p.GetSide<pyth::hypotenuse>() == Approx(2.5));
      CHECK(math::IsEqual(p.GetAngleOpposite().Get(), 90 - p.GetAngle().Get()) );
    }

    {
      tl_float angle = math::ACos(2.0f / 2.5f).Get();
      pyth p(Degree(Radian(angle) ), pyth::base(2.0));
      CHECK(p.GetSide<pyth::opposite>() == Approx(1.5));
      CHECK(p.GetSide<pyth::hypotenuse>() == Approx(2.5));
      CHECK(math::IsEqual(p.GetAngleOpposite().Get(), 90 - p.GetAngle().Get()) );
    }

    {
      tl_float angle = math::ACos(2.0f / 2.5f).Get();
      pyth p(Degree(Radian(angle) ), pyth::hypotenuse(2.5));
      CHECK(p.GetSide<pyth::base>() == Approx(2.0));
      CHECK(p.GetSide<pyth::opposite>() == Approx(1.5));
      CHECK(math::IsEqual(p.GetAngleOpposite().Get(), 90 - p.GetAngle().Get()) );
    }

    {
      tl_float angle = math::ACos(2.0f / 2.5f).Get();
      pyth p(Radian( angle ), pyth::hypotenuse(2.5));
      CHECK(p.GetSide<pyth::base>() == Approx(2.0));
      CHECK(p.GetSide<pyth::opposite>() == Approx(1.5));
      CHECK(math::IsEqual(p.GetAngleOpposite().Get(), 90 - p.GetAngle().Get()) );
    }
  }
};
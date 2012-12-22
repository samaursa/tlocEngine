#include "tlocTestCommon.h"

#include <tlocMath/angle/tlocAngle.h>
#include <tlocGraphics/data_types/tlocFOV.h>

namespace TestingFOV
{
  using namespace tloc;
  using namespace tloc::graphics;

  TEST_CASE("graphics/types/FOV", "")
  {
    using namespace graphics::types;
    AspectRatio ar(AspectRatio::width(1920), AspectRatio::height(1080));

    { // horizontal to vertical
      FOV f(math::Degree(90.0f), ar, p_FOV::horizontal() );
      CHECK(f.Get<p_FOV::horizontal>().GetAs<math::Degree>() == Approx(90.0f));
      CHECK(f.Get<p_FOV::vertical>().GetAs<math::Degree>() == Approx(58.715f));
    }

    { // vertical to horizontal
      FOV f(math::Degree(36.0f), ar, p_FOV::vertical() );
      CHECK(f.Get<p_FOV::vertical>().GetAs<math::Degree>() == Approx(36.0f));
      CHECK(f.Get<p_FOV::horizontal>().GetAs<math::Degree>() == Approx(60.024f));
    }

    {
      using namespace math::utils;
      typedef types::AspectRatio ar_type;

      Pythagoras pyth(Pythagoras::base(5), Pythagoras::opposite(5));
      FOV f(pyth,
            ar_type(ar_type::width(10), ar_type::height(10)),
            p_FOV::horizontal() );

      CHECK(f.Get<p_FOV::horizontal>().GetAs<math::Degree>() ==
            Approx(pyth.GetAngle().Get() ) );
      CHECK(f.Get<p_FOV::vertical>().GetAs<math::Degree>() ==
            Approx(pyth.GetAngle().Get() ) );
    }
  }
};
#include "tlocTestCommon.h"

#include <tlocMath/tlocMath.h>
#include <tlocMath/utilities/tlocScale.h>

namespace TestingScale
{
  using namespace tloc;

  template <typename T_RealType, typename T>
  void ScaleFloat()
  {
    typedef math_utils::Scale_T<T_RealType, T> scale_float_to_other;
    typedef math_utils::Scale_T<T, T_RealType> scale_other_to_float;

    {
      scale_float_to_other s
        (math::Range0to1<T_RealType, math::p_range::Inclusive>().Get(),
         math::Range_T<T>(0, 101));
      CHECK(s.ScaleUp(0.5f) == 50);
      CHECK(s.ScaleDown(50) == Approx(0.5f));
    }

    {
      scale_float_to_other s
        (math::Range0to1<T_RealType, math::p_range::Inclusive>().Get(),
         math::Range_T<T>(50, 101));
      CHECK(s.ScaleUp(0.5f) == 75);
      CHECK(s.ScaleDown(50) == Approx(0.0f));
      CHECK(s.ScaleDown(75) == Approx(0.5f));
    }

    {
      scale_other_to_float s(math::Range_T<T>(0, 21),
                             math::Range_T<T_RealType>(0,51));
      CHECK(s.ScaleDown(0.5f) == 0);
      CHECK(s.ScaleDown(25.0f) == 10);
      CHECK(s.ScaleUp(19) == Approx(47.5));
    }

    {
      scale_other_to_float s(math::Range_T<T>(50, 101),
                             math::Range_T<T_RealType>(70,121));
      CHECK(s.ScaleDown(70.0f) == 50);
      CHECK(s.ScaleDown(119.0f) == 99);
      CHECK(s.ScaleUp(50) == Approx(70.0f));
      CHECK(s.ScaleUp(75) == Approx(95.0f));
    }

    {
      scale_float_to_other s
        (math::RangeNeg1to1<T_RealType, math::p_range::Inclusive>().Get(),
         math::Range_T<T>(0, 101));
      CHECK(s.ScaleUp(-1.0f) == 0);
      CHECK(s.ScaleUp(0.0f) == 50);
      CHECK(s.ScaleUp(1.0f) == 100);

      CHECK(s.ScaleDown(0) == Approx(-1.0f));
      CHECK(s.ScaleDown(50) == Approx(0.0f));
      CHECK(s.ScaleDown(99) == Approx(0.98f));
    }

  }

  TEST_CASE("math/utilities/Scale", "")
  {
    ScaleFloat<f32, s8>();
    ScaleFloat<f32, s16>();
    ScaleFloat<f32, s32>();
    ScaleFloat<f32, s64>();
    ScaleFloat<f32, u8>();
    ScaleFloat<f32, u16>();
    ScaleFloat<f32, u32>();
    ScaleFloat<f32, u64>();

  }

  TEST_CASE("math/utilities/Scale/same type", "")
  {
    typedef math_utils::Scale_T<tl_float, tl_float> scale_float_to_float;

    scale_float_to_float s
      (math::RangeNeg1to1<tl_float, math::p_range::Inclusive>().Get(),
       math::Range_T<tl_float>(0.0f, 101.0f));
    CHECK(s.ScaleUp(-1.0f) == Approx(0.0f));
    CHECK(s.ScaleUp(0.0f) == Approx(50.0f));
    CHECK(s.ScaleUp(1.0f) == Approx(100.0f));

    CHECK(s.ScaleDown(0.0f) == Approx(-1.0f));
    CHECK(s.ScaleDown(50.0f) == Approx(0.0f));
    CHECK(s.ScaleDown(99.0f) == Approx(0.98f));
  }
};

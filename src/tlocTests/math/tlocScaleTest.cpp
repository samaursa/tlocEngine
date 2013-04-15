#include "tlocTestCommon.h"

#include <tlocMath/tlocMath.h>
#include <tlocMath/utilities/tlocScale.h>

namespace TestingScale
{
  using namespace tloc;

  template <typename T_RealType, typename T>
  void ScaleFloat()
  {
    typedef math_utils::Scale_T<T_RealType, T> scale_type;

    {
      scale_type s(core::Range_T<T_RealType>(0,1), core::Range_T<T>(0, 100));
      CHECK(s.ScaleUp(0.5f) == 50);
      CHECK(s.ScaleDown(50) == Approx(0.5f));
    }

    {
      scale_type s(core::Range_T<T_RealType>(0,1), core::Range_T<T>(50, 100));
      CHECK(s.ScaleUp(0.5f) == 75);
      CHECK(s.ScaleDown(50) == Approx(0.0f));
      CHECK(s.ScaleDown(75) == Approx(0.5f));
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
};

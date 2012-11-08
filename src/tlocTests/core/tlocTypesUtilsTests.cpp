#include "tlocTestCommon.h"

#include <tlocCore/utilities/tlocType.h>

namespace TestingTypeUtils
{
  using namespace tloc;
  using namespace core;

  TEST_CASE("core/utilities/type/CastTo32", "")
  {
    CHECK( (utils::CastTo32<s32, s64>(60) == 60) );
    CHECK( (utils::CastTo32<s32, s32>(60) == 60) );

    CHECK( (utils::CastTo32<f32, f64>(60.0) == Approx(60.0f)) );
    CHECK( (utils::CastTo32<f32, f32>(60.0f) == Approx(60.0f)) );
  }

  TEST_CASE("core/utilities/type/CastNumber", "")
  {
    CHECK( (utils::CastNumber<u32, s32>(60) == 60) );
    CHECK( (utils::CastNumber<s32, u32>(60) == 60) );

    CHECK( (utils::CastNumber<u32, u32>(60) == 60) );
    CHECK( (utils::CastNumber<s32, s32>(60) == 60) );
  }
};
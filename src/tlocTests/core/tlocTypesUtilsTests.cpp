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
    // Uncomment and you SHOULD get assertion failures
//#define CAUSE_PRECISION_FAILURES

    CHECK( (utils::CastNumber<s8, s32>(100) == 100) );
    CHECK( (utils::CastNumber<s8, s32>(-100) == -100) );

    CHECK( (utils::CastNumber<s8, u32>(100) == 100) );

    CHECK( (utils::CastNumber<u8, s32>(100) == 100) );
    CHECK( (utils::CastNumber<u8, s32>(200) == 200) );

    CHECK( (utils::CastNumber<u8, u32>(100) == 100) );
    CHECK( (utils::CastNumber<u8, u32>(200) == 200) );

    CHECK( (utils::CastNumber<s32, s8>(100) == 100) );
    CHECK( (utils::CastNumber<s32, s8>(-100) == -100) );
    CHECK( (utils::CastNumber<s32, u8>(100) == 100) );

    CHECK( (utils::CastNumber<u32, s8>(100) == 100) );
    CHECK( (utils::CastNumber<u32, u8>(100) == 100) );

    CHECK( (utils::CastNumber<u32, s32>(60) == 60) );
    CHECK( (utils::CastNumber<s32, u32>(60) == 60) );

    CHECK( (utils::CastNumber<u32, u32>(60) == 60) );
    CHECK( (utils::CastNumber<s32, s32>(60) == 60) );

    CHECK( (utils::CastNumber<f32, f32>(60.0) == Approx(60.0f)) );
    CHECK( (utils::CastNumber<f32, f64>(60.0) == Approx(60.0f)) );

    CHECK( (utils::CastNumber<f64, f32>(60.0f) == Approx(60.0)) );
    CHECK( (utils::CastNumber<f64, f32>(60.0f) == Approx(60.0)) );

#ifdef CAUSE_PRECISION_FAILURES
    CHECK( (utils::CastNumber<u32, s8>(-100) != 100) );
    CHECK( (utils::CastNumber<u8, u32>(400) != 100) );
    CHECK( (utils::CastNumber<u8, s32>(-100) != -100) );
    CHECK( (utils::CastNumber<s8, u32>(200) != 100) );
    CHECK( (utils::CastNumber<s8, s32>(200) != 100) );
#endif

  }
};